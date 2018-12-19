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

void printBoard(stackToken** Board, int size_tab){
	token tmp;
	int height;
	int width;
	for(height=size_tab-1;height>=0;height--){
		for(width=0;width<size_tab;width++){
			if(!isEmptyST(Board[width][height])){
				tmp=peekST(Board[width][height]);
				printf(" %s ",tmp.Name);
			}
		}
		printf("\n");
	}
}

void play(int size_board){
	int height;
	int width;
	int switch_token=0;
	int turn;
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
	stackToken** Board=(stackToken**) malloc(size_board*sizeof(struct stackToken*));
	for(width=0;width<size_board;width++){
		Board[width]=(stackToken*) malloc(size_board*sizeof(struct stackToken));
		for(height=0;height<size_board;height++){
			makeST(&Board[width][height],size_board);
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
		}
	}
	printBoard(Board,size_board);
}


int main(){
	char buffer[5];
	char* end;
	int size_board;
	printf("Entrez la taille du tableau: ");
	scanf("%5s",buffer);
	size_board=strtol(buffer,&end,10);
	play(size_board);
	return 1;
}
