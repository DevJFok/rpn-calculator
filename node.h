//
// Created by Jarrett Fok on 4/1/21.
//

#ifndef PS5_NODE_H
#define PS5_NODE_H


typedef struct node node;

typedef struct node {
    union{
        double value;
        char operator;
    } contents;
    int type;
    int precedence;
    node *next;
} node;

node* createNode(double, int);
node* createNodeChar(char, int);



#endif //PS5_NODE_H
