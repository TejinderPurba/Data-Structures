/**
 * @file extraFunctions.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing extra function definitions and implementations of an array heap
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "extraFunctions.h"
#include "heap.h"
#include "priorityQueue.h"

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
                        newNode = heap->heap[leftCatch];
                        catch = leftCatch;
                    }
                    else if (compFunc(rChildNode->data, lChildNode->data) < 0) {
                        temp = newNode;
                        heap->heap[catch] = rChildNode;
                        heap->heap[rightCatch] = temp;
                        newNode = heap->heap[rightCatch];
                        catch = rightCatch;
                    }
                    else if (compFunc(rChildNode->data, lChildNode->data) == 0) {
                        temp = newNode;
                        heap->heap[catch] = lChildNode;
                        heap->heap[leftCatch] = temp;
                        newNode = heap->heap[leftCatch];
                        catch = leftCatch;
                    }
                }
                else if (compFunc(rChildNode->data, newNode->data) < 0) {
                    temp = newNode;
                    heap->heap[catch] = rChildNode;
                    heap->heap[rightCatch] = temp;
                    newNode = heap->heap[rightCatch];
                    catch = rightCatch;
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
                    newNode = heap->heap[leftCatch];
                    catch = leftCatch;
                }
                else {
                    break;
                }
            }

            else {
                break;
            }


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
                        newNode = heap->heap[leftCatch];
                        catch = leftCatch;
                    }
                    else if (compFunc(rChildNode->data, lChildNode->data) > 0) {
                        temp = newNode;
                        heap->heap[catch] = rChildNode;
                        heap->heap[rightCatch] = temp;
                        newNode = heap->heap[rightCatch];
                        catch = rightCatch;
                    }
                    else if (compFunc(rChildNode->data, lChildNode->data) == 0) {
                        temp = newNode;
                        heap->heap[catch] = lChildNode;
                        heap->heap[leftCatch] = temp;
                        newNode = heap->heap[leftCatch];
                        catch = leftCatch;
                    }
                }
                else if (compFunc(rChildNode->data, newNode->data) > 0) {
                    temp = newNode;
                    heap->heap[catch] = rChildNode;
                    heap->heap[rightCatch] = temp;
                    newNode = heap->heap[rightCatch];
                    catch = rightCatch;
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
                    newNode = heap->heap[leftCatch];
                    catch = leftCatch;
                }
                else {
                    break;
                }
            }

            else {
                break;
            }

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

void parseData (Queue * temp, Queue * store, FILE * fp)
{
    PQNode *data;
    PQNode *storeData;
    int c;
    float priority;
    int random;

    srand(time(NULL));

    data = malloc(sizeof(PQNode));
    data->clientNum = malloc(sizeof(char)*101);
    data->sympCode = malloc(sizeof(char)*5);
    data->priorityNum = malloc(sizeof(float));
    data->procTime = malloc(sizeof(float));
    data->waitTime = malloc(sizeof(float));
    data->finishTime = malloc(sizeof(float));
    storeData = malloc(sizeof(PQNode));
    storeData->clientNum = malloc(sizeof(char)*101);
    storeData->sympCode = malloc(sizeof(char)*5);
    storeData->priorityNum = malloc(sizeof(float));
    storeData->procTime = malloc(sizeof(float));
    storeData->waitTime = malloc(sizeof(float));
    storeData->finishTime = malloc(sizeof(float));

    fscanf(fp, " %100s %1f %2s", data->clientNum, data->priorityNum, data->sympCode);

    strcpy(storeData->clientNum, data->clientNum);
    strcpy(storeData->sympCode, data->sympCode);
    priority = *data->priorityNum;
    *storeData->priorityNum = priority;

    random = -20 + rand() % (20 + (20));
    random = (random / 10) * 10;

    if (strcmp(data->sympCode, "CV") == 0) {
        *data->procTime = 30 + random;
        *storeData->procTime = 30 + random;
    }
    else if (strcmp(data->sympCode, "HN") == 0) {
        *data->procTime = 50 + random;
        *storeData->procTime = 50 + random;
    }
    else if (strcmp(data->sympCode, "EV") == 0) {
        *data->procTime = 50 + random;
        *storeData->procTime = 50 + random;
    }
    else if (strcmp(data->sympCode, "GI") == 0) {
        *data->procTime = 70 + random;
        *storeData->procTime = 70 + random;
    }
    else if (strcmp(data->sympCode, "MH") == 0) {
        *data->procTime = 40 + random;
        *storeData->procTime = 40 + random;
    }
    else if (strcmp(data->sympCode, "NC") == 0) {
        *data->procTime = 70 + random;
        *storeData->procTime = 70 + random;
    }
    else if (strcmp(data->sympCode, "EC") == 0) {
        *data->procTime = 30 + random;
        *storeData->procTime = 30 + random;
    }
    else if (strcmp(data->sympCode, "RC") == 0) {
        *data->procTime = 30 + random;
        *storeData->procTime = 30 + random;
    }
    else if (strcmp(data->sympCode, "SK") == 0) {
        *data->procTime = 70 + random;
        *storeData->procTime = 70 + random;
    }
    else if (strcmp(data->sympCode, "SA") == 0) {
        *data->procTime = 80 + random;
        *storeData->procTime = 80 + random;
    }
    else if (strcmp(data->sympCode, "TR") == 0) {
        *data->procTime = 30 + random;
        *storeData->procTime = 30 + random;
    }

    *data->waitTime = 0;
    *data->finishTime = 0;
    *storeData->waitTime = 0;
    *storeData->finishTime = 0;

    while ((c = fgetc(fp)) != EOF) {

        insert(temp, (void*)data);
        insert(store, (void*)storeData);

        data = malloc(sizeof(PQNode));
        data->clientNum = malloc(sizeof(char)*101);
        data->sympCode = malloc(sizeof(char)*5);
        data->priorityNum = malloc(sizeof(float));
        data->procTime = malloc(sizeof(float));
        data->waitTime = malloc(sizeof(float));
        data->finishTime = malloc(sizeof(float));
        storeData = malloc(sizeof(PQNode));
        storeData->clientNum = malloc(sizeof(char)*101);
        storeData->sympCode = malloc(sizeof(char)*5);
        storeData->priorityNum = malloc(sizeof(float));
        storeData->procTime = malloc(sizeof(float));
        storeData->waitTime = malloc(sizeof(float));
        storeData->finishTime = malloc(sizeof(float));
        fscanf(fp, " %100s %1f %2s", data->clientNum, data->priorityNum, data->sympCode);

        if (strlen(data->sympCode) == 0) {
            free(data->clientNum);
            free(data->sympCode);
            free(data->priorityNum);
            free(data->procTime);
            free(data->waitTime);
            free(data->finishTime);
            free(data);
            free(storeData->clientNum);
            free(storeData->sympCode);
            free(storeData->priorityNum);
            free(storeData->procTime);
            free(storeData->waitTime);
            free(storeData->finishTime);
            free(storeData);
            break;
        }

        strcpy(storeData->clientNum, data->clientNum);
        strcpy(storeData->sympCode, data->sympCode);
        priority = *data->priorityNum;
        *storeData->priorityNum = priority;

        random = -20 + rand() % (20 + (20));
        random = (random / 10) * 10;

        if (strcmp(data->sympCode, "CV") == 0) {
            *data->procTime = 30 + random;
            *storeData->procTime = 30 + random;
        }
        else if (strcmp(data->sympCode, "HN") == 0) {
            *data->procTime = 50 + random;
            *storeData->procTime = 50 + random;
        }
        else if (strcmp(data->sympCode, "EV") == 0) {
            *data->procTime = 50 + random;
            *storeData->procTime = 50 + random;
        }
        else if (strcmp(data->sympCode, "GI") == 0) {
            *data->procTime = 70 + random;
            *storeData->procTime = 70 + random;
        }
        else if (strcmp(data->sympCode, "MH") == 0) {
            *data->procTime = 40 + random;
            *storeData->procTime = 40 + random;
        }
        else if (strcmp(data->sympCode, "NC") == 0) {
            *data->procTime = 70 + random;
            *storeData->procTime = 70 + random;
        }
        else if (strcmp(data->sympCode, "EC") == 0) {
            *data->procTime = 30 + random;
            *storeData->procTime = 30 + random;
        }
        else if (strcmp(data->sympCode, "RC") == 0) {
            *data->procTime = 30 + random;
            *storeData->procTime = 30 + random;
        }
        else if (strcmp(data->sympCode, "SK") == 0) {
            *data->procTime = 70 + random;
            *storeData->procTime = 70 + random;
        }
        else if (strcmp(data->sympCode, "SA") == 0) {
            *data->procTime = 80 + random;
            *storeData->procTime = 80 + random;
        }
        else if (strcmp(data->sympCode, "TR") == 0) {
            *data->procTime = 30 + random;
            *storeData->procTime = 30 + random;
        }

        *data->waitTime = 0;
        *data->finishTime = 0;
        *storeData->waitTime = 0;
        *storeData->finishTime = 0;
    }

    if (c == EOF) {
    }
}

int removePatient (Queue * temp, char client[100])
{
    if (temp != NULL) {
        int i = 0;
        void (*deleteFunc)(void *data);
        deleteFunc = temp->theHeap->destroyData;
        Node *child;

        int check = -1;

        for (i = 0; i < temp->theHeap->size; ++i) {
            PQNode *store = temp->theHeap->heap[i]->data;
            if (strcmp(store->clientNum, client) == 0) {
                check = i;
                break;
            }
        }
        if (check != -1 && check != 0) {
            Node *parent = temp->theHeap->heap[check];
            if (parent == NULL) {
                return 0;
            }
            child = temp->theHeap->heap[temp->theHeap->size-1];
            temp->theHeap->heap[check] = child;
            deleteFunc(parent->data);
            free(parent);
            temp->theHeap->heap[temp->theHeap->size-1] = NULL;
            --temp->theHeap->size;
            heapifyDown(temp->theHeap, temp->theHeap->heap[check]);
            return 1;
        }
        else {
            return -1;
        }
    }
    return 0;
}

int progress(Queue *temp, Queue *store, int currPatient, int totalPatients, int rows, int cols, int counter, int patient, int prevCounter)
{

    char option[50];
    PQNode *storage;
    PQNode *pri;
    int i = 0;
    int check = 0;

    storage = temp->theHeap->heap[0]->data;
    for (i = 0; i < store->theHeap->size; ++i) {
        pri = store->theHeap->heap[i]->data;
        if (strcmp(pri->clientNum, storage->clientNum) == 0) {
            check = i;
            break;
        }
    }
    pri = store->theHeap->heap[check]->data;
    clear();

    mvprintw(0,0, "Progress: %d/%d Patients Treated", currPatient, totalPatients);
    if (patient != 0) {
        printw(" (%d In Queue To Be Added)", patient);
    }
    mvprintw(1,0, "Total Time: %d minute(s)", counter);
    mvprintw(2,0, "Next Patient: %.1f minute(s)", ((*storage->procTime + prevCounter) - counter));
    refresh();
    if (totalPatients < cols-2) {
        mvprintw(3,0, "[");
        refresh();
        int i = 0;
        for (i = 0; i < currPatient; ++i) {
            mvprintw(3,i+1, "=");
            refresh();
        }
        mvprintw(3,totalPatients+1, "]\n\n");
        refresh();
    }

    mvprintw(6,0, "[Current Patient Information]");
    mvprintw(7,0, "Client ID: %s", storage->clientNum);
    mvprintw(8,0, "Symptom Code: %s", storage->sympCode);
    mvprintw(9,0, "Priority Number (Old/New): %.1f/%.1f", *pri->priorityNum, *storage->priorityNum);

    mvprintw(12,0, "Select an option:");
    mvprintw(13,0, "------------------------------");
    mvprintw(14,0, "1) Add new patient");
    mvprintw(15,0, "2) Remove existing patient");
    mvprintw(16,0, "3) Increment one time unit");
    mvprintw(17,0, "4) Skip to next patient");
    mvprintw(18,0, "5) Complete & Exit Simulation\n\nOption: ");

    getnstr(option, 1);
    int optionChange = atoi(option);

    return optionChange;
}

void addPatient (Queue *temp, char clientName[100], char sympCode[100], float priority, int waitTime)
{
    PQNode *data;
    int random;

    srand(time(NULL));

    data = malloc(sizeof(PQNode));
    data->clientNum = malloc(sizeof(char)*101);
    data->sympCode = malloc(sizeof(char)*3);
    data->priorityNum = malloc(sizeof(float));
    data->procTime = malloc(sizeof(float));
    data->waitTime = malloc(sizeof(float));
    data->finishTime = malloc(sizeof(float));

    strcpy(data->clientNum, clientName);
    strcpy(data->sympCode, sympCode);
    *data->priorityNum = priority;

    random = -20 + rand() % (20 + (20));
    random = (random / 10) * 10;

    if (strcmp(data->sympCode, "CV") == 0) {
        *data->procTime = 30 + random;
    }
    else if (strcmp(data->sympCode, "HN") == 0) {
        *data->procTime = 50 + random;
    }
    else if (strcmp(data->sympCode, "EV") == 0) {
        *data->procTime = 50 + random;
    }
    else if (strcmp(data->sympCode, "GI") == 0) {
        *data->procTime = 70 + random;
    }
    else if (strcmp(data->sympCode, "MH") == 0) {
        *data->procTime = 40 + random;
    }
    else if (strcmp(data->sympCode, "NC") == 0) {
        *data->procTime = 70 + random;
    }
    else if (strcmp(data->sympCode, "EC") == 0) {
        *data->procTime = 30 + random;
    }
    else if (strcmp(data->sympCode, "RC") == 0) {
        *data->procTime = 30 + random;
    }
    else if (strcmp(data->sympCode, "SK") == 0) {
        *data->procTime = 70 + random;
    }
    else if (strcmp(data->sympCode, "SA") == 0) {
        *data->procTime = 80 + random;
    }
    else if (strcmp(data->sympCode, "TR") == 0) {
        *data->procTime = 30 + random;
    }

    *data->waitTime = (float)waitTime;
    *data->finishTime = 0;

    insert(temp, (void*)data);
}

void writeToFile (Queue *temp, Queue *store, int size, float counter)
{
    FILE *fp;
    int fileSize = 0;
    PQNode *tmp;
    PQNode *storage;
    int i = 0;
    int check;

    if (temp == NULL) {
        return;
    }

    fp = fopen("report.txt", "a+");
    if (fp == NULL) {
        clear();
        printw("\nError opening report file.\n\nPress any key to continue.\n\n");
        refresh();
        getch();
        return;
    }

    if (temp->theHeap->size == 0) {
        fprintf(fp, "\n\nTotal Simulation Time: %.1f minute(s)\n                       %.1f hour(s)", counter, (counter / 60));
        fclose(fp);
        return;
    }

    tmp = temp->theHeap->heap[0]->data;
    for (i = 0; i < store->theHeap->size; ++i) {
        storage = store->theHeap->heap[i]->data;
        if (strcmp(storage->clientNum, tmp->clientNum) == 0) {
            check = i;
            break;
        }
    }
    storage = store->theHeap->heap[check]->data;

    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    if (fileSize == 0) {
        fprintf(fp, "\nOrder of patients treated (first to last):\n\n[ Name ]\n| Symptom Code | Original Priority Number | Final Priority Number | Total Processing Time | Wait Time | Time Processed | Finished Time |\n\n");
    }

    fflush(fp);
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    if (fileSize > 0) {
        fprintf(fp, "[ %s ]\n|  %s  |  %.1f  |  %.1f  |  %.1f  |  %.1f  |  %.1f  |  %.1f  |\n------------------------------------------------------------------\n", tmp->clientNum, tmp->sympCode, *storage->priorityNum, *tmp->priorityNum, *tmp->procTime, *tmp->waitTime, (*tmp->finishTime - *tmp->procTime), *tmp->finishTime);

    }

    fclose(fp);
}



