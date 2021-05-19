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

char *strdup(const char *s);

typedef struct node *Node;
typedef struct rootnode {
	Node firstNode;
} *RootNode;


/* This struct represents a node in a linked list */

struct node {
	char *key;
	char *content;
	Node father;
	Node nextSibling;
	RootNode subList;
};


RootNode createLinkedList();
Node appendToList(RootNode list, char *key, char *content);
Node findInList(RootNode list, char *key);
void removeNode(RootNode list, Node node);
void destroyLinkedList(RootNode list, void (*freeFunction)(void*));
void changeNodeContent(Node node, char *newContent);


#endif /* Ending definition of datastructs.h */
