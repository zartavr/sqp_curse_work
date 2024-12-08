#include "player_interface.h"

#include <stdio.h>
#include <string.h>

#define MAX_INPUT_LEN PLAYER_NAME_MAX_LEN

extern int line_counter;

void player_print_header()
{
    printf("%-10s%-5s%-20s%-10s%-10s%-20s\n", "line", "id", "name", "score", "league", "country");
}

void player_print(void *data)
{
    Player *user = data;
    printf("%-10d%-5d%-20s%-10d%-10d%-20s\n",
           line_counter,
           user->id,
           user->name,
           user->score,
           user->league,
           user->country);
    line_counter++;
}

PlayerField player_filter_prompt()
{
    char input[MAX_INPUT_LEN];

    int variant;
    do
    {
        printf("%d - Filter by league\n", PLAYER_LEAGUE);
        printf("%d - Filter by country\n", PLAYER_COUNTRY);
        printf(">> ");
        fgets(input, MAX_INPUT_LEN, stdin);
    } while (sscanf(input,"%d", &variant) == 0 && variant < PLAYER_ID && variant > PLAYER_FIELD_NUM);

    return variant;
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
    char input[MAX_INPUT_LEN];

    int variant;
    do
    {
        printf("%d - Sort by name\n", PLAYER_NAME);
        printf("%d - Sort by score\n", PLAYER_SCORE);
        printf(">> ");
        fgets(input, MAX_INPUT_LEN, stdin);
    } while (sscanf(input,"%d", &variant) == 0 && variant < PLAYER_ID && variant > PLAYER_FIELD_NUM);

    return variant;
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

    printf("Enter id ('%d'): ", player->id);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%d", &player->id);
    }

    printf("Enter name ('%s'): ", player->name);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%[0-9a-zA-Z ]", player->name);
    }

    printf("Enter score ('%d'): ", player->score);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%d", &player->score);
    }

    printf("Enter league ('%d'): ", player->league);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%d", &player->league);
    }

    printf("Enter country ('%s'): ", player->country);
    fgets(input, MAX_INPUT_LEN, stdin);
    if (input[0] != '\n')
    {
        sscanf(input, "%[0-9a-zA-Z ]", player->country);
    }
}