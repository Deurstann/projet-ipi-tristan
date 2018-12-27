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

void printBoard(stackToken** Board, int size_board, stackToken printed_stack){
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
		if(height==printed_stack->summit && height!=0){
			tmp=popST(&printed_stack);
			printf("     %s",tmp.Name);
		}
		else if (printed_stack->summit==0 && height==0){
			tmp=popST(&printed_stack);
			printf(" %s: %s",coordtosquare(tmp.loc,size_board),tmp.Name);
		}
		printf("\n");
	}
}



int isVictory(stackToken** Board, int size_board){
	return 0;
}

int isValidSquare(char square[6],int size_board){
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
	printf("Erreur, veuillez entrez une case avec le format suivant: 'lettre''numéro'");
	return 0;
}

int squaretocoord(){
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
	printBoard(Board,size_board,empty);
	return Board;
	/*do{
		system("clear");
		printBoard(Board,size_board);
		square=
		do{
			printf("C'est au tour du joueur %i, quelle case voulez-vous manipulez?")

		}

	}
	while(!(winner=isVictory(Board,size_board)));*/
}

void play(stackToken** Board, int size_board){
	int turn=0;
	int winner;
	char square[3];
	char* joueur[2];
	joueur[0]="blancs";
	joueur[1]="noirs";
	do{
		printf("C'est au tours des %s, veuillez sélectionner une case:",joueur[turn%2]);
		scanf("%3s\n",square);
	}while(!isValidSquare(square,size_board));
	while(!(winner=isVictory(Board,size_board)));
}


int main(){
	char buffer[2];
	char* end;
	int size_board;
	stackToken** Board;
	printf("Entrez la la taille du tableau: ");
	scanf("%2s",buffer);
	size_board=strtol(buffer,&end,10);
	Board=init_board(size_board);
	play(Board,size_board);
	return 1;
}

