/**
 * @file functions.c
 * @author Tejinder Purba
 * @date June 5th 2017
 * @brief File containing the function definitions and implementations for manipulating queues
 **/

#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"
#include "QueueADT.h"

void printFunction(void *one)
{
    Node *test = one;
    Data *store;
    store = test->data;
    printf("%c %c %.2f \n", *(char*)store->direction, *(char*)store->path, *(float*)store->time);

    return;
}

void deleteFunction(void *one)
{
    Node *test = one;
    free(test);

    return;
}

float compareFunction(const void *one, const void *two)
{
    return *(float*)one - *(float*)two;
}


void northSort(Data *first, Data *data, float procTimeN, Queue *test)
{

    if (procTimeN > 0 && procTimeN >= *first->time) {
        *data->front = procTimeN + 1;
    }
    else {
        *data->front = *first->time;
    }
    insertSortedFront(test->theList, data);
    return;
}

void southSort(Data *first, Data *data, float procTimeS, Queue *test)
{
    if (procTimeS > 0 && procTimeS >= *first->time) {
        *data->front = procTimeS + 1;
    }
    else {
        *data->front = *first->time;
    }
    insertSortedFront(test->theList, data);
    return;
}

void eastSort(Data *first, Data *data, float procTimeE, Queue *test)
{

    if (procTimeE > 0 && procTimeE >= *first->time) {
        *data->front = procTimeE + 1;
    }
    else {
        *data->front = *first->time;
    }
    insertSortedFront(test->theList, data);
    return;
}

void westSort(Data *first, Data *data, float procTimeW, Queue *test)
{

    if (procTimeW > 0 && procTimeW >= *first->time) {
        *data->front = procTimeW + 1;
    }
    else {
        *data->front = *first->time;
    }
    insertSortedFront(test->theList, data);
    return;
}

Data *rightOfWay(Queue *queue, int amount) {


    Data *store;
    Data *store2;
    Data *store3;
    Data *store4;

    store = queue->theList->head->data;
    store2 = queue->theList->head->next->data;

    if (amount >= 3) {
        store3 = queue->theList->head->next->next->data;
    }
    if (amount == 4) {
        store4 = queue->theList->head->next->next->next->data;
    }

    if (*store->front == *store2->front) {
        if (amount >= 3) {
            if (*store2->front == *store3->front) {
                if (amount == 4) {
                    if (*store3->front == *store4->front) {
                        if (*store->direction == 'N') {
                            if (*store->path != 'L') {
                                return store;
                            }
                        }
                        else if (*store2->direction == 'N') {
                            if (*store->path != 'L') {
                                return store2;
                            }
                        }
                        else if (*store3->direction == 'N') {
                            if (*store->path != 'L') {
                                return store3;
                            }
                        }
                        else if (*store4->direction == 'N') {
                            if (*store->path != 'L') {
                                return store4;
                            }
                        }
                        else if (*store->direction == 'S') {
                            if (*store->path != 'L') {
                                return store;
                            }
                        }
                        else if (*store2->direction == 'S') {
                            if (*store2->path != 'L') {
                                return store2;
                            }
                        }
                        else if (*store3->direction == 'S') {
                            if (*store3->path != 'L') {
                                return store3;
                            }
                        }
                        else if (*store4->direction == 'S') {
                            if (*store4->path != 'L') {
                                return store4;
                            }
                        }
                        else if (*store->direction == 'E') {
                            if (*store->path != 'L') {
                                return store;
                            }
                        }
                        else if (*store2->direction == 'E') {
                            if (*store2->path != 'L') {
                                return store2;
                            }
                        }
                        else if (*store3->direction == 'E') {
                            if (*store3->path != 'L') {
                                return store3;
                            }
                        }
                        else if (*store4->direction == 'E') {
                            if (*store4->path != 'L') {
                                return store4;
                            }
                        }
                        else if (*store->direction == 'W') {
                            if (*store->path != 'L') {
                                return store;
                            }
                        }
                        else if (*store2->direction == 'W') {
                            if (*store2->path != 'L') {
                                return store2;
                            }
                        }
                        else if (*store3->direction == 'W') {
                            if (*store3->path != 'L') {
                                return store3;
                            }
                        }
                        else if (*store4->direction == 'W') {
                            if (*store4->path != 'L') {
                                return store4;
                            }
                        }

                    }
                    else {
                        if (*store->direction == 'N') {
                            if (*store2->direction != 'W' && *store3->direction != 'W') {
                                return store;
                            }
                            else if (*store2->direction == 'W' && *store3->direction != 'S') {
                                return store2;
                            }
                            else if (*store2->direction == 'W' && *store3->direction == 'S') {
                                return store3;
                            }
                            else if (*store3->direction == 'W' && *store2->direction != 'S') {
                                return store3;
                            }
                            else if (*store3->direction == 'W' && *store2->direction == 'S') {
                                return store2;
                            }
                        }
                        else if (*store->direction == 'E') {
                            if (*store2->direction != 'N' && *store3->direction != 'N') {
                                return store;
                            }
                            else if (*store2->direction == 'N' && *store3->direction != 'W') {
                                return store2;
                            }
                            else if (*store2->direction == 'N' && *store3->direction == 'W') {
                                return store3;
                            }
                            else if (*store3->direction == 'N' && *store2->direction != 'W') {
                                return store3;
                            }
                            else if (*store3->direction == 'N' && *store2->direction == 'W') {
                                return store2;
                            }
                        }
                        else if (*store->direction == 'W') {
                            if (*store2->direction != 'S' && *store3->direction != 'S') {
                                return store;
                            }
                            else if (*store2->direction == 'S' && *store3->direction != 'E') {
                                return store2;
                            }
                            else if (*store2->direction == 'S' && *store3->direction == 'E') {
                                return store3;
                            }
                            else if (*store3->direction == 'S' && *store2->direction != 'E') {
                                return store3;
                            }
                            else if (*store3->direction == 'S' && *store2->direction == 'E') {
                                return store2;
                            }
                        }
                        else if (*store->direction == 'S') {
                            if (*store2->direction != 'E' && *store3->direction != 'E') {
                                return store;
                            }
                            else if (*store2->direction == 'E' && *store3->direction != 'N') {
                                return store2;
                            }
                            else if (*store2->direction == 'E' && *store3->direction == 'N') {
                                return store3;
                            }
                            else if (*store3->direction == 'E' && *store2->direction != 'N') {
                                return store3;
                            }
                            else if (*store3->direction == 'E' && *store2->direction == 'N') {
                                return store2;
                            }
                        }
                    }
                }
                else {
                    if (*store->direction == 'N') {
                        if (*store2->direction != 'W' && *store3->direction != 'W') {
                            return store;
                        }
                        else if (*store2->direction == 'W' && *store3->direction != 'S') {
                            return store2;
                        }
                        else if (*store2->direction == 'W' && *store3->direction == 'S') {
                            return store3;
                        }
                        else if (*store3->direction == 'W' && *store2->direction != 'S') {
                            return store3;
                        }
                        else if (*store3->direction == 'W' && *store2->direction == 'S') {
                            return store2;
                        }
                    }
                    else if (*store->direction == 'E') {
                        if (*store2->direction != 'N' && *store3->direction != 'N') {
                            return store;
                        }
                        else if (*store2->direction == 'N' && *store3->direction != 'W') {
                            return store2;
                        }
                        else if (*store2->direction == 'N' && *store3->direction == 'W') {
                            return store3;
                        }
                        else if (*store3->direction == 'N' && *store2->direction != 'W') {
                            return store3;
                        }
                        else if (*store3->direction == 'N' && *store2->direction == 'W') {
                            return store2;
                        }
                    }
                    else if (*store->direction == 'W') {
                        if (*store2->direction != 'S' && *store3->direction != 'S') {
                            return store;
                        }
                        else if (*store2->direction == 'S' && *store3->direction != 'E') {
                            return store2;
                        }
                        else if (*store2->direction == 'S' && *store3->direction == 'E') {
                            return store3;
                        }
                        else if (*store3->direction == 'S' && *store2->direction != 'E') {
                            return store3;
                        }
                        else if (*store3->direction == 'S' && *store2->direction == 'E') {
                            return store2;
                        }
                    }
                    else if (*store->direction == 'S') {
                        if (*store2->direction != 'E' && *store3->direction != 'E') {
                            return store;
                        }
                        else if (*store2->direction == 'E' && *store3->direction != 'N') {
                            return store2;
                        }
                        else if (*store2->direction == 'E' && *store3->direction == 'N') {
                            return store3;
                        }
                        else if (*store3->direction == 'E' && *store2->direction != 'N') {
                            return store3;
                        }
                        else if (*store3->direction == 'E' && *store2->direction == 'N') {
                            return store2;
                        }
                    }
                }
            }

            else {
                if (*store->direction == 'N' && *store2->direction == 'E') {
                    return store;
                }
                else if (*store->direction == 'W' && *store2->direction == 'N') {
                    return store;
                }
                else if (*store->direction == 'S' && *store2->direction == 'W') {
                    return store;
                }
                else if (*store->direction == 'E' && *store2->direction == 'S') {
                    return store;
                }
                else if (*store->direction == 'N' && *store2->direction == 'W') {
                    return store2;
                }
                else if (*store->direction == 'W' && *store2->direction == 'S') {
                    return store2;
                }
                else if (*store->direction == 'S' && *store2->direction == 'E') {
                    return store2;
                }
                else if (*store->direction == 'E' && *store2->direction == 'N') {
                    return store2;
                }
                else if (*store->direction == 'N' && *store2->direction == 'S') {
                    if (*store->path == 'L' && *store2->path == 'L') {
                        return store;
                    }
                    else if (*store->path == 'L' && *store2->path != 'L') {
                        return store2;
                    }
                    else if (*store->path != 'L' && *store2->path == 'L') {
                        return store;
                    }
                    else if (*store->path != 'L' && *store2->path != 'L') {
                        return store;
                    }
                }
                else if (*store->direction == 'E' && *store2->direction == 'W') {
                    if (*store->path == 'L' && *store2->path == 'L') {
                        return store;
                    }
                    else if (*store->path == 'L' && *store2->path != 'L') {
                        return store2;
                    }
                    else if (*store->path != 'L' && *store2->path == 'L') {
                        return store;
                    }
                    else if (*store->path != 'L' && *store2->path != 'L') {
                        return store;
                    }
                }
                else if (*store->direction == 'S' && *store2->direction == 'N') {
                    if (*store->path == 'L' && *store2->path == 'L') {
                        return store2;
                    }
                    else if (*store->path == 'L' && *store2->path != 'L') {
                        return store;
                    }
                    else if (*store->path != 'L' && *store2->path == 'L') {
                        return store2;
                    }
                    else if (*store->path != 'L' && *store2->path != 'L') {
                        return store2;
                    }
                }
                else if (*store->direction == 'W' && *store2->direction == 'E') {
                    if (*store->path == 'L' && *store2->path == 'L') {
                        return store2;
                    }
                    else if (*store->path == 'L' && *store2->path != 'L') {
                        return store;
                    }
                    else if (*store->path != 'L' && *store2->path == 'L') {
                        return store2;
                    }
                    else if (*store->path != 'L' && *store2->path != 'L') {
                        return store2;
                    }
                }
            }
        }
        else {
            if (*store->direction == 'N' && *store2->direction == 'E') {
                return store;
            }
            else if (*store->direction == 'W' && *store2->direction == 'N') {
                return store;
            }
            else if (*store->direction == 'S' && *store2->direction == 'W') {
                return store;
            }
            else if (*store->direction == 'E' && *store2->direction == 'S') {
                return store;
            }
            else if (*store->direction == 'N' && *store2->direction == 'W') {
                return store2;
            }
            else if (*store->direction == 'W' && *store2->direction == 'S') {
                return store2;
            }
            else if (*store->direction == 'S' && *store2->direction == 'E') {
                return store2;
            }
            else if (*store->direction == 'E' && *store2->direction == 'N') {
                return store2;
            }
            else if (*store->direction == 'N' && *store2->direction == 'S') {
                if (*store->path == 'L' && *store2->path == 'L') {
                    return store;
                }
                else if (*store->path == 'L' && *store2->path != 'L') {
                    return store2;
                }
                else if (*store->path != 'L' && *store2->path == 'L') {
                    return store;
                }
                else if (*store->path != 'L' && *store2->path != 'L') {
                    return store;
                }
            }
            else if (*store->direction == 'E' && *store2->direction == 'W') {
                if (*store->path == 'L' && *store2->path == 'L') {
                    return store;
                }
                else if (*store->path == 'L' && *store2->path != 'L') {
                    return store2;
                }
                else if (*store->path != 'L' && *store2->path == 'L') {
                    return store;
                }
                else if (*store->path != 'L' && *store2->path != 'L') {
                    return store;
                }
            }
            else if (*store->direction == 'S' && *store2->direction == 'N') {
                if (*store->path == 'L' && *store2->path == 'L') {
                    return store2;
                }
                else if (*store->path == 'L' && *store2->path != 'L') {
                    return store;
                }
                else if (*store->path != 'L' && *store2->path == 'L') {
                    return store2;
                }
                else if (*store->path != 'L' && *store2->path != 'L') {
                    return store2;
                }
            }
            else if (*store->direction == 'W' && *store2->direction == 'E') {
                if (*store->path == 'L' && *store2->path == 'L') {
                    return store2;
                }
                else if (*store->path == 'L' && *store2->path != 'L') {
                    return store;
                }
                else if (*store->path != 'L' && *store2->path == 'L') {
                    return store2;
                }
                else if (*store->path != 'L' && *store2->path != 'L') {
                    return store2;
                }
            }
        }

    }
    return store;
}

