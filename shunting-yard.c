/**
 * Created by petr on 26.01.20.
 */

#include "shunting-yard.h"
#include "constants.h"
#include <stdlib.h>
#include "token_list.h"

int shunting_yard(TOKEN_LIST *head) {
    TOKEN_LIST *temp;

    TOKEN_LIST *output;
    TOKEN_LIST *stack;

    temp = head;
    while (temp != NULL) {
        TOKEN *current;
        current = temp->value;

        if (current->type == number_t || current->type == variable_t) {
            add_to_end(current, &output);
        } else if (current->type == left_parenthesis_t) {
            add_to_begin(current, &stack);
        } else if (current->type >= plus_op) {

        }


        temp = temp->next;
    }

}