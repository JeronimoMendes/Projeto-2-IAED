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


void selectCommand(char *command, RootNode list) {
	if (!strcmp(command, "help")) help();
	if (!strcmp(command, "set")) set(list);
	if (!strcmp(command, "find")) find(list);

}


void help() {
	printf(HELP);

 	return ;
}


void set(RootNode list) {
	char *path, *value, **dirs;
	int *count; 
	Node dir;

	count = (int*)malloc(sizeof(int));
	path = (char*)malloc(sizeof(char));
	value = (char*)malloc(sizeof(char));
	*count = 0;
	read_str(path, True);
	next_param();
	read_str(value, False);
	flushIO();

	dirs = malloc(sizeof(char*));
	dirs = getDirs(path, count);

	dir = findDir(list, dirs, *count);

	if (dir) changeNodeContent(dir, value);
	else addNewDir(list , dirs, value, *count);

	free(path);
	free(value);
	free(count);
}


void find(RootNode list) {
	char *path, **dirs;
	int *length;
	
	Node dir;

	length = (int*)malloc(sizeof(int));
	*length = 0;
	path = (char*)malloc(sizeof(char));
	read_str(path, True);
	flushIO();

	dirs = getDirs(path, length);

	dir = findDir(list, dirs, *length);

	if (dir) {
		if (strcmp(dir -> content, "")) printf("%s\n", dir -> content);
		else printf("no data\n");
	}
	
	else printf("not found\n");

	free(length);
	free(path);
}


/* Reads a string. if word = true it only reads 1 word. */
void read_str(char *str, int word){
    int i;
    char input;

    /* if word == True it will only read 1 word. */
    for (i = 0; (input = getchar()) != '\n' && input != EOF; i++) {
        if (word && (input == ' ' || input == '\t')) break;

        str[i] = input;
		str = realloc(str, sizeof(char) * i + 1);
    }
 
    str[i] = '\0'; 

    if (input == '\n') ungetc(input, stdin);
}


char** getDirs(char *path, int *count) {
	char *token, **dirs;

	dirs = malloc(sizeof(char*));

	for (token = strtok(path, "/"); token != NULL; token = strtok(NULL, "/")) {
		dirs = realloc(dirs ,sizeof(char*) * (*count + 1));
		dirs[(*count)++] = strdup(token);
	}

	return dirs;
}


/* Skips to the next parameter. If there's no instruction, it return Error */
int next_param(){
    char input;

    while ((input = getchar()) == ' ' || input == '\t')

    if (input == '\n') return EXIT_FAILURE;
    
    ungetc(input, stdin);
    return EXIT_SUCCESS;
}


/* Discards the rest of the inputs on the same line */
void flushIO(){
	while (getchar() != '\n');
}

void addNewDir(RootNode list, char **dirs, char *value, int length) {
	Node fatherDir = NULL;
	RootNode subdir;
	int i;
	char *path = (char*)malloc(strlen(dirs[0]));
	strcpy(path, dirs[0]);

	for (i = 0; i < length - 1; i++) {
		fatherDir = findInList(list, path);
		if (fatherDir == NULL) fatherDir = appendToList(list, strdup(path), "");
		list = fatherDir->subList;
		addSlashToPath(path);
		path = realloc(path, strlen(path) + strlen(dirs[i + 1]));
		path = strcat(path, dirs[i+1]);
	}

	if (fatherDir) subdir = fatherDir -> subList;
	else subdir = list;
	
	appendToList(subdir, path, value);
}

Node findDir(RootNode list, char **dirs, int length) {
	int i;
	Node dir;
	char *path = (char*)malloc(strlen(dirs[0]));
	strcpy(path, dirs[0]);

	for (i = 0; i < length && (dir = findInList(list, path)) != NULL; i++) {
		if (dir) list = dir -> subList;
		
		if (i + 1 < length) {
			addSlashToPath(path);
			path = realloc(path, strlen(path) + strlen(dirs[i + 1]));
			path = strcat(path, dirs[i + 1]);
		}
	}

	free(path);
	return dir;
}


/* Adds a trailing slash to a string */
void addSlashToPath(char* path) {
	path = strcat(path, "/");
	path = realloc(path, strlen(path) + 1);
}
