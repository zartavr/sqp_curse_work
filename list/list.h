#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief List structure
 *
 * @struct List
 * @var List::head
 * Pointer to the first element of the list
 * @var List::tail
 * Pointer to the last element of the list
 * @var List::len
 * Number of elements in the list
 */
typedef struct List
{
    void *head;
    void *tail;
    size_t len;
} List;

/**
 * @brief Get element at specified index
 *
 * @param list
 * List structure
 * @param index
 * Element index
 * @return
 * Pointer to the element at specified index
 */
void *list_at(const List *list, int index);

/**
 * @brief Add new element to the end of the list
 *
 * @param list
 * List structure
 * @param data
 * Pointer to the data to store in the element
 * @param size
 * Size of the data in bytes
 */
void list_push(List *list, const void *data, size_t size);

/**
 * @brief Remove element at specified index
 *
 * @param list
 * List structure
 * @param index
 * Element index
 */
void list_remove(List *list, int index);

/**
 * @brief Remove all elements from the list
 *
 * Free all allocated memory, reset list structure
 * 
 * @param list
 * List structure
 */
void list_clear(List *list);

/**
 * @brief Copy all elements from one list to another
 *
 * @param src
 * Source list structure
 * @param dst
 * Destination list structure
 */
void list_copy(const List *src, List *dst);

/**
 * @brief Get number of elements in the list
 *
 * @param list
 * List structure
 * @return
 * Number of elements in the list
 */
int list_get_len(const List *list);

/**
 * @brief Save list to file
 *
 * @param list
 * List structure
 * @param fout_ptr
 * File pointer
 */
void list_save(const List *list, FILE *fout_ptr);

/**
 * @brief Load list from file
 *
 * @param list
 * List structure
 * @param fin_ptr
 * File pointer
 * @return int - status: 0  - success,
 *                       -1 - file corrupted
 *                       -2 - invalid arguments
 */
int list_load(List *list, FILE *fin_ptr);

/**
 * @brief Pointer to callback function
 *
 * @param element
 * Element in the list
 */
typedef void (*foreach_cb)(void *element);

/**
 * @brief Apply callback function to all elements in the list
 *
 * @param list
 * List structure
 * @param callback
 * Callback function
 */
void list_foreach(List *list, foreach_cb callback);

/**
 * @brief Pointer to filter function
 *
 * @param element
 * Element in the list
 * @return
 * True if element should be kept
 */
typedef bool (*keep_cb)(void *element);

/**
 * @brief Filter elements in the list with user defined callback
 *
 * @param src
 * Source list structure
 * @param dst
 * Destination list structure
 * @param callback
 * Callback function, returns true if element should be kept
 */
void list_filter(const List *src, List *dst, keep_cb callback);

/**
 * @brief Pointer to comparison function
 *
 * @param element_left
 * Left element in the list
 * @param element_right
 * Right element in the list
 * @return
 * True if elements should be swapped
 */
typedef bool (*swap_cb)(void *element_left, void *element_right);

/**
 * @brief Sort elements in the list with user defined comparison function
 *
 * @param src
 * Source list structure
 * @param dst
 * Destination list structure
 * @param callback
 * Callback function, returns true if elements should be swapped
 */
void list_sort(const List *src, List *dst, swap_cb callback);
