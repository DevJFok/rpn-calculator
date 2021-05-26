#include "node.h"
#include <malloc.h>
#include <stdlib.h>


//This creates the new node
struct node* createNode(double value, int type){
    node* new_node = (struct node*)malloc(sizeof(node));
    if(new_node){
        new_node->contents.value = value;
        new_node->type = type;
        new_node->next = NULL;
    }
    return new_node;
}

struct node* createNodeChar(char value, int type){
    node* new_node = (struct node*)malloc(sizeof(node));
    if(new_node){
        new_node->contents.operator = value;
        new_node->type = type;
        new_node->next = NULL;
    }
    else {
        puts("Unable to allocate memory for a node. \n");
        exit(-1);
    }
    return new_node;
}
