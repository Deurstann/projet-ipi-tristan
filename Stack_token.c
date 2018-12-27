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
	return (ST->summit==-1);
}

void makeST(stackToken* ST){
	(*ST)=malloc(sizeof(struct PToken));
	(*ST)->summit=-1;
}

void pushST(stackToken* ST, token tk){
	stackToken tmp=malloc(sizeof(struct PToken));
	tmp->next = *ST;
	tmp->summit=(*ST)->summit+1;
	tmp->elm=tk;
	*ST=tmp;
}

token peekST(stackToken ST){
	return ST->elm;
}

token popST(stackToken* ST){
	token sm=(*ST)->elm;
	(*ST)=(*ST)->next;
	return sm;
}



