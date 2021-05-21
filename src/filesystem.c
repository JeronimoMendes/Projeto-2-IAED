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


void selectCommand(char *command, Head list) {
	if (!strcmp(command, "help")) help();
	if (!strcmp(command, "set")) set(list);
	if (!strcmp(command, "find")) find(list);
	if (!strcmp(command, "delete")) delete(list);
	if (!strcmp(command, "search")) search(list);
	if (!strcmp(command, "print")) print(list);

}


void help() {
	printf(HELP);

 	return ;
}


void set(Head list) {
	char *path, *value, **dirs;
	int *count, i;
	Element dir;

	count = (int*)malloc(sizeof(int));
	path = (char*)malloc(sizeof(char) + 1);
	value = (char*)malloc(sizeof(char) + 1);
	*count = 0;
	path = read_str(True);
	next_param();
	value = read_str(False);
	flushIO();

	dirs = malloc(sizeof(char*));
	dirs = getDirs(path, count);

	dir = findDir(list, dirs, *count);

	if (dir) changeNodeContent(dir, value);
	else addNewDir(list , dirs, value, *count);

	for (i = 0; i < *count; i++) free(dirs[i]);
	free(count);
}


void find(Head list) {
	char *path, **dirs;
	int *length;
	
	Element dir;

	length = (int*)malloc(sizeof(int));
	*length = 0;
	path = (char*)malloc(sizeof(char) + 1);
	path = read_str(True);
	
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


void delete(Head list) {
	char *path, **dirs;
	int *length;
	Element dir, fatherDir;

	length = (int*)malloc(sizeof(int));
	*length = 0;

	path = read_str(True);

	if (!path) {
		/* Erase directory */
	}

	dirs = getDirs(path, length);
	dir = findDir(list, dirs, *length);

	if (dir == NULL) {
		printf("not found\n");
		return;
	}

	fatherDir = findDir(list, dirs, *length - 1);
	if (fatherDir != dir) list = fatherDir->subList;


	removeNode(list, dir);
}


void search(Head list) {
	char *value, *result;
	Element node;

	value = read_str(False);
	flushIO();

	node = findContentInList(list, value);

	if (node == NULL) {
		printf("not found");
		return;
	}

	result = strdup(node->key);
	addLeadingSlash(&result);

	printf("%s\n", result);
	free(result);
}


void print(Head list) {
	iterateList(list, *printKeyContent);
}



/* Reads a string. if word = true it only reads 1 word. */
char* read_str(int word){
    int i;
    char input, *str;
	str = (char*)malloc(sizeof(char));


    /* if word == True it will only read 1 word. */
    for (i = 0; (input = getchar()) != '\n' && input != EOF; i++) {
        if (word && (input == ' ' || input == '\t')) break;

        str[i] = input;
		str = realloc(str, sizeof(char) * (i + 1) + 1);
    }
 
    str[i] = '\0'; 

    if (input == '\n') ungetc(input, stdin);
	return str;
}


char** getDirs(char *path, int *count) {
	char *token, **dirs, *aux;
	aux = strdup(path);

	dirs = malloc(sizeof(char*));

	for (token = strtok(aux, "/"); token != NULL; token = strtok(NULL, "/")) {
		dirs = realloc(dirs ,sizeof(char*) * (*count + 1));
		dirs[(*count)++] = strdup(token);
	}

	free(aux);
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

void addNewDir(Head list, char **dirs, char *value, int length) {
	Element fatherDir = NULL;
	Head subdir;
	int i;
	char *path = (char*)malloc(strlen(dirs[0]) + 1);
	strcpy(path, dirs[0]);

	for (i = 0; i < length - 1; i++) {
		fatherDir = findInList(list, path);
		if (fatherDir == NULL) fatherDir = appendToList(list, strdup(path), "");
		list = fatherDir->subList;
		addTrailingSlash(path);
		path = realloc(path, strlen(path) + strlen(dirs[i + 1]));
		path = strcat(path, dirs[i+1]);
	}

	if (fatherDir) subdir = fatherDir -> subList;
	else subdir = list;
	
	appendToList(subdir, path, value);
}

Element findDir(Head list, char **dirs, int length) {
	int i;
	Element dir;
	char *path = (char*)malloc(strlen(dirs[0]) + 1);
	strcpy(path, dirs[0]);

	for (i = 0; i < length && (dir = findInList(list, path)) != NULL; i++) {
		if (dir) list = dir -> subList;
		
		if (i + 1 < length) {
			addTrailingSlash(path);
			path = realloc(path, strlen(path) + strlen(dirs[i + 1]));
			path = strcat(path, dirs[i + 1]);
		}
	}

	return dir;
}


/* Adds a trailing slash to a string */
void addTrailingSlash(char* path) {
	path = strcat(path, "/");
	path = realloc(path, strlen(path) + 1);
}


/* Adds a leading slash to a string */
void addLeadingSlash(char** path) {
	char *slash;
	slash = strdup("/");
	slash = strcat(slash, *path);
	*path = realloc(*path, strlen(*path) + 1);
	*path = strdup(slash);
	free(slash);
}

void printKeyContent(char* key, char* content) {
	if (content[0] != '\0') {
		addLeadingSlash(&key);
		printf("%s %s\n", key, content);
	}
}
