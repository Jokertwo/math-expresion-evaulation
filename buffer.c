//
// Created by petr on 23.01.20.
//

#include "buffer.h"
#include "logger.h"
#include <stdlib.h>


int add_item(char item, NODE **head) {

    NODE *newNode = (NODE *) malloc((sizeof(NODE)));

    if (newNode == NULL) {
        logError("Cannot insert value: %c to number buffer", item);
        return S_FALSE;
    }
    // set values to new buffer
    newNode->item = item;
    newNode->next = NULL;

    // setting head of buffer
    if (*head == NULL) {
        logDebug("Number buffer is empty creating new head");
        *head = newNode;
        return S_TRUE;
    }

    // add to end of buffer
    logTrace("Buffer is not empty, adding new token to the end");
    NODE *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return S_TRUE;
}


int concat(char **result, NODE **head) {

    if (*head == NULL) {
        logError("Buffer is empty!!! There is nothing to concat");
        return S_FALSE;
    }

    // compute items in buffer
    int size = getSize(*head);

    // allocate string for all items in buffer
    char *tempResult = (char *) malloc(sizeof(char) * size + 1);

    // check if allocation was not successfully done
    if (tempResult == NULL) {
        logError("Cannot allocate buffer for creating number!!!");
        return S_FALSE;
    }

    // iterate throw buffer and concat all items into one string
    NODE *temp = *head;
    int counter = 0;
    while (temp != NULL) {
        tempResult[counter] = temp->item;
        counter++;
        temp = temp->next;
    }
    tempResult[size] = '\0';
    logInfo("Content of buffer was concat into: %s", tempResult);
    *result = tempResult;
    return S_TRUE;

}

void clear_buffer(NODE **head) {
    logInfo("Clearing number buffer");
    if (*head != NULL) {
        while (*head != NULL) {
            NODE *temp = (*head)->next;;
            free(*head);
            *head = temp;
        }
    } else {
        logWarn("Cannot clear number buffer because is empty");
    }
}


int getSize(NODE *head) {
    int counter = 0;
    NODE *temp = head;
    while (temp != NULL) {
        counter++;
        temp = temp->next;
    }
    return counter;
}
