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

    int result = concat(&expresion, &head_buf);
    if (result != S_TRUE) {
        return result;
    }
    if (strcmp(expresion, "x") == 0) {
        token->type = variable_t;
        free(expresion);
        token->other = 'x';
    } else {
        token->type = function_t;
        token->function = expresion;
    }

    clear_buffer(&head_buf);
    return S_TRUE;

}


int is_letter_buff_empty() {
    return head_buf == NULL ? S_TRUE : S_FALSE;
}
