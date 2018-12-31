/*
 * main.c
 *
 *  Created on: 16 déc. 2018
 *      Author: tristan
 */

#include "Token.h"
#include "Stack_token.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>


void printBoard(stackToken** Board, int size_board, stackToken printed_stack, char* localisation){
	token tmp;
	char* color[3];
	color[0]="\033[30;107m";
	color[1]="\033[97;40m";
	color[3]="\033[0m";
	char* printed_color=color[0];
	int alter_width=0;
	int alter_height=0;
	int height;
	int width;
	printf(" ");
	for(width=0;width<size_board;width++){
		printf(" %c",width+97);
	}
	printf("\n");
	for(height=size_board-1;height>=0;height--){
		printf("%i ",height+1);
		for(width=0;width<size_board;width++){
			if(!isEmptyST(Board[width][height])){
				tmp=peekST(Board[width][height]);
				printf("%s%s%s",printed_color,tmp.Name,color[3]);
			}
			else{
				printf("%s  %s",printed_color,color[3]);
			}
			alter_width=1-alter_width;
			printed_color=color[alter_width];
		}
		alter_height=1-alter_height;
		alter_width=alter_height;
		printed_color=color[alter_width];
		if(height+1==printed_stack->summit && height!=0){
			tmp=popST(&printed_stack);
			printf("     %s",tmp.Name);
		}
		else if (printed_stack->summit==1 && height==0){
			tmp=popST(&printed_stack);
			printf(" %s: %s",localisation,tmp.Name);
		}
		else if (isEmptyST(printed_stack) && height==0 && strcmp(localisation,"")){
			printf(" %s: ", localisation);
		}
		printf("\n");
	}
}



int isVictory(stackToken** Board, int size_board){
	int height;
	int width;
	int lisToken;
	int countTokenB=0;
	int countTokenN=0;
	int countFN[2];
	countFN[0]=countFN[1]=0;
	int countFB[2];
	countFB[0]=countFB[1]=0;
	int countTN=0;
	int countTB=0;
	stackToken curST;
	for(width=0;width<size_board;width++){
		for(height=0;height<size_board;height++){
			curST=Board[width][height];
			if(countTokenB<=2 && countTokenN<=2 && !isEmptyST(curST)){
				lisToken=lisST(curST);
				while(lisToken%2==0 && peekST(curST).Name[1]=='B') {
					countTokenB++;
					lisToken/=2;
				}
				while(lisToken%2==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					lisToken/=2;
				}
				while(lisToken%3==0 && peekST(curST).Name[1]=='B'){
					countTokenB++;
					countFB[abs(height%2-width%2)]++;
					lisToken/=3;
				}
				while(lisToken%3==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					countFB[abs(height%2-width%2)]++;
					lisToken/=3;
				}
				while(lisToken%5==0 && peekST(curST).Name[1]=='B'){
					countTokenB++;
					countTB++;
					lisToken/=5;
				}
				while(lisToken%5==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					countTN++;
					lisToken/=5;
				}
				while(lisToken%7==0 && peekST(curST).Name[1]=='B') {
					countTokenB++;
					lisToken/=7;
				}
				while(lisToken%7==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					lisToken/=7;
				}
				while(lisToken%9==0 && peekST(curST).Name[1]=='B') {
					countTokenB++;
					lisToken/=9;
				}
				while(lisToken%9==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					lisToken/=9;
				}
				while(lisToken%11==0 && peekST(curST).Name[1]=='B') {
					countTokenB++;
					lisToken/=11;
				}
				while(lisToken%11==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					lisToken/=11;
				}
				while(lisToken%13==0 && peekST(curST).Name[1]=='B') {
					countTokenB++;
					lisToken/=13;
				}
				while(lisToken%9==0 && peekST(curST).Name[1]=='N'){
					countTokenN++;
					lisToken/=13;
				}
			}
		}
	}
	if(countTokenB==2 && countTokenN==2){
		if((countFB[0] && countFB[1]) || (countFB[0] && countTB) || (countFB[1] && countTB)){
			if((countFB[0] && countFB[1]) || (countFB[0] && countTB) || (countFB[1] && countTB)){
				return 3;
			}
		}
	}
	if (countTokenB==1 && countTokenN==1){
		if((countFB[0] && countFN[1]) || (countFB[1] && countFN[0])){
			return 3;
		}
	}
	if(countTokenN==0) return 1;
	if(countTokenB==0) return 2;
	return 0;
}

int isValidSquare(char square[3],int size_board, char* test){
	int let=(int) square[0];
	char* end;
	char snum[3];
	int num;
	int i=1;
	if(let>=97 && let<97+size_board){
		while(square[i]!='\0'){
			snum[i-1]=square[i];
			i+=1;
		}
		num=strtol(snum, &end, 10);
		if(num >=1 && num<=size_board){
			if(strcmp(square,test)){
			return 1;
			}
			else{
				printf("Erreur: Veuillez entre une case différente de celle de départ.\n");
				return 0;
			}
		}
	}
	printf("Erreur: veuillez entrer une case avec le format suivant:lettre [%c,%c] + numéro [%i,%i]\n",'a','a'+size_board-1,1,size_board);
	return 0;
}

int accessSquare(stackToken ST, int turn){
	token tmp;
	if(isEmptyST(ST)){
		printf("La case sélectionnée est vide, veuillez en choisir une autre.\n");
		sleep(10);
		return 0;
	}
	tmp=peekST(ST);
	if((tmp.Name[1]=='B' && turn%2==0) || (tmp.Name[1]=='N' && turn%2==1)){
		printf("Vous ne pouvez pas bougez une case contenant des pièces de l'adversaire, veuillez en choisir une autre.\n");
		sleep(10);
		return 0;
	}
	return 1;
}

int isValidMove(stackToken start, stackToken end, int nbToMove, int locD, stackToken** Board, int size_board){
	int k;
	int i;
	int j;
	int invP=1;
	int nbCvl=0;
	int Tokenlist=1;
	int heightStart;
	int widthStart;
	int heightEnd;
	int widthEnd;
	int isPossibleC=1;
	int isPossibleP=1;
	int isPossibleD=1;
	int isPossibleF=1;
	int isPossibleT=1;
	token curToken=peekST(start);
	heightStart=curToken.loc/size_board;
	widthStart=curToken.loc%size_board;
	heightEnd=locD/size_board;
	widthEnd=locD%size_board;
	i=(heightEnd-heightStart)/abs(heightEnd-heightStart);
	j=(widthEnd-widthStart)/abs(widthEnd-widthStart);
	if(nbToMove<=end->summit && peekST(start).Name[1]!=peekST(end).Name[1]){
		printf("Déplacement impossible: le nombre de pièces adverse sur la case d'arrivée est supérieur au nombre de pièces que vous voulez déplacer.\n");
		sleep(5);
		return 0;
	}
	for(k=0;k<nbToMove;k++){
		curToken=popST(&start);
		if(curToken.Name[0]=='P'){
			if(curToken.isFirstMove && Tokenlist%2!=0) Tokenlist*=2;
			else if(!curToken.isFirstMove && Tokenlist%3!=0) Tokenlist*=3;
		}
		if(curToken.Name[0]=='F' && Tokenlist%5!=0) Tokenlist*=5;
		if(curToken.Name[0]=='T' && Tokenlist%7!=0) Tokenlist*=7;
		if(curToken.Name[0]=='D' && Tokenlist%11!=0) Tokenlist*=11;
		if(curToken.Name[0]=='R' && Tokenlist%13!=0) Tokenlist*=13;
		if(curToken.Name[0]=='C' && Tokenlist%17!=0){
			Tokenlist*=17;
			nbCvl++;
		}
	}
	if(Tokenlist%17==0){
		if(heightEnd-heightStart==2){
			if(widthEnd-widthStart==1){
				if((!isEmptyST(Board[widthStart+1][heightStart])&&!isEmptyST(Board[widthStart+1][heightStart+1])) || (!isEmptyST(Board[widthStart][heightStart+1]) && !isEmptyST(Board[widthStart][heightStart+2]))){
					isPossibleC=0;
				}
			}
			else if(widthEnd-widthStart==-1){
				if((!isEmptyST(Board[widthStart-1][heightStart])&&!isEmptyST(Board[widthStart-1][heightStart+1])) || (!isEmptyST(Board[widthStart][heightStart+1]) && !isEmptyST(Board[widthStart][heightStart+2]))){
					isPossibleC=0;
				}
			}
		}
		else if(heightEnd-heightStart==-2){
			if(widthEnd-widthStart==1){
				if((!isEmptyST(Board[widthStart+1][heightStart])&&!isEmptyST(Board[widthStart+1][heightStart-1])) || (!isEmptyST(Board[widthStart][heightStart-1]) && !isEmptyST(Board[widthStart][heightStart-2]))){
					isPossibleC=0;
				}
			}
			else if(widthEnd-widthStart==-1){
				if((!isEmptyST(Board[widthStart-1][heightStart])&&!isEmptyST(Board[widthStart-1][heightStart-1])) || (!isEmptyST(Board[widthStart][heightStart-1]) && !isEmptyST(Board[widthStart][heightStart-2]))){
					isPossibleC=0;
				}
			}
		}
		else if(heightEnd-heightStart==1){
			if(widthEnd-widthStart==2){
				if((!isEmptyST(Board[widthStart][heightStart+1])&&!isEmptyST(Board[widthStart+1][heightStart+1])) || (!isEmptyST(Board[widthStart+1][heightStart]) && !isEmptyST(Board[widthStart+2][heightStart]))){
					isPossibleC=0;
				}
			}
			else if(widthEnd-widthStart==-2){
				if((!isEmptyST(Board[widthStart][heightStart+1])&&!isEmptyST(Board[widthStart-1][heightStart+1])) || (!isEmptyST(Board[widthStart-1][heightStart]) && !isEmptyST(Board[widthStart-2][heightStart]))){
					isPossibleC=0;
				}
			}
		}
		else if(heightEnd-heightStart==-1){
			if(widthEnd-widthStart==2){
				if((!isEmptyST(Board[widthStart][heightStart-1])&&!isEmptyST(Board[widthStart+1][heightStart-1])) || (!isEmptyST(Board[widthStart+1][heightStart]) && !isEmptyST(Board[widthStart+2][heightStart]))){
					isPossibleC=0;
				}
			}
			else if(widthEnd-widthStart==-2){
				if((!isEmptyST(Board[widthStart][heightStart-1])&&!isEmptyST(Board[widthStart-1][heightStart-1])) || (!isEmptyST(Board[widthStart-1][heightStart]) && !isEmptyST(Board[widthStart-2][heightStart]))){
					isPossibleC=0;
				}
			}
		}
		else isPossibleC=0;
	}
	if (!isPossibleC){
		printf("Déplacement impossible: un Cavalier dans la pile bloque le déplacement.\n");
		sleep(5);
		return 0;
	}
	if(isPossibleC && nbCvl>=(nbToMove*2)) return 1;
	if(Tokenlist%2==0 || Tokenlist%3==0){
		if(curToken.Name[1]=='N') invP=-1;
		if(!isEmptyST(Board[widthStart][heightStart+1*invP])){
			if(heightEnd-heightStart!=1*invP && abs(widthEnd-widthStart)!=1){
				isPossibleP=0;
			}
		}
		else if (widthEnd!=widthStart) isPossibleP=0;
		else if (heightEnd-heightStart!=1*invP && Tokenlist%3==0) isPossibleP=0;
		else if (heightEnd-heightStart!=1*invP && heightEnd-heightStart!=2*invP) isPossibleP=0;
	}
	if(!isPossibleP){
		printf("Déplacement impossible: un Pion dans la pile bloque le déplacement.\n");
		sleep(5);
		return 0;
	}
	if(Tokenlist%13==0){
		if(abs(widthEnd-widthStart)!=1 || abs(heightEnd-heightStart)!=1){
			printf("Déplacement impossible: un Roi dans la pile bloque le déplacement.\n");
			sleep(10);
			return 0;
		}
	}
	if(Tokenlist%11==0){
		if(widthEnd==widthStart){
			for(k=1;k<abs(heightEnd-heightStart);k++){
				if(!isEmptyST(Board[widthStart][heightStart+k*i])) isPossibleD=0;
			}
		}
		else if (heightEnd==heightStart){
			for(k=1;k<abs(widthEnd-widthStart);k++){
				if(!isEmptyST(Board[widthStart+k*j][heightStart])) isPossibleD=0;
			}
		}
		else if(abs(widthEnd-widthStart)==abs(heightEnd-heightStart)){
			for(k=1;k<abs(widthEnd-widthStart);k++){
				if(!isEmptyST(Board[widthStart+k*j][heightStart+k*i])) isPossibleD=0;
			}
		}
		else isPossibleD=0;
	}
	if(!isPossibleD){
		printf("Déplacement impossible: une Dame dans la pile bloque le déplacement.\n");
		sleep(10);
		return 0;
	}
	if(Tokenlist%5==0){
		if(abs(widthEnd-widthStart)==abs(heightEnd-heightStart)){
			for(k=1;k<abs(widthEnd-widthStart);k++){
				if(!isEmptyST(Board[widthStart+k*j][heightStart+k*i])) isPossibleF=0;
			}
		}
		else isPossibleF=0;
	}
	if(!isPossibleF){
		printf("Déplacement impossible: un Fou dans la pile bloque le déplacement.\n");
		sleep(10);
		return 0;
	}
	if(Tokenlist%7==0){
		if(widthEnd==widthStart){
			for(k=1;k<abs(heightEnd-heightStart);k++){
				if(!isEmptyST(Board[widthStart][heightStart+k*i])) isPossibleD=0;
			}
		}
		else if (heightEnd==heightStart){
			for(k=1;k<abs(widthEnd-widthStart);k++){
				if(!isEmptyST(Board[widthStart+k*j][heightStart])) isPossibleD=0;
			}
		}
	}
	if(!isPossibleT){
		printf("Déplacement impossible: une Tour dans la pile bloque le déplacement.\n");
		sleep(10);
		return 0;
	}
	return 1;
}


void moveST(stackToken* start, stackToken* end, int heightD, int locD, int nbToMove, int size_board){
	int k;
	stackToken tmp=*start, tmp1=*start,inter;
	if(isEmptyST(*end) || peekST(*end).Name[1]!=peekST(tmp1).Name[1]){
		freeST(*end);
		for(k=0;k<nbToMove;k++){
			if(tmp->elm.Name[0]=='P'){
				tmp->elm.isFirstMove=0;
				if((heightD==0 && tmp->elm.Name[1]=='N') || (heightD==size_board-1 && tmp->elm.Name[1]=='B')) tmp->elm.Name[0]='D';
			}
			tmp->elm.loc=locD;
			tmp->summit=nbToMove-k;
			tmp=tmp->next;
		}
		tmp1=tmp;
		tmp=NULL;
		*end=*start;
		*start=tmp1;

	}
	else{
		makeST(&inter);
		for(k=0;k<nbToMove;k++){
			if(tmp->elm.Name[0]=='P'){
				tmp->elm.isFirstMove=0;
				if((heightD==0 && tmp->elm.Name[1]=='N') || (heightD==size_board-1 && tmp->elm.Name[1]=='B')) tmp->elm.Name[0]='D';
			}
			tmp->elm.loc=locD;
			pushST(&inter,tmp->elm);
			tmp=tmp->next;
		}
		while(!isEmptyST(inter)) pushST(end,popST(&inter));
		*start=tmp;
	}
}



stackToken** init_board(int size_board){
	int height;
	int width;
	int switch_token=0;
	token TN;
	token FN;
	token CN;
	token DN;
	token RN;
	token PN;
	token TB;
	token FB;
	token CB;
	token DB;
	token RB;
	token PB;
	stackToken empty;
	TN.Name="TN";
	FN.Name="FN";
	CN.Name="CN";
	DN.Name="DN";
	RN.Name="RN";
	PN.Name="PN";
	TB.Name="TB";
	FB.Name="FB";
	CB.Name="CB";
	DB.Name="DB";
	RB.Name="RB";
	PB.Name="PB";
	PN.isFirstMove=1;
	PB.isFirstMove=1;
	makeST(&empty);
	stackToken** Board=(stackToken**) malloc(size_board*sizeof(struct PToken**));
	for(width=0;width<size_board;width++){
		Board[width]=(stackToken*) malloc(size_board*sizeof(struct PToken*));

		for(height=0;height<size_board;height++){
			makeST(&Board[width][height]);
			if (switch_token==3) switch_token=0;
			if(height==size_board-1){
				if(width!=size_board/2-1 && width!=(int) size_board/2){
					switch(switch_token){
					case 0:pushST(&Board[width][height],FN); break;
					case 1:pushST(&Board[width][height],CN); break;
					case 2:pushST(&Board[width][height],TN); break;
					}
					switch_token+=1;
				}
				else if(width==size_board/2){
					pushST(&Board[width][height],DN);
				}
				else{
					pushST(&Board[width][height],RN);
				}
			}
			if(height==size_board-2){
				pushST(&Board[width][height],PN);
			}
			if(height==1){
				pushST(&Board[width][height],PB);
			}
			if(height==0){
				if(width!=size_board/2-1 && width!=size_board/2){
					switch(switch_token){
					case 0:pushST(&Board[width][height],FB); break;
					case 1:pushST(&Board[width][height],CB); break;
					case 2:pushST(&Board[width][height],TB); break;
					}
				}
				else if(width==size_board/2){
					pushST(&Board[width][height],DB);
				}
				else{
					pushST(&Board[width][height],RB);
				}
			}
			if(!isEmptyST(Board[width][height])){
				(Board[width][height]->elm).loc=width+size_board*height;
			}
		}
	}
	return Board;
}

int* getParam(){
	FILE* fp;
	char tmp[4];
	char tmp1[4];
	int turn,size_board;
	int *res=malloc(2*sizeof(int));
	if((fp=fopen("save","r+"))==NULL){
		printf("Erreur: le fichier de sauvegarde est illisible ou n'existe pas.");
		exit(1);
	}
	if(fgets(tmp,4,fp)==NULL){
		printf("Erreur: le fichier de sauvegarde est peut être corrompu.");
		exit(1);
	}
	sscanf(tmp,"%i",&size_board);
	if(fgets(tmp1,4,fp)==NULL){
		printf("Erreur: le fichier de sauvegarde est peut être corrompu.");
		exit(1);
	}
	sscanf(tmp1,"%i",&turn);
	res[0]=size_board;
	res[1]=turn;
	fclose(fp);
	return res;
}

stackToken** init_saved_board(int size_board){
	FILE* fp=fopen("save","r");
	char ntoken[2];
	int i;
	int height;
	int width;
	char* tmp=malloc(4*size_board);
	token nwtoken;
	stackToken empty;
	makeST(&empty);
	stackToken** Board=(stackToken**) malloc(size_board*sizeof(stackToken*));
	tmp=fgets(tmp,10,fp);
	tmp=fgets(tmp,10,fp);
	for(width=0;width<size_board;width++){
		Board[width]=(stackToken*) malloc(size_board*sizeof(stackToken));
		for(height=0;height<size_board;height++){
			makeST(&Board[width][height]);
			i=0;
			memset(tmp,0,4*size_board);
			tmp=fgets(tmp,4*size_board,fp);
			if(tmp[0]=='\n') Board[width][height]=empty;
			while(tmp[i]!='\n'){
				ntoken[0]=tmp[i];
				ntoken[1]=tmp[i+1];
				nwtoken.loc=width+size_board*height;
				if(ntoken[0]=='S'){
					nwtoken.isFirstMove=1;
					if(ntoken[1]=='N') nwtoken.Name="PN";
					else if(ntoken[1]=='B') nwtoken.Name="PB";
				}
				else{
					nwtoken.isFirstMove=0;
					if(!strcmp(ntoken,"PN")) nwtoken.Name="PN";
					if(!strcmp(ntoken,"PB")) nwtoken.Name="PB";
					if(!strcmp(ntoken,"CN")) nwtoken.Name="CN";
					if(!strcmp(ntoken,"FN")) nwtoken.Name="FN";
					if(!strcmp(ntoken,"TN")) nwtoken.Name="TN";
					if(!strcmp(ntoken,"RN")) nwtoken.Name="RN";
					if(!strcmp(ntoken,"DN")) nwtoken.Name="DN";
					if(!strcmp(ntoken,"CB")) nwtoken.Name="CB";
					if(!strcmp(ntoken,"FB")) nwtoken.Name="FB";
					if(!strcmp(ntoken,"TB")) nwtoken.Name="TB";
					if(!strcmp(ntoken,"RB")) nwtoken.Name="RB";
					if(!strcmp(ntoken,"DB")) nwtoken.Name="DB";
				}
				pushST(&Board[width][height],nwtoken);
				i+=2;
			}
		}
	}
	fclose(fp);
	return Board;
}

char* reverseToken(char* rs, int size){
	int i=0;
	char tmp[2];
	char* res=malloc(1+size*sizeof(char));
	for(i=size;i>=1;i-=2){
		tmp[0]=rs[i-1];
		tmp[1]=rs[i];
		strcat(res,tmp);
	}
	return res;
}

void saveGame(stackToken** Board, int turn, int size_board){
	int width;
	int height;
	int size;
	FILE* fp;
	token cur;
	char* tmp=malloc(2*size_board*sizeof(char));
	if((fp=fopen("save","w"))==NULL){
		printf("Erreur: impossible de créer le fichier de sauvegarde, la partie vas donc continuer.\n");
		return;
	}
	fprintf(fp,"%d\n",size_board);
	fprintf(fp,"%d\n",turn);
	for(width=0;width<size_board;width++){
		for(height=0;height<size_board;height++){
			memset(tmp,0,2*size_board);
			size=-1;
			while(!isEmptyST(Board[width][height])){
				cur=popST(&Board[width][height]);
				if(cur.Name[0]=='P' && cur.isFirstMove==1){
					if(cur.Name[1]=='N') cur.Name="SN";
					if(cur.Name[1]=='B') cur.Name="SB";
				}
				strcat(tmp,cur.Name);
				size+=2;
			}
			tmp=reverseToken(tmp,size);
			fprintf(fp,"%s\n",tmp);
		}
	}
	fclose(fp);
	printf("A bientot dans StackChess!\n");
	exit(0);
}


void play(stackToken** Board, int size_board, int turn){
	int winner;
	int loc;
	int locD;
	int height;
	int width;
	int heightD;
	int widthD;
	int Move;
	int nbToMove;
	int fix;
	char square[4];
	char squareD[4];
	char strMove[3];
	char choice;
	char temp[2];
	char* joueur[2];
	char* end;
	stackToken empty;
	stackToken curST;
	stackToken desST;
	makeST(&empty);
	joueur[0]="noirs";
	joueur[1]="blancs";
	do{
		do{
			fix=system("clear");
			printBoard(Board,size_board,empty,"");
			Move=0;
			do{
				printf("C'est au tours des %s, veuillez sélectionner une case:",joueur[turn%2]);
				fix=scanf("%3s",square);
				printf("\n");
			} while(!isValidSquare(square,size_board, "test"));
			loc=squaretocoord(square,size_board);
			height=loc/size_board;
			width=loc%size_board;
			curST=Board[width][height];
			fix=system("clear");
			printBoard(Board, size_board, curST, square);
			do{
				printf("Très bien, que voulez vous faire maintenant?\n");
				printf("Entrez c pour changer de case, d pour faire un déplacement, s pour sauvegarder et quitter et a pour abandonner:");
				fix=scanf("%2s",temp);
				printf("\n");
				choice=temp[0];
			} while(choice != 'c' && choice != 'd' && choice != 'a' && choice != 's');
			if(choice=='d'){
				if (accessSquare(Board[width][height],turn)){
					do{
						printf("Entrez le nombre de pièces que vous voulez déplacer (entre 1 et %i):",curST->summit);
						fix=scanf("%2s",strMove);
						printf("\n");
						nbToMove=strtol(strMove,&end,10);
						if(nbToMove<=0 || nbToMove>curST->summit) printf("Erreur: le nombre que vous avez saisi n'est pas valide.\n");
					} while(nbToMove<=0 || nbToMove>curST->summit);
					do{
						printf("Entrez la case de déstination:");
						fix=scanf("%3s",squareD);
						printf("\n");
					} while(!isValidSquare(squareD,size_board,square));
					locD=squaretocoord(squareD,size_board);
					heightD=locD/size_board;
					widthD=locD%size_board;
					desST=Board[widthD][heightD];
					Move=isValidMove(curST,desST,nbToMove,locD,Board, size_board);
				}
			}
			if(choice=='s'){
				saveGame(Board,turn,size_board);
			}
			if(choice=='a'){
				printf("\nLe joueur %s a abandonné, c'est donc une victoire du joueur %s!\n",joueur[turn%2],joueur[1-turn%2]);
				exit(0);
			}
		} while (!Move);
		moveST(&Board[width][height],&Board[widthD][heightD], heightD, locD,nbToMove, size_board);
		turn++;
	} while(!(winner=isVictory(Board,size_board)));
	if(winner==1){
		printf("C'est une victoire des blancs en %i tours, félicitations!\n",turn-1);
		printf("A bientot dans StackChess!");
		exit(0);
	}
	if(winner==2){
		printf("C'est une victoire des noirs en %i tours, félicitations\n", turn-1);
		printf("A bientot dans StackChess!");
		exit(0);
	}
	if(winner==3){
		printf("Egalité! Malheureusement, personne ne gagne. Cela a eu lieu au bout de %i tours.\n", turn-1);
		printf("A bientot dans StackChess!\n");
		exit(0);
	}
}


int main(){
	char buffer[3];
	char choice[2];
	char* end;
	int size_board;
	int* param;
	int fix;
	stackToken** Board;
	fix=system("clear");
	printSMenu();
	do{
		do{
			printf("Bienvenue dans StackChess! Que voulez vous faire:");
			fix=scanf("%1s",choice);
		} while(choice[0] != 'n' && choice[0] != 'c' && choice[0] != 'm' && choice[0] != 'q');
			if(choice[0] == 'n'){
			do{
				printf("Entrez la taille du tableau: ");
				fix=scanf("%2s",buffer);
				size_board=strtol(buffer,&end,10);
			} while(size_board<6 || size_board>26);
			Board=init_board(size_board);
			play(Board,size_board,1);
			}
			if(choice[0] == 'c'){
				param=getParam();
				Board=init_saved_board(param[0]);
				play(Board,param[0],param[1]);
			}
			if(choice[0] == 'm'){
				printMan();
			}
	}while(choice[0] != 'q');
	printf("\nA bientot dans StackChess!\n");
	return 1;
}

