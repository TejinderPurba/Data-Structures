/**
 * @file testMain.c
 * @author Tejinder Purba | 0968799 | tpurba@mail.uoguelph.ca
 * @date August 6th 2017
 * @brief File containing a main for testing of a Balanced Tree ADT
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "balancedTreeAPI.h"
#include "tree.h"
#include "extraFunctions.h"

/**This function prints user data.
 *@param data1 pointer to the data that is to be compared.
 *@param data2 pointer to the data that is to be compared.
 **/
int compareFP (void *data1, void *data2)
{
    return *(int*)data1 - *(int*)data2;
}

/**This function pdestroys user data.
 *@param data pointer to the data that is to be destroyed.
 **/
void destroyFP (void *data)
{
    free((int*)data);
}

/**This function copyies user data.
 *@param toBeCopy pointer to the data that is to be copied.
 **/
void *copyFP (void *toBeCopy)
{
    int *d1 = malloc(sizeof(int));
    *d1 = *(int*)toBeCopy;

    return (void*)d1;
}

/**This function prints user data.
 *@param data pointer to the data that is to be printed.
 **/
void printNodeFP (void *data)
{
    if(data != NULL)
    {
        printf("%d ", *(int*)data);
    }
}

/**This function is the main for the test harness.
 **/
int main() {

    int *d1 = malloc(sizeof(int));
    int *d2 = malloc(sizeof(int));
    int *d3 = malloc(sizeof(int));
    int *d4 = malloc(sizeof(int));
    int *d5 = malloc(sizeof(int));
    int *d6 = malloc(sizeof(int));
    int *d7 = malloc(sizeof(int));
    int *d10 = NULL;
    int grade = 0;
    int test = 0;
    void *store;

    *d1 = 22;
    *d2 = 21;
    *d3 = 23;
    *d4 = 18;
    *d5 = 19;
    *d6 = 14;
    *d7 = 10;

    /*
     *Test 1 Goal: To test whether the AVL tree is created and correctly allocated
     */
    printf("\nTest 1: CreateBalancedBinTree Function\n");
    Tree *temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    if (temp != NULL) {
        printf("        SUCCESS: Balanced Bin Tree created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree not created\n");
    }
    free(temp);
    temp = createBalancedBinTree(NULL, destroyFP, copyFP);
    if (temp == NULL) {
        printf("        SUCCESS: Balanced Bin Tree with NULL compare pointer not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree created\n");
    }
    temp = createBalancedBinTree(compareFP, NULL, copyFP);
    if (temp == NULL) {
        printf("        SUCCESS: Balanced Bin Tree with NULL destroy pointer not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree created\n");
    }
    temp = createBalancedBinTree(compareFP, destroyFP, NULL);
    if (temp == NULL) {
        printf("        SUCCESS: Balanced Bin Tree with NULL copy pointer not created\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree created\n");
    }
    printf("        ~~TESTS PASSED: %d/4~~\n", grade);
    destroyBalancedBinTree(temp);
    /*
     *Test 2 Goal: To test whether nodes are created and data is inserted into the AVL tree
     *             correctly
     */
    printf("\nTest 2: TreeInsertNode/CreateBalancedBinNode Function\n");
    {
        printf("        SUCCESS: Data not inserted into Empty tree\n");
        ++grade;
    }
    destroyBalancedBinTree(temp);
    temp = NULL;
    treeInsertNode(temp, (void*)d4);
    {
        printf("        SUCCESS: Data not inserted into NULL tree\n");
        ++grade;
    }
    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    treeInsertNode(temp, (void*)d10);
    {
        printf("        SUCCESS: NULL data not inserted\n");
        ++grade;
    }
    treeInsertNode(temp, (void*)d1);
    if (*(int*)temp->root->data == 22) {
        printf("        SUCCESS: Data '22' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    treeInsertNode(temp, (void*)d2);
    treePreOrderPrint(temp, printNodeFP);
    printf("\n\n");
    if (*(int*)temp->root->left->data == 21) {
        printf("        SUCCESS: Data '21' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    treeInsertNode(temp, (void*)d3);
    if (*(int*)temp->root->right->data == 23) {
        printf("        SUCCESS: Data '23' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    treeInsertNode(temp, (void*)d4);
    if (*(int*)temp->root->left->left->data == 18) {
        printf("        SUCCESS: Data '18' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    treeInsertNode(temp, (void*)d5);
    if (*(int*)temp->root->left->data == 19) {
        printf("        SUCCESS: Data '19' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    treeInsertNode(temp, (void*)d6);
    if (*(int*)temp->root->left->left->data == 14) {
        printf("        SUCCESS: Data '14' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    treeInsertNode(temp, (void*)d7);
    if (*(int*)temp->root->left->left->data == 10) {
        printf("        SUCCESS: Data '10' correctly inserted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data incorrectly inserted\n");
    }
    printf("        ~~TESTS PASSED: %d/10~~\n", grade-4);

    /*
     *Test 3 Goal: To test whether the tree is destroyed
     */
    printf("\nTest 3: DestroyBalancedBinTree Function\n");
    destroyBalancedBinTree(temp);
    if (temp->root == NULL) {
        printf("        SUCCESS: Balanced Bin Tree destroyed correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree not destroyed\n");
    }
    destroyBalancedBinTree(temp);
    if (temp->root == NULL) {
        printf("        SUCCESS: Empty Balanced Bin Tree handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty tree not handled\n");
    }
    temp = NULL;
    destroyBalancedBinTree(temp);
    if (temp == NULL) {
        printf("        SUCCESS: NULL Balanced Bin Tree handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: NULL tree not handled\n");
    }

    printf("        ~~TESTS PASSED: %d/3~~\n", grade-14);
    treePreOrderPrint(temp, printNodeFP);
    /*
     *Test 4 Goal: To test whether isEmpty function works accordingly
     */
    printf("\nTest 4: TreeIsEmpty Function\n");
    test = treeIsEmpty(temp);
    if (test == 1) {
        printf("        SUCCESS: NULL tree correctly determined\n");
        ++grade;
    }
    else {
        printf("        FAIL: NULL tree not correctly determined\n");
    }
    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    int *d11 = malloc(sizeof(int));
    *d11 = 50;
    treeInsertNode(temp, (void*)d11);
    test = treeIsEmpty(temp);
    if (test == 0) {
        printf("        SUCCESS: Filled tree correctly determined\n");
        ++grade;
    }
    else {
        printf("        FAIL: Filled tree not correctly determined\n");
    }
    destroyBalancedBinTree(temp);
    test = treeIsEmpty(temp);
    if (test == 1) {
        printf("        SUCCESS: Empty tree correctly determined\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty tree not correctly determined\n");
    }
    printf("        ~~TESTS PASSED: %d/3~~\n", grade-17);

    /*
     *Test 5 Goal: To test whether specific nodes are deleted
     */
    printf("\nTest 5: TreeDeleteNode Function\n");
    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));
    d5 = malloc(sizeof(int));
    d6 = malloc(sizeof(int));
    d7 = malloc(sizeof(int));
    int *d12 = malloc(sizeof(int));
    *d1 = 22;
    *d2 = 21;
    *d3 = 23;
    *d4 = 18;
    *d5 = 19;
    *d6 = 14;
    *d7 = 10;
    *d12 = 19;
    treeInsertNode(temp, (void*)d1);
    treeInsertNode(temp, (void*)d2);
    treeInsertNode(temp, (void*)d3);
    treeInsertNode(temp, (void*)d4);
    treeInsertNode(temp, (void*)d5);
    treeInsertNode(temp, (void*)d6);
    treeInsertNode(temp, (void*)d7);
    printf("        ***Tree populated with Test 2 data***\n");
    treeDeleteNode(temp, (void*)d7);
    store = treeFindNode(temp, (void*)d7);
    if (store == NULL) {
        printf("        SUCCESS: Data '10' successfully deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data not deleted\n");
    }
    treeDeleteNode(temp, (void*)d2);
    store = treeFindNode(temp, (void*)d2);
    if (store == NULL) {
        printf("        SUCCESS: Data '21' successfully deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data not deleted\n");
    }
    treeDeleteNode(temp, (void*)d5);
    store = treeFindNode(temp, (void*)d12);
    if (store == NULL) {
        printf("        SUCCESS: Tree root data '19' successfully deleted\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data not deleted\n");
    }
    free(d12);
    treeDeleteNode(temp, (void*)d10);
    printf("        SUCCESS: NULL data successfully handled\n");
    ++grade;
    d11 = malloc(sizeof(int));
    *d11 = 50;
    treeDeleteNode(temp, (void*)d11);
    store = treeFindNode(temp, (void*)d11);
    if (store == NULL) {
        printf("        SUCCESS: Data not in tree successfully handled\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data not handledn");
    }
    destroyBalancedBinTree(temp);
    treeDeleteNode(temp, (void*)d11);
    printf("        SUCCESS: Empty tree successfully handled\n");
    ++grade;
    temp = NULL;
    treeDeleteNode(temp, (void*)d11);
    printf("        SUCCESS: NULL tree successfully handled\n");
    ++grade;
    printf("        ~~TESTS PASSED: %d/7~~\n", grade-20);
    free(d11);

    /*
     *Test 6 Goal: To test whether tree nodes have two children
     */
    printf("\nTest 6: TreeHasTwoChildren Function\n");
    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));
    d5 = malloc(sizeof(int));
    d6 = malloc(sizeof(int));
    d7 = malloc(sizeof(int));
    *d1 = 22;
    *d2 = 21;
    *d3 = 23;
    *d4 = 18;
    *d5 = 19;
    *d6 = 14;
    *d7 = 10;

    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    test = treeHasTwoChildren(temp->root);

    if (test == 0) {
        printf("        SUCCESS: Empty tree handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty tree not handled correctly\n");
    }

    treeInsertNode(temp, (void*)d1);
    test = treeHasTwoChildren(temp->root);
    if (test == 0) {
        printf("        SUCCESS: Tree with 0 children handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree with 0 children not handled correctly\n");
    }
    treeInsertNode(temp, (void*)d2);
    test = treeHasTwoChildren(temp->root);
    if (test == 0) {
        printf("        SUCCESS: Tree with 1 child handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree with 1 child not handled correctly\n");
    }
    treeInsertNode(temp, (void*)d3);
    test = treeHasTwoChildren(temp->root);
    if (test == 1) {
        printf("        SUCCESS: Tree with 2 children handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree with 2 children not handled correctly\n");
    }
    treeInsertNode(temp, (void*)d4);
    test = treeHasTwoChildren(temp->root);
    if (test == 1) {
        printf("        SUCCESS: Tree with 2+ children handled correctly\n");
        ++grade;
    }
    else {
        printf("        FAIL: Tree with 2+ children not handled correctly\n");
    }
    treeInsertNode(temp, (void*)d5);
    treeInsertNode(temp, (void*)d6);
    treeInsertNode(temp, (void*)d7);
    destroyBalancedBinTree(temp);
    printf("        ~~TESTS PASSED: %d/5~~\n", grade-27);

    /*
     *Test 7 Goal: To test whether data can be found correctly
     */
    printf("\nTest 7: TreeFindNode Function\n");
    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));
    d5 = malloc(sizeof(int));
    d6 = malloc(sizeof(int));
    d7 = malloc(sizeof(int));
    *d1 = 22;
    *d2 = 21;
    *d3 = 23;
    *d4 = 18;
    *d5 = 19;
    *d6 = 14;
    *d7 = 10;


    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    treeInsertNode(temp, (void*)d1);
    treeInsertNode(temp, (void*)d2);
    treeInsertNode(temp, (void*)d3);
    treeInsertNode(temp, (void*)d4);
    treeInsertNode(temp, (void*)d5);
    treeInsertNode(temp, (void*)d6);
    treeInsertNode(temp, (void*)d7);

    printf("        ***Tree populated with Test 2 data***\n");
    store = treeFindNode(temp, (void*)d5);
    if (*(int*)store == 19) {
        printf("        SUCCESS: Root data '19' found successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Root data not found\n");
    }
    store = treeFindNode(temp, (void*)d6);
    if (*(int*)store == 14) {
        printf("        SUCCESS: Leaf data '14' found successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Leaf data not found\n");
    }
    d11 = malloc(sizeof(int));
    *d11 = 50;
    store = treeFindNode(temp, (void*)d11);
    if (store == NULL) {
        printf("        SUCCESS: Data not in tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Data not handled successfully\n");
    }
    store = treeFindNode(temp, (void*)d10);
    if (store == NULL) {
        printf("        SUCCESS: NULL data handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: NULL data not handled successfully\n");
    }
    destroyBalancedBinTree(temp);
    store = treeFindNode(temp, (void*)d11);
    if (store == NULL) {
        printf("        SUCCESS: Empty tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Empty tree not handled successfully\n");
    }
    temp = NULL;
    store = treeFindNode(temp, (void*)d11);
    if (store == NULL) {
        printf("        SUCCESS: NULL tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: NULL tree not handled successfully\n");
    }
    printf("        ~~TESTS PASSED: %d/6~~\n", grade-32);
    free(d11);
    /*
     *Test 8 Goal: To test whether min and max data can be found correctly
     */
    printf("\nTest 8: TreeFindMin/TreeFindMax Function\n");

    temp = NULL;
    printf("        ***Tree populated with Test 2 data***\n");
    store = treeFindMin(temp);
    if (store == NULL) {
        printf("        SUCCESS: FindMin NULL tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: FindMin NULL tree not handled successfully\n");
    }
    store = treeFindMax(temp);
    if (store == NULL) {
        printf("        SUCCESS: FindMax NULL tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: FindMax NULL tree not handled successfully\n");
    }
    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    store = treeFindMin(temp);
    if (store == NULL) {
        printf("        SUCCESS: FindMin Empty tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: FindMin Empty tree not handled successfully\n");
    }
    store = treeFindMax(temp);
    if (store == NULL) {
        printf("        SUCCESS: FindMax Empty tree handled successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: FindMax Empty tree not handled successfully\n");
    }

    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));
    d5 = malloc(sizeof(int));
    d6 = malloc(sizeof(int));
    d7 = malloc(sizeof(int));
    *d1 = 22;
    *d2 = 21;
    *d3 = 23;
    *d4 = 18;
    *d5 = 19;
    *d6 = 14;
    *d7 = 10;

    treeInsertNode(temp, (void*)d1);
    treeInsertNode(temp, (void*)d2);
    treeInsertNode(temp, (void*)d3);
    treeInsertNode(temp, (void*)d4);
    treeInsertNode(temp, (void*)d5);
    treeInsertNode(temp, (void*)d6);
    treeInsertNode(temp, (void*)d7);

    store = treeFindMin(temp);
    if (*(int*)store == 10) {
        printf("        SUCCESS: Min data '10' found successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Min data not found successfully\n");
    }
    store = treeFindMax(temp);
    if (*(int*)store == 23) {
        printf("        SUCCESS: Max data '23' found successfully\n");
        ++grade;
    }
    else {
        printf("        FAIL: Max data not found successfully\n");
    }

    destroyBalancedBinTree(temp);

    printf("        ~~TESTS PASSED: %d/6~~\n", grade-38);

    /*
     *Test 9 Goal: To test whether print outputs correctly
     */
    printf("\nTest 9: InOrder/PreOrder/PostOrder Printing Functions (Not Graded)\n");

    temp = NULL;
    printf("        ***Tree populated with Test 2 data***\n");

    destroyBalancedBinTree(temp);

    d1 = malloc(sizeof(int));
    d2 = malloc(sizeof(int));
    d3 = malloc(sizeof(int));
    d4 = malloc(sizeof(int));
    d5 = malloc(sizeof(int));
    d6 = malloc(sizeof(int));
    d7 = malloc(sizeof(int));
    *d1 = 22;
    *d2 = 21;
    *d3 = 23;
    *d4 = 18;
    *d5 = 19;
    *d6 = 14;
    *d7 = 10;
    temp = createBalancedBinTree(compareFP, destroyFP, copyFP);
    treeInsertNode(temp, (void*)d1);
    treeInsertNode(temp, (void*)d2);
    treeInsertNode(temp, (void*)d3);
    treeInsertNode(temp, (void*)d4);
    treeInsertNode(temp, (void*)d5);
    treeInsertNode(temp, (void*)d6);
    treeInsertNode(temp, (void*)d7);

    printf("        InOrderPrint Expected: 10 14 18 19 21 22 23\n                       Actual: ");
    treeInOrderPrint(temp, printNodeFP);
    printf("\n\n");
    printf("        PreOrderPrint Expected: 19 14 10 18 22 21 23\n                        Actual: ");
    treePreOrderPrint(temp, printNodeFP);
    printf("\n\n");
    printf("        PostOrderPrint Expected: 10 18 14 21 23 22 19\n                         Actual: ");
    treePostOrderPrint(temp, printNodeFP);
    printf("\n\n");
    destroyBalancedBinTree(temp);
    temp = NULL;
    printf("        NULL InOrderPrint Expected: NULL\n                            Actual: ");
    treeInOrderPrint(temp, printNodeFP);
    if (temp == NULL) {
        printf("NULL");
    }
    printf("\n\n");
    printf("        NULL PreOrderPrint Expected: NULL\n                             Actual: ");
    treePreOrderPrint(temp, printNodeFP);
    if (temp == NULL) {
        printf("NULL");
    }
    printf("\n\n");
    printf("        NULL PostOrderPrint Expected: NULL\n                              Actual: ");
    treePostOrderPrint(temp, printNodeFP);
    if (temp == NULL) {
        printf("NULL");
    }
    printf("\n");

    printf("\nFINAL GRADE: %d/44\n\n", grade);

    return 0;
}
