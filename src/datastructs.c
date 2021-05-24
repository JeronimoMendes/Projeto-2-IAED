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
	Head head;
	head = (Head)malloc(sizeof(struct head_s));
	/* root = malloc(sizeof(struct rootnode)); */

	head->firstNode = NULL;
	head->parentList = NULL;
	head->avlTree = NULL;

	return head;
}


/* Appends an element to the end of a list */
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
	sub->parentList = list; /* Reference parent list */
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


/* Finds an element in a list with a given key. Returns pointer to node */
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


/* Removes a given element from a list */
void removeElement(Head list, Element element) {
	Element prev, temp;
	Head mainList;

	mainList = getFirstHead(list);

	mainList->avlTree = removeNodeAVL(mainList->avlTree, element);

	temp = list->firstNode;
	if (element == temp) list->firstNode = element->nextSibling;

	prev = temp;
	while (temp != NULL && temp->nextSibling != element) {
		prev = temp;
		temp = temp->nextSibling;
	}

	if (temp != NULL) {
		prev->nextSibling = element->nextSibling;
	}

	destroyLinkedList(element->subList);
	free(element->content);
	free(element->key);
	free(element);
}


/* Returns head list of a given head */
Head getFirstHead(Head list) {
	Head aux;
	aux = list;
	while (list != NULL) {
		aux = list;
		list = list->parentList;
	}
	return aux;
}


/* Destroys a given list */
void destroyLinkedList(Head list) {
	Element node, aux;

	node = list -> firstNode;

	while (node) {
		aux = node->nextSibling;
		removeElement(list, node);
		node = aux;
	}

	free(list);
	list = NULL;
}


/* Erases data on a list, keeping the head */
void eraseData(Head list) {
	Element node, aux;

	node = list -> firstNode;

	while (node) {
		aux = node->nextSibling;
		removeElement(list, node);
		node = aux;
	}
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

/* Returns bigger number from 2 integers */
int max(int n1, int n2) {
	if (n1 > n2) return n1;
	else return n2;
}


/* Returns height of AVL node */
int height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}


/* Starts an AVL. Returns head node */
Node* newNode(Element ele) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->element = ele;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  
    return(node);
}

/* Performs a right rotation on a node */
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
 
    /* Rotate */
    x->right = y;
    y->left = T2;
 
    /* Update heights */
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}


/* Performs a left rotation on a node */
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}


/* Returns balance of AVL */
int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}


/* Inserts a new node into the AVL */
Node* insertNode(Node* node, Element ele) {
	if (node == NULL)
		return newNode(ele);
	if (strcmp(node->element->key, ele->key) > 0)
		node->left = insertNode(node->left, ele);
	else
		node->right = insertNode(node->right, ele);

	node=AVLbalance(node);
	return node;
}


/* Balances the AVL. Returns the new head node */
Node *AVLbalance(Node *node) {
	int balanceFactor;
	if (node==NULL) return node;
		balanceFactor= getBalance(node);
	if(balanceFactor>1) {
		if (getBalance(node->left)>=0) node=rightRotate(node);
		else
			node=leftRotate(leftRotate(node));
	}
	else if(balanceFactor<-1){
		if (getBalance(node->right)<=0) node = leftRotate(node);
		else
			node = rightRotate(rightRotate(node));
	}
	else
		node->height=height(node);
	return node;
}


/* Returns node with minimum value on an AVL */
Node* minValueNode(Node* node) {
    Node* current = node;
  
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
  
    return current;
}


/* Removes node from AVL */
Node* removeNodeAVL(Node *node, Element ele) {
	Node *aux;
	int balance;
	if (node == NULL) return node;
	if (strcmp(node->element->key, ele->key) > 0)
		node->left = removeNodeAVL(node->left, ele);

	else if(strcmp(node->element->key, ele->key) < 0)
		node->right = removeNodeAVL(node->right, ele);

	else {
		if( (node->left == NULL) || (node->right == NULL) ) {
			aux = node->left ? node->left : node->right;
			if (aux == NULL) {
				aux = node;
				node = NULL;
			}
			else  *node = *aux; 
			free(aux);
		}
		else {
			aux = minValueNode(node->right);
			node->element = aux->element;
			node->right = removeNodeAVL(node->right, aux->element);
		}
	}
    if (node == NULL) return node;
  
    node->height = 1 + max(height(node->left),height(node->right));
    balance = getBalance(node);
  
    if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
  
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
  
    if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
  
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}


/* Utilities that join the two structures */

/* Adds an element to the global data structure (LL + AVL) */
Element addElement(Head list, char *key, char *content){
	Element ele;
	Head rootHead = list;

	while (rootHead->parentList != NULL) rootHead = rootHead->parentList;

	ele = appendToList(list, key, content);
	if (rootHead->avlTree == NULL) rootHead->avlTree = newNode(ele);
	else insertNode(rootHead->avlTree, ele);
	
	return ele;
}


/* Deletes an element from the global data structure (LL + AVL) */
void deleteElement(Head list, char *key) {
	Element ele;
	ele = findInList(list, key);
	if (ele == NULL) return;

	removeElement(list, ele);
	ele = NULL;
}


/* Iterates AVL inorder, applying a given function to each node */
void iterateAVLInOrder(Node* node,char* dir, int(*filter)(char*, char*, char*),\
 void (*function)(char*, char*)){
    if (node == NULL) return;
 
    iterateAVLInOrder(node->left, dir, filter, function);

	if (filter != NULL){
		if (filter(node->element->key, node->element->content, dir))
    		function(node->element->key, node->element->content);
	}
		
	else if (filter == NULL) 
		function(node->element->key, node->element->content);
 
    iterateAVLInOrder(node->right, dir, filter, function);
}


