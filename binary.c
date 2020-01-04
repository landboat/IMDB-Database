/*Name: Owen Douglas
 *Student ID: 1056143
 *Email: douglaso@uoguelph.ca
 */

#include "binary.h"
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"

void addNode(struct tree **root, char *key, void *data) {
	if (*root) {
		if (strcmp(key, (*root)->key) < 0) {
			/*Recursively calls addNode on node's left child.*/
			addNode(&((*root)->child[0]), key, data);
		}
		else {
			/*Recursively calls addNode on node's right child.*/
			addNode(&((*root)->child[1]), key, data);
		}
	}
	/*Base case.*/
	else {
		/*Adds new node when a NULL root (leaf) is found*/
		(*root) = malloc(sizeof(struct tree));
		(*root)->key = key;
		(*root)->data = (void*)data;
		(*root)->child[0] = NULL;
		(*root)->child[1] = NULL;
	}
	return;
}

void *findNode(struct tree **root, char *search) {
	void *result = NULL;

	if (*root) {
		if (strcmp(search, (*root)->key) != 0) {
			if (strcmp(search, (*root)->key) < 0) {
				/*Recursively calls findNode on node's left child.*/
				return findNode(&((*root)->child[0]), search);
			}
			else if (strcmp(search, (*root)->key) > 0) {
				/*Recursively calls findNode on node's right child.*/
				return findNode(&((*root)->child[1]), search);
			}
			/* Seg fault???*/
			else {
				return NULL;
			}
		}
		/*Base case.*/
		else {
			/*Condition if strcmp returns 0.*/
			result = (*root)->data;
			return result;
		}
	}
	else {
		/*Returns NULL if root is empty.*/
		return NULL;
	}


}

/*Function used by find_tp_alt to return a tree leaf instead of an array index.*/
void *findPrincipals(struct tree **root, char *search) {
	void *result = NULL;

	if (*root) {
		if (strcmp(search, (*root)->key) != 0) {

			if (strcmp(search, (*root)->key) < 0) {
				/*Recursively calls findNode on node's left child.*/
				return findPrincipals(&((*root)->child[0]), search);
			}
			else if (strcmp(search, (*root)->key) > 0) {
				/*Recursively calls findNode on node's right child.*/
				return findPrincipals(&((*root)->child[1]), search);
			}
		}
		/*Base case.*/
		else {
			/*Condition if strcmp returns 0.*/
			result = (void*)(*root);
			return result;
		}
	}
	else {
		/*Returns NULL if root is empty.*/
		return NULL;
	}
}