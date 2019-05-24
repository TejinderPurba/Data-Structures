/**
 * @file linkedList.c
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing the function definitions and implementations of a doubly linked list
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "QueueADT.h"
#include "Functions.h"

List *initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted), float (*compareFunction)(const void *first,const void *second))
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
    float (*insertFunc)(const void*, const void*);
    float test;
    Node *orgHead;
    Node *storeNode;

    if (list->head == NULL) {
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
    Data *store;
    Data *store2;

    store = orgHead->data;
    store2 = toBeAdded;

    test = insertFunc((void*)store->time, (void*)store2->time);

    while (list->head != NULL) {
        if (test < 0) {
            storeNode->data = orgHead->data;
            orgHead->data = newNode->data;
            newNode->data = storeNode->data;
        }
        if (orgHead->next != NULL) {
            orgHead = orgHead->next;
            newNode = newNode->next;
            test = insertFunc((void*)store->time, (void*)store2->time);
        }
        else if (orgHead->next == NULL) {

            free(storeNode);
            return;
        }
    }


    free(storeNode);
    return;
}

void insertSortedFront(List *list, void *toBeAdded)
{
    Node *newNode;
    Node *orgHead;
    Node *storeNode;
    float (*insertFunc)(const void*, const void*);
    float test;

    if (list->head == NULL) {
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
    Data *store;
    Data *store2;

    store = orgHead->data;
    store2 = toBeAdded;

    test = insertFunc((void*)store->front, (void*)store2->front);

    while (list->head != NULL) {
        if (test < 0) {
            storeNode->data = orgHead->data;
            orgHead->data = newNode->data;
            newNode->data = storeNode->data;
        }
        if (orgHead->next != NULL) {
            orgHead = orgHead->next;
            newNode = newNode->next;
            test = insertFunc((void*)store->front, (void*)store2->front);
        }
        else if (orgHead->next == NULL) {
            free(storeNode);
            return;
        }
    }
    free(storeNode);
    return;
}

void insertSortedWait(List *list, void *toBeAdded)
{
    Node *newNode;
    Node *orgHead;
    Node *storeNode;
    float (*insertFunc)(const void*, const void*);
    float test;

    if (list->head == NULL) {
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
    Data *store;
    Data *store2;

    store = orgHead->data;
    store2 = toBeAdded;

    test = insertFunc((void*)store->wait, (void*)store2->wait);

    while (list->head != NULL) {
        if (test > 0) {
            storeNode->data = orgHead->data;
            orgHead->data = newNode->data;
            newNode->data = storeNode->data;
        }

        while (orgHead->next != NULL) {
            orgHead = orgHead->next;
            newNode = newNode->next;
            store = orgHead->data;
            test = insertFunc((void*)store->wait, (void*)store2->wait);
            if (test > 0) {
                storeNode->data = orgHead->data;
                orgHead->data = newNode->data;
                newNode->data = storeNode->data;
            }
        }

        if (orgHead->next == NULL) {
            free(storeNode);
            return;
        }
    }
    free(storeNode);
    return;
}

void printForward(List *list)
{
    Node *tmpNode;
    void (*printFunc)(void *);
    int count = 1;

    printFunc = list->printData;
    tmpNode = list->head;

    while (tmpNode != NULL) {
        printf("%d)  ", count);
        printFunc(tmpNode);
        tmpNode = tmpNode->next;
        ++count;
    }
    return;
}
