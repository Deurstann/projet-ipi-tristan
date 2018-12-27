/*
 * Token.c
 *
 *  Created on: 16 d�c. 2018
 *      Author: Tristan
 */
#include "Token.h"
#include <stdlib.h>


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
