/**
 * @file extraFunctions.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date August 6th 2017
 * @brief File containing extra function definitions and implementations of an AVL tree
 **/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balancedTreeAPI.h"
#include "tree.h"
#include "extraFunctions.h"

char *parser(char *string, char const *delim)
{
    static char *source = NULL;
    char *temp = 0;
    char *ret = 0;

    if (string != NULL) {
        source = string;
    }

    if (source == NULL || *source == '\0') {
        return " ";
    }

    ret = source;
    temp = strpbrk(source, delim);

    if (temp != NULL) {
        *temp = 0;
        source = ++temp;
    }

    else {
        source += strlen(source);
    }

    return ret;
}

void parseData(Tree *theTree, FILE *fp)
{
    Data *temp;
    char buffer[1000];
    char line[1000];
    int c = 0;
    const char sep[2] = ",";
    char *token;

    temp = malloc(sizeof(Data));
    temp->productID = malloc(sizeof(char)*500);
    temp->productName = malloc(sizeof(char)*500);
    temp->publisher = malloc(sizeof(char)*500);
    temp->genre = malloc(sizeof(char)*500);
    temp->taxable = malloc(sizeof(char)*500);
    temp->price = malloc(sizeof(char)*500);
    temp->quantity = malloc(sizeof(float));

    fgets(buffer, 500, fp); /*skips first line*/
    fgets(line, 500, fp);

    token = parser(line, sep);
    strcpy(temp->productID, token);
    token = parser(NULL, sep);
    strcpy(temp->productName, token);
    token = parser(NULL, sep);
    strcpy(temp->publisher, token);
    token = parser(NULL, sep);
    strcpy(temp->genre, token);
    token = parser(NULL, sep);
    strcpy(temp->taxable, token);
    token = parser(NULL, sep);
    strcpy(temp->price, token);
    token = parser(NULL, sep);
    *temp->quantity = atof(token);

    while (fgets(line, sizeof(line), fp)) {

        treeInsertNode(theTree, (void*)temp);

        temp = malloc(sizeof(Data));
        temp->productID = malloc(sizeof(char)*500);
        temp->productName = malloc(sizeof(char)*500);
        temp->publisher = malloc(sizeof(char)*500);
        temp->genre = malloc(sizeof(char)*500);
        temp->taxable = malloc(sizeof(char)*500);
        temp->price = malloc(sizeof(char)*500);
        temp->quantity = malloc(sizeof(float));

        token = parser(line, sep);
        strcpy(temp->productID, token);
        token = parser(NULL, sep);
        strcpy(temp->productName, token);
        token = parser(NULL, sep);
        strcpy(temp->publisher, token);
        token = parser(NULL, sep);
        strcpy(temp->genre, token);
        token = parser(NULL, sep);
        strcpy(temp->taxable, token);
        token = parser(NULL, sep);
        strcpy(temp->price, token);
        token = parser(NULL, sep);
        *temp->quantity = atof(token);
    }
    treeInsertNode(theTree, (void*)temp);
    if (c == EOF) {
    }

}

void returnData (Tree *inventory, Tree *invoiceType, TreeNode *temp)
{
    if (temp != NULL) {
        if (temp->left != NULL) {
            returnData (inventory, invoiceType, temp->left);
        }
        if (temp->right != NULL) {
            returnData (inventory, invoiceType, temp->right);
        }
        Data *store2 = temp->data;
        Data *store = treeFindNode(inventory, temp->data);
        *store->quantity += *store2->quantity;
    }
    return;
}

void updateBinaryInventory(Tree *inventory)
{
    FILE *fp;

    fp = fopen("assets/Games", "wb+");

    fprintf(fp, "Product ID,Product Name,Publisher,Genre,Taxable,price,Quantity\n");

    updateHelp(inventory->root, fp);
    fclose(fp);
}

void updateHelp(TreeNode *temp, FILE *fp)
{
    if (temp != NULL) {
        if (temp->left != NULL) {
            updateHelp(temp->left, fp);
        }
        if (temp->right != NULL) {
            updateHelp(temp->right, fp);
        }
        Data *store = temp->data;
        fprintf(fp, "%s,%s,%s,%s,%s,%s,%f\n", store->productID, store->productName, store->publisher, store->genre, store->taxable, store->price, *store->quantity);
    }


}

int match(char string[], char lookFor[]) {
    int stringLength;
    int lookForLength;

    stringLength = strlen(string);
    lookForLength = strlen(lookFor);

    if (lookForLength > stringLength) {
        return -1;
    }

    if (strstr(string, lookFor) != NULL) {
        return 0;
    }

    return -1;
}

void *searchFunction(Tree *inventory, Tree *inventoryID, char text[500], TreeNode *temp)
{
    int *count;
    int num = 0;
    count = &num;
    Data *store;
    char option[500];
    Data *check = malloc(sizeof(Data));
    check->productID = malloc(sizeof(char)*500);

    while (1) {
        clear();
        endwin();
        printf("\033[2J");
        printf("----------------Search----------------\nProduct Name | Product ID | Price\n\n");
        searchHelper(inventory, text, inventory->root, count);

        if (*count == 0) {
            initscr();
            scrollok(stdscr,TRUE);
            clear();
            printw("\nNo products found. Press any key to continue...\n\n");
            refresh();
            getch();
            free(check->productID);
            free(check);
            return NULL;
        }
        else {
            printf("\n\nEnter a product ID or enter 'N' to exit.\n\nOption: ");
            fgets(option, 400, stdin);
            option[strlen(option)-1] = '\0';
            if (strcmp(option, "N") == 0) {
                initscr();
                scrollok(stdscr,TRUE);
                free(check->productID);
                free(check);
                return NULL;
            }
            else {
                strcpy(check->productID, option);
                store = treeFindNode(inventoryID, (void*)check);
                if (store != NULL) {
                    initscr();
                    scrollok(stdscr,TRUE);
                    return store;
                }
                else {
                    initscr();
                    scrollok(stdscr,TRUE);
                    clear();
                    printw("\nIncorrect Product ID. Press any key to continue...\n\n");
                    refresh();
                    getch();
                }
            }
        }
    }
    return NULL;
}

void searchHelper(Tree *inventory, char text[500], TreeNode *temp, int *count)
{
    if (temp != NULL) {
        if (temp->left != NULL) {
            searchHelper(inventory, text, temp->left, count);
        }
        if (temp->right != NULL) {
            searchHelper(inventory, text, temp->right, count);
        }
        Data *store = temp->data;
        int test = match(store->productName, text);
        if (test != -1) {
            printf("-%s | %s | %s\n", store->productName, store->productID, store->price);
            ++*count;
        }
    }
}









