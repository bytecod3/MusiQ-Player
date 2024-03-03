#include "log.h"
#include <string.h>


/**
 * @brief create log message
 * @param lvl log level
 * @param msg message to log
 * @param msg_buffer where to copy the message to
*/
void system_log(LOG_LEVEL lvl, const char* msg, char* msg_buffer) {
    strcpy(msg_buffer, msg);

}