/*
 * File: filesystem.h
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains all the utilities to work with primitive filesystem.
 * 
 */

#include "datastructs.h"


/* Constants */
#define HELP "help: Imprime os comandos disponíveis.\n\
quit: Termina o programa.\n\
set: Adiciona ou modifica o valor a armazenar.\n\
print: Imprime todos os caminhos e valores.\n\
find: Imprime o valor armazenado.\n\
list: Lista todos os componentes imediatos de um sub-caminho.\n\
search: Procura o caminho dado um valor.\n\
delete: Apaga um caminho e todos os subcaminhos.\n"

#define True 1
#define False 0

/* Function declaration */
char* read_str(int word);
int next_param();
char** getDirs(char *path, int *count);
void addNewDir(Head list, char **dirs, char *value, int length);
void selectCommand(char *command, Head list, char lastChar);
Element findDir(Head list, char **dirs, int length);
void addTrailingSlash(char** path);
void addLeadingSlash(char** path);
void printKeyContent(char* key, char* content);
void printPath(char* path, char* nun);
int sameDir(char* path, char* content, char* dir);

void help();
void quit();
void set(Head list);
void print();
void find(Head list);
void list(Head list, char lastChar);
void search(Head list);
void delete(Head list);
void flushIO();
