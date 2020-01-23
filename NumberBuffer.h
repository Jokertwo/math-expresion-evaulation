/**
 * Created by petr on 22.01.20.
 */
#ifndef CLION_SVATAVA_NUMBERBUFFER_H
#define CLION_SVATAVA_NUMBERBUFFER_H

#include "constants.h"

/**
 * Add new number to buffer
 * @param number part of number (can be number, dot or minus)
 * @return return S_TRUE if everything was ok else S_FALSE
 */
int add_number(char number);

/**
 * number from all items which is stored in buffer
 * @param token
 * @return S_TRUE if all was ok, else S_FALSE if something fail and message is stored in token
 */
int get_number(TOKEN **token);

#endif
