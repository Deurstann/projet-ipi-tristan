/*
 * main.c
 *
 *  Created on: 16 déc. 2018
 *      Author: tristan
 */

#include "Token.h"
#include "Stack_token.h"
#include <stdlib.h>
#include <stdio.h>


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
		if(height==printed_stack->summit+1 && height!=0){
			tmp=popST(&printed_stack);
			printf("     %s",tmp.Name);
		}
		else if (printed_stack->summit==1 && height==0){
			tmp=popST(&printed_stack);
			printf(" %s: %s",localisation,tmp.Name);
		}
		else if (isEmptyST(printed_stack) && height==0 && !strcmp(localisation,"")){
			printf(" %s: ", localisation);
		}
		printf("\n");
	}
}



int isVictory(stackToken** Board, int size_board){
	return 0;
}

int isValidSquare(char square[3],int size_board){
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
			return 1;
		}
	}
	printf("\nErreur, veuillez entrer une case avec le format suivant:lettre [%c,%c] + numéro [%i,%i]\n",'a','a'+size_board-1,1,size_board);
	return 0;
}

int accessSquare(char* square,stackToken ST, int turn){
	token tmp;
	if(isEmptyST(ST)){
		printf("La case sélectionnée est vide, veuillez en choisir une autre.");
		sleep(10);
		return 0;
	}
	tmp=peekST(ST);
	if((tmp.Name[1]=='B' && turn%2==0) || (tmp.Name[1]=='N' && turn%2==1)){
		printf("Vous ne pouvez pas bougez une case contenant des pions des l'adversaire, veuillez en choisir une autre.");
		sleep(10);
		return 0;
	}
	return 1;
}

int isValidMove(stackToken start, stackToken end, int nbToMove, int locD, stackToken** Board, int size_board){
	int k;
	int nbCvl=0;
	int Tokenlist=1;
	int heightStart;
	int widthStart;
	int heightEnd;
	int widthEnd;
	int isVerifiedDiag=0;
	int isVerifiedVert=0;
	int isVerifiedHori=0;
	int isPossibleHors=1;
	int isPossibleP=1;
	token curToken;
	if(nbToMove<=end->summit){
		printf("Déplacement impossible: le nombre de pièces adverse sur la case d'arrivée est supérieur au nombre de pièces que vous voulez déplacer.\n");
		return 0;
	}
	for(k=0;k<nbToMove;k++){
		curToken=popST(&start);
		if(curToken.Name[0]=='P'){
			if(curToken.isFirstMove && Tokenlist%2!=0) Tokenlist*=2;
			else if(Tokenlist%3!=0) Tokenlist*=3;
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
	heightStart=curToken.loc/size_board;
	widthStart=curToken.loc%size_board;
	heightEnd=locD/size_board;
	widthStart=locD%size_board;
	if(Tokenlist%17==0){
		if(heightEnd-heightStart==2){
			if(widthEnd-widthStart==1){
				if((!isEmpty(Board[widthStart+1][heightStart])&&!isEmpty(Board[widthStart+1][heightStart+1])) || (!isEmpty(Board[widthStart][heightStart+1]) && !isEmpty(Board[widthStart][heightStart+2]))){
					isPossibleHors=0;
				}
			}
			else if(widthEnd-widthStart==-1){
				if((!isEmpty(Board[widthStart-1][heightStart])&&!isEmpty(Board[widthStart-1][heightStart+1])) || (!isEmpty(Board[widthStart][heightStart+1]) && !isEmpty(Board[widthStart][heightStart+2]))){
					isPossibleHors=0;
				}
			}
		}
		else if(heightEnd-heightStart==-2){
			if(widthEnd-widthStart==1){
				if((!isEmpty(Board[widthStart+1][heightStart])&&!isEmpty(Board[widthStart+1][heightStart-1])) || (!isEmpty(Board[widthStart][heightStart-1]) && !isEmpty(Board[widthStart][heightStart-2]))){
					isPossibleHors=0;
				}
			}
			else if(widthEnd-widthStart==-1){
				if((!isEmpty(Board[widthStart-1][heightStart])&&!isEmpty(Board[widthStart-1][heightStart-1])) || (!isEmpty(Board[widthStart][heightStart-1]) && !isEmpty(Board[widthStart][heightStart-2]))){
					isPossibleHors=0;
				}
			}
		}
		else if(heightEnd-heightStart==1){
			if(widthEnd-widthStart==2){
				if((!isEmpty(Board[widthStart][heightStart+1])&&!isEmpty(Board[widthStart+1][heightStart+1])) || (!isEmpty(Board[widthStart+1][heightStart]) && !isEmpty(Board[widthStart+2][heightStart]))){
					isPossibleHors=0;
				}
			}
			else if(widthEnd-widthStart==-2){
				if((!isEmpty(Board[widthStart][heightStart+1])&&!isEmpty(Board[widthStart-1][heightStart+1])) || (!isEmpty(Board[widthStart-1][heightStart]) && !isEmpty(Board[widthStart-2][heightStart]))){
					isPossibleHors=0;
				}
			}
		}
		else if(heightEnd-heightStart==-1){
			if(widthEnd-widthStart==2){
				if((!isEmpty(Board[widthStart][heightStart-1])&&!isEmpty(Board[widthStart+1][heightStart-1])) || (!isEmpty(Board[widthStart+1][heightStart]) && !isEmpty(Board[widthStart+2][heightStart]))){
					isPossibleHors=0;
				}
			}
			else if(widthEnd-widthStart==-2){
				if((!isEmpty(Board[widthStart][heightStart-1])&&!isEmpty(Board[widthStart-1][heightStart-1])) || (!isEmpty(Board[widthStart-1][heightStart]) && !isEmpty(Board[widthStart-2][heightStart]))){
					isPossibleHors=0;
				}
			}
		}
		else isPossibleHors=0;
	}
	if (!isPossibleHors){
		printf("Déplacement impossible: un cavalier dans la pile bloque le déplacement.\n");
		sleep(10);
		return 0;
	}
	if(isPossibleHors && nbCvl>=(nbToMove*2)) return 1;
	if(Tokenlist%2==0 || Tokenlist%3==0){
		if(!isEmptyST(Board[widthStart][heightStart+1])){
			if(heightEnd-heightStart!=1 || abs(widthEnd-widthStart)!=1){
				isPossibleP=0;
			}
		}
		else if (widthEnd!=widthStart || (heightEnd-heightStart!=1 && heightEnd-heightStart!=2)) isPossibleP=0;
	}
	if(!isPossibleP){
		printf("Déplacement impossible: un pion dans la pile bloque le déplacement.\n");
	}
	if()
	return 1;
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
					switch_token=0;
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
					switch_token+=1;
				}
				else if(width==size_board/2){
					pushST(&Board[width][height],DB);
				}
				else{
					pushST(&Board[width][height],RB);
					switch_token=0;
				}
			}
			if(!isEmptyST(Board[width][height])){
				(Board[width][height]->elm).loc=width+size_board*height;
			}
		}
	}
	return Board;
}


void play(stackToken** Board, int size_board){
	int turn=1;
	int winner;
	int loc;
	int locD;
	int height;
	int width;
	int Move;
	int nbToMove;
	char square[3];
	char squareD[3];
	char strMove[2];
	char choice;
	char temp[2];
	char* joueur[2];
	char* end;
	stackToken empty;
	stackToken curST;
	makeST(&empty);
	joueur[0]="noirs";
	joueur[1]="blancs";
	do{
		system("clear");
		printBoard(Board,size_board,empty,"");
		Move=0;
		do{
			do{
				printf("C'est au tours des %s, veuillez sélectionner une case:",joueur[turn%2]);
				scanf("%4s",square);
				printf("\n");
			} while(!isValidSquare(square,size_board));
			loc=squaretocoord(square,size_board);
			height=loc/size_board;
			width=loc%size_board;
			curST=Board[width][height];
			printBoard(Board, size_board, Board[width][height], square);
			do{
				printf("Très bien, que voulez vous faire maintenant?\n");
				printf("Entrez c pour changer de case, d pour faire un déplacement ou a pour abandonner:");
				scanf("%2s",temp);
				printf("\n");
				choice=temp[0];
			} while(choice != 'c' && choice != 'd' && choice != 'a');
			if(choice=='d'){
				if (accessSquare(square,Board[width][height],turn)){
					do{
						printf("Entrez le nombre de pièces que vous voulez déplacer (entre 1 et %i):",curST->summit);
						scanf("%3s",strMove);
						printf("\n");
						nbToMove=strtol(strMove,&end,10);
						if(nbToMove<=0 || nbToMove>curST->summit) printf("Erreur: le nombre que vous avez saisi n'est pas valide.\n");
					} while(nbToMove<=0 || nbToMove>curST->summit);
					do{
						printf("Entrez la case de déstination:");
						scanf("%4s",squareD);
						printf("\n");
					} while(!isValidSquare(squareD,size_board));
					locD=squaretocoord(squareD,size_board);
					Move=isValidMove();
				}
			}
		} while (!Move);
		turn++;
	} while(!(winner=isVictory(Board,size_board)));
}


int main(){
	char buffer[2];
	char* end;
	int size_board;
	stackToken** Board;
	printf("Entrez la la taille du tableau: ");
	scanf("%3s",buffer);
	size_board=strtol(buffer,&end,10);
	Board=init_board(size_board);
	play(Board,size_board);
	return 1;
}

