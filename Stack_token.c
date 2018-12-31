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
	return (ST->summit==0);
}

void makeST(stackToken* ST){
	(*ST)=malloc(sizeof(struct PToken));
	(*ST)->summit=0;
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
int lisST(stackToken ST){
	int res=1;
	token curToken;
	while(!isEmptyST(ST)){
		curToken=popST(&ST);
		if(curToken.Name[0]=='P') res*=2;
		if(curToken.Name[0]=='F') res*=3;
		if(curToken.Name[0]=='T') res*=5;
		if(curToken.Name[0]=='D') res*=7;
		if(curToken.Name[0]=='R') res*=11;
		if(curToken.Name[0]=='C') res*=13;
	}
	return res;
}
void freeST(stackToken ST){
	stackToken tmp;
	while(!isEmptyST(ST)){
		tmp=ST;
		ST=ST->next;
		free(tmp);
	}
}





