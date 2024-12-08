#pragma once

#define PLAYER_NAME_MAX_LEN 16
#define PLAYER_COUNTRY_MAX_LEN 16

/**
 * @brief Player struct
 *
 */
typedef struct Player
{
    int id;                               ///< Player id
    char name[PLAYER_NAME_MAX_LEN];       ///< Player name
    int score;                            ///< Player score
    int league;                           ///< Player league id
    char country[PLAYER_COUNTRY_MAX_LEN]; ///< Player country
} Player;
