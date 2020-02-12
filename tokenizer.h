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


/**
 * Iterate throw list and try find an unary operators by following rules:
 * if '-' is first token in list or previous token is operator_t or left parenthesis then token is unary operator_t
 * @param head head of token list
 * @return return S_TRUE if everything was ok else some error code
 */
int resolveUnary(TOKEN_LIST **head);

#endif
