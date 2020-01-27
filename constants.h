/*Created by petr on 22.01.20.*/

#ifndef SEMESTRALKA_CONSTANTS_H
#define SEMESTRALKA_CONSTANTS_H


#define UNKNOWN_OPERATOR -100
#define OUT_OF_MEMORY 50

const int S_TRUE;
const int S_FALSE;


typedef enum {
    number_t,
    variable_t,
    left_parenthesis_t,
    right_parenthesis_t,
    function_t,
    plus_op,
    minus_op,
    pow_op,
    divide_op,
    multi_op
} TYPE;

typedef struct token {
    TYPE type;
    double number;
    char *function;
    char other;
} TOKEN;

typedef struct node_b {
    char item;
    struct node_b *next;
} NODE;

typedef struct token_list {
    TOKEN *value;
    struct token_list *next;
} TOKEN_LIST;

#endif
