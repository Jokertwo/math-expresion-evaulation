/**
 * Created by petr on 26.01.20.
 */

#include "constants.h"

#ifndef CLION_SVATAVA_TOKEN_LIST_H
#define CLION_SVATAVA_TOKEN_LIST_H

/**
 * Insert token at to begin of list
 * @param token inserted token
 * @param head head of list
 * @return return S_TRUE if everything was ok else some error code
 */
int add_to_begin(TOKEN *token, TOKEN_LIST **head);

/**
 * Insert token at the end of list
 * @param token inserted token
 * @param head head of list
 * @return return S_TRUE if everything was ok else some error code
 */
int add_to_end(TOKEN *token, TOKEN_LIST **head);

/**
 * Take first token from list and remove it
 * @param token
 * @return return S_TRUE if everything was ok else some error code
 */
int pop_token(TOKEN **token, TOKEN_LIST **head);

/**
 * Clear token list
 * @param head
 */
void clear(TOKEN_LIST **head);

/**
 * Print content of token list
 * @param head
 */
void print_tokens(TOKEN_LIST *head);

int is_empty(TOKEN_LIST *head);

/**
 * Allocate memory and create new epmpty token
 * @param token
 * @return return S_TRUE if token was successfully created else OUT_OF_MEMORY when can not be created new token
 */
int create_new_token(TOKEN **token);

/**
 * Create new token list node
 * @param list
 * @return return S_TRUE if node was successfully created else OUT_OF_MEMORY when can not be created new node
 */
int create_new_token_list(TOKEN_LIST **list);

#endif
