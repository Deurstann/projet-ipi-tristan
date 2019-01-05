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

/*
 @requires: ST bien formée
 @assigns: nothing
 @ensures: retourne 1 si ST est vide, 0 sinon
 */
int isEmptyST(stackToken ST){
	return (ST->summit==0);
}

/*
 @requires: nothing
 @assigns: ST
 @ensures: Construit la pile ST et met son sommet à 0
 */

void makeST(stackToken* ST){
	(*ST)=malloc(sizeof(struct PToken));
	(*ST)->summit=0;
}

/*
 @requires: ST et tk bien formés
 @assigns: ST
 @ensures: met le token tk en tête de la pile ST, et incrémente le sommet de la pile
 */

void pushST(stackToken* ST, token tk){
	stackToken tmp=malloc(sizeof(struct PToken));
	tmp->next = *ST;
	tmp->summit=(*ST)->summit+1;
	tmp->elm=tk;
	*ST=tmp;
}

/*
 @requires: ST pile bien formée
 @assigns: nothing
 @ensures: retourne le token en tête de pile
 */

token peekST(stackToken ST){
	return ST->elm;
}

/*
 @requires: ST pile bien formée
 @assigns: ST
 @ensures: retourne le token en tête de pile en l'ayant supprimé de la pile au préalable
 */

token popST(stackToken* ST){
	token sm=(*ST)->elm;
	(*ST)=(*ST)->next;
	return sm;
}

/*
 @requires: ST pile bien formée
 @assigns: rien
 @ensures: retourne un entier caractérisant le nombre et le type des pièces dans la pile
 */

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

/*
 @requires: ST pile bien formée
 @assigns: ST
 @ensures: libère la mémoire alloué à tous les éléments de la pile
 */

void freeST(stackToken ST){
	stackToken tmp;
	while(!isEmptyST(ST)){
		tmp=ST;
		ST=ST->next;
		free(tmp);
	}
}





