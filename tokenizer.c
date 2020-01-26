/**
 * Created by petr on 23.01.20.
 */

#include "logger.h"
#include "letter_buffer.h"
#include "number_buffer.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

static TOKEN_LIST *head_list;

/**
 * Add token to token list
 * @param token token which should be added
 * @return return S_TRUE if everything was ok, else some error code
 */
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
 * Create new function token and store it in list
 * @param operator function which should be stored
 * @return return S_TRUE if function was successfully created and stored, else UNKNOWN_OPERATOR if cannot be resolved or OUT_OF_MEMORY when can not be created new token
 */
static int create_operator(char operator);

/**
 * Resolve type of function
 * @param operator function where should be resolved the type
 * @param token token where will be result store
 * @return return S_TRUE if function was resolved, else error code (UNKNOWN_OPERATOR)
 */
static int resolve_operator(char operator, TOKEN **token);

int tokenize_expresion(char *expresion) {
    int i;
    logInfo("Start tokenize expresion: %s", expresion);
    size_t len = strlen(expresion);

    //hodnota je pouziva pro detekci toho jestli se nekde behem vypoctu/tokenizace nepokazilo
    int checkResult = S_TRUE;

    // prochazim vstupnim stringem pismeno po pismenu
    for (i = 0; i < len; i++) {
        char item = expresion[i];

        // pokud na narazim na jeden z techto znaku, znamena to zmenu stavu (napr precetl jsem vsechny cisla ktera k sobe patri
        if (item == '(' || item == ')' || item == '*' || item == '+' || item == '/' || item == '^' || isspace(item) ||
            item == '-') {

            /**  pokud jsem do ted cetl pismena vztvorim z nich jedno slovo */
            if (!is_letter_buff_empty()) {
                checkResult = create_string();
            }
            /** pokud jsem do ted cetl cisla*/
            if (!is_number_buff_empty()) {
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
                    checkResult = create_number();
                }
            }
            /** nakonec je treba zpracovat aktulni znak, mezery se neukladaji protoze je az ted k nicemu nepotrebuju*/
            if (!isspace(item)) {
                checkResult = create_operator(item);
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
        checkResult = create_number();
    }
    if (checkResult != S_TRUE) return checkResult;

    if (!is_letter_buff_empty()) {
        checkResult = create_string();
    }

    return checkResult;
}


void print_tokens() {
    TOKEN_LIST *temp = head_list;
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

void clear() {

    while (head_list != NULL) {
        TOKEN_LIST *temp = head_list->next;
        free(head_list->value->function);
        free(head_list->value);
        free(head_list);
        head_list = temp;
    }
}


static int add_token(TOKEN *token) {
    TOKEN_LIST *newNode = (TOKEN_LIST *) malloc((sizeof(TOKEN_LIST)));
    if (newNode == NULL) {
        logError("Unable to allocate memory for new TOKEN_LIST node");
        return OUT_OF_MEMORY;
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
    logDebug("New token added to token list");
    return S_TRUE;

}

static int create_number() {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    if (token == NULL) {
        logError("Cannot create new token for stored a new number");
        return OUT_OF_MEMORY;
    }
    token->function = NULL;
    int result = get_number(token);
    if (result != S_TRUE) {
        return result;
    }
    return add_token(token);
}

static int create_string() {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    if (token == NULL) {
        logError("Cannot create new token for stored a new function/variable");
        return OUT_OF_MEMORY;
    }
    token->function = NULL;

    //concat all letters together
    int result = get_letter(token);
    if (result != S_TRUE) {
        logError("Can not create new token from string");
        return result;
    }
    return add_token(token);
}

static int create_operator(char operator) {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    if (token == NULL) {
        logError("Cannot create new token for stored a new function");
        return OUT_OF_MEMORY;
    }
    token->function = NULL;

    //resolve operator
    int returnValue = resolve_operator(operator, &token);
    if (returnValue != S_TRUE) {
        logError("Unknown operator %c, returning error code: %d", operator, returnValue);
        return returnValue;
    }

    //adding operator to token
    token->other = operator;

    logInfo("Created new token, type: %d, other: %c", token->type, token->other);

    //adding token to token list
    return add_token(token);
}

static int resolve_operator(char operator, TOKEN **token) {
    int returnValue = S_TRUE;
    switch (operator) {
        case ')':
            (*token)->type = right_parenthesis_t;
            break;
        case '(':
            (*token)->type = left_parenthesis_t;
            break;
        case '+':
            (*token)->type = plus_op;
            break;
        case '-':
            (*token)->type = minus_op;
            break;
        case '/':
            (*token)->type = divide_op;
            break;
        case '^':
            (*token)->type = pow_op;
            break;
        case '*':
            (*token)->type = multi_op;
            break;
        default:
            returnValue = UNKNOWN_OPERATOR;
    }
    return returnValue;
}
