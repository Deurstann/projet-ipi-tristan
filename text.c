/*
 * text.c
 *
 *  Created on: 30 déc. 2018
 *      Author: tristan
 */
#include "text.h"
#include <stdlib.h>
#include <stdio.h>

/*
 @requires: nothing
 @assigns: nothing
 @ensures: Affiche le logo du jeu
 */

void printSMenu(){
	if(system("clear")==-1){
		printf("Erreur: Impossible d'éffacer l'écran!");
	}
	printf("\033[36m");
	printf("     _______.___________.    ___       ______  __  ___   ______  __    __   _______     _______.     _______.\n");
	printf("    /       |           |   /   \\     /      ||  |/  /  /      ||  |  |  | |   ____|   /       |    /       |\n");
	printf("   |   (----`---|  |----`  /  ^  \\   |  ,----'|  '  /  |  ,----'|  |__|  | |  |__     |   (----`   |   (----`\n");
	printf("    \\   \\       |  |      /  /_\\  \\  |  |     |    <   |  |     |   __   | |   __|     \\   \\        \\   \\    \n");
	printf(".----)   |      |  |     /  _____  \\ |  `----.|  .  \\  |  `----.|  |  |  | |  |____.----)   |   .----)   |   \n");
	printf("|_______/       |__|    /__/     \\__\\ \\______||__|\\__\\  \\______||__|  |__| |_______|_______/    |_______/    \n");
	printf("\033[0m");
	printf("                   ____________________    ______________    ___________    ____________\n");
	printf("                  | n: Nouvelle partie |  | c: Continuer |  | m: Manuel |  | q: quitter |\n");
	printf("                   --------------------    --------------    -----------    ------------\n");
}

void printMan(){
	printf("\n                                             ______\n");
	printf("********************************************|Manuel|**********************************************\n\n");
	printf("StackChess est un jeu d'échec un peu particulier. En effet, ici il est possible d'empiler les pièces!\n");
	printf("En ce qui concerne les règles, les voici:\n");
	printf("   - Pour empiler des pièces, il suffit de déplacer une pièce sur une autre pièce ou une pile de pièces.\n");
	printf("   - Il n'y a pas de restriction sur le nombre ou le type des pièces que l'on peut empiler.\n");
	printf("   - Lorsque l'on déplace la pile on peut soit déplacer tout ses éléments, soit une partie.\n");
	printf("   - Pour pouvoir déplacer une pile, il faut que le déplacement soit valide pour toutes les pièces s'y trouvant.\n");
	printf("   - Les cavaliers peuvent porter des pièces. Par exemple, si la pile possède un nombre 2n de pièces\n");
	printf("     et s'il y a un nombre supérieur à n de cavaliers, alors on peut considérer la pile comme une pile de cavaliers.\n");
	printf("   - On ne peut pas déplacer de pièces par dessus d'autre pièces, sauf dans le cas des cavalier.\n");
	printf("   - Pour prendre des pièces à l'adversaire il faut que la taille de la pile que l'on déplace soit\n");
	printf("     supérieure à la taille de la pile de de l'adversaire.\n");
	printf("   - La partie se termine lorsque l'un des joueurs n'a plus de pièces ou lorsque les 2 joueurs sont en incapacité\n");
	printf("     de prendre des pièces à l'autre.\n");
	printf("   - A chaque tours, vous pouvez choisir de sauvegarder la partie pour y revenir plus tard.\n");
	printf("   - Lorsque le programme demande de rentrer une case, celle-ci doit être de la forme a2, b5,...\n");
	printf("C'est tout, je vous souhaite un agréable moment passé à jouer à StackChess!\n");
	printf("\n************************************************************************************************\n");
}


