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


/*
 * LINKED LIST
 *
 * This data structure is a singly linked list, with each element
 * pointing to another linked list (sublist)
 * 
*/

/* Creates a new empty linked list */
Head createLinkedList(){
	Head root;
	root = (Head)malloc(sizeof(struct head_s));
	/* root = malloc(sizeof(struct rootnode)); */

	root->firstNode = NULL;

	return root;
}


/* Appends a node to the end of a list */
Element appendToList(Head list, char *key, char *content) {
	Element new, last = NULL, aux = NULL;
	Head sub;
	new = (Element)malloc(sizeof(struct element_s));

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
Element findInList(Head list, char *key) {
	Element current = list -> firstNode;

	while(current) {
		if (!strcmp(current -> key, key)) {
			return current;
		}

		current = current -> nextSibling;
	}

	return NULL;
}


/* 
 * Finds an element from *list* with a given *content* 
 * Returns a Node or NULL if no Node is found with such content or list
 * isnt't populated
*/
Element findContentInList(Head list, char *content) {
	Element current = list -> firstNode, subdirResult;

	if (list == NULL) return NULL;

	while (current) {
		if (!strcmp(current -> content, content)) {
			return current;
		}

		subdirResult = findContentInList(current->subList, content);
		if (subdirResult != NULL) return subdirResult;
		current = current -> nextSibling;
	}

	return NULL;
}


/* Removes a given node from a list, freeing all it's allocated memory */
void removeNode(Head list, Element node) {
	Element prev, temp;

	temp = list->firstNode;

	if (node == temp) list->firstNode = node->nextSibling;

	prev = temp;
	while (temp != NULL && temp->nextSibling != node) {
		prev = temp;
		temp = temp->nextSibling;
	}

	if (temp == NULL) return;

	prev->nextSibling = node->nextSibling;

	destroyLinkedList(node->subList, NULL);
	free(node);
	node = NULL;
}


/* Destroys a given list, freeing all it's allocated memory */
void destroyLinkedList(Head list, void (*freeFunction)(void*)) {
	Element node, aux;
	Head childrenRootNode;

	node = list -> firstNode;

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
	list = NULL;
}


/* Changes content of a given element */
void changeNodeContent(Element node, char *newContent) {
	char *oldContent;
	oldContent = node -> content;
	node -> content = strdup(newContent);
	free(oldContent);
}


/* Iterates a list, applying a given function to keys and content of elements */
void iterateList(Head list, void (*function)(char*, char*)) {
	Element current = list -> firstNode;

	if (list == NULL) return;

	while (current) {
		function(current->key, current->content);

		iterateList(current->subList, *function);
		current = current -> nextSibling;
	}
}


/*
 * AVL TREE
 *
 * Each node points to an element in the structure above.
 * 
*/

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


struct Node* newNode(Element ele) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->element = ele;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}


struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    /* Rotate */
    x->right = y;
    y->left = T2;
 
    /* Update heights */
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}


int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


struct Node* insert(struct Node* node, Element ele) {
    if (node == NULL)
        return(newNode(ele));
 
    if (strcmp(node->element, ele->key))
        node->left  = insert(node->left, ele);
    else if (strcmp(ele->key, node->element))
        node->right = insert(node->right, ele);
    else 
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(node->left->element, ele->key)) 
		return rightRotate(node);
 
    if (balance < -1 && strcmp(ele->key, node->right->element)) 
		return leftRotate(node);
 
    if (balance > 1 && strcmp(ele->key, node->left->element)) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    if (balance < -1 && strcmp(node->right->element, ele->key)) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}
