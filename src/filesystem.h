/*
 * File: filesystem.h
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains all the utilities to work with primitive filesystem.
 * 
 */

/* Constants */
#define HELP 	"help: Imprime os comandos disponíveis.\n\
				quit: Termina o programa.\n\
				set: Adiciona ou modifica o valor a armazenar.\n\
				print: Imprime todos os caminhos e valores.\n\
				find: Imprime o valor armazenado.\n\
				list: Lista todos os componentes imediatos de um sub-caminho.\n\
				search: Procura o caminho dado um valor.\n\
				delete: Apaga um caminho e todos os subcaminhos.\n"



/* Function declaration */
void selectCommand(char *command);
void help();
void quit();
void set();
void print();
void find();
void list();
void search();
/* void delete(); */
void flushIO();
