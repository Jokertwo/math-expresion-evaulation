/*Created by petr on 22.01.20.*/

#ifndef SEMESTRALKA_CONSTANTS_H
#define SEMESTRALKA_CONSTANTS_H

const int S_TRUE;
const int S_FALSE;


typedef enum {
    number_t,
    variable_t,
    left_parenthesis_t,
    right_parenthesis_t,
    operator_t,
    error_t
} TYPE;

typedef struct token {
    TYPE type;
    double number;
    char *operator;
} TOKEN;

typedef struct node_b {
    char item;
    struct node_b *next;
} NODE;

#endif
