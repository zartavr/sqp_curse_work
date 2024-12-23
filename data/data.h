/**
* @file data.h
* @defgroup data 
* @{
* @brief Table API
*/

#pragma once

#include "list/list.h"
#include "player_interface.h"
#include "logmsg_interface.h"

/**
 * @brief Supported data types in Table
 * 
 */
typedef enum DataType{
    LOGMSG,
    PLAYER
}DataType;

/**
 * @brief Print Table data
 * 
 * @param list - list pointer
 * @param type - data type in list
 */
void print_data(List* list, DataType type);

/**
 * @brief Filter Table 
 * 
 * @param list - list pointer
 * @param type - data type in list
 * @return int - status: 0  - success,
 *                       -1 - wrong user input
 *                       -2 - unsupported data type
 *                       -3 - list is empty
 */
int filter_data(List* list, DataType type);

/**
 * @brief Sort Table 
 * 
 * @param list - list pointer
 * @param type - data type in list
 * @return int - status: 0  - success,
 *                       -1 - wrong user input
 *                       -2 - unsupported data type
 *                       -3 - list is empty
 */
int sort_data(List* list, DataType type);

/**
 * @brief Add new data to Table 
 * 
 * @param list - list pointer
 * @param type - data type in list
 */
void push_data(List* list, DataType type);

///  @}
