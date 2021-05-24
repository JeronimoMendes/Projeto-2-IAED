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

/* Selects a command given a string */
void selectCommand(char *command, Head data, char lastChar) {
	if (!strcmp(command, "help")) help();
	if (!strcmp(command, "set")) set(data);
	if (!strcmp(command, "find")) find(data);
	if (!strcmp(command, "delete")) delete(data);
	if (!strcmp(command, "search")) search(data);
	if (!strcmp(command, "print")) print(data);
	if (!strcmp(command, "list")) list(data, lastChar);

}


/* Prints available commands */
void help() {
	printf(HELP);

 	return ;
}


/* Creates a new directory */
void set(Head list) {
	char *path, *value, **dirs;
	int *count, i;
	Element dir;

	count = (int*)malloc(sizeof(int));
	*count = 0;
	path = read_str(True);
	next_param();
	value = read_str(False);
	flushIO();

	dirs = getDirs(path, count);

	dir = findDir(list, dirs, *count);

	if (dir) changeNodeContent(dir, value);
	else addNewDir(list , dirs, value, *count);

	for (i = 0; i < *count; i++) free(dirs[i]);
	free(dirs);
	free(count);
	free(path);
	free(value);
}


/* Finds a directory and prints its value */
void find(Head list) {
	char *path, **dirs;
	int *length, i;
	
	Element dir;

	length = (int*)malloc(sizeof(int));
	*length = 0;
	path = read_str(True);
	
	flushIO();

	dirs = getDirs(path, length);

	dir = findDir(list, dirs, *length);

	if (dir) {
		if (strcmp(dir -> content, "")) printf("%s\n", dir -> content);
		else printf("no data\n");
	}
	
	else printf("not found\n");

	for (i = 0; i < *length; i++) free(dirs[i]);
	free(dirs);
	free(length);
	free(path);
}


/* Deletes a directory or the whole filesystem */
void delete(Head list) {
	char *path, **dirs;
	int *length, i;
	Element dir, fatherDir;

	length = (int*)malloc(sizeof(int));
	*length = 0;

	path = read_str(True);

	if (!path) {
		eraseData(list);
	} else {
		dirs = getDirs(path, length);
		dir = findDir(list, dirs, *length);

		if (dir == NULL) {
			printf("not found\n");
			return;
		}

		fatherDir = findDir(list, dirs, *length - 1);
		if (fatherDir != dir) list = fatherDir->subList;
		deleteElement(list, path);
		for (i = 0; i < *length; i++) free(dirs[i]);
		free(dirs);
	}
	free(length);
	free(path);
}


/* Searches for a directory with a given value */
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
	free(value);
}


/* Prints all directories and corresponding values */
void print(Head list) {
	iterateList(list, *printKeyContent);
}


/* Lists all directories in a given directory or root */
void list(Head list, char lastChar) {
	char *path = NULL, **dirs;
	int *length, i;
	

	if (lastChar != '\n') {
		length = (int*)malloc(sizeof(int));
		*length = 0;
		path = read_str(True);
		dirs = getDirs(path, length);

		if (findDir(list, dirs, *length) == NULL) {
			printf("not found");
			return;
		}
		iterateAVLInOrder(list->avlTree, dirs[*length-1], *sameDir,  *printPath);
		for (i = 0; i < *length; i++) free(dirs[i]);
		free(dirs);
		free(path);
		free(length);
		return;
	}	
	
	iterateAVLInOrder(list->avlTree, "", *sameDir, *printPath);
}


/* Reads a string. if word = true it only reads 1 word. */
char* read_str(int word){
    int i;
    char input, *str;
	str = (char*)malloc(sizeof(char));
	next_param();


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


/* Returns a list of directories on a path */
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


/* Adds a new directory to a path */
void addNewDir(Head list, char **dirs, char *value, int length) {
	Element fatherDir = NULL;
	Head subdir;
	int i;
	char *path = (char*)malloc(strlen(dirs[0]) + 1);
	strcpy(path, dirs[0]);

	for (i = 0; i < length - 1; i++) {
		fatherDir = findInList(list, path);
		if (fatherDir == NULL) fatherDir = addElement(list, path, "");
		list = fatherDir->subList;
		addTrailingSlash(&path);
		path = realloc(path, strlen(path) + strlen(dirs[i + 1]) + 1);
		strcat(path, dirs[i+1]);
	}

	if (fatherDir) subdir = fatherDir -> subList;
	else subdir = list;
	
	addElement(subdir, path, value);
	free(path);
}


/* Finds a directory if it exists in a given path. Returns NULL if not. */
Element findDir(Head list, char **dirs, int length) {
	int i;
	Element dir;
	char *path; 
	path = (char*)malloc(strlen(dirs[0]) + 1);
	strcpy(path, dirs[0]);

	for (i = 0; i < length && (dir = findInList(list, path)) != NULL; i++) {
		if (dir) list = dir -> subList;
		
		if (i + 1 < length) {
			addTrailingSlash(&path);
			path = realloc(path, strlen(path) + strlen(dirs[i + 1]) + 1);
			strcat(path, dirs[i + 1]);
		}
	}

	free(path);
	return dir;
}


/* Adds a trailing slash to a string */
void addTrailingSlash(char** path) {
	*path = realloc(*path, strlen(*path) + 2);
	strcat(*path, "/");
}


/* Adds a leading slash to a string */
void addLeadingSlash(char** path) {
	char *slash;
	slash = (char*)malloc(strlen(*path) + 2);
	strcpy(slash, "/");
	strcat(slash, *path);
	*path = realloc(*path, strlen(*path) + 2);
	strcpy(*path, slash);
	free(slash);
}


/* Prints content of a directory */
void printKeyContent(char* key, char* content) {
	if (content[0] != '\0') {
		printf("/%s %s\n", key, content);
	}
}


/* Prints path of a given directory */
void printPath(char* path, char* nun) {
	char *lastDirInPath, *token, *aux;
	lastDirInPath = strdup(path);

	token = (char*)malloc(1);
	aux = strtok(lastDirInPath, "/");
	while (aux != NULL) {
		token = realloc(token, strlen(aux) + 1);
		strcpy(token, aux);
		aux = strtok(NULL, "/");
	}

	if (nun) {};
	printf("%s\n", token);

	if (lastDirInPath == aux) free(lastDirInPath);
	else {
		free(lastDirInPath);
		free(aux);
	}
	free(token);
}


/* Checks if two directories are at the same level */
int sameDir(char* path, char* content, char* dir) {
	char *aux, *token;
	int count = 0, startCounter = False, i = 0;
	aux = (char*)malloc(strlen(path) + 1);
	strcpy(aux, path);
	token = strtok(aux, "/");
	if (content) {};
	while (token != NULL) {
		if (startCounter) count++;
		if (!strcmp(token, dir)) startCounter = True;
		token = strtok(NULL, "/");
		i++;
	}

	free(aux);

	if (!strcmp(dir, "") && i == 1) {
		
		return True;
	}
	return count == 1;
}

