/**
 * Created by petr on 26.01.20.
 */

#include "shunting-yard.h"
#include "constants.h"
#include <stdlib.h>
#include "token_list.h"
#include "logger.h"

static int get_precedence(OPERATOR_TYPE operatorType);

static ASSOC get_associativity(OPERATOR_TYPE operatorType);

/**
 * print one token on debug severity
 * @param token printed token
 */
static void printToken(TOKEN *token);

int shunting_yard(TOKEN_LIST *head, TOKEN_LIST **output) {
    TOKEN_LIST *temp, *operatorStack;
    TOKEN *poped;
    operatorStack = NULL;
    temp = head;
    logInfo("SHUNTING-YARD: Starting shunting yard");
    while (temp != NULL) {
        TOKEN *current;
        current = temp->value;

        printToken(current);

        if (current->type == number_t) {
            logDebug("SHUNTING-YARD: add number: %f to output", current->number);
            add_to_end(current, output);
        } else if (current->type == variable_t) {
            logDebug("SHUNTING-YARD: add variable: %c to output", current->other);
            add_to_end(current, output);
        } else if (current->type == function_t) {
            logDebug("SHUNTING-YARD: add function %s to operator stack", current->function);
            add_to_begin(current, &operatorStack);
        } else if (current->type == operator_t) {
            while (!is_empty(operatorStack) && (operatorStack->value->type == function_t ||
                                                get_precedence(operatorStack->value->operator_type) >
                                                get_precedence(current->operator_type) ||
                                                (
                                                        (get_precedence(operatorStack->value->operator_type) ==
                                                         get_precedence(current->operator_type) &&
                                                         get_associativity(current->operator_type) == right))) &&
                   operatorStack->value->type != left_parenthesis_t) {
                poped = NULL;
                pop_token(&poped, &operatorStack);
                if (poped->type == function_t) {
                    logDebug("SHUNTING-YARD: add function: %s to output", poped->function);
                } else {
                    logDebug("SHUNTING-YARD: add operator: %c to output", poped->other);
                }
                add_to_end(poped, output);
            }
            if (current->type == function_t) {
                logDebug("SHUNTING-YARD: add function: %s to operator stack", current->function);
            } else {
                logDebug("SHUNTING-YARD: add operator: %c to operator stack", current->other);
            }
            add_to_begin(current, &operatorStack);
        } else if (current->type == left_parenthesis_t) {
            logDebug("SHUNTING-YARD: add parenthesis: %c to operator stack", current->other);
            add_to_begin(current, &operatorStack);
        } else if (current->type == right_parenthesis_t) {
            while (operatorStack->value->type != left_parenthesis_t) {
                poped = NULL;
                pop_token(&poped, &operatorStack);
                if (poped->type == function_t) {
                    logDebug("SHUNTING-YARD: add function: %s to output", poped->function);
                } else {
                    logDebug("SHUNTING-YARD: add operator: %c to output", poped->other);
                }
                add_to_end(poped, output);
            }
            if (operatorStack->value->type == left_parenthesis_t) {
                poped = NULL;
                logDebug("SHUNTING-YARD: removing left parenthesis from operator stack");
                pop_token(&poped, &operatorStack);
            }
        }
        temp = temp->next;
    }
    while (!is_empty(operatorStack)) {
        poped = NULL;
        pop_token(&poped, &operatorStack);
        if (poped->type == function_t) {
            logDebug("SHUNTING-YARD: add function: %s to output", poped->function);
        } else {
            logDebug("SHUNTING-YARD: add operator: %c to output", poped->other);
        }
        add_to_end(poped, output);
    }

    return S_TRUE;
}

static void printToken(TOKEN *token) {
    if (token->type == number_t) {
        logDebug("SHUNTING-YARD: Processing token type: number, value: %f", token->number);
    } else if (token->type == function_t) {
        logDebug("SHUNTING-YARD: Processing token type: function, value: %s", token->function);
    } else if (token->type == variable_t) {
        logDebug("SHUNTING-YARD: Processing token type: variable, value: %c", token->other);
    } else if (token->type == left_parenthesis_t || token->type == right_parenthesis_t) {
        logDebug("SHUNTING-YARD: Processing token type: parenthesis, value: %c", token->other);
    } else {
        logDebug("SHUNTING-YARD: Processing token type: operator, value: %c", token->other);
    }
}

static int get_precedence(OPERATOR_TYPE operatorType) {
    int precedence;
    precedence = 0;
    switch (operatorType) {
        case add_op:
        case sub_op:
            precedence = 2;
            break;
        case mul_op:
        case div_op:
            precedence = 3;
            break;
        case pow_op:
            precedence = 4;
            break;
    }
    return precedence;
}

static ASSOC get_associativity(OPERATOR_TYPE operatorType) {
    ASSOC assoc = left;
    switch (operatorType) {
        case add_op:
        case sub_op:
        case mul_op:
        case div_op:
            assoc = left;
            break;
        case pow_op:
            assoc = right;
            break;
    }
    return assoc;
}

