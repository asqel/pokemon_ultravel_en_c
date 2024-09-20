#ifndef PLAYER_H
#define PLAYER_H

#include "world.h"

// X : player_t
#define FRAME_COOLDOWN_MAX(X) ((X).is_sprinting ? 5 : 10)

void player_go_up(player_t *player);
void player_go_down(player_t *player);
void player_go_left(player_t *player);
void player_go_right(player_t *player);
void tick_player(player_t *player);

// X : player_t
#define PLAYER_SPEED(X) ((X).is_sprinting ? 3 : 1)
void do_key_actions(player_t *player) ;

void player_change_world(player_t *player, char *name, vec2i_t pos);
#endif