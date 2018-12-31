/*
 * Token.h
 *
 *  Created on: 16 d�c. 2018
 *      Author: Tristan
 */

#ifndef TOKEN_H_
#define TOKEN_H_

struct token{
	char* Name;
	int loc;
	int isFirstMove;
};
typedef struct token token;

char* coordtosquare(int loc, int size_board);
int squaretocoord(char* square, int size_board);



#endif /* TOKEN_H_ */
