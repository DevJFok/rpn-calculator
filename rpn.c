//
// Created by Jarrett Fok on 4/23/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "rpn.h"
#include "node.h"
#include "stack.h"
#include "errors.h"
//Enum for the different types
enum type {
    NUMBER, PLUS, MINUS, MULTIPLY, DIVIDE, POWER, OPARENTHESES,CPARENTHESES
};
struct node* rpnNode_Walker = NULL;
//Function to evaluate the stack
double evaluate(char *expression, int *status) {
    //Returns error if expression length is 0 or expression is NULL
    if(strlen(expression) == 0 || expression == NULL){
        *status = SOMETHINGMISSING;
        return -999;
    }

    //Clear stack to remove previous stack information
    clearStack();

    //Variables
    char *token;

    //Token to find the value and type of node
    token = strtok(expression, " ");

    //While loop until token is NULL
    while (token != NULL) {
        //Placeholder variable for type
        int type = 0;
        //Switch statement based on token value
        switch (*token){
            case '+':
                //Assigns type as PLUS
                type = PLUS;
                break;
            case '-':
                //Assigns type as MINUS
                type = MINUS;
                break;
            case '*':
                //Assigns type as MULTIPLY
                type = MULTIPLY;
                break;
            case '/':
                //Assigns type as DIVIDE
                type = DIVIDE;
                break;
            case '^':
                //Assigns type as POWER
                type = POWER;
                break;
            default:
                //Assigns type as NUMBER as default
                type = NUMBER;
        }

        //Using the parsed token, use the information to create nodes into the stack
        if (type == NUMBER) {
            //Pushes number and type NUMBER
            double value = atof(token);
            push(createNode(value, type));
        }
        else {
            //Pushes type of operator with value of -1
            push(createNode(-1, type));
        }

        //Find the next token
        token = strtok(NULL, " ");
    }

    //Reverse the stack to place it in the appropriate order
    reverseStack();

    //Runs the mathOpertaion function if condition met
    //Further Error checking
    if(operationNumber()) {
        mathOperation(status);
    }
    else if (peek()->next != NULL) {
        *status = BADENTRY;
        return -999;
    }
    else{
        *status = BADENTRY;
        return -999;
    }
    //Returns the value of the top node
    return peek()->contents.value;


}
//Helper function to conduct the math operations
double mathOperation(int *status) {
    //Additional error checking
    if (peek() == NULL || peek()->type != 0) {
        *status = ERRNULLPTR;
        return -999;
    }

    //While loop until the next pointer is NULL
    while (peek()->next != NULL) {
        //Pops first two nodes to get number values
        node* nodeFirst = pop();
        double firstValue = nodeFirst->contents.value;
        node* nodeSecond = pop();
        double secondValue = nodeSecond->contents.value;

        //Returns an error if there are no operations after retrieving the numbers
        if (peek()->type == 0) {
            *status = SOMETHINGMISSING;
            return -999;
        }
        else if(nodeFirst->type != 0 || nodeSecond->type != 0) {
            *status = BADENTRY;
            return -999;
        }
        else {
            //Assigns operationValue to the type of the next node
            int operationValue = pop()->type;

            //Switch statement for different operationValue
            switch (operationValue) {
                case 1:
                    //Pushes the sum of the two nodes
                    push(createNode(firstValue + secondValue, 0));
                    break;
                case 2:
                    //Pushes the difference of the two nodes
                    push(createNode(firstValue - secondValue, 0));
                    break;
                case 3:
                    //Pushes the product of the two nodes
                    push(createNode(firstValue * secondValue, 0));
                    break;
                case 4:
                    //If the second node is 0, returns an error
                    if (secondValue == 0) {
                        *status = SOMETHINGMISSING;
                        return -999;
                    }
                        //Pushes the division of the two nodes
                    else {
                        push(createNode(firstValue / secondValue, 0));
                        break;
                    }
                case 5:
                    //Pushes the power of the two nodes using recursion
                    //Calls helper function recursivePowerFunction
                    push(createNode(recursivePowerFunction(firstValue, secondValue), 0));
                    break;
                default:
                    //If operation does not meet one of the cases, returns an error
                    *status = BADENTRY;
                    return -999;
            }
        }
    }
}

//Helper function to using recursion to compute the power function
float recursivePowerFunction(double firstNumber, double secondNumber) {
    //If the second number is 0, returns 1
    if (secondNumber == 0){
        return 1;
    }
        //If the second number is greater than 1, recursively calls function decrementing by 1
    else if (secondNumber > 0){
        return firstNumber * recursivePowerFunction(firstNumber, secondNumber - 1);
    }
        //If the second number is less than 1, recursively calls function incrementing by 1
    else{
        return 1 / firstNumber * recursivePowerFunction(firstNumber, secondNumber + 1);
    }
}







//Function to convert infix to postfix
double myConverterFunction (char* expression, int* status, char* output){
    //Returns error if expression length is 0 or expression is NULL
    if(strlen(expression) == 0 || expression == NULL){
        *status = SOMETHINGMISSING;
        return -999;
    }

    //Clear stack to remove previous stack information
    clearStack();

    //Variables
    char *token;
    int index = 0;
    int realCounter = 0;
    int arrayNumber[strlen(expression)];

    //Token to find the value and type of node
    token = strtok(expression, " ");

    //While loop until token is NULL
    while (token != NULL) {
        //Placeholder variable for type
        int type = 0;
        //Switch statement based on token value
        switch (*token) {
            case '+':
                //Assigns type as PLUS
                type = PLUS;
                break;
            case '-':
                //Assigns type as MINUS
                type = MINUS;
                break;
            case '*':
                //Assigns type as MULTIPLY
                type = MULTIPLY;
                break;
            case '/':
                //Assigns type as DIVIDE
                type = DIVIDE;
                break;
            case '^':
                //Assigns type as POWER
                type = POWER;
                break;
            case '(':
                //Assigns type as OPARENTHESES
                type = OPARENTHESES;
                break;
            case ')':
                //Assigns type as CPARENTHESES
                type = CPARENTHESES;
                break;
            case '@':
            case '!':
            case '#':
            case '$':
            case '%':
            case '&':
            case '?':
                //Catches invalid symbols
                *status = SOMETHINGMISSING;
                return -999;
            default:
                //Assigns type as NUMBER as default
                type = NUMBER;
        }

        //Using the parsed token, use the information to create nodes
        if (type == NUMBER) {
            //Pushes number to array
            double value = atof(token);
            arrayNumber[index] = value;
            index++;

        } else {
            //Pushes operator to stack
            rpnNode_Walker = createNodeChar(*token, type);
            rpnNode_Walker->precedence = getPrecedence(rpnNode_Walker->contents.operator);

            //If nothing on stack
            if (peek() == NULL) {
                //push rpnNode_Walker
                push(rpnNode_Walker);
            }
            //Something is on the stack
            else {
                //find the current HEAD of stack
                node *nodeHolder = peek();
                nodeHolder->precedence = getPrecedence(nodeHolder->contents.operator);
                //if the current operator comparison is ')', pop all operators until we see '('
                if (rpnNode_Walker->contents.operator == ')') {
                    //Check if something is on the stack
                    if (nodeHolder != NULL) {
                        //Pop operators until '('
                        while (nodeHolder->contents.operator != '(') {
                            operatorStack(arrayNumber, &index);
                            nodeHolder = peek();
                            //If peek is NULL, return error
                            if (nodeHolder == NULL) {
                                *status = SOMETHINGMISSING;
                                return -999;
                            }
                        }
                        //If '(' is found, pop it and decrease realCounter by 2
                        if (nodeHolder->contents.operator == '(') {
                            pop();
                            realCounter = realCounter - 2;
                        }
                        //If '(' cannot be found, return error
                        else {
                            *status = SOMETHINGMISSING;
                            return -999;
                        }
                    }
                    //if nothing is on the stack, returns error
                    else {
                        *status = SOMETHINGMISSING;
                        return -999;
                    }

                }
                //if the current operator comparison is '('
                else if (rpnNode_Walker->contents.operator == '(') {
                    //push rpnNode_Walker
                    push(rpnNode_Walker);
                }
                //if current precedence value in stack is higher than the current comparison
                else if (nodeHolder->precedence >= rpnNode_Walker->precedence) {
                    //pop and adds current value in stack, pushes rpnNode_Walker to stack
                    operatorStack(arrayNumber, &index);
                    push(rpnNode_Walker);

                }
                else {
//                  //push rpnNode_Walker if no conditions met
                    push(rpnNode_Walker);
                }
            }
        }
        //Find the next token
        token = strtok(NULL, " ");
        //Increment realCounter
        realCounter++;
    }
//    printf("final index: %i \n", index);

    //divides the array in the middle with numbers and operators
    int newArrayHolder[realCounter];

    //Additional error checking
    if (peek() == NULL) {
        *status = ERRNULLPTR;
        return -999;
    }
    else{
        //adds remaining operators in the stack
        while (peek() != NULL) {
            //calls upon helper function
            operatorStack(arrayNumber, &index);
        }
    }

    //adds numbers in arrayNumber to finalized newArrayHolder
    for(int traverse = 0; traverse < index; traverse++){
        newArrayHolder[traverse] = arrayNumber[traverse];
    }

    //sets postfixIndex value
    int postfixIndex = 0;

    //For loop to traverse finalized array and add it to the output char
    for (int newTraverse = 0; newTraverse < realCounter; newTraverse++){
        if (newArrayHolder[newTraverse] == -901){
            //adding + sign
            sprintf(&output[postfixIndex], "%c ", '+');
            postfixIndex++;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
        else if (newArrayHolder[newTraverse] == -902){
            //adding - sign
            sprintf(&output[postfixIndex], "%c ", '-');
            postfixIndex++;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
        else if (newArrayHolder[newTraverse] == -903){
            //adding * sign
            sprintf(&output[postfixIndex], "%c ", '*');
            postfixIndex++;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
        else if (newArrayHolder[newTraverse] == -904){
            //adding / sign
            sprintf(&output[postfixIndex], "%c ", '/');
            postfixIndex++;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
        else if (newArrayHolder[newTraverse] == -905){
            //adding ^ sign
            sprintf(&output[postfixIndex], "%c ", '^');
            postfixIndex++;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
        else if (newArrayHolder[newTraverse] > 9){
            //adding double digit ints
            sprintf(&output[postfixIndex], "%d ", newArrayHolder[newTraverse]);
            postfixIndex = postfixIndex + 2;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
        else{
            //adding single digit ints
            sprintf(&output[postfixIndex], "%d ", newArrayHolder[newTraverse]);
            postfixIndex++;
            sprintf(&output[postfixIndex], "%c ", ' ');
            postfixIndex++;
        }
    }
    //returns 1 to checker if the process does not hit an error
    return 1;
}

//Helper function to add values onto the array and updates index value
double operatorStack(int currentArray[], int *currentIndex){
    // pops first node
    node* nodeFirst = pop();
    // finds the operator value of the ndoe
    char operationValue = nodeFirst->contents.operator;

    switch (operationValue) {
        case '+':
            //adds -901 as placeholder for '+'
            currentArray[*currentIndex] = -901;
            *currentIndex = *currentIndex + 1;
            break;
        case '-':
            //adds -902 as placeholder for '-'
            currentArray[*currentIndex] = -902;
            *currentIndex = *currentIndex + 1;
            break;
        case '*':
            //adds -903 as placeholder for '*'
            currentArray[*currentIndex] = -903;
            *currentIndex = *currentIndex + 1;
            break;
        case '/':
            //adds -904 as placeholder for '/'
            currentArray[*currentIndex] = -904;
            *currentIndex = *currentIndex + 1;
            break;
        case '^':
            //adds -905 as placeholder for '^'
            currentArray[*currentIndex] = -905;
            *currentIndex = *currentIndex + 1;
            break;
        default:
            //If operation does not meet one of the cases, does not add
            printf("just a number");
    }
}