#include "cmd.h"

#define CMD_INPUT_LEN 3

int main()
{
    Table table = {};
    char input[CMD_INPUT_LEN];
    while (true)
    {
        print_header();

        int cmd = EMPTY;
        fgets(input, CMD_INPUT_LEN, stdin);
        if (input[0] != '\n')
        {
            sscanf(input,"%d", &cmd);
        }
        
        switch (cmd)
        {
        case EXIT:
            cmd_exit();
            break;

        case LIST_FILES:
            cmd_list_files();
            break;

        case LOAD_LIST:
            cmd_load_table(&table);
            break;

        case SAVE_LIST:
            cmd_save_table(&table);
            break;

        case FILTER_LIST:
            cmd_filter_table(&table);
            break;

        case PRINT_LIST:
            if (table.data_list.len != 0)
            {
                cmd_print(&table);
            }
            else
            {
                printf("List is empty\n");
            }
            break;

        case SORT_LIST:
            cmd_sort_table(&table);
            break;

        case ADD_NODE:
            cmd_add_node(&table);
            break;

        case REMOVE_NODE:
            cmd_remove_node(&table);
            break;

        default:
            break;
        }
    }
}
