//
// Created by petr on 22.01.20.
//
#include "logger.h"
#include <stdio.h>
#include "constants.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

const int TRACE = 5;
const int DEBUG = 10;
const int INFO = 20;
const int WARN = 30;
const int ERROR = 40;
const int OFF = 100;
int SEVERITY = 10;


static char *get_severity_name(int severity);

static int count_size(const char *ptr);

static int is_new_line(const char *format);

static int print_new_line(const char *format);

static char *createMessage(const char *severity, const char *message);


void logTrace(const char *message, ...) {
    if (SEVERITY <= TRACE && message != NULL) {
        char *formatted = createMessage("TRACE: ", message);
        va_list args;

        va_start (args, message);
        vprintf(formatted, args);
        va_end (args);

        print_new_line(formatted);
        free(formatted);
    }
}


void logDebug(const char *message, ...) {
    if (SEVERITY <= DEBUG && message != NULL) {
        char *formatted = createMessage("DEBUG: ", message);
        va_list args;

        va_start (args, message);
        vprintf(formatted, args);
        va_end (args);

        print_new_line(formatted);
        free(formatted);
    }
}


void logInfo(const char *message, ...) {
    if (SEVERITY <= INFO && message != NULL) {
        char *formatted = createMessage("INFO:  ", message);
        va_list args;
        va_start (args, message);
        vprintf(formatted, args);
        va_end (args);
        print_new_line(message);
        free(formatted);
    }
}


void logWarn(const char *message, ...) {
    if (SEVERITY <= WARN && message != NULL) {
        char *formatted = createMessage("WARN:  ", message);
        va_list args;
        va_start (args, message);
        vprintf(formatted, args);
        va_end (args);
        print_new_line(message);
        free(formatted);
    }
}

void logError(const char *message, ...) {
    if (SEVERITY <= ERROR && message != NULL) {
        char *formatted = createMessage("ERROR: ", message);
        va_list args;
        va_start (args, message);
        vprintf(formatted, args);
        va_end (args);
        print_new_line(message);
        free(formatted);
    }
}


int setLogLevel(int severity) {
    if (severity >= TRACE && severity <= OFF) {
        char *oldValue = get_severity_name(SEVERITY);
        char *newValue = get_severity_name(severity);
        char str[80];
        SEVERITY = severity;
        sprintf(str, "Changing log level from: %s, to: %s", oldValue, newValue);
        logInfo(str);
        free(oldValue);
        free(newValue);
        return S_TRUE;
    }
    logError("Unknown logger level!!! Setting default INFO level");
    SEVERITY = INFO;
    return S_FALSE;
}


static char *get_severity_name(int severity) {
    char *name = malloc(sizeof(char) * 10);
    if (DEBUG == severity) {
        strcpy(name, "DEBUG");
    } else if (severity == INFO) {
        strcpy(name, "INFO");
    } else if (severity == WARN) {
        strcpy(name, "WARN");
    } else if (severity == ERROR) {
        strcpy(name, "ERROR");
    } else if (severity == OFF) {
        strcpy(name, "OFF");
    } else if (severity == TRACE) {
        strcpy(name, "TRACE");
    } else {
        strcpy(name, "UNKNOWN");
    }
    return name;
}


static int is_new_line(const char *format) {
    int size = count_size(format);
    if (size > 1 && format[size - 1] == '\n') {
        return S_TRUE;
    }
    return S_FALSE;
}

static int count_size(const char *ptr) {
    //variable used to access the subsequent array elements.
    int offset = 0;
    //variable that counts the number of elements in your array
    int count = 0;

    //While loop that tests whether the end of the array has been reached
    while (*(ptr + offset) != '\0') {
        //increment the count variable
        ++count;
        //advance to the next element of the array
        ++offset;
    }
    //return the size of the array
    return count;
}

static int print_new_line(const char *format) {
    if (is_new_line(format)) {
        printf("\n");
    }
}

static char *createMessage(const char *severity, const char *message) {
    int severity_size = count_size(severity);
    int message_size = count_size(message);

    char *formatted = (char *) malloc((sizeof(char) * (severity_size + message_size + 1)));
    strcpy(formatted, severity);
    strncat(formatted, message, message_size);
    formatted[severity_size + message_size] = '\0';
    return formatted;
}