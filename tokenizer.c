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

static TOKEN *create_token();

static int add_token(TOKEN *token);

/**
 * Create number from content of number_buffer
 *
 * @return
 */
static int create_number();

/**
 * Create string form content of letter_buffer
 *
 * @return
 */
static int create_string();

/**
 * Create new operator token and store it in list
 */
static void create_operator(char operator);


int tokenize_expresion(char *expresion) {
    int i;

    size_t len = strlen(expresion);


    for (i = 0; i < len; i++) {
        char item = expresion[i];

        if (item == '(' || item == ')' || item == '*' || item == '+' || item == '/' || item == '^' || isspace(item) ||
            item == '-') {
            if (!is_letter_buff_empty()) {
                create_string();
            }
            if (!is_number_buff_empty()) {
                if (expresion[i - 1] == 'e' || expresion[i - 1] == 'E') {
                    add_number(item);
                    continue;
                } else {
                    create_number();
                }
            }
            if (!isspace(item)) {
                create_operator(item);
            }
        } else if (isdigit(item) || item == '.') {
            add_number(item);
        } else if (isalpha(item)) {
            if (!is_number_buff_empty()) {
                add_number(item);
            } else {
                add_letter(item);
            }
        }
    }

    if (!is_number_buff_empty()) {
        create_number();
    }
    if (!is_letter_buff_empty()) {
        create_string();
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

static int create_number() {
    TOKEN *token = create_token();
    get_number(token);
    add_token(token);
    return S_TRUE;
}

static int create_string() {
    TOKEN *token = create_token();
    get_letter(token);
    add_token(token);
    return S_TRUE;
}

static void create_operator(char operator) {
    TOKEN *token = create_token();
    token->type = operator_t;
    token->operator = (char *) malloc(sizeof(char) * 4);
    if (token->operator == NULL) {
        logError("Unable to allocate memory for new operator");
        exit(-100);
    }

    strcpy(token->operator, &operator);
    token->operator[1] = '\0';

    add_token(token);
}
