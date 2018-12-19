/*
 * Stack_token.c
 *
 *  Created on: 16 d�c. 2018
 *      Author: Tristan
 */
#include "Stack_token.h"
#include "Token.h"
#include <stddef.h>
#include <stdlib.h>


int isEmptyST(stackToken ST){
	return (ST.summit==-1);
}

void makeST(stackToken* ST, int size){
	ST->stackElt=(token*)malloc(size*sizeof(token));
	ST->summit=-1;
}

void pushST(stackToken* ST, token tk){
	ST->summit+=1;
	ST->stackElt[ST->summit]=tk;
}

token peekST(stackToken ST){
	return ST.stackElt[ST.summit];
}

token popST(stackToken* ST){
	token sm=ST->stackElt[ST->summit];
	ST->summit-=1;
	return sm;
}



