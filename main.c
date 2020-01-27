
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "logger.h"
#include "number_buffer.h"
#include "letter_buffer.h"
#include "tokenizer.h"
#include "token_list.h"

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
    int result;
    TOKEN *token;
    logInfo(" ------ Start testing number buffer ------ ");

    result = add_number('-');
    if (result != S_TRUE) exit(result);

    result = add_number('1');
    if (result != S_TRUE) exit(result);

    result = add_number('.');
    if (result != S_TRUE) exit(result);

    result = add_number('5');
    if (result != S_TRUE) exit(result);

    token = createToken();
    if (token == NULL) {
        logError("Unable memory for token");
        exit(OUT_OF_MEMORY);
    }
    result = get_number(token);
    if (result != S_TRUE) {
        logWarn("Some error during creating token number");
        exit(result);
    }
    if (!is_number_buff_empty()) {
        logError("Number buffer is not empty but should be!");
        exit(-4);
    }
    logInfo("%f", token->number);
    releaseToken(&token);


    result = add_number('-');
    if (result != S_TRUE) exit(result);

    result = add_number('1');
    if (result != S_TRUE) exit(result);

    result = add_number('.');
    if (result != S_TRUE) exit(result);

    result = add_number('5');
    if (result != S_TRUE) exit(result);


    token = createToken();
    if (token == NULL) {
        logError("Unable memory for token");
        exit(OUT_OF_MEMORY);
    }
    result = get_number(token);
    if (result != S_TRUE) {
        logWarn("Some error during creating token number");
        exit(result);
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
    TOKEN *token;
    logInfo(" ------ Start testing letter buffer ------ ");

    add_letter('5');
    add_letter('a');
    add_letter('g');

    token = createToken();
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
    logInfo("%s", token->function);
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

    logInfo("%s", token->function);
    releaseToken(&token);

    logInfo(" ------ Stop testing letter buffer ------ ");
}

void testTokenize() {
    char *expresion;
    TOKEN_LIST *head = NULL;
    logInfo(" ------ Start testing tokenizer ------ ");
    expresion = " -(3+-6)-5*-cos(2^-5)";
    tokenize_expresion(expresion, &head);
    print_tokens(head);
    clear(&head);
    logInfo(" ------ End testing tokenizer ------ ");
}

int main(int argc, char *argv[]) {
    setLogLevel(DEBUG);
    logInfo("Starting app");

    testStack();
    testLetterBuffer();
    testNumberBuffer();
    testTokenize();


    logInfo("Exiting app");

    return 0;
}

static TOKEN *createToken() {
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->function = NULL;
    return token;
}

static void releaseToken(TOKEN **token) {
    free((*token)->function);
    free(*token);
}
