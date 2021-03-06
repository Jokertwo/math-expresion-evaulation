/**
 * Created by petr on 22.01.20.
 */

#include "number_buffer.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include "constants.h"


static NODE *head_buf = NULL;


int add_number(char number) {
    logInfo("Inserting to number buffer new value: %c", number);
    return add_item(number, &head_buf);
}


int get_number(TOKEN *token) {
    char *number, *pEnd;
    double d1;
    int result;
    number = NULL;
    if (head_buf == NULL) {
        logError("Number buffer is empty!");
        return OUT_OF_MEMORY;
    }

    result = concat(&number, &head_buf);
    if (result != S_TRUE) {
        logError("Cannot concat number buffer!!!");
        return result;
    }


    /* convert string to number*/
    pEnd = NULL;

    d1 = strtod(number, &pEnd);
    if (strlen(pEnd) > 0) {
        logError("In number buffer was not only number: %s ", pEnd);
        free(pEnd);
        return S_FALSE;
    }
    /* release allocated resources*/
    token->function = NULL;
    token->number = d1;
    token->type = number_t;
    free(number);
    clear_buffer(&head_buf);
    return S_TRUE;
}


int is_number_buff_empty() {
    return head_buf == NULL ? S_TRUE : S_FALSE;
}


