
/**
 * @brief implements system logging 
*/

#ifndef LOG_H
#define LOG_H

typedef enum level {
    EMERGENCY,
    ALERT,
    CRITICAL,
    ERROR,
    WARNING,
    NOTICE,
    INFO,
    DEBUG

} LOG_LEVEL;

/**
 * @brief create log message
 * @param lvl log level
 * @param msg message to log
 * @param msg_buffer where to copy the message to
*/
void system_log(LOG_LEVEL lvl, const char* msg, char* msg_buffer);


#endif
