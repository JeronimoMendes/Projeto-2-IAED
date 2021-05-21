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
	Node *avlTree;
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

typedef struct node_s
{
    Element element;
    Node *left;
    Node *right;
    int height;
} Node;

Node *leftRotate(Node *x);
int getBalance(Node *N);
Node* insertNode(Node* node, Element ele);


/* MISC */
char *strdup(const char *s);



#endif /* Ending definition of datastructs.h */
