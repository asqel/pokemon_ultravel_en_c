#ifndef WORLD_EDITOR_H
#define WORLD_EDITOR_H

#ifdef WORLD_EDITOR

#include "world.h"

void init_we();
void we_keys(player_t *player);
void we_unload_chunk(world_t *world, chunk_t *chunk);

extern texture_t we_target_texture[2];

extern int we_walk_cooldown;

extern pk_uint_t we_obj_idx;
extern int we_obj_layer;

extern int we_target_texture_cooldown;
extern int we_target_texture_idx;

#endif

#endif