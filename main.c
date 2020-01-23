
#include <stdlib.h>
#include "zasobnik.h"
#include "logger.h"
#include "number_buffer.h"

int main() {
    setLogLevel(INFO);
    logInfo("Starting app");

    logInfo("Start testing stack");
    logInfo("Add %d to stack", 5);
    push(5);
    logInfo("Add %d to stack",10);
    push(10);
    logInfo("Add %d to stack",100);
    push(100);

    while (isEmpty() != S_TRUE){
        int data = pop();
        logInfo("Pop %d from stack.\n", data);
    }
    logInfo("Stack is empty");

    logInfo("Start testing number buffer");
    add_number('-');
    add_number('1');
    add_number('.');
    add_number('5');


    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    if (token == NULL) {
        logError("Unable memory for token");
        exit(-1);
    }
    if (get_number(token) != S_TRUE) {
        logWarn("Some error during creating token number");
        exit(-2);
    }
    logInfo("%f", token->number);
    free(token);

    logInfo("Exiting app");

    return 0;
}
