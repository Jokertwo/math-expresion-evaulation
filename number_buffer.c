//
// Created by petr on 22.01.20.
//

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

    char *number = NULL;
    if (head_buf == NULL) {
        logError("Number buffer is empty!");
        return S_FALSE;
    }

    if (concat(&number, &head_buf) == S_FALSE) {
        logError("Cannot concat number buffer!!!");
        return S_FALSE;
    }


    // convert string to number
    char *pEnd = NULL;
    double d1;
    d1 = strtod(number, &pEnd);
    if (strlen(pEnd) > 0) {
        logError("In number buffer was not only number: %s ", pEnd);
        free(pEnd);
        return S_FALSE;
    }
    // release allocated resources
    token->operator = NULL;
    token->number = d1;
    token->type = number_t;
    free(number);
    clear_buffer(&head_buf);
    return S_TRUE;
}


