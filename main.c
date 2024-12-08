#include "cmd.h"

int main()
{
    Table table = {};
    int cmd = 0;
    while (true)
    {
        print_header();

        scanf("%d", &cmd);

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
            print_data(&table.data_list, table.data_type);
            break;

        case SAVE_LIST:
            cmd_save_table(&table);
            break;

        case FILTER_LIST:
            cmd_filter_table(&table);
            break;

        case PRINT_LIST:
            cmd_print(&table);
            break;

        case SORT_LIST:
            cmd_sort_table(&table);
            break;

        case ADD_NODE:
            cmd_add_node(&table);
            break;

        case REMOVE_NODE:
            cmd_remove_node(&table);
            print_data(&table.data_list, table.data_type);
            break;

        default:
            break;
        }
    }
}
