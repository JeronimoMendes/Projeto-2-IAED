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
void read_str(char *str, int word);
int next_param();
char** getDirs(char *path, int *count);
void addNewDir(RootNode list, char **dirs, char *value, int length);
void selectCommand(char *command, RootNode list);
Node findDir(RootNode list, char **dirs, int length);
void addSlashToPath(char* path);

void help();
void quit();
void set(RootNode list);
void print();
void find(RootNode list);
void list();
void search();
/* void delete(); */
void flushIO();
