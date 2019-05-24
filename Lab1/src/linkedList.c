/**
 * @file linkedList.c
 * @author Tejinder Purba
 * @date May 29th 2017
 * @brief File containing the function definitions and implementations of a doubly linked list  
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second))
{
    List *tempList;

    tempList = malloc(sizeof(List));

    if (tempList != NULL) {
        tempList->head = NULL;
        tempList->tail = NULL;
        tempList->printData = printFunction;
        tempList->deleteData = deleteFunction;
        tempList->compare = compareFunction;
    }
    return tempList;
}

Node *initializeNode(void *data)
{
    Node *newNode;

    newNode = malloc(sizeof(Node));

    if (newNode != NULL) {
        newNode->data = data;
        newNode->next = NULL;
        newNode->previous = NULL;
    } 
    else {
        return NULL;
    }
    return newNode;
}

void insertFront(List *list, void *toBeAdded) 
{

    Node *newNode;

    if (list == NULL) {
        return;
    }

    newNode = initializeNode(toBeAdded);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->next = list->head;
    list->head->previous = newNode;
    list->head = newNode;

}

void insertBack(List *list, void *toBeAdded) 
{

    Node *newNode;

    if (list == NULL) {
        return;
    }

    newNode = initializeNode(toBeAdded);

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->previous = list->tail;
    list->tail->next = newNode;
    list->tail = newNode;
}

void deleteList(List *list) 
{
    Node *tmpNode;
    void (*deleteFunc)(void *);
   
    if (list->deleteData != NULL) {
        deleteFunc = list->deleteData;
    }

    if (list == NULL || list->head == NULL) {
        return;
    }

    while (list->head != NULL) {
        tmpNode = list->head;
        list->head = tmpNode->next;     

        deleteFunc(tmpNode);
    }
    list->head = NULL;
    list->tail = NULL;
    return; 
}

void insertSorted(List *list, void *toBeAdded) 
{
    Node *newNode;
    Node *orgHead;
    Node *storeNode;
    int (*insertFunc)(const void*, const void*);
    int test;
    
    if (list->head == NULL || toBeAdded == NULL) {
        newNode = initializeNode(toBeAdded);
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    storeNode = malloc(sizeof(Node));
    insertFunc = list->compare;
    insertFront(list, toBeAdded);
    newNode = list->head;
    orgHead = list->head->next;

    test = insertFunc((void*)orgHead->data, (void*)toBeAdded);
    
    while (list->head != NULL) {
        if (test < 0) {
            storeNode->data = orgHead->data;
            orgHead->data = newNode->data;
            newNode->data = storeNode->data;
        }
        if (orgHead->next != NULL) {
            orgHead = orgHead->next;
            newNode = newNode->next;
            test = insertFunc((void*)orgHead->data, (void*)toBeAdded);
        }
        else if (orgHead->next == NULL) {
            free(storeNode);
            return;
        }
    }
    free(storeNode);
    return;
}

int deleteDataFromList(List *list, void *toBeDeleted)
{
    Node *tmpNode;

    if (list == NULL || toBeDeleted == NULL) {
        return EXIT_FAILURE;
    }

    void (*deleteFunc)(void *);
    deleteFunc = list->deleteData;
    tmpNode = list->head;
    while (list->head != NULL) {
        if (tmpNode->data == toBeDeleted) {
            if (tmpNode == list->head) {
                list->head = tmpNode->next;
				list->head->previous = NULL;
                deleteFunc(tmpNode);
            }
            else if (tmpNode == list->tail) {
                list->tail = tmpNode->previous;
                list->tail->next = NULL;
                deleteFunc(tmpNode);
            }
            else {
                tmpNode->previous->next = tmpNode->next;
                tmpNode->next->previous = tmpNode->previous;
                deleteFunc(tmpNode);
            }
            return EXIT_SUCCESS;
        }
        if (tmpNode->next != NULL) {
            tmpNode = tmpNode->next;
        }
        else {
            return -1;
        }
    }
    return -1;  
}

void *getFromFront(List *list)
{
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    return list->head->data;
}

void *getFromBack(List *list) 
{
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    return list->tail->data;
}

void printForward(List *list)
{
    Node *tmpNode;
    void (*printFunc)(void *);

    printFunc = list->printData;
    tmpNode = list->head;

    while (tmpNode != NULL) {
        printFunc(tmpNode);
        tmpNode = tmpNode->next;
    }
    return;
}

void printBackwards(List *list)
{
    Node *tmpNode;
    void (*printFunc)(void *);

    printFunc = list->printData;
    tmpNode = list->tail;

    while (tmpNode != NULL) {
        printFunc(tmpNode);
        tmpNode = tmpNode->previous;
    }
    return;
}
