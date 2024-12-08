#include "cmd.h"

#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

void cmd_exit()
{
    exit(0);
}

void cmd_list_files()
{
    DIR *dir;
    struct dirent *ent;
    dir = opendir(".");
    if (dir != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] != '.')
            {
                printf("%s\n", ent->d_name);
            }
        }
        closedir(dir);
    }
}

void cmd_load_table(Table *table)
{
    if (table==NULL)
    {
        return;
    }

    char file_name_input[FILE_NAME_MAX_LEN];

    printf("input file name: ");
    scanf("%s", file_name_input);
    FILE *fin_ptr;

    fin_ptr = fopen(file_name_input, "rb");

    if (fin_ptr == NULL)
    {
        printf("file not found\n");
        return;
    }
    fscanf(fin_ptr, "data_type: %u\tname: %s\n", &table->data_type, table->name);
    list_load(&table->data_list, fin_ptr);
    fclose(fin_ptr);

    memmove(&table->name, file_name_input, FILE_NAME_MAX_LEN);
}

void cmd_save_table(Table *table)
{
    if (table==NULL)
    {
        return;
    }

    char file_name_input[FILE_NAME_MAX_LEN];

    printf("input file name (y - use current name \"%s\"): ", table->name);
    int ret = scanf("%s", file_name_input);
    FILE *fout_ptr;

    if (strcmp(file_name_input, "y") == 0 || strcmp(file_name_input, table->name) == 0)
    {
        fout_ptr = fopen(table->name, "wb");
    }
    else
    {
        fout_ptr = fopen(file_name_input, "rb");
        if (fout_ptr != NULL)
        {
            char accept[2];
            do
            {
                printf("file already exists, overwrite? (y/n): ");
                scanf("%s", accept);
                if (strcmp(accept, "n") == 0)
                {
                    fclose(fout_ptr);
                    return;
                }
            } while (strcmp(accept, "y") != 0);
            fclose(fout_ptr);
        }
        memmove(table->name, file_name_input, FILE_NAME_MAX_LEN);
        fout_ptr = fopen(table->name, "wb");
    }
    fprintf(fout_ptr, "data_type: %u\tname: %s\n", table->data_type, table->name);
    list_save(&table->data_list, fout_ptr);
    fclose(fout_ptr);
}

void cmd_print(Table *table)
{
    if (table==NULL)
    {
        return;
    }
    print_data(&table->data_list, table->data_type);
}

void cmd_filter_table(Table *table)
{
    if (table==NULL)
    {
        return;
    }

    if (filter_data(&table->data_list, table->data_type) == 0)
    {
        print_data(&table->data_list, table->data_type);
    }
}

void cmd_sort_table(Table *table)
{
    if (table==NULL)
    {
        return;
    }

    if (sort_data(&table->data_list, table->data_type) == 0)
    {
        print_data(&table->data_list, table->data_type);
    }
}

void cmd_add_node(Table* table){
    if (table==NULL)
    {
        return;
    }

    push_data(&table->data_list, table->data_type);
}

void cmd_remove_node(Table* table){
    if (table==NULL)
    {
        return;
    }

    int line = 0;
    do
    {
        printf("Line number to remove (1 - %ld): ", table->data_list.len);
    } while (scanf("%d", &line) == 0);

    list_remove(&table->data_list, line - 1);
}

void print_help()
{
    printf("%d - exit\t%d - list files\t%d - load list\t%d - save list\n",
           EXIT, LIST_FILES, LOAD_LIST, SAVE_LIST);
    printf("%d - print list\t%d - filter list\t%d - sort list\t%d - add node\t%d - remove node\n",
           PRINT_LIST, FILTER_LIST, SORT_LIST, ADD_NODE, REMOVE_NODE);
}

void print_header()
{
    printf("\nWelcome to listDOS, commands:\n");
    print_help();
    printf(">> ");
}
