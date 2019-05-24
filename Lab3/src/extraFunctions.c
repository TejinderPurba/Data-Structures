/**
 * @file extraFunctions.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 10th 2017
 * @brief File containing extra function definitions and implementations of an array heap
 **/

#include <stdio.h>
#include <stdlib.h>
#include "extraFunctions.h"
#include "heap.h"

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) (x - 1) / 2

void heapifyDown (Heap * heap, Node * newNode)
{
    Node *lChildNode = NULL;
    Node *rChildNode = NULL;
    Node *temp;
    int catch = 0;
    int leftCatch = 0;
    int rightCatch = 0;
    int (*compFunc)(const void*, const void*);

    newNode = heap->heap[0];
    catch = 0;

    if (heap->heap[1] == NULL) {
        return;
    }

    compFunc = heap->compare;
    if (heap->type == MIN_HEAP) {
        leftCatch = LCHILD(catch);
        rightCatch = RCHILD(catch);
        while(1) {
            if (leftCatch <= heap->size) {
                lChildNode = heap->heap[leftCatch];
            }
            else {
                lChildNode = NULL;
            }
            if (rightCatch <= heap->size) {
                rChildNode = heap->heap[rightCatch];
            }
            else {
                rChildNode = NULL;
            }
            if (lChildNode != NULL && rChildNode != NULL) {
                if (compFunc(lChildNode->data, newNode->data) < 0) {
		    if (compFunc(lChildNode->data, rChildNode->data) < 0) {
                        temp = newNode;
                        heap->heap[catch] = lChildNode;
                        heap->heap[leftCatch] = temp;
                    }
		  else if (compFunc(rChildNode->data, lChildNode->data) < 0) {
                        temp = newNode;
                        heap->heap[catch] = rChildNode;
                        heap->heap[rightCatch] = temp;
                    }
                }
                else if (compFunc(rChildNode->data, newNode->data) < 0) {
                    temp = newNode;
                    heap->heap[catch] = rChildNode;
                    heap->heap[rightCatch] = temp;
                }
                else {
                    break;
                }
            }

            else if (lChildNode != NULL) {
	        if (compFunc(lChildNode->data, newNode->data) < 0) {
                    temp = newNode;
                    heap->heap[catch] = lChildNode;
                    heap->heap[leftCatch] = temp;
                }
                else {
                    break;
                }
            }

            else {
                break;
            }


            newNode = heap->heap[0];
            catch = 0;


            leftCatch = LCHILD(catch);
            rightCatch = RCHILD(catch);

            if (newNode == NULL) {
                break;
            }
        }
    }

    else if (heap->type == MAX_HEAP) {
        leftCatch = LCHILD(catch);
        rightCatch = RCHILD(catch);
        while(1) {
            if (leftCatch <= heap->size) {
                lChildNode = heap->heap[leftCatch];
            }
            else {
                lChildNode = NULL;
            }
            if (rightCatch <= heap->size) {
                rChildNode = heap->heap[rightCatch];
            }
            else {
                rChildNode = NULL;
            }
            if (lChildNode != NULL && rChildNode != NULL) {
                if (compFunc(lChildNode->data, newNode->data) > 0) {
		    if (compFunc(lChildNode->data, rChildNode->data) > 0) {
                        temp = newNode;
                        heap->heap[catch] = lChildNode;
                        heap->heap[leftCatch] = temp;
                    }
		    else if (compFunc(rChildNode->data, lChildNode->data) > 0) {
                        temp = newNode;
                        heap->heap[catch] = rChildNode;
                        heap->heap[rightCatch] = temp;
                    }
                }
                else if (compFunc(rChildNode->data, newNode->data) > 0) {
                    temp = newNode;
                    heap->heap[catch] = rChildNode;
                    heap->heap[rightCatch] = temp;
                }
                else {
                    break;
                }
            }

            else if (lChildNode != NULL) {
	        if (compFunc(lChildNode->data, newNode->data) > 0) {
                    temp = newNode;
                    heap->heap[catch] = lChildNode;
                    heap->heap[leftCatch] = temp;
                }
                else {
                    break;
                }
            }

            else {
                break;
            }

            newNode = heap->heap[0];
            catch = 0;

            leftCatch = LCHILD(catch);
            rightCatch = RCHILD(catch);

            if (newNode == NULL) {
                break;
            }
        }
    }
}

void heapifyUp (Heap * heap, Node * newNode)
{
    Node *parentNode;
    Node *temp;
    int i = 0;
    int catch = 0;
    int parentCatch = 0;
    int (*compFunc)(const void*, const void*);

    if (heap->initialSize > 1) {
        if (heap->heap[1] == NULL) {
            return;
        }
    }

    for (i = 0; i < heap->size; ++i) {
        if (heap->heap[i] == newNode) {
            catch = i;
        }
    }
    compFunc = heap->compare;
    if (heap->type == MIN_HEAP) {
        parentNode = heap->heap[PARENT(catch)];
        if (parentNode != NULL) {
	        while (compFunc(newNode->data, parentNode->data) < 0) {
                for (i = 0; i < heap->size; ++i) {
                    if (heap->heap[i] == parentNode) {
                        parentCatch = i;
                    }
                }
                temp = parentNode;
                heap->heap[parentCatch] = newNode;
                heap->heap[catch] = temp;
                for (i = 0; i < heap->size; ++i) {
                    if (heap->heap[i] == newNode) {
                        catch = i;
                    }
                }
                parentNode = heap->heap[PARENT(catch)];
                if (parentNode == NULL) {
                    break;
                }
            }
        }
    }
    else if (heap->type == MAX_HEAP) {
        parentNode = heap->heap[PARENT(catch)];
        if (parentNode != NULL) {
	    while (compFunc(newNode->data, parentNode->data) > 0) {
                for (i = 0; i < heap->size; ++i) {
                    if (heap->heap[i] == parentNode) {
                        parentCatch = i;
                    }
                }
                temp = parentNode;
                heap->heap[parentCatch] = newNode;
                heap->heap[catch] = temp;
                for (i = 0; i < heap->size; ++i) {
                    if (heap->heap[i] == newNode) {
                        catch = i;
                    }
                }
                parentNode = heap->heap[PARENT(catch)];
                if (parentNode == NULL) {
                    break;
                }
            }
        }
    }
}

