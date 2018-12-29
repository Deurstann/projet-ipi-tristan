/*
 * Token.c
 *
 *  Created on: 16 d�c. 2018
 *      Author: Tristan
 */
#include "Token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char* coordtosquare(int loc, int size_board){
	int height=loc/size_board;
	int width=loc%size_board;
	char snum[2];
	char* res = malloc(3*sizeof(char));
	res[0]=(char) (height+97);
	sprintf(snum,"%d",width);
	strcat(res,snum);
	return res;
}

int squaretocoord(char* square, int size_board){
	char temp[2];
	char* end;
	temp[0]=square[1];
	temp[1]=square[2];
	int width = (int) (square[0]-'a');
	int height=strtol(temp, &end, 10)-1;
	return width+size_board*height;
}
