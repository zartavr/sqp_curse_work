#include "list.h"

#include <memory.h>

/**
 * @brief Node structure
 *
 * Internal list element descriptor
 *
 */
typedef struct Node
{
    void *data;
    size_t data_size;
    struct Node *next;
} Node;

// Forward declaration for internal functions
Node *_list_node_at(const List *list, int index);

void _list_node_foreach(List *list, foreach_cb callback);

void _node_swap(Node *prev, Node *current);
void _node_print(const void *const data);
void _print_memory(FILE *fout_ptr, const void *pointer, size_t size);

void list_print(const List *list)
{
    if (list == NULL)
    {
        return;
    }

    printf("head: %p, tail: %p, length: %lu\n", list->head, list->tail, list->len);
}

void *list_at(const List *list, int index)
{
    if (list == NULL)
    {
        return NULL;
    }

    Node *target_node = _list_node_at(list, index);
    return target_node ? target_node->data : NULL;
}

void list_remove(List *list, int index)
{
    if (list == NULL)
    {
        return;
    }

    if (index < 0 || index >= list->len)
    {
        return;
    }

    Node *prev_node, *node, *next_node;

    if (index > 0 && index < list->len - 1)
    {
        prev_node = _list_node_at(list, index - 1);
        node = prev_node->next;
        next_node = node->next;

        prev_node->next = next_node;
    }
    else if (index == 0) // rm head
    {
        node = list->head;
        next_node = node->next;

        list->head = next_node;
    }
    else if (index == list->len - 1) // rm tail
    {
        prev_node = _list_node_at(list, index - 1);
        node = prev_node->next;

        prev_node->next = 0;
        list->tail = prev_node;
    }
    free(node->data);
    free(node);

    list->len--;
}

void list_push(List *list, const void *data, size_t size)
{
    if (list == NULL || data == NULL)
    {
        return;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));

    void *heap_data = malloc(size);
    memcpy(heap_data, data, size);

    new_node->data = heap_data;
    new_node->data_size = size;
    new_node->next = 0;

    if (list->head != 0)
    {
        Node *tail_node = (Node *)list->tail;
        tail_node->next = new_node;
        list->tail = new_node;
    }
    else // first element
    {
        list->head = new_node;
        list->tail = new_node;
    }

    list->len++;
};

void list_save(const List *list, FILE *fout_ptr)
{
    if (list == NULL || fout_ptr == NULL)
    {
        return;
    }

    _print_memory(fout_ptr, list, sizeof(List));

    Node *node = list->head;

    while (node != 0)
    {
        _print_memory(fout_ptr, node, sizeof(Node));
        _print_memory(fout_ptr, node->data, node->data_size);
        node = node->next;
    }
}

void list_load(List *list, FILE *fin_ptr)
{
    if (list == NULL || fin_ptr == NULL)
    {
        return;
    }

    char *byte_pointer;

    List buf = {};

    byte_pointer = (char *)&buf;
    for (size_t i = 0; i < sizeof(List); i++)
    {
        *byte_pointer = getc(fin_ptr);
        byte_pointer++;
    }

    list_clear(list);

    for (size_t i = 0; i < buf.len; i++)
    {
        Node node = {};
        byte_pointer = (char *)&node;

        for (size_t i = 0; i < sizeof(Node); i++)
        {
            *byte_pointer = getc(fin_ptr);
            byte_pointer++;
        }

        void *data = malloc(node.data_size);
        byte_pointer = data;
        for (size_t i = 0; i < node.data_size; i++)
        {
            *byte_pointer = getc(fin_ptr);
            byte_pointer++;
        }

        list_push(list, data, node.data_size);

        free(data);
    }
}

void list_foreach(List *list, foreach_cb callback)
{
    if (list == NULL || callback == NULL)
    {
        return;
    }

    Node *node = list->head;

    while (node != 0)
    {
        callback(node->data);
        node = node->next;
    }
};

int list_get_len(const List *list)
{
    if (list == NULL)
    {
        return 0;
    }

    return list->len;
}

void list_clear(List *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *node = list->head;

    while (node != 0)
    {
        Node *next_node = node->next;
        free(node->data);
        free(node);
        node = next_node;
    }

    list->head = 0;
    list->tail = 0;
    list->len = 0;
}

void list_filter(const List *src, List *dst, keep_cb callback)
{
    if (src == NULL || dst == NULL || callback == NULL)
    {
        return;
    }

    Node *node = src->head;
    List buf = {};

    while (node != 0)
    {
        bool condition = callback(node->data);
        if (condition)
        {
            list_push(&buf, node->data, node->data_size);
        }
        node = node->next;
    }

    list_clear(dst);

    memcpy(dst, &buf, sizeof(List));
}

void list_copy(const List *src, List *dst)
{
    if (src == NULL || dst == NULL)
    {
        return;
    }

    if (src == dst || dst->len != 0)
    {
        // WARNING: source and destination list are equal
        // WARNING: destination list not empty
        return;
    }

    Node *node = src->head;

    while (node != 0)
    {
        list_push(dst, node->data, node->data_size);
        node = node->next;
    }
}

void list_sort(const List *src, List *dst, swap_cb callback)
{
    if (src == NULL || dst == NULL || callback == NULL)
    {
        return;
    }

    List buf = {};

    list_copy(src, &buf);

    for (size_t i = 0; i < buf.len; i++)
    {
        Node *prev = 0;
        Node *node = buf.head;
        while (node->next != 0)
        {
            Node *next = node->next;
            bool condition = callback(node->data, next->data);
            if (condition)
            {
                _node_swap(prev, node);
                if (prev == 0)
                {
                    buf.head = next;
                }
            }
            prev = node;
            node = next;
        }
    }

    list_clear(dst);

    memcpy(dst, &buf, sizeof(List));
}

Node *_list_node_at(const List *list, int index)
{

    if (index < 0 || index >= list->len)
    {
        return NULL;
    }

    Node *current = list->head;

    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    return current;
}

void _list_node_foreach(List *list, foreach_cb callback)
{
    Node *current = list->head;

    while (current != 0)
    {
        callback(current);
        current = current->next;
    }
}

void _node_swap(Node *prev, Node *current)
{
    Node *next = current->next;

    if (prev != 0)
    {
        prev->next = next;
        current->next = next->next;
        next->next = current;
    }
    else
    {
        Node *buf = next->next;
        next->next = current;
        current->next = buf;
    }
}

void _node_print(const void *const data)
{
    const Node *node = data;
    printf("addr: %p\t next: %p\t data: %p\t data_size: %lu\n",
           (void *)node, node->next, node->data, node->data_size);
}

void _print_memory(FILE *fout_ptr, const void *pointer, size_t size)
{
    const char *byte = pointer;
    for (size_t i = 0; i < size; i++)
    {
        fputc(byte[i], fout_ptr);
    }
}
