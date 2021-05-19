/*
 * File: datastructs.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains structures and respective functions to work with them
 * 
 */

#include "datastructs.h"

/* Creates a new empty linked list */
RootNode createLinkedList(){
	RootNode root;
	root = (RootNode)malloc(sizeof(struct rootnode));
	/* root = malloc(sizeof(struct rootnode)); */

	root->firstNode = NULL;

	return root;
}


/* Appends a node to the end of a list */
Node appendToList(RootNode list, char *key, char *content) {
	Node new, last = NULL, aux = NULL;
	RootNode sub;
	new = (Node)malloc(sizeof(struct node));

	aux = list -> firstNode;
	if (aux == NULL) last = aux;
	while (aux != NULL) {
		last = aux;
		aux = last->nextSibling;
	}
	

	sub = createLinkedList();
	new->subList = sub;
	new->content = strdup(content);
	new->key = strdup(key);
	new->nextSibling = NULL;

	if(last){
		last -> nextSibling = new;
	} else {
		list -> firstNode = new;
	}

	return new;
}


/* Finds a node in a list with a given key. Returns pointer to node */
Node findInList(RootNode list, char *key) {
	Node current = list -> firstNode;

	while(current) {
		if (!strcmp(current -> key, key)) {
			return current;
		}

		current = current -> nextSibling;
	}

	return NULL;
}


/* Removes a given node from a list, freeing all it's allocated memory */
void removeNode(RootNode list, Node node) {
	Node prev, temp;
	RootNode children;

	temp = list->firstNode;

	children = node -> subList;

	if (node == temp) list->firstNode = node->nextSibling;

	while (temp != NULL && temp->nextSibling != node) {
		prev = temp;
		temp = temp->nextSibling;
	}

	if (temp == NULL) return;

	prev->nextSibling = node->nextSibling;

	if (children -> firstNode) destroyLinkedList(children, NULL);
	free(node);
}


/* Destroys a given list, freeing all it's allocated memory */
void destroyLinkedList(RootNode list, void (*freeFunction)(void*)) {
	Node node, aux;
	RootNode childrenRootNode;

	while (node) {
		if (freeFunction) freeFunction(node -> content);
		else free(node -> content);

		if (node -> key) free(node -> key);

		childrenRootNode = node -> subList;
		if (childrenRootNode -> firstNode) destroyLinkedList(childrenRootNode, NULL);

		aux = node;
		node = node -> nextSibling;

		free(aux);
	}

	free(list);
}


void changeNodeContent(Node node, char *newContent) {
	char *oldContent;
	oldContent = node -> content;
	node -> content = strdup(newContent);
	free(oldContent);
}
