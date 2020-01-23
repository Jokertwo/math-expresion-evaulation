#include <stdio.h>
#include "zasobnik.h"
#include "logger.h"
#include "NumberBuffer.h"

int main() {
    setLogLevel(INFO);
    logInfo("Starting app");

    logInfo("Start testing stack");
    logInfo("Add %d to stack",5);
    push(5);
    logInfo("Add %d to stack",10);
    push(10);
    logInfo("Add %d to stack",100);
    push(100);

    while (isEmpty() != S_TRUE){
        int data = pop();
        logInfo("Pop %d from stack.\n",data);
    }
    logInfo("Stack is empty");

    logInfo("Start testing number buffer");
    add_number('-');
    add_number('1');
    add_number('.');
    add_number('5');

    double b = 1e2;
    double a = 1 + get_number();
    logInfo("%f",a);

    logInfo("Exiting app");

    return 0;
}
