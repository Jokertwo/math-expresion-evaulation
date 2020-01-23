/**
 *  Created by petr on 23.01.20.
 */

#include "constants.h"
#include "buffer.h"

#ifndef CLION_SVATAVA_LETTER_BUFFER_H
#define CLION_SVATAVA_LETTER_BUFFER_H

/**
 * Add new letter to buffer
 * @param letter letter which should be stored
 * @return return S_TRUE if everything was ok, else S_FALSE
 */
int add_letter(char letter);

/**
 * Create new token from buffer content
 * @param token token where will be stored crated content
 * @return return S_TRUE if everything was ok, else S_FALSE
 */
int get_letter(TOKEN *token);

#endif /*CLION_SVATAVA_LETTER_BUFFER_H*/
