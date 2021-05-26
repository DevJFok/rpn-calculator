//
// Created by Jarrett Fok on 4/23/21.
//

#ifndef PS5_RPN_H
#define PS5_RPN_H

//Evaluate Function
double evaluate (char* expression, int* status);
//Helper Function, mathOperation Function
double mathOperation(int *status);
//Helper Function, recursivePowerFunction
float recursivePowerFunction(double number1, double number2);
//Helper Function, converterFunction Function
double myConverterFunction (char* expression, int* status, char* output);
//Helper Function, operatorStack Function
double operatorStack(int currentArray[], int* currentIndex);
#endif //PS5_RPN_H
