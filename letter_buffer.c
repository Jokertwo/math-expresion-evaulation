/**
 * Created by petr on 23.01.20.
 */

#include "letter_buffer.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>


static NODE *head_buf = NULL;


int add_letter(char letter) {
    logDebug("Inserting to letter buffer new value: %c", letter);
    return add_item(letter, &head_buf);
}

int get_letter(TOKEN *token) {
    char *expresion;

    if (concat(&expresion, &head_buf) == S_FALSE) {
        logError("Cannot concat letter to word!!!");
        return S_FALSE;
    }
    token->type = operator_t;
    token->operator = expresion;

    clear_buffer(&head_buf);
    return S_TRUE;

}
