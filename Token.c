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

/*
 @requires: loc et size_board positifs
 @assigns: nothing
 @ensures: retourne  la case correspondant à l'entier loc par rapport à la taille du plateau
 */
char* coordtosquare(int loc, int size_board){
	int height=loc/size_board;
	int width=loc%size_board;
	char snum[2];
	char tmp[12];
	char* res = malloc(3*sizeof(char));
	res[0]=(char) (height+97);
	sprintf(tmp,"%d",width);
	snum[0]=tmp[0];
	snum[1]=tmp[1];
	strcat(res,snum);
	return res;
}

/*
 @requires: square de taille 2 ou 3 (sans compter le '\0')
 @assigns: rien
 @ensures: retourne un entier caractérisant la localisation de la case par rapport à la taille du plateau
 */

int squaretocoord(char* square, int size_board){
	char temp[2];
	char* end;
	temp[0]=square[1];
	temp[1]=square[2];
	int width = (int) (square[0]-'a');
	int height=strtol(temp, &end, 10)-1;
	return width+size_board*height;
}
