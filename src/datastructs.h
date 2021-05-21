/*
 * File: datastructs.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains structures and respective functions to work with them
 * 
 */

#ifndef DATASTRUCTS
#define DATASTRUCTS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*
 * LINKED LIST
*/

typedef struct element_s *Element;
typedef struct head_s {
	Element firstNode;
} *Head;


struct element_s {
	char *key;
	char *content;
	Element father;
	Element nextSibling;
	Head subList;
};


Head createLinkedList();
Element appendToList(Head list, char *key, char *content);
Element findInList(Head list, char *key);
void removeNode(Head list, Element node);
void destroyLinkedList(Head list, void (*freeFunction)(void*));
void changeNodeContent(Element node, char *newContent);
Element findContentInList(Head list, char *content);
void iterateList(Head list, void (*function)(char*, char*));


/*
 * AVL TREE
*/

struct Node
{
    Element element;
    struct Node *left;
    struct Node *right;
    int height;
};

struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, Element ele);


/* MISC */
char *strdup(const char *s);



#endif /* Ending definition of datastructs.h */
