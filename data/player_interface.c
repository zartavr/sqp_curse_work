#include "player_interface.h"

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN PLAYER_NAME_MAX_LEN

void player_print_header()
{
    printf("%-5s%-20s%-10s%-10s%-20s\n", "id", "name", "score", "league", "country");
}

void player_print(void *data)
{
    Player *user = data;
    printf("%-5d%-20s%-10d%-10d%-20s\n",
           user->id,
           user->name,
           user->score,
           user->league,
           user->country);
}

PlayerField player_filter_prompt()
{
    int input;
    do
    {
        printf("%d - Filter by league\n", PLAYER_LEAGUE);
        printf("%d - Filter by country\n", PLAYER_COUNTRY);
        printf(">> ");
    } while (scanf("%d", &input) == 0 && input < PLAYER_ID && input > PLAYER_FIELD_NUM);

    return input;
}

bool player_league_filter(void *player)
{
    Player *user = player;
    return user->league == 1;
}

bool player_country_filter(void *player)
{
    Player *user = player;
    return strcmp(user->country, "Korea") == 0;
}

PlayerField player_sort_prompt()
{
    int input;
    do
    {
        printf("%d - Sort by name\n", PLAYER_NAME);
        printf("%d - Sort by score\n", PLAYER_SCORE);
        printf(">> ");
    } while (scanf("%d", &input) == 0 && input < PLAYER_ID && input > PLAYER_FIELD_NUM);

    return input;
}

bool player_score_sort(void *a, void *b)
{
    Player *user_a = a;
    Player *user_b = b;
    return user_a->score < user_b->score;
}

bool player_name_sort(void *a, void *b)
{
    Player *user_a = a;
    Player *user_b = b;
    return strcmp(user_a->name, user_b->name) > 0;
}

void player_insert_prompt(Player *player)
{
    char input[MAX_INPUT_LEN];

    printf("Enter id (. - use '%d'): ", player->id);
    scanf("%s", input);
    if (input[0] != '.')
    {
        sscanf(input, "%d", &player->id);
    }

    printf("Enter name (. - use '%s'): ", player->name);
    scanf("%s", input);
    if (input[0] != '.')
    {
        sscanf(input, "%s", player->name);
    }

    printf("Enter score (. - use '%d'): ", player->score);
    scanf("%s", input);
    if (input[0] != '.')
    {
        sscanf(input, "%d", &player->score);
    }

    printf("Enter league (. - use '%d'): ", player->league);
    scanf("%s", input);
    if (input[0] != '.')
    {
        sscanf(input, "%d", &player->league);
    }

    printf("Enter country (. - use '%s'): ", player->country);
    scanf("%s", input);
    if (input[0] != '.')
    {
        sscanf(input, "%s", player->country);
    }
}