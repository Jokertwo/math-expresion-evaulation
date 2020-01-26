
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "logger.h"
#include "number_buffer.h"
#include "letter_buffer.h"
#include "tokenizer.h"

static TOKEN *createToken();

static void releaseToken(TOKEN **token);

void testStack() {
    logInfo(" ------ Start testing stack ------ ");
    logInfo("Add %d to stack", 5);
    push(5);
    logInfo("Add %d to stack", 10);
    push(10);
    logInfo("Add %d to stack", 100);
    push(100);

    while (isEmpty() != S_TRUE) {
        int data = pop();
        logInfo("Pop %d from stack.\n", data);
    }

    logInfo("Add %d to stack", 5);
    push(500);
    logInfo("Add %d to stack", 10);
    push(1110);
    logInfo("Add %d to stack", 100);
    push(-100);

    while (isEmpty() != S_TRUE) {
        int data = pop();
        logInfo("Pop %d from stack.\n", data);
    }

    logInfo(" ------ Finish testing stack ------ ");
}

void testNumberBuffer() {
    logInfo(" ------ Start testing number buffer ------ ");
    add_number('-');
    add_number('1');
    add_number('.');
    add_number('5');


    TOKEN *token = createToken();
    if (token == NULL) {
        logError("Unable memory for token");
        exit(-1);
    }
    if (!get_number(token)) {
        logWarn("Some error during creating token number");
        exit(-2);
    }
    if (!is_number_buff_empty()) {
        logError("Number buffer is not empty but should be!");
        exit(-4);
    }
    logInfo("%f", token->number);
    releaseToken(&token);


    add_number('-');
    add_number('1');
    add_number('.');
    add_number('5');


    token = createToken();
    if (token == NULL) {
        logError("Unable memory for token");
        exit(-1);
    }
    if (!get_number(token)) {
        logError("Some error during creating token number");
        exit(-2);
    }
    if (!is_number_buff_empty()) {
        logError("Number buffer is not empty but should be!");
        exit(-4);
    }

    logInfo("%f", token->number);
    releaseToken(&token);

    logInfo(" ------ Finish testing number buffer ------ ");
}

void testLetterBuffer() {
    logInfo(" ------ Start testing letter buffer ------ ");

    add_letter('5');
    add_letter('a');
    add_letter('g');

    TOKEN *token = createToken();
    if (token == NULL) {
        logError("Unable memory for token");
        exit(-1);
    }
    if (!get_letter(token)) {
        logError("Some error during creating token numbertoken");
        exit(-2);
    }

    if (!is_letter_buff_empty()) {
        logError("Letter buffer is not empty but should be!");
        exit(-3);
    }
    logInfo("%s", token->operator);
    releaseToken(&token);

    add_letter('6');
    add_letter('4');
    add_letter('g');

    token = createToken();
    if (token == NULL) {
        logError("Unable memory for token");
        exit(-1);
    }
    if (!get_letter(token)) {
        logWarn("Some error during creating token number");
        exit(-2);
    }
    if (!is_letter_buff_empty()) {
        logError("Letter buffer is not empty but should be!");
        exit(-3);
    }

    logInfo("%s", token->operator);
    releaseToken(&token);

    logInfo(" ------ Stop testing letter buffer ------ ");
}

void testTokenize() {
    char *expresion = " 0x12          +((2*cos(x^2)/5)+5) * sin(x^(tan(x + 5E5)))   88 9 +";
    tokenize_expresion(expresion);
    print_tokens();
    clear();
}

int main(int argc, char *argv[]) {
    setLogLevel(DEBUG);
    logInfo("Starting app");

    //testStack();
    //testLetterBuffer();
    //testNumberBuffer();
    testTokenize();
    int a = 0x12;
    logInfo("%d", a);

    logInfo("Exiting app");

    return 0;
}

static TOKEN *createToken() {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->operator = NULL;
    return token;
}

static void releaseToken(TOKEN **token) {
    free((*token)->operator);
    free(*token);
}
