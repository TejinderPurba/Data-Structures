/**
 * @file balancedTreeAPI.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 31st 2017
 * @brief File containing the function definitions and implementations of a Balanced Tree ADT
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "balancedTreeAPI.h"

Tree *createBalancedBinTree(int (*compareFP) (void *data1, void *data2), void (*destroyFP) (void *toBeDeleted),void *(*copyFP)(void *toBeCopy))
{

	Tree* newTree;

	if (compareFP == NULL || destroyFP == NULL || copyFP == NULL) {
		return NULL;
	}
	newTree = malloc(sizeof(Tree));
	newTree->compareFP = compareFP;
	newTree->destroyFP = destroyFP;
	newTree->copyFP = copyFP;
	newTree->root = NULL;

	return newTree;

}

TreeNode *createBalancedBinNode(void *data)
{
	TreeNode *newNode;

	newNode = malloc(sizeof(TreeNode));

	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void destroyBalancedBinTree(Tree *toBeDeleted)
{
	if (toBeDeleted == NULL) {
		return;
	}
	if (toBeDeleted->root == NULL) {
		return;
	}
	if (toBeDeleted->root != NULL) { 
		destroyNodes(toBeDeleted, toBeDeleted->root);
		free(toBeDeleted);
	}

    return;
}

void treeInsertNode(Tree *theTree, void *toBeInserted)
{
	TreeNode *temp;
	TreeNode *prev;
	TreeNode *newNode;

	if (theTree == NULL) {
		return;
	}
	if (toBeInserted == NULL) {
		return;
	}

	temp = theTree->root;
	prev = NULL;

	int (*compFunc)(void*, void*);
    compFunc = theTree->compareFP;
    void (*deleteFunc)(void *data);
    deleteFunc = theTree->destroyFP;
	newNode = createBalancedBinNode(toBeInserted);

	if (temp == NULL) {
		theTree->root = newNode;
		return;
	}

	while (temp != NULL) {
		prev = temp;
		if (compFunc(temp->data, toBeInserted) > 0) {
			temp = temp->left;
		}
		else if (compFunc(temp->data, toBeInserted) < 0) {
			temp = temp->right;
		}
		else if (compFunc(temp->data, toBeInserted) == 0) {
			deleteFunc(newNode->data);
			free(newNode);
			return;
		}
	}

	if (prev != NULL) {
		if (compFunc(prev->data, toBeInserted) > 0) {
			prev->left = newNode;
		}
		else if (compFunc(prev->data, toBeInserted) < 0) {
			prev->right = newNode;
		}
	}
	
	balanceTree(theTree);
	return;
}

void treeDeleteNode(Tree *theTree, void *toBeDeleted)
{
	if (theTree == NULL || toBeDeleted == NULL) {
		return;
	}
	if (theTree->root == NULL) {
		return;
	}

	if (theTree->root != NULL) {
		deleteNode(theTree, theTree->root, toBeDeleted);
		balanceTree(theTree);
	}
	return;
}

int treeIsEmpty(Tree *theTree)
{
	if (theTree == NULL) {
		return 1;
	}
	else if (theTree->root == NULL) {
		return 1;
	}
	else {
		return 0;
	}

}

int treeHasTwoChildren(TreeNode *root)
{
	if (root != NULL) {
		if (root->left != NULL && root->right != NULL) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

void *treeFindNode(Tree *theTree, void *data)
{
	TreeNode *temp;
	if (data == NULL || theTree == NULL) {
		return NULL;
	}
	if (theTree->root == NULL) {
		return NULL;
	}
	int (*compFunc)(void *, void *);
    compFunc = theTree->compareFP;

	if (theTree->root == NULL) {
		return NULL;
	}
		
	temp = theTree->root;

	while (temp != NULL) {
		if (compFunc(temp->data, data) > 0) {
			temp = temp->left;
		}
		else if (compFunc(temp->data, data) < 0) {
			temp = temp->right;
		}
		else if (compFunc(temp->data, data) == 0) {
			return temp->data;
		}
	}

	return NULL;
}

void *treeFindMin(Tree *theTree)
{
	if (theTree == NULL) {
		return NULL;
	}
	TreeNode *temp = theTree->root;
	TreeNode *prev = NULL;

	if (temp == NULL) {
		return NULL;
	}

	while (temp != NULL) {
		prev = temp;
		temp = temp->left;
	}

	if (prev != NULL) {
		return prev->data;
	}
	return NULL;
}

void *treeFindMax(Tree *theTree)
{
	if (theTree == NULL) {
		return NULL;
	}
	TreeNode *temp = theTree->root;
	TreeNode *prev = NULL;

	if (temp == NULL) {
		return NULL;
	}

	while (temp != NULL) {
		prev = temp;
		temp = temp->right;
	}

	if (prev != NULL) {
		return prev->data;
	}
	return NULL;
}

void treeInOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
	if (theTree == NULL || theTree->root == NULL) {
		return;
	}
	else {
		inOrder(theTree->root, printNodeFP);
	}
}

void treePreOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
	if (theTree == NULL || theTree->root == NULL) {
		return;
	}
	else {
		preOrder(theTree->root, printNodeFP);
	}
}

void treePostOrderPrint(Tree *theTree, void (*printNodeFP) (void *data))
{
	if (theTree == NULL || theTree->root == NULL) {
		return;
	}
	else {
		postOrder(theTree->root, printNodeFP);
	}
	
}
