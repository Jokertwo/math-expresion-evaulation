/**
 * Created by petr on 22.01.20.
 */

#ifndef CLION_SVATAVA_LOGGER_H
#define CLION_SVATAVA_LOGGER_H

const int TRACE;
const int DEBUG;
const int INFO;
const int WARN;
const int ERROR;
const int OFF;


/**
 * Print log message on TRACE severity
 * @param message message message to print
 * @param ... (optional) message parameter
 */
void logTrace(const char *message, ...);

/**
 * Print log message on DEBUG severity
 * @param message message to print
 * @param ... (optional) message parameter
 */
void logDebug(const char *message, ...);

/**
 * Print log message on INFO severity
 * @param message message to print
 * @param ... (optional) message parameter
 */
void logInfo(const char *message, ...);


/**
 * Print log message on WARN severity
 * @param message  message to print
 * @param ... (optional) message parameter
 */
void logWarn(const char *message, ...);

/**
 * Print log message on ERROR severity
 * @param ... (optional) message parameter
 * @param message
 */
void logError(const char *message, ...);

/**
 * Set message level
 * @param severity
 */
int setLogLevel(int severity);

#endif /*CLION_SVATAVA_LOGGER_H*/
