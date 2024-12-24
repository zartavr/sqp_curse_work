/** 
 * @ingroup logmsg
 * @{ 
 * @file logmsg_interface.h
 * @brief LogMsg Table interface
*/

#pragma once

#include "structure/logmsg.h"

#include <stdbool.h>

/**
 * @brief Enum of data structure fields
 * 
 */
typedef enum LogMsgField{
    LOGMSG_SEVERITY = 1,
    LOGMSG_MESSAGE,
    LOGMSG_PATH,
    LOGMSG_LINE,
    
    LOGMSG_FIELD_NUM
}LogMsgField;

/**
 * @brief Print fields names
 * 
 */
void logmsg_print_header();

/**
 * @brief Print all structure fields
 * 
 * callback for list_foreach
 * 
 * @param data - pointer to logmsg structure
 */
void logmsg_print(void *data);

/**
 * @brief User input filter prompt
 * 
 * @return LogMsgField - field to filter
 */
LogMsgField logmsg_filter_prompt();

/**
 * @brief Filter by path (hardcoded)
 * 
 * callback for list_filter
 * 
 * @param person - pointer to logmsg structure
 * @return true - keep
 * @return false - drop
 */
bool logmsg_path_filter(void *person);

/**
 * @brief Filter by severity (hardcoded)
 * 
 * callback for list_filter
 * 
 * @param person - pointer to logmsg structure
 * @return true - keep
 * @return false - drop
 */
bool logmsg_severity_filter(void *person);

/**
 * @brief User input sort prompt
 * 
 * @return LogMsgField - field to sort
 */
LogMsgField logmsg_sort_prompt();

/**
 * @brief Sort by path (hardcoded ascending)
 * 
 * @param a - pointer to left logmsg structure
 * @param b - pointer to right logmsg structure
 * @return true - swap
 * @return false - don't swap
 */
bool logmsg_path_sort(void *a, void *b);

/**
 * @brief Sort by line number (hardcoded ascending)
 * 
 * @param a - pointer to left logmsg structure
 * @param b - pointer to right logmsg structure
 * @return true - swap
 * @return false - don't swap
 */
bool logmsg_line_sort(void *a, void *b);

/**
 * @brief User input insert new record prompt
 * 
 * @param log_msg - pointer to logmsg structure
 */
void logmsg_insert_prompt(LogMsg *log_msg);
