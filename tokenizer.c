/**
 * Created by petr on 23.01.20.
 */

#include "tokenizer.h"
#include "logger.h"
#include "letter_buffer.h"
#include "number_buffer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static TOKEN_LIST *head_list;

typedef enum {
    NUMBER_STATE,
    LETTER_STATE
} STATE;

static TOKEN *create_token();

static int add_token(TOKEN *token);


int tokenize_expresion(char *expresion) {
    int i;
    char lastItem = 0;
    size_t len = strlen(expresion);

    STATE status = NUMBER_STATE;

    for (i = 0; i < len; i++) {
        char item = expresion[i];
        TOKEN *token;
        //skip space
        if (isspace(item)) {
            continue;
        }

        if (item == '(' || item == ')' || item == '*' || item == '+' || item == '/' || item == '^') {
            if (!is_letter_buff_empty()) {
                token = create_token();
                get_letter(token);
                add_token(token);
            }
            if (!is_number_buff_empty()) {
                token = create_token();
                get_number(token);
                add_token(token);
            }

            token = create_token();
            token->type = operator_t;
            token->operator = (char *) malloc(sizeof(char) * 4);
            if (token->operator == NULL) {
                logError("Unable to allocate memory for new operator");
                return S_FALSE;
            }

            strcpy(token->operator, &item);
            token->operator[1] = '\0';

            add_token(token);
        } else if (isdigit(item) || item == '.') {
            add_number(item);
        } else if (isalpha(item)) {
            if (!is_number_buff_empty()) {
                add_number(item);
            } else {
                add_letter(item);
            }
        }
        lastItem = item;
    }
    TOKEN *token;
    if (!is_letter_buff_empty()) {
        token = create_token();
        get_letter(token);
        add_token(token);
    }
    if (!is_letter_buff_empty()) {
        token = create_token();
        get_number(token);
        add_token(token);
    }

    return S_TRUE;
}


void print_tokens() {
    TOKEN_LIST *temp = head_list;
    while (temp != NULL) {
        if (temp->value->type == number_t) {
            logInfo("Token type: number, value: %f", temp->value->number);
        } else {
            logInfo("Token type: string, value: %s", temp->value->operator);
        }
        temp = temp->next;
    }
}

void clear() {

    while (head_list != NULL) {
        TOKEN_LIST *temp = head_list->next;
        free(head_list->value->operator);
        free(head_list->value);
        free(head_list);
        head_list = temp;
    }
}


static TOKEN *create_token() {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->operator = NULL;
    return token;
}

static int add_token(TOKEN *token) {
    TOKEN_LIST *newNode = (TOKEN_LIST *) malloc((sizeof(TOKEN_LIST)));
    if (newNode == NULL) {
        logError("Unable to allocate memory for new TOKEN_LIST node");
        return S_FALSE;
    }

    newNode->value = token;
    newNode->next = NULL;

    if (head_list == NULL) {
        head_list = newNode;
        return S_TRUE;
    }
    TOKEN_LIST *temp = head_list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;

    return S_TRUE;

}