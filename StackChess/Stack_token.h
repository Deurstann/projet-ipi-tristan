/*
 * Stack_token.h
 *
 *  Created on: 16 d�c. 2018
 *      Author: Tristan
 */

#include "Token.h"
#ifndef STACK_TOKEN_H_
#define STACK_TOKEN_H_

struct stackToken{
	token* stackElt;
	int summit;
};
typedef struct stackToken stackToken;

int isEmptyST(stackToken ST);
void makeST(stackToken* ST, int size);
void pushST(stackToken* ST,token tk);
token peekST(stackToken ST);
token popST(stackToken* ST);

#endif /* STACK_TOKEN_H_ */
