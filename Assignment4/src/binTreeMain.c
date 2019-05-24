/**
 * @file binTreeMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date August 6th 2017
 * @brief File containing the main for the simulation of an AVL tree Point of Sale System
 **/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balancedTreeAPI.h"
#include "tree.h"
#include "extraFunctions.h"

/**This function compares user data.
 *@param data1 pointer to the data that is to be compared.
 *@param data2 pointer to the data that is to be compared.
 **/
int compareFP (void *data1, void *data2)
{
    Data *temp1 = data1;
    Data *temp2 = data2;

    return strcmp(temp1->productName, temp2->productName);
}

/**This function compares user data.
 *@param data1 pointer to the data that is to be compared.
 *@param data2 pointer to the data that is to be compared.
 **/
int compareFPID (void *data1, void *data2)
{
    Data *temp1 = data1;
    Data *temp2 = data2;

    return strcmp(temp1->productID, temp2->productID);
}

/**This function pdestroys user data.
 *@param data pointer to the data that is to be destroyed.
 **/
void destroyFP (void *data)
{
    Data *temp = data;
    free(temp->productName);
    free(temp->productID);
    free(temp->publisher);
    free(temp->genre);
    free(temp->price);
    free(temp->taxable);
    free(temp->quantity);
    free(temp);
}

/**This function copyies user data.
 *@param toBeCopy pointer to the data that is to be copied.
 **/
void *copyFP (void *toBeCopy)
{
    Data *store = toBeCopy;
    Data *temp;
    temp = malloc(sizeof(Data));
    temp->productID = malloc(sizeof(char)*500);
    temp->productName = malloc(sizeof(char)*500);
    temp->publisher = malloc(sizeof(char)*500);
    temp->genre = malloc(sizeof(char)*500);
    temp->taxable = malloc(sizeof(char)*500);
    temp->price = malloc(sizeof(char)*500);
    temp->quantity = malloc(sizeof(float));

    *temp->quantity = *store->quantity;
    strcpy(temp->price, store->price);
    strcpy(temp->taxable, store->taxable);
    strcpy(temp->genre, store->genre);
    strcpy(temp->publisher, store->publisher);
    strcpy(temp->productName, store->productName);
    strcpy(temp->productID, store->productID);

    return (void*)temp;
}

/**This function prints user data.
 *@param data pointer to the data that is to be printed.
 **/
void printNodeFP (void *data)
{
    if(data != NULL)
    {
        Data *temp = data;
        printf("%s | %.1f\n", temp->productName, *temp->quantity);
    }
}
/**This function prints user data.
 *@param data pointer to the data that is to be printed.
 **/
void printNodeFPInvoice (void *data)
{
    if(data != NULL)
    {
        Data *temp = data;
        printf("%s | %s | %s | %.1f\n", temp->productName, temp->productID, temp->price, *temp->quantity);
    }
}

/**This function is the main for the test harness.
 **/
int main(int argc, char* argv[]) {
    initscr();
    scrollok(stdscr,TRUE);

    FILE *fp = NULL;
    int choice;
    char option[100];
    char removed[100];
    Data *store;
    Data *store2;
    int quantity;
    Data *check;
    Data *check2;

    if (argc > 1) {
        char *fileName = argv[1];
        if (strcmp(fileName, "-i") == 0) {
            fp = fopen("assets/Games.csv", "r+");
        }
        else if (strcmp(fileName, "-c") == 0) {
            fp = fopen("assets/Games", "r+");
        }
        else {
            printw("\nError, incorrect inventory flag given. Exiting...\n\n");
            refresh();
            getch();
            endwin();
            fp = NULL;
            return 0;
        }
    }
    else {
        printw("\nError, no inventory flag given. Exiting...\n\n");
        refresh();
        getch();
        endwin();
        fp = NULL;
        return 0;
    }

    if (fp == NULL) {
        printw("\nError, inventory file does not exist. Exiting...\n\n");
        refresh();
        getch();
        endwin();
        return 0;
    }

    Tree *inventory = createBalancedBinTree(compareFP, destroyFP, copyFP);
    Tree *inventoryID = createBalancedBinTree(compareFPID, destroyFP, copyFP);
    parseData(inventory, fp);
    fseek(fp, 0, SEEK_SET);
    parseData(inventoryID, fp);
    fclose(fp);
    check = malloc(sizeof(Data));
    check->productName = malloc(sizeof(char)*500);
    check2 = malloc(sizeof(Data));
    check2->productID = malloc(sizeof(char)*500);

    while (1) {
        Tree *invoiceTax = NULL;
        Tree *invoiceNonTax = NULL;
        clear();
        printw("----------Point of Sale System----------\n\nSelect An Option:\n");
        printw("1. Start New Invoice\n");
        printw("2. Remove Item From Inventory\n");
        printw("3. Add Additional Inventory File\n");
        printw("4. Display Current Inventory\n");
        printw("5. Exit\n\nOption: ");
        getnstr(option, 1);
        int optionChange = atoi(option);

        switch (optionChange) {

        case 1:
            invoiceTax = createBalancedBinTree(compareFP, destroyFP, copyFP);
            invoiceNonTax = createBalancedBinTree(compareFP, destroyFP, copyFP);
            while(1) {
                clear();
                printw("\n1. Search & Add By Product Name\n");
                printw("2. Add By Product ID\n");
                printw("3. View Current Invoice\n");
                printw("4. Complete Invoice\n");
                printw("5. Cancel Invoice\n\nOption: ");
                getnstr(option, 1);
                choice = atoi(option);

                if (choice == 1) {
                    clear();
                    printw("\nEnter Product Name To Search For:\n\n");
                    refresh();
                    getnstr(option, 100);
                    strcpy(check->productName, option);
                    store = treeFindNode(inventory, (void*)check);
                    if (store == NULL) {
                        store2 = searchFunction(inventory, inventoryID, option, inventory->root);
                        if (store2 != NULL) {
                            if (*store2->quantity == 0) {
                                printw("\nNone left in stock! Press any key to continue...\n\n");
                                refresh();
                                getch();
                            }
                            else {
                                strcpy(check->productName, store2->productName);
                                store = treeFindNode(inventory, (void*)check);
                                printw("\nEnter Quantity of '%s' To Purchase:\n\n", store->productName);
                                getnstr(option, 3);
                                quantity = atoi(option);
                                if (quantity <= 0) {
                                    clear();
                                    printw("\nIncorrect quantity. Press any key to continue...\n\n");
                                    refresh();
                                    getch();
                                }
                                else {
                                    if (*store2->quantity - quantity < 0) {
                                        while (1) {
                                            printw("\nOnly %.1f left in stock, continue? (Y/N)\n\nOption: ", *store2->quantity);
                                            refresh();
                                            getnstr(option, 1);
                                            if (strcmp(option, "Y") == 0) {
                                                Data *temp2 = copyFP(store2);
                                                *temp2->quantity = *store2->quantity;
                                                if (strcmp(store2->taxable, "1") == 0) {
                                                    treeInsertNode(invoiceTax, (void*)temp2);
                                                }
                                                else if (strcmp(store2->taxable, "0") == 0) {
                                                    treeInsertNode(invoiceNonTax, (void*)temp2);
                                                }
                                                *store2->quantity = 0;
                                                *store->quantity = 0;
                                                break;
                                            }
                                            else if (strcmp(option, "N") == 0) {
                                                break;
                                            }
                                            else {
                                                clear();
                                                printw("\nIncorrect option. Press any key to try again...\n\n");
                                                refresh();
                                                getch();
                                                clear();
                                            }
                                        }
                                    }
                                    else {
                                        Data *temp2 = copyFP(store2);
                                        *temp2->quantity = quantity;
                                        *store2->quantity -= quantity;
                                        *store->quantity -= quantity;
                                        if (strcmp(store2->taxable, "1") == 0) {
                                            treeInsertNode(invoiceTax, (void*)temp2);
                                        }
                                        else if (strcmp(store2->taxable, "0") == 0) {
                                            treeInsertNode(invoiceNonTax, (void*)temp2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (*store->quantity == 0) {
                        printw("\nNone left in stock! Press any key to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else {
                        strcpy(check2->productID, store->productID);
                        store2 = treeFindNode(inventoryID, (void*)check2);

                        printw("\nEnter Quantity:\n\n");
                        getnstr(option, 3);
                        quantity = atoi(option);
                        if (quantity <= 0) {
                            clear();
                            printw("\nIncorrect quantity. Press any key to continue...\n\n");
                            refresh();
                            getch();
                        }
                        else {
                            if (*store->quantity - quantity < 0) {
                                while (1) {
                                    printw("\nOnly %.1f left in stock, continue? (Y/N)\n\nOption: ", *store->quantity);
                                    refresh();
                                    getnstr(option, 1);
                                    if (strcmp(option, "Y") == 0) {
                                        Data *temp = copyFP(store);
                                        *temp->quantity = *store->quantity;
                                        if (strcmp(store->taxable, "1") == 0) {
                                            treeInsertNode(invoiceTax, (void*)temp);
                                        }
                                        else if (strcmp(store->taxable, "0") == 0) {
                                            treeInsertNode(invoiceNonTax, (void*)temp);
                                        }
                                        *store->quantity = 0;
                                        *store2->quantity = 0;
                                        break;
                                    }
                                    else if (strcmp(option, "N") == 0) {
                                        break;
                                    }
                                    else {
                                        clear();
                                        printw("\nIncorrect option. Press any key to try again...\n\n");
                                        refresh();
                                        getch();
                                        clear();
                                    }
                                }
                            }
                            else {
                                Data *temp = copyFP(store);
                                *temp->quantity = quantity;
                                *store->quantity -= quantity;
                                *store2->quantity -= quantity;
                                if (strcmp(store->taxable, "1") == 0) {
                                    treeInsertNode(invoiceTax, (void*)temp);
                                }
                                else if (strcmp(store->taxable, "0") == 0) {
                                    treeInsertNode(invoiceNonTax, (void*)temp);
                                }
                            }
                        }
                    }

                }
                else if (choice == 2) {
                    clear();
                    printw("\nEnter Product ID To Remove:\n\n");
                    refresh();
                    getnstr(option, 100);
                    strcpy(check2->productID, option);
                    store2 = treeFindNode(inventoryID, (void*)check2);
                    if (store2 == NULL) {
                        clear();
                        printw("\nProduct not found. Press any key to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else if (*store2->quantity == 0) {
                        printw("\nNone left in stock! Press any key to continue...\n\n");
                        refresh();
                        getch();
                    }
                    else {
                        strcpy(check->productName, store2->productName);
                        store = treeFindNode(inventory, (void*)check);
                        printw("\nEnter Quantity of '%s' To Purchase:\n\n", store->productName);
                        getnstr(option, 3);
                        quantity = atoi(option);
                        if (quantity <= 0) {
                            clear();
                            printw("\nIncorrect quantity. Press any key to continue...\n\n");
                            refresh();
                            getch();
                        }
                        else {
                            if (*store2->quantity - quantity < 0) {
                                while (1) {
                                    printw("\nOnly %.1f left in stock, continue? (Y/N)\n\nOption: ", *store2->quantity);
                                    refresh();
                                    getnstr(option, 1);
                                    if (strcmp(option, "Y") == 0) {
                                        Data *temp2 = copyFP(store2);
                                        *temp2->quantity = *store2->quantity;
                                        if (strcmp(store2->taxable, "1") == 0) {
                                            treeInsertNode(invoiceTax, (void*)temp2);
                                        }
                                        else if (strcmp(store2->taxable, "0") == 0) {
                                            treeInsertNode(invoiceNonTax, (void*)temp2);
                                        }
                                        *store2->quantity = 0;
                                        *store->quantity = 0;
                                        break;
                                    }
                                    else if (strcmp(option, "N") == 0) {
                                        break;
                                    }
                                    else {
                                        clear();
                                        printw("\nIncorrect option. Press any key to try again...\n\n");
                                        refresh();
                                        getch();
                                        clear();
                                    }
                                }
                            }
                            else {
                                Data *temp2 = copyFP(store2);
                                *temp2->quantity = quantity;
                                *store2->quantity -= quantity;
                                *store->quantity -= quantity;
                                if (strcmp(store2->taxable, "1") == 0) {
                                    treeInsertNode(invoiceTax, (void*)temp2);
                                }
                                else if (strcmp(store2->taxable, "0") == 0) {
                                    treeInsertNode(invoiceNonTax, (void*)temp2);
                                }
                            }
                        }
                    }

                }
                else if (choice == 3) {
                    printf("\033[2J");
                    endwin();
                    printf("\nProduct Name | Product ID | Individual Price | Quantity\n");
                    printf("\n----------------Invoice Taxable----------------\n");
                    treeInOrderPrint(invoiceTax, printNodeFPInvoice);
                    printf("\n--------------Invoice Non-Taxable--------------\n");
                    treeInOrderPrint(invoiceNonTax, printNodeFPInvoice);
                    printf("\n\nEnter any key to continue...\n\n");
                    getch();
                    initscr();
                    scrollok(stdscr,TRUE);
                }
                else if (choice == 4) {
                    printf("\033[2J");
                    endwin();
                    printf("\nProduct Name | Quantity\n\n");
                    printf("----------------Inventory----------------\n");
                    treeInOrderPrint(inventory, printNodeFP);
                    printf("\n\nProduct Name | Product ID | Individual Price | Quantity\n");
                    printf("\n----------------Invoice Taxable----------------\n");
                    treeInOrderPrint(invoiceTax, printNodeFPInvoice);
                    printf("\n--------------Invoice Non-Taxable--------------\n");
                    treeInOrderPrint(invoiceNonTax, printNodeFPInvoice);
                    printf("\n\nEnter any key to continue...\n\n");
                    getch();
                    if (invoiceTax->root == NULL) {
                        free(invoiceTax);
                    }
                    else {
                        destroyBalancedBinTree(invoiceTax);
                    }
                    if (invoiceNonTax->root == NULL) {
                        free(invoiceNonTax);
                    }
                    else {
                        destroyBalancedBinTree(invoiceNonTax);
                    }
                    initscr();
                    scrollok(stdscr,TRUE);
                    updateBinaryInventory(inventory);
                    break;
                }
                else if (choice == 5) {
                    returnData(inventory, invoiceTax, invoiceTax->root);
                    returnData(inventory, invoiceNonTax, invoiceNonTax->root);
                    break;
                }
                else {
                    clear();
                    printw("\nIncorrect option. Press any key to try again...\n\n");
                    refresh();
                    getch();
                }
            }
            break;

        case 2:
            while (1) {
                clear();
                printw("\n1. Search & Remove By Product Name\n");
                printw("2. Remove By Product ID\n");
                printw("3. Return\n\nOption: ");
                refresh();
                getnstr(option, 1);
                choice = atoi(option);
                if (choice == 1) {
                    clear();
                    printw("\nEnter Product Name To Remove:\n\n");
                    refresh();
                    getnstr(removed, 100);
                    strcpy(check->productName, removed);
                    store = treeFindNode(inventory, (void*)check);
                    if (store == NULL) {
                        store2 = searchFunction(inventory, inventoryID, removed, inventory->root);
                        if (store2 != NULL) {
                            strcpy(check->productName, store2->productName);
                            store = treeFindNode(inventory, (void*)check);
                            while (1) {
                                clear();
                                printw("\nRemove '%s' from inventory? (Y/N)\n\nOption: ", store2->productName);
                                refresh();
                                getnstr(option, 1);
                                if (strcmp(option, "Y") == 0) {
                                    treeDeleteNode(inventory, (void*)store);
                                    treeDeleteNode(inventoryID, (void*)store2);
                                    updateBinaryInventory(inventory);
                                    break;
                                }
                                else if (strcmp(option, "N") == 0) {
                                    break;
                                }
                                else {
                                    clear();
                                    printw("\nIncorrect option. Press any key to try again...\n\n");
                                    refresh();
                                    getch();
                                }
                            }
                        }
                        break;
                    }
                    else {
                        strcpy(check2->productID, store->productID);
                        store2 = treeFindNode(inventoryID, (void*)check2);
                        while (1) {
                            clear();
                            printw("\nRemove '%s' from inventory? (Y/N)\n\nOption: ", store->productName);
                            refresh();
                            getnstr(option, 1);
                            if (strcmp(option, "Y") == 0) {
                                treeDeleteNode(inventory, (void*)store);
                                treeDeleteNode(inventoryID, (void*)store2);
                                updateBinaryInventory(inventory);
                                break;
                            }
                            else if (strcmp(option, "N") == 0) {
                                break;
                            }
                            else {
                                clear();
                                printw("\nIncorrect option. Press any key to try again...\n\n");
                                refresh();
                                getch();
                            }
                        }

                    }
                    break;
                }
                else if (choice == 2) {
                    clear();
                    printw("\nEnter Product ID To Remove:\n\n");
                    refresh();
                    getnstr(removed, 100);
                    strcpy(check2->productID, removed);
                    store2 = treeFindNode(inventoryID, (void*)check2);
                    if (store2 == NULL) {
                        clear();
                        printw("\nProduct not found. Press any key to continue...\n\n");
                        refresh();
                        getch();
                        break;
                    }
                    else {
                        strcpy(check->productName, store2->productName);
                        store = treeFindNode(inventory, (void*)check);
                        while (1) {
                            clear();
                            printw("\nRemove '%s' from inventory? (Y/N)\n\nOption: ", store2->productName);
                            refresh();
                            getnstr(option, 1);
                            if (strcmp(option, "Y") == 0) {
                                treeDeleteNode(inventory, (void*)store);
                                treeDeleteNode(inventoryID, (void*)store2);
                                updateBinaryInventory(inventory);
                                break;
                            }
                            else if (strcmp(option, "N") == 0) {
                                break;
                            }
                            else {
                                clear();
                                printw("\nIncorrect option. Press any key to try again...\n\n");
                                refresh();
                                getch();
                            }
                        }

                    }
                    break;
                }
                else if (choice == 3) {
                    break;
                }
                else {
                    clear();
                    printw("\nIncorrect option. Press any key to try again...\n\n");
                    refresh();
                    getch();
                }
            }
            break;

        case 3:
            clear();
            printw("\nEnter Inventory Filename To Open: (Include File Type)\n\n");
            refresh();
            getnstr(option, 100);
            char newFile[500];
            sprintf(newFile, "assets/%s", option);
            fp = fopen(newFile, "a+");
            if (fp == NULL) {
                clear();
                printw("\nError, file cannot be opened. Press any key to continue...\n\n");
                refresh();
                getch();
            }
            else {
                fseek(fp, 0, SEEK_END);
                choice = ftell(fp);
                if (choice == 0) {
                    clear();
                    printw("\nError, file is empty. Press any key to continue...\n\n");
                    refresh();
                    getch();
                    remove(newFile);
                }
                else {
                    endwin();
                    fseek(fp, 0, SEEK_SET);
                    parseData(inventory, fp);
                    fseek(fp, 0, SEEK_SET);
                    parseData(inventoryID, fp);
                    clear();
                    printw("\nAdded! Press any key to continue...\n\n");
                    refresh();
                    getch();
                    updateBinaryInventory(inventory);
                }
                fclose(fp);
            }
            break;

        case 4:
            printf("\033[2J");
            endwin();
            printf("Product Name | Quantity");
            printf("\n\n--------------------Inventory--------------------\n");
            treeInOrderPrint(inventory, printNodeFP);
            printf("\n\nEnter any key to continue...\n\n");
            getch();
            initscr();
            scrollok(stdscr,TRUE);
            break;

        case 5:
            destroyBalancedBinTree(inventory);
            destroyBalancedBinTree(inventoryID);
            endwin();
            printf("\033[2J");
            return 0;
            break;

        default:
            break;
        }
    }

    endwin();
    return 0;
}
