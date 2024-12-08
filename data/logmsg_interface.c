#include "logmsg_interface.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_INPUT_LEN LOGMSG_MSG_MAX_LEN

extern int line_counter;

void logmsg_print_header()
{
    printf("%-10s%-10s%-30s%-30s%-5s\n", "line", "severity", "message", "path", "line");
}

void logmsg_print(void *data)
{
    LogMsg *log_msg = data;
    printf("%-10d%-10d%-30s%-30s%-5d\n",
           line_counter,
           log_msg->severity,
           log_msg->message,
           log_msg->path,
           log_msg->line);
    line_counter++;
}

LogMsgField logmsg_filter_prompt()
{
    char input[MAX_INPUT_LEN];

    int variant;
    do
    {
        printf("%d - Filter by severity\n", LOGMSG_SEVERITY);
        printf("%d - Filter by path\n", LOGMSG_PATH);
        printf(">> ");
        fgets(input, MAX_INPUT_LEN, stdin);
    } while (sscanf(input, "%d", &variant) == 0 && variant < LOGMSG_SEVERITY && variant > LOGMSG_FIELD_NUM);

    return variant;
}

bool logmsg_path_filter(void *logmsg)
{
    LogMsg *log_msg = logmsg;
    return strcmp(log_msg->path, "module/process.c") == 0;
}

bool logmsg_severity_filter(void *logmsg)
{
    LogMsg *log_msg = logmsg;
    return log_msg->severity == ERROR;
}

LogMsgField logmsg_sort_prompt()
{
    char input[MAX_INPUT_LEN];

    int variant;
    do
    {
        printf("%d - Sort by path\n", LOGMSG_PATH);
        printf("%d - Sort by line number\n", LOGMSG_LINE);
        printf(">> ");
        fgets(input, MAX_INPUT_LEN, stdin);
    } while (sscanf(input, "%d", &variant) == 0 && variant < LOGMSG_SEVERITY && variant > LOGMSG_FIELD_NUM);

    return variant;
}

bool logmsg_path_sort(void *a, void *b)
{
    LogMsg *log_msg_a = a;
    LogMsg *log_msg_b = b;
    return strcmp(log_msg_a->path, log_msg_b->path) > 0;
}

bool logmsg_line_sort(void *a, void *b)
{
    LogMsg *log_msg_a = a;
    LogMsg *log_msg_b = b;
    return log_msg_a->line > log_msg_b->line;
}

void logmsg_insert_prompt(LogMsg *log_msg)
{    
    char input[MAX_INPUT_LEN];

    printf("Enter severity ('%d'): ", log_msg->severity);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%u", (unsigned int*)&log_msg->severity);
    }

    printf("Enter message ('%s'): ", log_msg->message);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%[0-9a-zA-Z ]", log_msg->message);
    }

    printf("Enter path ('%s'): ", log_msg->path);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%[0-9a-zA-Z ]", log_msg->path);
    }

    printf("Enter line ('%d'): ", log_msg->line);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%d", &log_msg->line);
    }
}
