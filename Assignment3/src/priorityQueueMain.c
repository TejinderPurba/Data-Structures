/**
 * @file priorityQueueMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date July 19th 2017
 * @brief File containing the main for the simulation of a priority queue minor emergency clinic
 **/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extraFunctions.h"
#include "heap.h"
#include "priorityQueue.h"

void destroyDataFP(void *data) {
    PQNode *temp = data;

    free(temp->clientNum);
    free(temp->sympCode);
    free(temp->priorityNum);
    free(temp->procTime);
    free(temp->waitTime);
    free(temp->finishTime);
    free(temp);
    return;
}

void printNodeFP(void *toBePrinted) {
    if (toBePrinted != NULL) {
        Node *temp = toBePrinted;
        printw("\n%d \n", *(int*)temp->data);
        refresh();
    }
    return;
}

int compareFP(const void *first, const void *second) {

    const PQNode *temp = first;
    const PQNode *temp2 = second;

    return *(float*)temp->priorityNum - *(float*)temp2->priorityNum;
}

int main(int argc, char* argv[]) {

    initscr();

    float counter = 0;
    int i = 0;
    int j = 0;
    int patientCheck = 0;
    int check = 0;
    int waitTime = 0;
    Queue *patients = create(100, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    Queue *storage = create(100, MIN_HEAP, destroyDataFP, printNodeFP, compareFP);
    char clientName[101][100];
    char client[101];
    char sympCode[101][100];
    char tempPriority[101][100];
    char choice[10];
    float priority;
    PQNode *temp;
    FILE *fp;
    int rows;
    int cols;
    int patientSize = 0;
    float prevCounter = 0;
    int addCheck = 0;

    if (argc > 1) {
        char *fileName = argv[1];
        fp = fopen(fileName,"r");
    }
    else {
        fp = NULL;
    }

    if (fp == NULL) {
        printw("\nError, file cannot be opened. Exiting...\n\n");
        refresh();
        getch();
        endwin();
        destroy(patients);
        destroy(storage);
        return 0;
    }

    parseData(patients, storage, fp);
    patientSize = patients->theHeap->size;
    fclose(fp);

    getmaxyx(stdscr, rows, cols);

    clear();
    printw("\nSimulation ready. %d/%d patients loaded. \n\nEnter any key to continue...\n\n", patients->theHeap->size, patients->theHeap->size);
    refresh();
    getch();
    remove("report.txt");

    while (patientCheck <= patientSize) {
        if (patientCheck < patientSize) {
            starvation(patients);
            int optionChange = progress(patients, storage, patientCheck, patientSize, rows, cols, counter, addCheck, prevCounter);

            switch (optionChange) {

            case 1:
                clear();
                printw("Enter client name: \n\n");
                refresh();
                getnstr(clientName[addCheck], 100);
                if (strlen(clientName[addCheck]) < 1) {
                    clear();
                    printw("\nNo client name given.\n\nPress any key to continue...");
                    refresh();
                    getch();
                    break;
                }
                printw("\n\nEnter client symptom code (two letters): \n\n");
                refresh();
                getnstr(sympCode[addCheck], 2);
                if ((strcmp(sympCode[addCheck], "CV") != 0) && (strcmp(sympCode[addCheck], "HN") != 0) && (strcmp(sympCode[addCheck], "EV") != 0) && (strcmp(sympCode[addCheck], "GI") != 0) && (strcmp(sympCode[addCheck], "MH") != 0) && (strcmp(sympCode[addCheck], "NC") != 0) && (strcmp(sympCode[addCheck], "EC") != 0) && (strcmp(sympCode[addCheck], "RC") != 0) && (strcmp(sympCode[addCheck], "SK") != 0) && (strcmp(sympCode[addCheck], "SA") != 0) && (strcmp(sympCode[addCheck], "TR") != 0)) {
                    clear();
                    printw("\nInvalid symptom code.\n\nPress any key to continue...");
                    refresh();
                    getch();
                    break;
                }
                printw("\n\nEnter client priority number (1-5): \n\n");
                refresh();
                getnstr(tempPriority[addCheck], 1);
                priority = atof(tempPriority[addCheck]);
                if (priority > 5 || priority < 1) {
                    clear();
                    printw("\nInvalid priority number.\n\nPress any key to continue...");
                    refresh();
                    getch();
                    break;
                }

                while(1) {
                    clear();
                    printw("\nClient Name: %s\nSymptom Code: %s\nPriority Number: %.1f\n\nSave and continue? (Y/N)\n\n", clientName, sympCode, priority);
                    refresh();
                    getnstr(choice, 1);

                    if (strcmp(choice, "Y") == 0) {
                        ++addCheck;
                        break;
                    }
                    else if (strcmp(choice, "N") == 0) {
                        break;
                    }
                    else {
                        clear();
                        printw("Invalid choice.\n\nPress any key to continue...\n\n");
                        refresh();
                        getch();
                    }
                }

                break;

            case 2:
                clear();
                printw("\nEnter client name to remove\n\n");
                refresh();
                getnstr(client, 100);
                if (strlen(client) < 1) {
                    clear();
                    printw("\nNo client name given.\n\nPress any key to continue...\n\n");
                    refresh();
                    getch();
                    break;
                }
                i = removePatient(patients, client);
                removePatient(storage, client);
                if (i == -1) {
                    clear();
                    printw("\nClient not found.\n\nPress any key to continue...\n\n");
                    refresh();
                    getch();
                    break;
                }
                else {
                    clear();
                    printw("\nClient removed successfully.\n\nPress any key to continue...\n\n");
                    refresh();
                    getch();
                }
                --patientSize;
                break;

            case 3:
                ++counter;
                temp = patients->theHeap->heap[0]->data;
                if (counter - prevCounter == *temp->procTime) {
                    *temp->finishTime = counter;
                    ++patientCheck;
                    for (i = 1; i < patients->theHeap->size; ++i) {
                        temp = patients->theHeap->heap[i]->data;
                        ++*temp->waitTime;
                    }
                    writeToFile(patients, storage, patientCheck, counter);
                    removeMax(patients);
                    prevCounter = counter;
                    if (addCheck != 0) {
                        for (i = 0; i < addCheck; ++i) {
                            addPatient(patients, clientName[i], sympCode[i], atof(tempPriority[i]), waitTime);
                            addPatient(storage, clientName[i], sympCode[i], atof(tempPriority[i]), waitTime);
                            ++patientSize;
                        }
                        waitTime = 0;
                        addCheck = 0;
                    }
                    break;
                }
                if (addCheck != 0) {
                    ++waitTime;
                }

                for (i = 1; i < patients->theHeap->size; ++i) {
                    temp = patients->theHeap->heap[i]->data;
                    ++*temp->waitTime;
                }
                break;

            case 4:
                temp = patients->theHeap->heap[0]->data;
                check = (prevCounter + *temp->procTime) - counter;
                *temp->finishTime = prevCounter + *temp->procTime;
                ++patientCheck;
                counter = *temp->finishTime;
                prevCounter = counter;
                for (i = 1; i < patients->theHeap->size; ++i) {
                    temp = patients->theHeap->heap[i]->data;
                    *temp->waitTime += check;
                }
                writeToFile(patients, storage, patientCheck, counter);
                removeMax(patients);
                if (addCheck != 0) {
                    waitTime += check;
                    for (i = 0; i < addCheck; ++i) {
                        addPatient(patients, clientName[i], sympCode[i], atof(tempPriority[i]), waitTime);
                        addPatient(storage, clientName[i], sympCode[i], atof(tempPriority[i]), waitTime);
                        ++patientSize;
                    }
                    addCheck = 0;
                }

                break;

            case 5:
                for (j = patientCheck; j < patientSize; ++j) {
                    temp = patients->theHeap->heap[0]->data;
                    check = (prevCounter + *temp->procTime) - counter;
                    *temp->finishTime = prevCounter + *temp->procTime;
                    ++patientCheck;
                    counter = *temp->finishTime;
                    prevCounter = counter;
                    for (i = 1; i < patients->theHeap->size; ++i) {
                        temp = patients->theHeap->heap[i]->data;
                        *temp->waitTime += check;
                    }
                    writeToFile(patients, storage, patientCheck, counter);
                    removeMax(patients);
                    if (addCheck != 0) {
                        waitTime += check;
                        for (i = 0; i < addCheck; ++i) {
                            addPatient(patients, clientName[i], sympCode[i], atof(tempPriority[i]), waitTime);
                            addPatient(storage, clientName[i], sympCode[i], atof(tempPriority[i]), waitTime);
                            ++patientSize;
                        }
                        addCheck = 0;
                    }
                    starvation(patients);
                }
                writeToFile(patients, storage, patientCheck, counter);
                destroy(patients);
                destroy(storage);
                endwin();
                return 0;
                break;

            default:

                break;
            }
        }
        if (patientCheck == patientSize) {
            while(1) {
                clear();
                printw("\nAll patients treated. \n\nEnter 'Y' to continue adding patients.\nEnter 'N' to exit the simulation.\n\n");
                refresh();
                getnstr(choice, 1);
                if (strcmp(choice, "Y") == 0) {
                    clear();
                    printw("Enter client name: \n\n");
                    refresh();
                    getnstr(clientName[0], 100);
                    if (strlen(clientName[0]) < 1) {
                        clear();
                        printw("\nNo client name given.\n\nPress any key to continue...");
                        refresh();
                        getch();
                        break;
                    }
                    printw("\n\nEnter client symptom code (two letters): \n\n");
                    refresh();
                    getnstr(sympCode[0], 2);
                    if ((strcmp(sympCode[0], "CV") != 0) && (strcmp(sympCode[0], "HN") != 0) && (strcmp(sympCode[0], "EV") != 0) && (strcmp(sympCode[0], "GI") != 0) && (strcmp(sympCode[0], "MH") != 0) && (strcmp(sympCode[0], "NC") != 0) && (strcmp(sympCode[0], "EC") != 0) && (strcmp(sympCode[0], "RC") != 0) && (strcmp(sympCode[0], "SK") != 0) && (strcmp(sympCode[0], "SA") != 0) && (strcmp(sympCode[0], "TR") != 0)) {
                        clear();
                        printw("\nInvalid symptom code.\n\nPress any key to continue...");
                        refresh();
                        getch();
                        break;
                    }
                    printw("\n\nEnter client priority number (1-5): \n\n");
                    refresh();
                    getnstr(tempPriority[0], 1);
                    priority = atof(tempPriority[0]);
                    if (priority > 5 || priority < 1) {
                        clear();
                        printw("\nInvalid priority number.\n\nPress any key to continue...");
                        refresh();
                        getch();
                        break;
                    }

                    while(1) {
                        clear();
                        printw("\nClient Name: %s\nSymptom Code: %s\nPriority Number: %.1f\n\nSave and continue? (Y/N)\n\n", clientName, sympCode, priority);
                        refresh();
                        getnstr(choice, 1);

                        if (strcmp(choice, "Y") == 0) {
                            addPatient(patients, clientName[0], sympCode[0], atof(tempPriority[0]), 0);
                            addPatient(storage, clientName[0], sympCode[0], atof(tempPriority[0]), 0);
                            ++patientSize;
                            break;
                        }
                        else if (strcmp(choice, "N") == 0) {
                            break;
                        }
                        else {
                            clear();
                            printw("Invalid choice.\n\nPress any key to continue...\n\n");
                            refresh();
                            getch();
                        }
                    }
                }
                else if (strcmp(choice, "N") == 0) {
                    writeToFile(patients, storage, patientCheck, counter);
                    destroy(patients);
                    destroy(storage);
                    endwin();
                    return 0;
                }
                else {
                    clear();
                    printw("\nInvalid Choice.\n\nPress any key to try again...\n\n");
                    refresh();
                    getch();
                }
                break;
            }
        }
    }

    /*Filler to get rid of cppcheck warnings*/
    changeHeapType(storage->theHeap);
    changeHeapType(storage->theHeap);
    temp = getMinOrMax(storage->theHeap);
    if (temp == NULL) {
    }
    isEmpty(storage);
    destroy(patients);
    destroy(storage);
    endwin();
    return 0;
}
