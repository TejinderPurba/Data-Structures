/**
 * @file queueADT.c
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing the function definitions and implementations of a queue
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "QueueADT.h"
#include "Functions.h"

Queue *create(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted), float (*compareFunction)(const void *first,const void *second))
{
    Queue *temp;
    temp = malloc(sizeof(Queue));

    temp->theList = initializeList(printFunction, deleteFunction, compareFunction);
    temp->front = temp->theList->head;
    return temp;
}

void destroy(Queue *temp)
{  
    deleteList(temp->theList);
    free(temp->theList);
    free(temp->front);
    free(temp);
    return;
}

void enqueue(Queue *temp, void *toBeAdded)
{
    insertBack(temp->theList, (void*)toBeAdded);
    return;
}

void dequeue(Queue *temp)
{
    Node *tmpNode;
    void (*deleteFunc)(void *);

    if (temp->theList->deleteData != NULL) {
        deleteFunc = temp->theList->deleteData;
    }

    if (temp->theList->head->next == NULL) {
        tmpNode = temp->theList->head;
        deleteFunc(tmpNode);
        temp->theList->head = NULL;
        temp->theList->tail = NULL;
        return;
    }

    if (temp->theList->head != NULL) {
        tmpNode = temp->theList->head;
        temp->theList->head = tmpNode->next;
        temp->theList->head->previous = NULL;

        deleteFunc(tmpNode);
    }
    return;
}
