/**
 * Created by petr on 23.01.20.
 */

#include "logger.h"
#include "letter_buffer.h"
#include "number_buffer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "token_list.h"


/**
 * Create number from content of number_buffer
 *
 * @return
 */
static int create_number(TOKEN_LIST **head);

/**
 * Create string form content of letter_buffer
 *
 * @return
 */
static int create_string(TOKEN_LIST **head);

/**
 * Create new function token and store it in list
 * @param operator function which should be stored
 * @return return S_TRUE if function was successfully created and stored, else UNKNOWN_OPERATOR if cannot be resolved or OUT_OF_MEMORY when can not be created new token
 */
static int create_operator(char operator, TOKEN_LIST **head);

/**
 * Resolve type of function
 * @param operator function where should be resolved the type
 * @param token token where will be result store
 * @return return S_TRUE if function was resolved, else error code (UNKNOWN_OPERATOR)
 */
static int resolve_operator(char operator, TOKEN **token);


int resolveUnary(TOKEN_LIST **head) {
    int returnValue;
    TOKEN_LIST *current = NULL, *previous = NULL, *list = NULL;
    TOKEN *temp = NULL;
    current = *head;
    returnValue = S_TRUE;

    while (current->next != NULL) {
        if (previous == NULL && current->value->type == operator_t && current->value->other == '-') {
            if (current->next->value->type == number_t) {
                current->value->number = -current->next->value->number;
                current->value->type = number_t;
                list = current->next;
                current->next = current->next->next;
                free(list->value);
                free(list);

            } else {
                current->value->type = number_t;
                current->value->number = -1;

                returnValue = create_new_token_list(&list);
                if (returnValue != S_TRUE) {
                    logError("Cannot create new list node for negative number!!!");
                    return returnValue;
                }

                returnValue = create_new_token(&temp);
                if (returnValue != S_TRUE) {
                    logError("Cannot create new token for stored a new negative number");
                    return returnValue;
                }

                temp->type = operator_t;
                temp->other = '*';
                list->value = temp;
                list->next = current->next;
                current->next = list;
            }
        } else if (previous != NULL && current->value->type == operator_t && current->value->other == '-' &&
                   (previous->value->type == operator_t || previous->value->type == left_parenthesis_t)) {
            if (current->next->value->type == number_t) {
                current->next->value->number = -current->next->value->number;
                previous->next = current->next;
                free(current->value);
                free(current);
                current = previous;
            } else if (current->next->value->type == left_parenthesis_t || current->next->value->type == function_t ||
                       current->next->value->type == variable_t) {
                current->value->type = number_t;
                current->value->number = -1;

                returnValue = create_new_token_list(&list);
                if (returnValue != S_TRUE) {
                    logError("Cannot create new list node for negative number!!!");
                    return returnValue;
                }

                returnValue = create_new_token(&temp);
                if (returnValue != S_TRUE) {
                    logError("Cannot create new token for stored a new number");
                    return returnValue;
                }

                temp->type = operator_t;
                temp->other = '*';
                list->value = temp;
                list->next = current->next;
                current->next = list;
            }
        }
        previous = current;
        current = current->next;
    }
    return returnValue;
}


int tokenize_expresion(char *expresion, TOKEN_LIST **head) {
    int i, checkResult;
    size_t len;
    logInfo("Start tokenize expresion: %s", expresion);
    len = strlen(expresion);

    /**hodnota je pouziva pro detekci toho jestli se nekde behem vypoctu/tokenizace nepokazilo*/
    checkResult = S_TRUE;

    /** prochazim vstupnim stringem pismeno po pismenu*/
    for (i = 0; i < len; i++) {
        char item = expresion[i];

        /** pokud na narazim na jeden z techto znaku, znamena to zmenu stavu (napr precetl jsem vsechny cisla ktera k sobe patri*/
        if (item == '(' || item == ')' || item == '*' || item == '+' || item == '/' || item == '^' || isspace(item) ||
            item == '-') {

            /**  pokud jsem do ted cetl pismena vztvorim z nich jedno slovo */
            if (!is_letter_buff_empty()) {
                checkResult = create_string(head);
            }
                /** pokud jsem do ted cetl cisla*/
            else if (!is_number_buff_empty()) {
                /**
                 * je-li prechzejici znak 'e/E' => vedecka notace, pridej aktulni znak ho ciselneho bufferu
                 * patri sem jak 5E5 tak 5E-5
                 */
                if (expresion[i - 1] == 'e' || expresion[i - 1] == 'E') {
                    checkResult = add_number(item);
                    if (checkResult != S_TRUE) {
                        return checkResult;
                    }
                    continue;
                } else {
                    /** ve vsech ostatnich pripadech vytvor cislo z toho co je v bufferu*/
                    checkResult = create_number(head);

                }
            }

            /** nakonec je treba zpracovat aktulni znak, mezery se neukladaji protoze je az ted k nicemu nepotrebuju*/
            if (!isspace(item)) {
                checkResult = create_operator(item, head);
            }
            /** pokud je znak cislo nebo desetina tecka pridej to do ciselneho bufferu*/
        } else if (isdigit(item) || item == '.') {
            checkResult = add_number(item);
            /** zde se pak zpracuje zbytek*/
        } else {
            /**
             * pokud se do ted cetla cisla pridej aktualni znak do ciselneho bufferu
             * to dovoli zpracovat vstupy jako 2e5(vedecka notace) nebo 0x25(hexadecimalni a oktalová soustava)
             */
            if (!is_number_buff_empty()) {
                checkResult = add_number(item);
            } else {
                /** vse ostatni co zbyva jsou funkce (cos,sin,...) a promena (x) a neplatne znaky (jestli vyraz obsahuje neplatne se resi behem vyvareni tokenu)*/
                checkResult = add_letter(item);
            }
        }
        if (checkResult != S_TRUE) {
            return checkResult;
        }
    }

    if (!is_number_buff_empty()) {
        checkResult = create_number(head);
    }
    if (checkResult != S_TRUE) return checkResult;

    if (!is_letter_buff_empty()) {
        checkResult = create_string(head);
    }

    return checkResult;
}


static int create_number(TOKEN_LIST **head) {
    int result;
    TOKEN *token;
    result = create_new_token(&token);
    if (result != S_TRUE) {
        logError("Cannot create new token for number!!!");
        return result;
    }
    /* concat all digits in buffer together*/
    result = get_number(token);
    if (result != S_TRUE) {
        return result;
    }
    return add_to_end(token, head);
}

static int create_string(TOKEN_LIST **head) {
    int result;
    TOKEN *token;
    result = create_new_token(&token);
    if (result != S_TRUE) {
        logError("Cannot create new token for string!!!");
        return result;
    }
    /*concat all letters together*/
    result = get_letter(token);
    if (result != S_TRUE) {
        logError("Can not create new token from string");
        return result;
    }
    return add_to_end(token, head);
}

static int create_operator(char operator, TOKEN_LIST **head) {
    int returnValue;
    TOKEN *token;

    returnValue = create_new_token(&token);
    if (returnValue != S_TRUE) {
        logError("Cannot create new token for operator_t!!!");
        return returnValue;
    }

    /*resolve operator_t*/
    returnValue = resolve_operator(operator, &token);
    if (returnValue != S_TRUE) {
        logError("Unknown operator_t %c, returning error code: %d", operator, returnValue);
        return returnValue;
    }

    /*adding operator_t to token*/
    token->other = operator;

    logInfo("Created new token, type: %d, other: %c", token->type, token->other);

    /*adding token to token list*/
    return add_to_end(token, head);
}

static int resolve_operator(char operator, TOKEN **token) {
    int returnValue = S_TRUE;
    switch (operator) {
        case ')':
            (*token)->type = right_parenthesis_t;
            (*token)->operator_type = other;
            break;
        case '(':
            (*token)->type = left_parenthesis_t;
            (*token)->operator_type = other;
            break;
        case '+':
            (*token)->type = operator_t;
            (*token)->operator_type = add_op;
            break;
        case '-':
            (*token)->type = operator_t;
            (*token)->operator_type = sub_op;
            break;
        case '/':
            (*token)->type = operator_t;
            (*token)->operator_type = div_op;
            break;
        case '^':
            (*token)->type = operator_t;
            (*token)->operator_type = pow_op;
            break;
        case '*':
            (*token)->type = operator_t;
            (*token)->operator_type = mul_op;
            break;
        default:
            returnValue = UNKNOWN_OPERATOR;
    }
    return returnValue;
}


