/**
 * @file tree.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date August 6th 2017
 * @brief File containing extra function definitions and implementations of a Balanced Tree ADT
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "balancedTreeAPI.h"

TreeNode *rotateRightRight(TreeNode *temp)
{
    TreeNode *temp1 = temp;
    TreeNode *temp2 = temp1->right;

    temp1->right = temp2->left;
    temp2->left = temp1;

    return temp2;
}

TreeNode *rotateLeftLeft(TreeNode *temp)
{
    TreeNode *temp1 = temp;
    TreeNode *temp2 = temp1->left;

    temp1->left = temp2->right;
    temp2->right = temp1;

    return temp2;
}

TreeNode *rotateLeftRight(TreeNode *temp)
{
    TreeNode *temp1 = temp;
    TreeNode *temp2 = temp1->left;
    TreeNode *temp3 = temp2->right;

    temp1->left = temp3->right;
    temp2->right = temp3->left;
    temp3->left = temp2;
    temp3->right = temp1;

    return temp3;
}

TreeNode *rotateRightLeft(TreeNode *temp)
{
    TreeNode *temp1 = temp;
    TreeNode *temp2 = temp1->right;
    TreeNode *temp3 = temp2->left;

    temp1->right = temp3->left;
    temp2->left = temp3->right;
    temp3->right = temp2;
    temp3->left = temp1;

    return temp3;
}

void destroyNodes(Tree *toBeDeleted, TreeNode *temp)
{
    if (temp == NULL) {
        return;
    }
    if (toBeDeleted == NULL) {
        return;
    }
    void (*deleteFunc)(void *data);
    deleteFunc = toBeDeleted->destroyFP;
    if (temp->left != NULL) {
        destroyNodes(toBeDeleted, temp->left);
    }
    if (temp->right != NULL) {
        destroyNodes(toBeDeleted, temp->right);
    }
    deleteFunc(temp->data);
    free(temp);

    return;
}

int height (TreeNode *temp)
{
    if (temp == NULL) {
        return 0;
    }
    int heightLeft = height(temp->left);
    int heightRight = height(temp->right);

    if (heightLeft > heightRight) {
        return (heightLeft + 1);
    }
    else {
        return (heightRight + 1);
    }
}

void balanceTree (Tree *theTree)
{
    TreeNode *temp;

    temp = balanceNode(theTree->root);

    if (temp != theTree->root) {
        theTree->root = temp;
    }
    return;
}

int balanceFactor (TreeNode *temp)
{
    int bFactor = 0;

    if (temp->left != NULL) {
        if (temp->left != NULL) {
            bFactor += height(temp->left);
        }
    }
    if (temp->right != NULL) {
        if (temp->right != NULL) {
            bFactor -= height(temp->right);
        }
    }
    return bFactor;
}

void *balanceNode (TreeNode *temp)
{
    TreeNode *newNode = NULL;

    if (temp->left != NULL) {
        temp->left = balanceNode(temp->left);
    }
    if (temp->right != NULL) {
        temp->right = balanceNode(temp->right);
    }

    int bF = balanceFactor(temp);

    if (bF >= 2) {
        if (balanceFactor(temp->left) <= -1) {
            newNode = rotateLeftRight(temp);
        }
        else {
            newNode = rotateLeftLeft(temp);
        }
    }

    else if (bF <= -2) {
        if (balanceFactor(temp->right) >= 1) {
            newNode = rotateRightLeft(temp);
        }
        else {
            newNode = rotateRightRight(temp);
        }
    }

    else {
        newNode = temp;
    }

    return newNode;
}

TreeNode *minValueNode (TreeNode *temp)
{
    TreeNode *node = temp;

    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

TreeNode *deleteNode (Tree *theTree, TreeNode *temp, void *toBeDeleted)
{
    void (*deleteFunc)(void *data);
    deleteFunc = theTree->destroyFP;
    int (*compFunc)(void*, void*);
    compFunc = theTree->compareFP;
    void *(*copyFunc)(void *);
    copyFunc = theTree->copyFP;

    if (temp == NULL) {
        return NULL;
    }

    if (compFunc(temp->data, toBeDeleted) > 0) {
        temp->left = deleteNode(theTree, temp->left, toBeDeleted);
    }
    else if (compFunc(temp->data, toBeDeleted) < 0) {
        temp->right = deleteNode(theTree, temp->right, toBeDeleted);
    }
    else if (compFunc(temp->data, toBeDeleted) == 0) {

        if (temp->left == NULL && temp->right == NULL) {
            deleteFunc(temp->data);
            free(temp);
            temp = NULL;
        }
        else if (temp->left == NULL) {
            TreeNode *root = temp;
            temp = temp->right;
            deleteFunc(root->data);
            free(root);
        }
        else if (temp->right == NULL) {
            TreeNode *root = temp;
            temp = temp->left;
            deleteFunc(root->data);
            free(root);
        }
        else {
            TreeNode *root = minValueNode(temp->right);
            deleteFunc(temp->data);
            temp->data = copyFunc(root->data);
            temp->right = deleteNode(theTree, temp->right, (void*)root->data);
        }
    }

    return temp;
}

void inOrder (TreeNode *temp, void (*printNodeFP) (void *data))
{
    if (temp == NULL) {
        return;
    }
    else {
        inOrder(temp->left, printNodeFP);
        printNodeFP(temp->data);
        inOrder(temp->right, printNodeFP);
    }
}

void preOrder (TreeNode *temp, void (*printNodeFP) (void *data))
{
    if (temp == NULL) {
        return;
    }
    else {
        printNodeFP(temp->data);
        preOrder(temp->left, printNodeFP);
        preOrder(temp->right, printNodeFP);
    }
}

void postOrder (TreeNode *temp, void (*printNodeFP) (void *data))
{
    if (temp == NULL) {
        return;
    }
    else {
        postOrder(temp->left, printNodeFP);
        postOrder(temp->right, printNodeFP);
        printNodeFP(temp->data);
    }
}

