/**
 * @file hashTableMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date June 26th 2017
 * @brief File containing the main for the simulation of a hashtable password vault
 **/

#include <ncurses.h>
#include <string.h>
#include "HashTableAPI.h"
#include "ExtraFunctions.h"

#define SIZE 800

int hashFunction (size_t tableSize, char *key) {
    unsigned int hash = 0;
    int c;

    while ((c = *key++)) {
        hash = hash + c;
    }

    while (1) {
        if (hash > tableSize) {
            hash = hash - tableSize;
        }
        else {
            break;
        }
    }
    return hash;
}

void destroyData (void *data) {
    free(((dataTable*)data)->key);
    free(((dataTable*)data)->password);
    free((dataTable*)data);
    return;
}

void printData (void *toBePrinted) {
    if (toBePrinted != NULL) {
        dataTable *temp = (dataTable*)toBePrinted;
        printw("%s \n", temp->password);
    }
    return;
}

int main()
{
    HTable *storeHash = createTable(SIZE, &hashFunction, &destroyData, &printData);
    dataTable *temp = NULL;
    dataTable *temp2 = NULL;
    FILE *fp;
    char fileName[500];
    char option[50];
    char choice[10];
    int check = 0;
    int overWrite = 0;
    char storePass[1000];
    char storeKey[1000];

    initscr();
    printw("\nPassword Vault Program. \n\nEnter any key to begin...\n\n");
    refresh();
    getch();

    fp = fopen("vault", "rb+");

    if (fp == NULL) {
        clear();
        printw("\n**CAUTION**\n\nThere is no master password. It is highly recommended to set one up.\n\nPress enter to continue...\n\n");
        refresh();
        getch();
    }
    else {
        destroyTable(storeHash);
        storeHash = createTable(SIZE, &hashFunction, &destroyData, &printData);
        parseData(storeHash, fp);
        temp2 = (dataTable*)lookupData(storeHash, "Admin");

        if (temp2 == NULL) {
            clear();
            printw("\n**CAUTION**\n\nThere is no master password. It is highly recommended to set one up.\n\nPress enter to continue...\n\n");
            refresh();
            getch();
        }
        else {
            while(1) {
                clear();
                printw("\nPlease enter the master password to continue:\n\n");
                refresh();
                getnstr(storePass, 999);

                if (strcmp(storePass, temp2->password) == 0) {
                    clear();
                    printw("\nAccess Granted\n\nPress enter to continue...\n\n");
                    refresh();
                    getch();
                    break;
                }
                else {
                    clear();
                    printw("\nIncorrect Password\n\nPress enter to try again, or enter 'q' to quit...\n\n");
                    refresh();
                    getnstr(choice, 1);

                    if (strcmp(choice, "q") == 0) {
                        destroyTable(storeHash);
                        endwin();
                        return 0;
                    }
                }
            }
        }
        fclose(fp);
    }


    while(1) {

        clear();
        mvprintw(0, 0, "-----Please enter a menu option:-----\n");
        mvprintw(1, 0, "(1) Manage Passwords\n");
        mvprintw(2, 0, "(2) Setup & Change The Program Password\n");
        mvprintw(3, 0, "(3) Quit Program\n\nOption: ");
        refresh();

        getnstr(option, 1);
        int optionChange = atoi(option);
        switch(optionChange) {
        case 1:
            memset(fileName, 0, 500);
            check = 0;
            fp = NULL;
            while(check == 0) {
                overWrite = 0;
                temp2 = NULL;
                clear();
                mvprintw(0, 0, "-------Manage Passwords-------\n");
                mvprintw(1, 0, "Please enter a menu option:\n");
                mvprintw(2, 0, "(1) Create New Password File\n");
                mvprintw(3, 0, "(2) Open Existing Password File\n");
                mvprintw(4, 0, "(3) Add Password");
                mvprintw(5, 0, "(4) Remove Password\n");
                mvprintw(6, 0, "(5) Update Password\n");
                mvprintw(7, 0, "(6) Retrieve Password\n");
                mvprintw(8, 0, "(7) Return\n\nCurrent File Open: %s\n\nOption: ", fileName);
                refresh();
                getnstr(option, 1);
                optionChange = atoi(option);
                switch(optionChange) {
                case 1:
                    clear();
                    printw("\nEnter filename (Do not include file extension): ");
                    refresh();
                    getnstr(fileName, 499);
                    if (strcmp(fileName, "vault") != 0) {
                        fp = fopen(fileName, "wb+");
                        destroyTable(storeHash);
                        storeHash = createTable(SIZE, &hashFunction, &destroyData, &printData);
                        parseData(storeHash, fp);
                    }
                    else {
                        memset(fileName, 0, 500);
                        fp = NULL;
                        clear();
                        printw("\nFilename cannot be named 'vault'. Access README for more info.\n\nPress enter to continue..\n\n");
                        refresh();
                        getch();
                    }
                    break;

                case 2:
                    clear();
                    printw("\nEnter filename (Do not include file extension): ");
                    refresh();
                    getnstr(fileName, 499);
                    if (strcmp(fileName, "vault") != 0) {
                        fp = fopen(fileName, "ab+");
                        destroyTable(storeHash);
                        storeHash = createTable(SIZE, &hashFunction, &destroyData, &printData);
                        parseData(storeHash, fp);
                    }
                    else {
                        memset(fileName, 0, 500);
                        fp = NULL;
                        clear();
                        printw("\nFilename cannot be named 'vault'. Access README for more info.\n\nPress enter to continue..\n\n");
                        refresh();
                        getch();
                    }
                    break;

                case 3:
                    if (fp == NULL) {
                        clear();
                        printw("\nNo file currently open. Press enter to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else {
                        clear();
                        printw("\nEnter system name (key name):\n\n");
                        refresh();
                        getnstr(storeKey, 999);
                        printw("\nEnter password:\n\n");
                        refresh();
                        getnstr(storePass, 999);
                        temp2 = (dataTable*)lookupData(storeHash, storeKey);
                        if (temp2 == NULL) {
                            clear();
                            printw("System Name: %s \nPassword: %s\n\nSave and Continue? (Y/N)\n\n", storeKey, storePass);
                            refresh();
                            getnstr(option, 1);
                        }
                        else {
                            clear();
                            printw("System Name: %s \nPassword: %s\n\nKey Already Exists...Overwrite and Continue? (Y/N)\n\n", storeKey, storePass);
                            refresh();
                            getnstr(option, 1);
                            overWrite = 1;
                        }
                        if (strcmp(option, "Y") == 0) {
                            temp = malloc(sizeof(dataTable));
                            temp->password = malloc(sizeof(char)*strlen(storePass)+1);
                            temp->key = malloc(sizeof(char)*strlen(storeKey)+1);
                            strcpy(temp->password, storePass);
                            strcpy(temp->key, storeKey);
                            if (overWrite == 0) {
                                insertData(storeHash, temp->key, (void*)temp);
                            }
                            else if (overWrite == 1) {
                                updateData(storeHash, temp->key, (void*)temp);
                            }
                            writeToFile(storeHash, fileName);
                            clear();
                            printw("\nAdded Successfully.\n\nPress enter to continue...\n\n");
                            refresh();
                            getch();
                        }
                        else if (strcmp(option, "N") == 0) {
                            break;
                        }
                        else {
                            clear();
                            printw("\nInvalid Choice, press enter to try again...\n\n");
                            refresh();
                            getch();
                        }
                    }
                    break;

                case 4:
                    if (fp == NULL) {
                        clear();
                        printw("\nNo file currently open. Press enter to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else {
                        clear();
                        printw("\nEnter system name to remove (key name):\n\n");
                        refresh();
                        getnstr(storeKey, 999);
                        temp2 = (dataTable*)lookupData(storeHash, storeKey);
                        if (temp2 != NULL) {
                            clear();
                            printw("System Name To Remove: %s \n\nSave and Continue? (Y/N)\n\n", storeKey);
                            refresh();
                            getnstr(option, 1);

                            if (strcmp(option, "Y") == 0) {
                                removeData(storeHash, storeKey);
                                writeToFile(storeHash, fileName);
                                clear();
                                printw("\nRemoved Successfully.\n\nPress enter to continue...\n\n");
                                refresh();
                                getch();
                            }

                            else if (strcmp(option, "N") == 0) {
                                break;
                            }

                            else {
                                clear();
                                printw("\nInvalid Choice, press enter to try again...\n\n");
                                refresh();
                                getch();
                            }
                        }
                        else {
                            clear();
                            printw("\nInvalid Key.\n\nPress enter to continue...\n\n");
                            refresh();
                            getch();
                        }
                    }
                    break;

                case 5:
                    temp2 = NULL;
                    if (fp == NULL) {
                        clear();
                        printw("\nNo file currently open. Press enter to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else {
                        clear();
                        printw("\nEnter system name to update (key name):\n\n");
                        refresh();
                        getnstr(storeKey, 999);
                        temp2 = (dataTable*)lookupData(storeHash, storeKey);
                        if (temp2 != NULL) {
                            printw("\nEnter updated password:\n\n");
                            refresh();
                            getnstr(storePass, 999);
                            clear();
                            printw("System Name To Update: %s\nPassword To Update: %s \n\nSave and Continue? (Y/N)\n\n", storeKey, storePass);
                            refresh();
                            getnstr(option, 1);

                            if (strcmp(option, "Y") == 0) {
                                temp = malloc(sizeof(dataTable));
                                temp->password = malloc(sizeof(char)*strlen(storePass)+1);
                                temp->key = malloc(sizeof(char)*strlen(storeKey)+1);
                                strcpy(temp->password, storePass);
                                strcpy(temp->key, storeKey);
                                updateData(storeHash, temp->key, (void*)temp);
                                writeToFile(storeHash, fileName);
                                clear();
                                printw("\nNew Values Stored Successfully.\n\nPress enter to continue...\n\n");
                                refresh();
                                getch();

                            }

                            else if (strcmp(option, "N") == 0) {
                                break;
                            }

                            else {
                                clear();
                                printw("\nInvalid Choice, press enter to try again...\n\n");
                                refresh();
                                getch();
                            }
                        }

                        else {
                            clear();
                            printw("\nInvalid Key.\n\nPress enter to continue...\n\n");
                            refresh();
                            getch();
                        }
                    }
                    break;

                case 6:
                    if (fp == NULL) {
                        clear();
                        printw("\nNo file currently open. Press enter to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else {
                        clear();
                        printw("\nEnter system name to retrieve password for (key name):\n\n");
                        refresh();
                        getnstr(storeKey, 999);

                        temp2 = (dataTable*)lookupData(storeHash, storeKey);
                        if (temp2 == NULL) {
                            clear();
                            printw("\nPassword not found.\n\nPress enter to continue...\n\n");
                            refresh();
                            getch();
                        }
                        else {
                            clear();
                            printw("\nSystem Name: %s\n\nPassword: ", storeKey);
                            storeHash->printData((void*)temp2);
                            printw("\n\nPress enter to continue...\n\n");
                            refresh();
                            getch();
                        }

                    }
                    break;


                case 7:
                    if (fp != NULL) {
                        fclose(fp);
                    }
                    check = 1;
                    break;
                }
            }
            break;


        case 2:
            check = 0;
            temp2 = NULL;
            memset(choice, 0, 10);
            clear();
            refresh();
            fp = fopen("vault", "rb+");
            if (fp == NULL) {

                while(1) {
                    clear();
                    printw("\nNo master password set. Would you like to set a master password? (Y/N)\n\n");
                    refresh();
                    getnstr(choice, 1);
                    if (strcmp(choice, "Y") == 0) {
                        clear();
                        printw("\nEnter a password:\n\n");
                        refresh();
                        getnstr(storePass, 999);
                        while(1) {
                            clear();
                            printw("\nPassword chosen is: %s\nSave?...(Y/N)\n\n", storePass);
                            refresh();
                            getnstr(choice, 1);
                            if (strcmp(choice, "Y") == 0) {
                                temp = malloc(sizeof(dataTable));
                                temp->password = malloc(sizeof(char)*strlen(storePass)+1);
                                temp->key = malloc(sizeof(char)*strlen("Admin")+1);
                                strcpy(temp->password, storePass);
                                strcpy(temp->key, "Admin");
                                insertData(storeHash, temp->key, (void*)temp);
                                writeToFile(storeHash, "vault");
                                check = 1;
                                break;
                            }
                            else if (strcmp(choice, "N") == 0) {
                                check = 1;
                                break;
                            }
                            else {
                                clear();
                                printw("\nInvalid Choice, press enter to try again...\n\n");
                                refresh();
                                getch();
                            }
                        }
                        break;
                    }
                    else if (strcmp(choice, "N") == 0) {
                        check = 1;
                        break;
                    }
                    else {
                        clear();
                        printw("\nInvalid Choice, press enter to try again...\n\n");
                        refresh();
                        getch();
                    }
                }
            }
            if (check == 0) {
                destroyTable(storeHash);
                storeHash = createTable(SIZE, &hashFunction, &destroyData, &printData);
                parseData(storeHash, fp);
                temp2 = (dataTable*)lookupData(storeHash, "Admin");
                if (temp2 == NULL) {
                    while(1) {
                        clear();
                        printw("\nNo master password set. Would you like to set a master password? (Y/N)\n\n");
                        refresh();
                        getnstr(choice, 1);
                        if (strcmp(choice, "Y") == 0) {
                            clear();
                            printw("\nEnter a password: \n\n");
                            refresh();
                            getnstr(storePass, 999);
                            while(1) {
                                clear();
                                printw("\nPassword chosen is: %s\nSave?...(Y/N)\n\n", storePass);
                                refresh();
                                getnstr(choice, 1);
                                if (strcmp(choice, "Y") == 0) {
                                    temp = malloc(sizeof(dataTable));
                                    temp->password = malloc(sizeof(char)*strlen(storePass)+1);
                                    temp->key = malloc(sizeof(char)*strlen("Admin")+1);
                                    strcpy(temp->password, fileName);
                                    strcpy(temp->key, "Admin");
                                    insertData(storeHash, temp->key, (void*)temp);
                                    writeToFile(storeHash, "vault");
                                    check = 1;
                                    break;
                                }
                                else if (strcmp(choice, "N") == 0) {
                                    break;
                                }
                                else {
                                    clear();
                                    printw("\nInvalid Choice, press enter to try again...\n\n");
                                    refresh();
                                    getch();
                                }
                            }
                            break;
                        }
                        else if (strcmp(choice, "N") == 0) {
                            break;
                        }
                        else {
                            clear();
                            printw("\nInvalid Choice, press enter to try again...\n\n");
                            refresh();
                            getch();
                        }
                    }
                    fclose(fp);
                }
                if (temp2 != NULL) {
                    while(1) {
                        clear();
                        printw("\nMaster password set. Would you like to change the master password? (Y/N)\n\n");
                        refresh();
                        getnstr(choice, 1);
                        if (strcmp(choice, "Y") == 0) {
                            while (1) {
                                clear();
                                printw("\nEnter your current master password\n\n");
                                refresh();
                                getnstr(storePass, 999);
                                if (strcmp(storePass, temp2->password) == 0) {
                                    clear();
                                    printw("\nEnter your new master password, or enter 'remove' to remove the master password:\n");
                                    refresh();
                                    getnstr(storePass, 999);
                                    while(1) {
                                        if (strcmp(storePass, "remove") == 0) {
                                            clear();
                                            printw("\nMaster password will be removed.\n\nSave and Continue?...(Y/N)\n\n");
                                            refresh();
                                            getnstr(choice, 1);
                                            if (strcmp(choice, "Y") == 0) {
                                                removeData(storeHash, "Admin");
                                                writeToFile(storeHash, "vault");
                                                break;
                                            }
                                            else if (strcmp(choice, "N") == 0) {
                                                break;
                                            }
                                            else {
                                                clear();
                                                printw("\nInvalid Choice, press enter to try again...\n\n");
                                                refresh();
                                                getch();
                                            }

                                        }
                                        clear();
                                        printw("\nPassword chosen is: %s\nSave?...(Y/N)\n\n", storePass);
                                        refresh();
                                        getnstr(choice, 1);
                                        if (strcmp(choice, "Y") == 0) {
                                            temp = malloc(sizeof(dataTable));
                                            temp->password = malloc(sizeof(char)*strlen(storePass)+1);
                                            temp->key = malloc(sizeof(char)*strlen("Admin")+1);
                                            strcpy(temp->password, storePass);
                                            strcpy(temp->key, "Admin");
                                            updateData(storeHash, temp->key, (void*)temp);
                                            writeToFile(storeHash, "vault");
                                            break;
                                        }
                                        else if (strcmp(choice, "N") == 0) {
                                            break;
                                        }
                                        else {
                                            clear();
                                            printw("\nInvalid Choice, press enter to try again...\n\n");
                                            refresh();
                                            getch();
                                        }
                                    }
                                    break;
                                }
                                else {
                                    clear();
                                    printw("\nIncorrect password, press enter to try again or enter 'q' to exit...\n\n");
                                    refresh();
                                    getnstr(choice, 1);
                                    if (strcmp(choice, "q") == 0 || strcmp(choice, "Q") == 0) {
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        else if (strcmp(choice, "N") == 0) {
                            break;
                        }
                        else {
                            clear();
                            printw("\nInvalid Choice, press enter to try again...\n\n");
                            refresh();
                            getch();
                        }
                    }
                    fclose(fp);
                }
            }
            break;

        case 3:
            destroyTable(storeHash);
            endwin();
            return 0;
            break;

        default:
            clear();
            mvprintw(0, 0, "\nIncorrect menu item.  \n\nEnter any key to try again...\n\n");
            refresh();
            getch();
        }
    }

    endwin();
    return 0;
}
