/**
 * Created by petr on 23.01.20.
 */

#ifndef CLION_SVATAVA_TOKENIZER_H
#define CLION_SVATAVA_TOKENIZER_H

/**
 * Convert expresion to list of tokens
 * @param expresion math expresion
 * @return return S_TRUE if everything was ok else S_FALSE
 */
int tokenize_expresion(char *expresion, TOKEN_LIST **head);


#endif
