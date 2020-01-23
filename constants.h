/*Created by petr on 22.01.20.*/

#ifndef SEMESTRALKA_CONSTANTS_H
#define SEMESTRALKA_CONSTANTS_H

const int S_TRUE;
const int S_FALSE;


typedef enum {
    number,
    variable,
    left_parenthesis,
    right_parenthesis,
    operator,
    error
}TYPE;

typedef struct token{
    TYPE type;
    double number;
    char operator;
} TOKEN;

#endif
