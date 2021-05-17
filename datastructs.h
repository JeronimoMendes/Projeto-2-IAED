/*
 * File: datastructs.c
 *
 * Author: Jeronimo Mendes 99086 LEIC-T
 *   
 * Description: 
 * This file contains structures and respective functions to work with them
 * 
 */


/* This struct represents a node in a linked list */
typedef struct {
	char *key;
	void *content;
	Node *father;
	Node *previousSibling;
	Node *nextSibling;
	Node *firstChildren;
} Node;


typedef struct {
	Node *firstNode;
	Node *lastNode;
} RootNode;


RootNode* createLinkedList();
