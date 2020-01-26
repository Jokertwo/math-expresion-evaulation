/**
 * Created by petr on 26.01.20.
 */

#include "token_list.h"
#include <stdlib.h>
#include "logger.h"

int add_to_begin(TOKEN *token, TOKEN_LIST **head) {
    TOKEN_LIST *newNode;
    newNode = (TOKEN_LIST *) malloc((sizeof(TOKEN_LIST)));
    if (newNode == NULL) {
        logError("Unable to allocate memory for new TOKEN_LIST node");
        return OUT_OF_MEMORY;
    }

    newNode->value = token;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return S_TRUE;
    }
    newNode->next = *head;
    *head = newNode;
    logDebug("New token added to begin of token list");
    return S_TRUE;
}

int add_to_end(TOKEN *token, TOKEN_LIST **head) {
    TOKEN_LIST *temp, *newNode;
    newNode = (TOKEN_LIST *) malloc((sizeof(TOKEN_LIST)));
    if (newNode == NULL) {
        logError("Unable to allocate memory for new TOKEN_LIST node");
        return OUT_OF_MEMORY;
    }

    newNode->value = token;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return S_TRUE;
    }
    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    logDebug("New token added to token list");
    return S_TRUE;
}


void print_tokens(TOKEN_LIST *head) {
    TOKEN_LIST *temp = head;
    while (temp != NULL) {
        if (temp->value->type == number_t) {
            logInfo("Token type: number, value: %f", temp->value->number);
        } else if (temp->value->type == function_t) {
            logInfo("Token type: function, value: %s", temp->value->function);
        } else if (temp->value->type == variable_t) {
            logInfo("Token type: variable, value: %c", temp->value->other);
        } else {
            logInfo("Token type: operator, value: %c", temp->value->other);
        }
        temp = temp->next;
    }
}

void clear(TOKEN_LIST **head) {

    while (*head != NULL) {
        TOKEN_LIST *temp = (*head)->next;
        free((*head)->value->function);
        free((*head)->value);
        free((*head));
        (*head) = temp;
    }
}
