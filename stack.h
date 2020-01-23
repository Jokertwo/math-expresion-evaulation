/*Created by petr on 22.01.20.*/

#ifndef SEMESTRALKA_ZASOBNIK_H
#define SEMESTRALKA_ZASOBNIK_H

#include "constants.h"




/**
 * Insert value into stack
 * @param value value which should be stored in stack
 * @return return S_TRUE if everything was ok else S_FALSE
 */
int push(int value);

/**
 * Check if stack is empty
 * @return return S_TRUE if stack is empty else S_FALSE
 */
int isEmpty();

/**
 * Remove first value from the top of stack and return it.
 * @return return value from stack
 */
int pop();


#endif
