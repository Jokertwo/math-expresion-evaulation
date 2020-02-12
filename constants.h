/*Created by petr on 22.01.20.*/

#ifndef SEMESTRALKA_CONSTANTS_H
#define SEMESTRALKA_CONSTANTS_H


#define UNKNOWN_OPERATOR -100
#define BAD_SYNTAX -75
#define OUT_OF_MEMORY -50

const int S_TRUE;
const int S_FALSE;


typedef enum {
    number_t,
    variable_t,
    function_t,
    left_parenthesis_t,
    right_parenthesis_t,
    operator_t
} TYPE;

typedef enum {
    add_op,
    sub_op,
    mul_op,
    div_op,
    pow_op,
    other
} OPERATOR_TYPE;

typedef enum {
    left,
    right
} ASSOC;

typedef struct token {
    TYPE type;
    OPERATOR_TYPE operator_type;
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
