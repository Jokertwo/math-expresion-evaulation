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

    if ((*head) == NULL) {
        (*head) = newNode;
        return S_TRUE;
    }
    temp = (*head);
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    logDebug("New token added to token list");
    return S_TRUE;
}

int pop_token(TOKEN **token, TOKEN_LIST **head) {
    TOKEN_LIST *temp;
    if ((*head) == NULL) {
        logError("Empty head!!!");
        return S_FALSE;
    }
    (*token) = (*head)->value;
    temp = (*head)->next;
    free((*head));
    (*head) = temp;

    return S_TRUE;
}

int is_empty(TOKEN_LIST *list) {
    return list == NULL || list->value == NULL;
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

int create_new_token(TOKEN **token) {
    *token = (TOKEN *) malloc(sizeof(TOKEN));
    if (*token == NULL) {
        logError("Can not create new token!!!");
        return OUT_OF_MEMORY;
    }
    (*token)->number = 0;
    (*token)->type = -1;
    (*token)->function = NULL;
    (*token)->other = '\0';
    return S_TRUE;
}

int create_new_token_list(TOKEN_LIST **list) {
    *list = (TOKEN_LIST *) malloc(sizeof(TOKEN_LIST));
    if (*list == NULL) {
        logError("Can not create new token list node!!!");
        return OUT_OF_MEMORY;
    }
    (*list)->value = NULL;
    (*list)->next = NULL;
    return S_TRUE;
}
