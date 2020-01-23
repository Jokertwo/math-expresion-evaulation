//
// Created by petr on 22.01.20.
//

#include "NumberBuffer.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

typedef struct node_b {
    char number;
    struct node_b *next;
} NODE;

/**
 * Clear whole buffer
 */
static void clear_buffer();

/**
 * Compute size of buffer
 * @return return number of items in buffer
 */
static int getSize();

NODE *head_buf = NULL;
NODE *tail_buf = NULL;


int add_number(char number) {
    logInfo("Inserting to number buffer new value: %c", number);
    NODE *newNode = (NODE *) malloc((sizeof(NODE)));

    if (newNode == NULL) {
        logError("Cannot insert value: %c to number buffer", number);
        return S_FALSE;
    }
    // set values to new buffer
    newNode->number = number;
    newNode->next = NULL;

    // setting head of buffer
    if (head_buf == NULL) {
        logDebug("Number buffer is empty creating new head");
        head_buf = newNode;
        tail_buf = newNode;
        return S_TRUE;
    }

    // add to end of buffer
    logDebug("Buffer is not empty, adding new token to the end");
    tail_buf->next = newNode;
    tail_buf = newNode;
    return S_TRUE;
}


TOKEN get_number() {
    // compute items in buffer
    int size = getSize();

    // allocate string for all items in buffer
    char *number = (char *) malloc(sizeof(char) * size + 1);

    // check if allocation was successfully done
    if (number == NULL) {
        logError("Cannot allocate buffer for creating number!!!");
        return S_FALSE;
    }

    // iterate throw buffer and concat all items into one string
    NODE *temp = head_buf;
    int counter = 0;
    while (temp != NULL) {
        number[counter] = temp->number;
        counter++;
        temp = temp->next;
    }
    number[size] = '\0';

    // convert string to number
    char *pEnd = NULL;
    double d1;
    d1 = strtod(number, &pEnd);
    if (strlen(pEnd) > 0) {
        logError("In number buffer was not only number: %s ", pEnd);
        free(pEnd);
        return S_FALSE;
    }
    // release allocated resources
    free(number);
    clear_buffer();
    return d1;
}


static void clear_buffer() {
    logInfo("Clearing number buffer");
    if (head_buf != NULL) {
        while (head_buf != NULL) {
            NODE *temp = head_buf->next;
            free(head_buf);
            head_buf = temp;
        }
    } else {
        logWarn("Cannot clear number buffer because is empty");
    }
}

static int getSize() {
    int counter = 0;
    NODE *temp = head_buf;
    while (temp != NULL) {
        counter++;
        temp = temp->next;
    }
    return counter;
}

