/**
 * @file queueMain.c
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing a main for the simulation of an intersection
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "QueueADT.h"
#include "Functions.h"

int main(int argc, char* argv[])
{

    char *fileName = argv[1];
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("\nError, file cannot be opened. Exiting...\n\n");
        return 0;
    }

    Queue *north = create(printFunction, deleteFunction, compareFunction);
    Queue *south = create(printFunction, deleteFunction, compareFunction);
    Queue *east = create(printFunction, deleteFunction, compareFunction);
    Queue *west = create(printFunction, deleteFunction, compareFunction);
    Queue *order = create(printFunction, deleteFunction, compareFunction);
    Queue *storage = create(printFunction, deleteFunction, compareFunction);
    Queue *test = create(printFunction, deleteFunction, compareFunction);

    int c;
    int carCount = 0;
    int starterCar = 0;
    int count = 1;
    int check = 0;
    int orderNum = 0;
    int i = 0;
    int avgCount = 0;
    float counter = 0.0;
    float avgWait = 0.0;
    float avgWaitN = 0.0;
    float avgWaitS = 0.0;
    float avgWaitE = 0.0;
    float avgWaitW = 0.0;
    float procTimeN = 0.0;
    float procTimeS = 0.0;
    float procTimeE = 0.0;
    float procTimeW = 0.0;
    float temp = 0.0;
    Data *data;
    Node *tempNode;
    Data *first;
    Data *store;
    Data *northStore;
    Data *southStore;
    Data *eastStore;
    Data *westStore;

    data = malloc(sizeof(Data));
    data->direction = malloc(sizeof(char));
    data->path = malloc(sizeof(char));
    data->time = malloc(sizeof(float));
    data->proc = malloc(sizeof(float));
    data->front = malloc(sizeof(float));
    data->finish = malloc(sizeof(float));
    data->wait = malloc(sizeof(float));

    fscanf(fp, " %1c %1c %10f", data->direction, data->path, data->time);
    while ((c = fgetc(fp)) != EOF) {

        if (*data->direction == 'N') {
            insertSorted(north->theList, (void*)data);
        }
        else if (*data->direction == 'S') {
            insertSorted(south->theList, (void*)data);
        }
        else if (*data->direction == 'E') {
            insertSorted(east->theList, (void*)data);
        }
        else if (*data->direction == 'W') {
            insertSorted(west->theList, (void*)data);
        }
        data = malloc(sizeof(Data));
        data->direction = malloc(sizeof(char));
        data->path = malloc(sizeof(char));
        data->time = malloc(sizeof(float));
        data->proc = malloc(sizeof(float));
        data->front = malloc(sizeof(float));
        data->finish = malloc(sizeof(float));
        data->wait = malloc(sizeof(float));
        fscanf(fp, " %1c %1c %10f", data->direction, data->path, data->time);
        ++carCount;
    }
    if (c == EOF) {
    }

    fclose(fp);

    while(orderNum != carCount) {
        ++counter;
        ++orderNum;
        int northCheck = 0;
        int southCheck = 0;
        int eastCheck = 0;
        int westCheck = 0;

        if (north->theList->head != NULL) {
            northStore = north->theList->head->data;
        }
        else {
            northStore = NULL;
        }
        if (south->theList->head != NULL) {
            southStore = south->theList->head->data;
        }
        else {
            southStore = NULL;
        }
        if (east->theList->head != NULL) {
            eastStore = east->theList->head->data;
        }
        else {
            eastStore = NULL;
        }
        if (west->theList->head != NULL) {
            westStore = west->theList->head->data;
        }
        else {
            westStore = NULL;
        }

        if(northStore != NULL && *northStore->time <= counter) {
            northCheck = 1;
        }
        if(southStore != NULL && *southStore->time <= counter) {
            southCheck = 1;
        }
        if(eastStore != NULL && *eastStore->time <= counter) {
            eastCheck = 1;
        }
        if(westStore != NULL && *westStore->time <= counter) {
            westCheck = 1;
        }
        if (northCheck == 0 && southCheck == 0 && eastCheck == 0 && westCheck == 0) {
            --orderNum;
            continue;
        }
        if (starterCar == 0) {

            if (northCheck == 1) {
                if (southCheck == 1 && eastCheck == 1 && westCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, southStore);
                    insertSorted(storage->theList, eastStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;

                }
                else if (southCheck == 1 && eastCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, southStore);
                    insertSorted(storage->theList, eastStore);

                    first = storage->theList->head->data;

                }
                else if (southCheck == 1 && westCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, southStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;

                }
                else if (eastCheck == 1 && westCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, eastStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;

                }
                else if (southCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, southStore);

                    first = storage->theList->head->data;

                }
                else if (eastCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, eastStore);

                    first = storage->theList->head->data;

                }
                else if (westCheck == 1) {
                    insertSorted(storage->theList, northStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;

                }
                else {

                    insertSorted(storage->theList, northStore);

                    first = storage->theList->head->data;
                }
            }
            else if (southCheck == 1) {
                if (eastCheck == 1 && westCheck == 1) {
                    insertSorted(storage->theList, southStore);
                    insertSorted(storage->theList, eastStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;
                }
                else if (eastCheck == 1) {
                    insertSorted(storage->theList, southStore);
                    insertSorted(storage->theList, eastStore);

                    first = storage->theList->head->data;
                }
                else if (westCheck == 1) {
                    insertSorted(storage->theList, southStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;
                }
                else {
                    insertSorted(storage->theList, southStore);

                    first = storage->theList->head->data;
                }
            }
            else if (eastCheck == 1) {
                if (westCheck == 1) {
                    insertSorted(storage->theList, eastStore);
                    insertSorted(storage->theList, westStore);

                    first = storage->theList->head->data;
                }
                else {
                    insertSorted(storage->theList, eastStore);

                    first = storage->theList->head->data;
                }
            }
            else if (westCheck == 1) {
                insertSorted(storage->theList, westStore);

                first = storage->theList->head->data;
            }
            starterCar = 1;


            if (*first->direction == 'N') {
                *northStore->front = *first->time;
                *northStore->proc = *first->time;
                if (*northStore->path == 'F') {
                    *northStore->finish = *first->time + 2;
                }
                else if (*northStore->path == 'R') {
                    *northStore->finish = *first->time + 1.5;
                }
                else if (*northStore->path == 'L') {
                    *northStore->finish = *first->time + 3.5;
                }
                *northStore->wait = 0.0;
                procTimeN = *first->time;
                enqueue(order, (void*)northStore);
                dequeue(north);
            }

            else if (*first->direction == 'S') {
                *southStore->front = *first->time;
                *southStore->proc = *first->time;
                if (*southStore->path == 'F') {
                    *southStore->finish = *first->time + 2;
                }
                else if (*southStore->path == 'R') {
                    *southStore->finish = *first->time + 1.5;
                }
                else if (*southStore->path == 'L') {
                    *southStore->finish = *first->time + 3.5;
                }
                *southStore->wait = 0.0;
                procTimeS = *first->time;
                enqueue(order, (void*)southStore);
                dequeue(south);
            }

            else if (*first->direction == 'E') {
                *eastStore->front = *first->time;
                *eastStore->proc = *first->time;
                if (*eastStore->path == 'F') {
                    *eastStore->finish = *first->time + 2;
                }
                else if (*eastStore->path == 'R') {
                    *eastStore->finish = *first->time + 1.5;
                }
                else if (*eastStore->path == 'L') {
                    *eastStore->finish = *first->time + 3.5;
                }
                *eastStore->wait = 0.0;
                procTimeE = *first->time;
                enqueue(order, (void*)eastStore);
                dequeue(east);
            }

            else if (*first->direction == 'W') {
                *westStore->front = *first->time;
                *westStore->proc = *first->time;
                if (*westStore->path == 'F') {
                    *westStore->finish = *first->time + 2;
                }
                else if (*westStore->path == 'R') {
                    *westStore->finish = *first->time + 1.5;
                }
                else if (*westStore->path == 'L') {
                    *westStore->finish = *first->time + 3.5;
                }
                *westStore->wait = 0.0;
                procTimeW = *first->time;
                enqueue(order, (void*)westStore);
                dequeue(west);
            }
            continue;

        }

        if (northCheck == 1) {

            if (southCheck == 1 && eastCheck == 1 && westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, southStore);
                insertSorted(storage->theList, eastStore);
                insertSorted(storage->theList, westStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 4; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    else if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 4);

            }
            else if (southCheck == 1 && eastCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, southStore);
                insertSorted(storage->theList, eastStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 3; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    else if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 3);
            }
            else if (southCheck == 1 && westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, southStore);
                insertSorted(storage->theList, westStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 3; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 3);
            }
            else if (eastCheck == 1 && westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, eastStore);
                insertSorted(storage->theList, westStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 3; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first =  rightOfWay(test, 3);
            }
            else if (southCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, southStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 2; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 2);
            }
            else if (eastCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, eastStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 2; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 2);
            }
            else if (westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                insertSorted(storage->theList, westStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 2; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'N') {
                        northSort(first, northStore, procTimeN, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 2);
            }
            else {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, northStore);
                first = storage->theList->head->data;

                if (*first->direction == 'N') {
                    northSort(first, northStore, procTimeN, test);
                }
                check = 1;
                first = test->theList->head->data;
            }

        }
        else if (southCheck == 1) {
            if (eastCheck == 1 && westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, southStore);
                insertSorted(storage->theList, westStore);
                insertSorted(storage->theList, eastStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 3; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    else if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 3);
            }
            else if (eastCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, southStore);
                insertSorted(storage->theList, eastStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 2; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    else if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 2);
            }
            else if (westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, southStore);
                insertSorted(storage->theList, westStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 2; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'S') {
                        southSort(first, southStore, procTimeS, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 2);
            }
            else {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, southStore);
                first = storage->theList->head->data;

                if (*first->direction == 'S') {
                    southSort(first, southStore, procTimeS, test);
                }
                check = 1;
                first = test->theList->head->data;
            }
        }
        else if (eastCheck == 1) {
            if (westCheck == 1) {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, eastStore);
                insertSorted(storage->theList, westStore);

                tempNode = storage->theList->head;
                for (i = 0; i < 2; ++i) {
                    first = tempNode->data;
                    if (*first->direction == 'E') {
                        eastSort(first, eastStore, procTimeE, test);
                    }
                    else if (*first->direction == 'W') {
                        westSort(first, westStore, procTimeW, test);
                    }
                    tempNode = tempNode->next;
                }
                check = 1;
                first = rightOfWay(test, 2);
            }
            else {
                destroy(storage);
                storage = create(printFunction, deleteFunction, compareFunction);
                destroy(test);
                test = create(printFunction, deleteFunction, compareFunction);
                insertSorted(storage->theList, eastStore);
                first = storage->theList->head->data;

                if (*first->direction == 'E') {
                    eastSort(first, eastStore, procTimeE, test);
                }
                check = 1;
                first = test->theList->head->data;
            }

        }
        else if (westCheck == 1) {
            destroy(storage);
            storage = create(printFunction, deleteFunction, compareFunction);
            destroy(test);
            test = create(printFunction, deleteFunction, compareFunction);
            insertSorted(storage->theList, westStore);
            first = storage->theList->head->data;

            if (*first->direction == 'W') {
                westSort(first, westStore, procTimeW, test);
            }
            check = 1;
            first = test->theList->head->data;
        }

        if (check == 1) {
            if (*first->direction == 'N') {
                store = order->theList->tail->data;
                *northStore->proc = *store->finish;
                if (*northStore->proc < *northStore->time) {
                    *northStore->proc = *northStore->time;
                }
                if (*northStore->path == 'F') {
                    *northStore->finish = 2 + *northStore->proc;
                }
                else if (*northStore->path == 'R') {
                    *northStore->finish = 1.5 + *northStore->proc;
                }
                else if (*northStore->path == 'L') {
                    *northStore->finish = 3.5 + *northStore->proc;
                }
                *northStore->wait = *northStore->proc - *northStore->time;
                procTimeN = *northStore->proc;
                enqueue(order, (void*)northStore);
                dequeue(north);
            }

            else if (*first->direction == 'S') {

                store = order->theList->tail->data;
                *southStore->proc = *store->finish;
                if (*southStore->proc < *southStore->time) {
                    *southStore->proc = *southStore->time;
                }
                if (*southStore->path == 'F') {
                    *southStore->finish = 2 + *southStore->proc;
                }
                else if (*southStore->path == 'R') {
                    *southStore->finish = 1.5 + *southStore->proc;
                }
                else if (*southStore->path == 'L') {
                    *southStore->finish = 3.5 + *southStore->proc;
                }
                *southStore->wait = *southStore->proc - *southStore->time;
                procTimeS = *southStore->proc;
                enqueue(order, (void*)southStore);
                dequeue(south);
            }

            else if (*first->direction == 'E') {

                store = order->theList->tail->data;
                *eastStore->proc = *store->finish;
                if (*eastStore->proc < *eastStore->time) {
                    *eastStore->proc = *eastStore->time;
                }
                if (*eastStore->path == 'F') {
                    *eastStore->finish = 2 + *eastStore->proc;
                }
                else if (*eastStore->path == 'R') {
                    *eastStore->finish = 1.5 + *eastStore->proc;
                }
                else if (*eastStore->path == 'L') {
                    *eastStore->finish = 3.5 + *eastStore->proc;
                }
                *eastStore->wait = *eastStore->proc - *eastStore->time;
                procTimeE = *eastStore->proc;
                enqueue(order, (void*)eastStore);
                dequeue(east);
            }

            else if (*first->direction == 'W') {
                store = order->theList->tail->data;
                *westStore->proc = *store->finish;
                if (*westStore->proc < *westStore->time) {
                    *westStore->proc = *westStore->time;
                }
                if (*westStore->path == 'F') {
                    *westStore->finish = 2 + *westStore->proc;
                }
                else if (*westStore->path == 'R') {
                    *westStore->finish = 1.5 + *westStore->proc;
                }
                else if (*westStore->path == 'L') {
                    *westStore->finish = 3.5 + *westStore->proc;
                }
                *westStore->wait = *westStore->proc - *westStore->time;
                procTimeW = *westStore->proc;
                enqueue(order, (void*)westStore);
                dequeue(west);
            }
            check = 0;
            store = order->theList->tail->data;
            counter = *store->finish;
        }
    }

    fp = fopen("report.txt", "a+");

    if (fp == NULL)
    {
        printf("\n**Error creating report file.**\n\n");
    }

    printf("\nOrder of cars (first to last):\n\n");
    fprintf(fp, "\nOrder of cars (first to last):\n\n");
    printForward(order->theList);

    tempNode = order->theList->head;
    while (tempNode != NULL) {
        store = tempNode->data;
        fprintf(fp, "%d)  %c %c %.2f\n", count, *(char*)store->direction, *(char*)store->path, *(float*)store->time);
        tempNode = tempNode->next;
        ++count;
    }

    destroy(storage);
    storage = create(printFunction, deleteFunction, compareFunction);
    tempNode = order->theList->head;

    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        insertSortedWait(storage->theList, first);
        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }

    if (storage->theList->head != NULL) {
        first = storage->theList->head->data;
        printf("\nMax wait time: %.2fs\n", *first->wait);
	fprintf(fp,"\nMax wait time: %.2fs\n", *first->wait);
    }

    if (order->theList->head != NULL) {
        tempNode = order->theList->head;
    }
    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        temp = temp + *first->wait;
        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }
    if (carCount != 0) {
        avgWait = (temp/carCount);
    }
    printf("\nAverage wait time: %.2fs\n", avgWait);
    fprintf(fp, "\nAverage wait time: %.2fs\n", avgWait);

    avgCount = 0;
    temp = 0;
    tempNode = order->theList->head;
    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        if (*first->direction == 'N') {
            temp = temp + *first->wait;
            ++avgCount;
        }
        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }
    if (avgCount != 0) {
        avgWaitN = (temp/avgCount);
    }
    printf("\nAverage wait time (North): %.2fs\n", avgWaitN);
    fprintf(fp, "\nAverage wait time (North): %.2fs\n", avgWaitN);

    avgCount = 0;
    temp = 0;
    tempNode = order->theList->head;
    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        if (*first->direction == 'S') {
            temp = temp + *first->wait;
            ++avgCount;
        }
        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }
    if (avgCount != 0) {
        avgWaitS = (temp/avgCount);
    }
    printf("\nAverage wait time (South): %.2fs\n", avgWaitS);
    fprintf(fp, "\nAverage wait time (South): %.2fs\n", avgWaitS);

    avgCount = 0;
    temp = 0;
    tempNode = order->theList->head;
    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        if (*first->direction == 'E') {
            temp = temp + *first->wait;
            ++avgCount;
        }
        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }
    if (avgCount != 0) {
        avgWaitE = (temp/avgCount);
    }
    printf("\nAverage wait time (East): %.2fs\n", avgWaitE);
    fprintf(fp, "\nAverage wait time (East): %.2fs\n", avgWaitE);

    avgCount = 0;
    temp = 0;
    tempNode = order->theList->head;
    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        if (*first->direction == 'W') {
            temp = temp + *first->wait;
            ++avgCount;
        }
        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }
    if (avgCount != 0) {
        avgWaitW = (temp/avgCount);
    }
    printf("\nAverage wait time (West): %.2fs\n\n", avgWaitW);
    fprintf(fp, "\nAverage wait time (West): %.2fs\n\n", avgWaitW);

    tempNode = order->theList->head;
    for (i = 0; i < carCount; ++i) {
        first = tempNode->data;
        free(first->direction);
        free(first->path);
        free(first->time);
        free(first->front);
        free(first->proc);
        free(first->finish);
        free(first->wait);
        free(first);

        if (tempNode->next != NULL) {
            tempNode = tempNode->next;
        }
    }

    if (data->direction != NULL) {
        free(data->direction);
        free(data->path);
        free(data->time);
        free(data->proc);
        free(data->wait);
        free(data->finish);
        free(data->front);
        free(data);
    }

    destroy(north);
    destroy(south);
    destroy(east);
    destroy(west);
    destroy(order);
    destroy(test);
    destroy(storage);

    fclose(fp);

    return 0;
}
