#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "stack.h"
#include "rpn.h"

int main(int argc, const char * argv[]){
    //Opens inputfile
    FILE *inputfile = fopen("/home/cs210/cs210/cs210/PS5/ps5-infile.txt", "r");
    //If there is an error, return -1
    if(!inputfile){
        perror("No Input. \n");
        return -1;
    }
    //Opens outputfile
    FILE *outputfile = fopen("/home/cs210/cs210/cs210/PS5/ps5-outfile.txt", "w");
    //If there is an error, return -1
    if(!outputfile){
        perror("No Input. \n");
        return -1;
    }

    //Variables for line output
    char currentline[50];
    int status1 = 0;
    char postfix[100] = {0};
    int inputCounter = 1;

    //While line exists in the inputfile
    while (fgets(currentline, sizeof(currentline), inputfile) != NULL) {
        //Prints out the input number
        fprintf(outputfile, "Input %d \n", inputCounter);
        //increment inputCounter
        inputCounter++;

        //Calls function to convert
        double checker = myConverterFunction(currentline, &status1, postfix);

        //If there is no error, Checker == 1
        if (checker == 1){
            //Postfix form
            fprintf(outputfile, "Postfix Form: %s \n", postfix);
            //Result of the expression
            fprintf(outputfile, "Result: %f \n\n", evaluate(postfix, &status1));
        }
        //There is an error, prints out error
        else{
            fprintf(outputfile, "Postfix Form: Error \n");
            fprintf(outputfile, "Result: Error \n\n");
        }

    }
    //Closes input and output file
    fclose(inputfile);
    fclose(outputfile);


    unsigned short whatValue = 0;
    whatValue |= (0b00000001 << 4);
    printf("%d\n", whatValue);
}