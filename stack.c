
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "logger.h"

const int S_TRUE = 1;
const int S_FALSE = 0;

typedef struct node {
    int val;
    struct node *next;
} node_t;


node_t *head = NULL;

int push(int value) {
    logDebug("Inserting to stack a new value: %d", value);
    node_t *newNode = (node_t *) malloc(sizeof(node_t));
    if (newNode == NULL) {
        logError("Cannot allocate memory for new item in stack.");
        return S_FALSE;
    }
    newNode->val = value;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return S_TRUE;
    }
    newNode->next = head;
    head = newNode;
    return S_TRUE;
}

int isEmpty() {
    return head == NULL ? S_TRUE : S_FALSE;
}


int pop() {
    node_t *temp = NULL;

    if(head == NULL){
        logError("Cannot pop value from stack because is empty");
        return S_FALSE;
    }

    int returnValue = head->val;
    temp = head->next;

    free(head);
    head = temp;

    logDebug("Pop value: %d from stack", returnValue);
    return returnValue;
}


