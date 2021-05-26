//
// Created by Jarrett Fok on 4/1/21.
//
#include "stack.h"
#include "node.h"
#include <stdbool.h>
#include <malloc.h>


//Global variables
struct node* HEAD = NULL;
struct node* node_Walker = NULL;
struct node* nodePop1 = NULL;
struct node* nodePop2 = NULL;
struct node* delete_node = NULL;
struct node* delete_node2 = NULL;
struct node* operationNumberNode_p = NULL;

//Function to push stack
//I changed it to return a bool to see whether or not the function created a node
bool push(node* newNode){
    int precedenceCounter = 0;
    //Will not push node if newNode is NULL, returns false
    if(newNode == NULL){
        return false;
    }
        //Will set HEAD to newNode if HEAD is NULL, returns true
    else if(HEAD == NULL){
        HEAD = newNode;
        node_Walker = newNode;
        return true;
    }
        //Will push the new node in the reverse order, returns true
        //Will require a function to reverse the order, see reverseStack() function
    else{
        node_Walker = newNode;
        node_Walker->next = HEAD;
        HEAD = newNode;
        return true;
    }
}
//Function to pop stack
node* pop(){
    //Holds the next pointer of the popped Node
    nodePop2 = HEAD;
    if(HEAD == NULL){
        return -1;
    }
    else{
        nodePop1 = HEAD->next;
        HEAD->next = NULL;
    }

    //new
    HEAD = nodePop1;

    //Returns Node
    return nodePop2;
}
//Function to peek the stack
node* peek(){
    //Returns current HEAD
    return HEAD;
}
char charPeek(){
    return HEAD->contents.operator;
}
//Function to clear the entire stack
void clearStack(){
    //Assigns first deleted Node to current HEAD
    delete_node = HEAD;

    //While loop until the end of the stack
    while (delete_node != NULL){
        delete_node2 = delete_node->next;
        HEAD = delete_node2;
        free(delete_node);
        delete_node = HEAD;
    }
}
//Function to print the entire stack
void printStack(){
    //prints stack haha through a while loop traversing the array without popping
    struct node* node_p1 = NULL;
    node_p1 = HEAD;

    //While loop until the end of the stack
    while(node_p1 != NULL) {
        printf("%c \n", node_p1->contents.operator);
        node_p1 = node_p1->next;
    }

}
//Function to reverse the stack
//Helper function needed due to method we pushed to stack
void reverseStack(){
    //Variables to hold current HEAD
    struct node* nodeReverse1 = HEAD;
    struct node* nodeReverse2 = NULL;

    //While loop until the end of the stack
    while (nodeReverse1 != NULL) {
        struct node* node_nextTemp = nodeReverse1->next;
        nodeReverse1->next = nodeReverse2;
        nodeReverse2 = nodeReverse1;
        nodeReverse1 = node_nextTemp;
    }
    //Assigns HEAD to the new order
    HEAD = nodeReverse2;
}
//Function to find number of operations relative to numbers
//Returns true if there is exactly 1 more number than operations, else returns false
bool operationNumber(){
    //Variables to hold operation, numbers, and total
    int operations = 0;
    int numbers = 0;
    int total = 0;

    //Assigns operationNumberNode_p to HEAD
    operationNumberNode_p = HEAD;

    //While loop until the end of the stack
    while(operationNumberNode_p != NULL) {
        //If type is a number, increment number count
        if(operationNumberNode_p->type == 0){
            numbers++;
        }
            //If type is an operation, increment operation count
        else{
            operations++;
        }
        operationNumberNode_p = operationNumberNode_p->next;
    }
    //Finds total by the difference of operation and numbers
    total = numbers - operations;
    if(total == 1){
        return true;
    }
    else{
        return false;
    }
}
//Function to find precedence of node
//Return precedence value
int getPrecedence(char operator){
    int precedence;
    //switch statement
    switch(operator){
        case '^':
            precedence = 3;
            break;
        case '*':
        case '/':
            precedence = 2;
            break;
        case '+':
        case '-':
            precedence = 1;
            break;
        default:
            precedence = 0;
    }
    //returns precedence value
    return precedence;
}