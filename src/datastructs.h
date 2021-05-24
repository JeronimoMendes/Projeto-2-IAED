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
typedef struct node_s Node;
typedef struct element_s *Element;
typedef struct head_s *Head;
struct head_s {
	Element firstNode;
	Node *avlTree;
	Head parentList;
};


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
void removeElement(Head list, Element node);
void destroyLinkedList(Head list);
void changeNodeContent(Element node, char *newContent);
Element findContentInList(Head list, char *content);
void iterateList(Head list, void (*function)(char*, char*));
Head getFirstHead(Head list);


/*
 * AVL TREE
*/
struct node_s
{
    Element element;
    Node *left;
    Node *right;
    int height;
};

Node *leftRotate(Node *x);
int getBalance(Node *N);
Node* insertNode(Node* node, Element ele);
int height(Node *N);
Node *rightRotate(Node *y);
Node* maxNode(Node *node);
Node* removeNodeAVL(Node *node, Element ele);
void freeAVL(Node* node);


Node *AVLbalance(Node *node);


/* MISC */
char *strdup(const char *s);
Element addElement(Head list, char *key, char *content);
void iterateAVLInOrder(Node* node,char* dir, int(*filter)(char*, char*, char*),\
 void (*function)(char*, char*));
void deleteElement(Head list, char *key);

void eraseData(Head list);


void printAVL(Node* node);

#endif /* Ending definition of datastructs.h */
