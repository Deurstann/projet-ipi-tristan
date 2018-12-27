/*
 * Stack_token.h
 *
 *  Created on: 16 d�c. 2018
 *      Author: Tristan
 */

#include "Token.h"
#ifndef STACK_TOKEN_H_
#define STACK_TOKEN_H_

typedef struct PToken* stackToken;

struct PToken{
	stackToken next;
	token elm;
	int summit;
};

int isEmptyST(stackToken ST);
void makeST(stackToken* ST);
void pushST(stackToken* ST,token tk);
token peekST(stackToken ST);
token popST(stackToken* ST);

#endif /* STACK_TOKEN_H_ */
