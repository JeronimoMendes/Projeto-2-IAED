/*
 * File: filesystem.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains all the utilities to work with primitive filesystem.
 * 
 */

#include <stdio.h>
#include <string.h>
#include "filesystem.h"
#include "datastructs.h"

void help();

void selectCommand(char *command) {
	if (!strcmp(command, "help")) help();

}


void help() {
	flushIO();

	printf("help: Imprime os comandos disponíveis.\nquit: Termina o programa.\n");

 	return ;
}




/* Discards the rest of the inputs on the same line */
void flushIO(){
	while (getchar() != '\n');
}