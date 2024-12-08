#pragma once

#define LOGMSG_PATH_MAX_LEN 30
#define LOGMSG_MSG_MAX_LEN 30

/**
 * @brief LogMsg Severity level enum
 *
 */
typedef enum Severity
{
    ERROR,
    WARNING,
    INFO,
    DEBUG,
} Severity;

/**
 * @brief LogMsg struct
 *
 */
typedef struct LogMsg
{
    Severity severity;                 ///< Severity level
    char message[LOGMSG_PATH_MAX_LEN]; ///< Log Message text
    char path[LOGMSG_MSG_MAX_LEN];     ///< Message source file path
    int line;                          ///< Message source file line number
} LogMsg;
