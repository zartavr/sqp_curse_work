#include "data.h"

#define MAX_INPUT_LEN 50

void print_data(List *list, DataType type)
{
    if (list == NULL)
    {
        return;
    }
    
    switch (type)
    {
    case LOGMSG:
        logmsg_print_header();
        list_foreach(list, logmsg_print);
        break;

    case PLAYER:
        player_print_header();
        list_foreach(list, player_print);
        break;

    default:
        break;
    }
}

int filter_data(List *list, DataType type)
{
    if (list == NULL)
    {
        return -3;
    }
    
    int variant = 0;

    switch (type)
    {
    case LOGMSG:
        variant = logmsg_filter_prompt();
        switch (variant)
        {
        case LOGMSG_PATH:
            list_filter(list, list, logmsg_path_filter);
            break;

        case LOGMSG_SEVERITY:
            list_filter(list, list, logmsg_severity_filter);
            break;

        default:
            goto no_filter;
            break;
        }
        break;

    case PLAYER:
        variant = player_filter_prompt();
        switch (variant)
        {
        case PLAYER_LEAGUE:
            list_filter(list, list, player_league_filter);
            break;

        case PLAYER_COUNTRY:
            list_filter(list, list, player_country_filter);
            break;

        default:
            goto no_filter;
            break;
        }
        break;

    default:
        goto unckunown_data_type;
        break;
    }

    printf("Filtered data:\n");
    return 0;

no_filter:
    return -1;

unckunown_data_type:
    return -2;
}

int sort_data(List *list, DataType type)
{
    if (list == NULL)
    {
        return -3;
    }
    
    int variant = 0;

    switch (type)
    {
    case LOGMSG:
        variant = logmsg_sort_prompt();
        switch (variant)
        {
        case LOGMSG_LINE:
            list_sort(list, list, logmsg_line_sort);
            break;

        case LOGMSG_PATH:
            list_sort(list, list, logmsg_path_sort);
            break;

        default:
            goto no_filter;
            break;
        }
        break;

    case PLAYER:
        variant = player_sort_prompt();
        switch (variant)
        {
        case PLAYER_NAME:
            list_sort(list, list, player_name_sort);
            break;

        case PLAYER_SCORE:
            list_sort(list, list, player_score_sort);
            break;

        default:
            goto no_filter;
            break;
        }
        break;

    default:
        goto unckunown_data_type;
        break;
    }

    printf("Sorted data:\n");
    return 0;

no_filter:
    return -1;

unckunown_data_type:
    return -2;
}

void push_data(List *list, DataType type)
{
    if (list == NULL)
    {
        return;
    }

    switch (type)
    {
    case LOGMSG:
        LogMsg log_msg_template = {};
        logmsg_insert_prompt(&log_msg_template);
        list_push(list, &log_msg_template, sizeof(LogMsg));
        break;

    case PLAYER:
        Player player_template = {.id = list->len};
        player_insert_prompt(&player_template);
        list_push(list, &player_template, sizeof(Player));
        break;

    default:
        break;
    }
}
