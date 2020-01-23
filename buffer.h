//
// Created by petr on 23.01.20.
//

#ifndef CLION_SVATAVA_BUFFER_H
#define CLION_SVATAVA_BUFFER_H


#include "constants.h"

/**
 * Add new item to buffer. At the end of buffer
 * @param item item which should be stored
 * @param head head of buffer
 * @return return S_TRUE if everything was ok, else S_FALSE
 */
int add_item(char item, NODE **head);

/**
 * Concat content of buffer into one string
 * @param result pointer where will be value stored
 * @return return S_TRUE if everything was ok, else S_FALSE
 */
int concat(char **result, NODE **head);

/**
 * Clear buffer
 * @param head head of buffer
 */
void clear_buffer(NODE **head);

/**
 * Returns size of buffer
 * @param head
 * @return
 */
int getSize(NODE *head);

#endif
