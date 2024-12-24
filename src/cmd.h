/**
 * @file cmd.h
 * @defgroup gui GUI
 * @{
 * @brief App Command Line Interface
 */
#pragma once

#include "list/list.h"
#include "data/data.h"

#define FILE_NAME_MAX_LEN 50

/**
 * @brief App commands
 * 
 */
enum CmdID
{
    EXIT,
    LIST_FILES,
    LOAD_LIST,
    SAVE_LIST,
    PRINT_LIST,
    FILTER_LIST,
    SORT_LIST,
    ADD_NODE,
    REMOVE_NODE,

    EMPTY
};

/**
 * @brief Table 
 * 
 * Combines data structure, list and files
 * 
 */
typedef struct Table
{
    char name[FILE_NAME_MAX_LEN];
    DataType data_type;
    List data_list;
}Table;

/**
 * @brief Print App header
 * 
 */
void print_header();

/**
 * @brief Print help with commads list
 * 
 */
void print_help();

/**
 * @brief Exit App
 * 
 */
void cmd_exit();

void cmd_list_files();
void cmd_print(Table* table);
void cmd_load_table(Table* table);
void cmd_save_table(Table* table);
void cmd_filter_table(const Table* table);
void cmd_sort_table(const Table* table);
void cmd_add_node(Table* table);
void cmd_remove_node(Table* table);
/// @}
