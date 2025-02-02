/** 
 * @ingroup player
 * @{
 * @file player_interface.h 
 * @brief Player Table interface, for further information see logmsg_interface.h
*/
#pragma once

#include "structure/player.h"

#include <stdbool.h>

typedef enum PlayerField{
    PLAYER_ID = 1,
    PLAYER_NAME,
    PLAYER_SCORE,
    PLAYER_LEAGUE,
    PLAYER_COUNTRY,

    PLAYER_FIELD_NUM
}PlayerField;

void player_print_header();
void player_print(void *data);

PlayerField player_filter_prompt();
bool player_league_filter(void *person);
bool player_country_filter(void *person);

PlayerField player_sort_prompt();
bool player_score_sort(void *a, void *b);
bool player_name_sort(void *a, void *b);

void player_insert_prompt(Player *player);
/// @}
