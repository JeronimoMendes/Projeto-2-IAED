/*
 * File: datastructs.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains structures and respective functions to work with them
 * 
 */

#include <stdlib.h>
#include <string.h>

typedef struct node Node;
typedef struct rootnode {
	Node *firstNode;
	Node *lastNode;
} RootNode;


/* This struct represents a node in a linked list */

struct node {
	char *key;
	void *content;
	Node *father;
	Node *previousSibling;
	Node *nextSibling;
	RootNode *firstChildren;
};


RootNode* createLinkedList();
Node *appendToList(RootNode *list, char *key, void *content);
Node *findInList(RootNode *list, char *key);
void removeNode(RootNode *list, Node *node);
void destroyLinkedList(RootNode *list, void (*freeFunction)(void*));
