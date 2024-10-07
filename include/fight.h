#ifndef FIGHT_H
#define FIGHT_H

#include "types.h"
#include "world.h"
#include "pokemon.h"

typedef struct {
	int (*ai_func)(struct fight_info_t *info);
	player_t *player;
	pokemon_t op_team[6];
	int turn;
	u8 first_to_move; // 0: player, 1: op
	pk_attack_t *last_move;


} fight_info_t;


extern u8 is_in_fight;


#endif