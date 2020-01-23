/**
 * Created by petr on 22.01.20.
 */
#ifndef CLION_SVATAVA_NUMBER_BUFFER_H
#define CLION_SVATAVA_NUMBER_BUFFER_H

#include "constants.h"
#include "buffer.h"

/**
 * Add new number to buffer
 * @param number part of number (can be number, dot or minus)
 * @return return S_TRUE if everything was ok else S_FALSE
 */
int add_number(char number);

/**
 * number from all items which is stored in buffer
 * @param token where will be stored created number
 * @return S_TRUE if all was ok, else S_FALSE if something fail
 */
int get_number(TOKEN *token);

#endif
