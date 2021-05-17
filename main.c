/*
 * File: main.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * The goal of this project is to develop a primitive file system that can
 * store strings in various directories.
 * 
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filesystem.h"


int main() {
	char command;
	char *pCommand; /* Pointer to command */
	int i = 0;

	while (1) {

		pCommand = (char *)malloc(sizeof(char));

		i = 0;
		while ((command = getchar()) != ' ' && command != '\n') {
			pCommand[i] = command;

			i += 1;
			pCommand = (char *)realloc(pCommand, sizeof(char) * (i + 1) );
		}
		pCommand[i] = '\0';

		selectCommand(pCommand);

		if (!strcmp(pCommand, "quit")) break;
	}

	free(pCommand);

	return 0;
}