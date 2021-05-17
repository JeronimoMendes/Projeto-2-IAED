/*
 * File: datastructs.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * THis file contains structures and respective functions to work with them
 * 
 */

#include "datastructs.h"
#include <stdlib.h>
#include <string.h>

/* Creates a new empty linked list */
RootNode* createLinkedList(){
	RootNode* root = malloc(sizeof(RootNode));

	root -> firstNode = NULL;
	root -> lastNode = NULL;

	return root;
}


/* Appends a node to the end of a list */
Node *appendToList(RootNode *list, char *key, void *content) {
	Node *new, *last;
	new = malloc(sizeof(Node));
	last = list -> lastNode;

	Node *children = createLinkedList();

	new -> previousSibling = last;
	new -> nextSibling = NULL;
	new -> firstChildren = children;
	new -> content = content;
	new -> key = key;

	if(last){
		last -> nextSibling = new;
	} else {
		list -> firstNode = new;
	}

	list -> lastNode = new;

	return new;
}


/* Finds a node in a list with a given key. Returns pointer to node */
Node *findInList(RootNode *list, char *key) {
	Node *current = list -> firstNode;

	while(current) {
		if (!strcmp(current -> key, key)) {
			return current;
		}

		current = current -> nextSibling;
	}

	return NULL;
}


/* Removes a given node from a list, freeing all it's allocated memory */
void removeNode(RootNode *list, Node *node) {
	Node *next, *previous;

	next = node -> nextSibling;
	previous = node -> previousSibling;

	if (previous) next -> previousSibling = previous;
	else list -> firstNode = next; 

	if (next) previous -> nextSibling = next;
	else list -> lastNode = previous;

	if ((node -> firstChildren) -> firstNode) destroyLinkedList(node -> firstChildren, NULL);
	free(node);
}


/* Destroys a given list, freeing all it's allocated memory */
void destroyLinkedList(RootNode *list, void (*freeFunction)(void*)) {
	Node *node, *aux;

	while (node) {
		if (freeFunction) freeFunction(node -> content);
		else free(node -> content);

		if (node -> key) free(node -> key);

		RootNode *childrenRootNode = (node -> firstChildren) -> firstNode;
		if (childrenRootNode) destroyLinkedList(childrenRootNode, NULL);

		aux = node;
		node = node -> nextSibling;

		free(aux);
	}

	free(list);
}