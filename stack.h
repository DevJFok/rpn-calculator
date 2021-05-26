//
// Created by Jarrett Fok  on 4/1/21.
//

#ifndef PS5_STACK_H
#define PS5_STACK_H
#include <stdbool.h>
#include "node.h"

//Push function, returns bool
bool push(node* node);
//Pop function
node* pop();
//Peek function
node* peek();
//new peek function
char charPeek();
//Helper Function, clearStack function
void clearStack();
//Helper Function, printStack function
void printStack();
//Helper Function, reverseStack function
void reverseStack();
//Helper Function, operationNumber function, returns bool
bool operationNumber();
//Helper Function, get precedence function
int getPrecedence(char operator);


#endif //PS5_STACK_H
