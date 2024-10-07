#ifdef WORLD_EDITOR

#include "world_editor.h"
#include "world.h"
#include "textures.h"
#include "keys.h"
#include <SDL2/SDL.h>
#include "save.h"
#include "registers.h"
#include "uti.h"


texture_t we_target_texture[2];

void init_we() {
	we_target_texture[0] = get_texture("world_editor", "target1");
	we_target_texture[1] = get_texture("world_editor", "target2");
}

int we_walk_cooldown = 20;

pk_uint_t we_obj_idx = 0;
int we_obj_layer = 0;

int we_target_texture_cooldown = 0;
int we_target_texture_idx = 0;

void we_keys(player_t *player) {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			exit(1);
		}
		if (e.type == SDL_KEYUP) {
			for (int i = 0; i < KEY_T_LEN; i++) {
				if (key_map[i] == e.key.keysym.scancode) {
					key_pressed[i] = 0;
					break;
				}
			}
		}
		if (e.type == SDL_KEYDOWN) {
			for (int i = 0; i < KEY_T_LEN; i++) {
				if (key_map[i] == e.key.keysym.scancode) {
					key_pressed[i] += 1;
					break;
				}
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_LEFT) {
				if (we_obj_idx == 0) {
					we_obj_idx = obj_register.len - 1;
				}
				we_obj_idx -= 1;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
				we_obj_idx += 1;
				if (we_obj_idx >= obj_register.len) {
					we_obj_idx = 0;
				}
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_UP) {
				we_obj_layer += 1;
				if (we_obj_layer >= 3)
					we_obj_layer = 0;
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_DOWN) {
				we_obj_layer -= 1;
				if (we_obj_layer < 0)
					we_obj_layer = 2;
			}
			if (e.key.keysym.sym == SDLK_p) {
				int x = player->pos.x - player->world.loaded_chunks[1][1].top_left.x;
				int y = player->pos.y - player->world.loaded_chunks[1][1].top_left.y;
				if (we_obj_layer == 0) {
					player->world.loaded_chunks[1][1].background_obj[y][x] = get_object_by_temp_id(we_obj_idx);
				}
				if (we_obj_layer == 1) {
					player->world.loaded_chunks[1][1].objects[y][x] = get_object_by_temp_id(we_obj_idx);
				}
				if (we_obj_layer == 2) {
					player->world.loaded_chunks[1][1].objects_foreground[y][x] = get_object_by_temp_id(we_obj_idx);
				}
			}
			if (e.key.keysym.sym == SDLK_o) {
				int x = player->pos.x - player->world.loaded_chunks[1][1].pos.x;
				int y = player->pos.y - player->world.loaded_chunks[1][1].pos.y;
				if (we_obj_layer == 0) {
					player->world.loaded_chunks[1][1].background_obj[y][x] = object_air;
				}
				if (we_obj_layer == 1) {
					player->world.loaded_chunks[1][1].objects[y][x] = object_air;
				}
				if (we_obj_layer == 2) {
					player->world.loaded_chunks[1][1].objects_foreground[y][x] = object_air;
				}
			}
			if (e.key.keysym.sym == SDLK_l) {
				if (we_obj_layer == 0) {
					for (int y = 0; y < CHUNK_LEN; y++)
						for (int x = 0; x < CHUNK_LEN; x++)
							player->world.loaded_chunks[1][1].background_obj[y][x] = get_object_by_temp_id(we_obj_idx);
				}
				if (we_obj_layer == 1) {
					for (int y = 0; y < CHUNK_LEN; y++)
						for (int x = 0; x < CHUNK_LEN; x++)
							player->world.loaded_chunks[1][1].objects[y][x] = get_object_by_temp_id(we_obj_idx);
				}
				if (we_obj_layer == 2) {
					for (int y = 0; y < CHUNK_LEN; y++)
						for (int x = 0; x < CHUNK_LEN; x++)
							player->world.loaded_chunks[1][1].objects_foreground[y][x] = get_object_by_temp_id(we_obj_idx);
				}
			}
			if (e.key.keysym.sym == SDLK_0) {
				for (int i = 0; i < 3; i++)
					for (int k = 0; k < 3; k++)
						save_chunk(&player->world, &player->world.loaded_chunks[i][k]);
			}
		}
	}
	if (we_walk_cooldown)
		we_walk_cooldown -= 1;
	if (key_pressed[KEY_T_UP]) {
		if (key_pressed[KEY_T_SPRINT]) {
			player->pos.y -= 1;
		}
		else if (we_walk_cooldown == 0) {
			player->pos.y -= 1;
			we_walk_cooldown = 20;
		}
	}
	if (key_pressed[KEY_T_DOWN]) {
		if (key_pressed[KEY_T_SPRINT]) {
			player->pos.y += 1;
		}
		else if (we_walk_cooldown == 0) {
			player->pos.y += 1;
			we_walk_cooldown = 20;
		}
	}
	if (key_pressed[KEY_T_LEFT]) {
		if (key_pressed[KEY_T_SPRINT]) {
			player->pos.x -= 1;
		}
		else if (we_walk_cooldown == 0) {
			player->pos.x -= 1;
			we_walk_cooldown = 20;
		}
	}
	if (key_pressed[KEY_T_RIGHT]) {
		if (key_pressed[KEY_T_SPRINT]) {
			player->pos.x += 1;
		}
		else if (we_walk_cooldown == 0) {
			player->pos.x += 1;
			we_walk_cooldown = 20;
		}
	}
	if (key_pressed[KEY_T_STAY]) {
		DEBUG(\
			"(%d %d)\n"\
			"\n(%d %d) (%d %d) (%d %d)\n"\
			"(%d %d) (%d %d) (%d %d)\n"\
			"(%d %d) (%d %d) (%d %d)\n",\
			player->pos.x, player->pos.y,\
			player->world.loaded_chunks[0][0].pos.x, player->world.loaded_chunks[0][0].pos.y, player->world.loaded_chunks[0][1].pos.x, player->world.loaded_chunks[0][1].pos.y, player->world.loaded_chunks[0][2].pos.x, player->world.loaded_chunks[0][2].pos.y,\
			player->world.loaded_chunks[1][0].pos.x, player->world.loaded_chunks[1][0].pos.y, player->world.loaded_chunks[1][1].pos.x, player->world.loaded_chunks[1][1].pos.y, player->world.loaded_chunks[1][2].pos.x, player->world.loaded_chunks[1][2].pos.y,\
			player->world.loaded_chunks[2][0].pos.x, player->world.loaded_chunks[2][0].pos.y, player->world.loaded_chunks[2][1].pos.x, player->world.loaded_chunks[2][1].pos.y, player->world.loaded_chunks[2][2].pos.x, player->world.loaded_chunks[2][2].pos.y);
	}
}

void we_unload_chunk(world_t *world, chunk_t *chunk) {
	save_chunk(world, chunk);
	free_chunk(*chunk);
}

#endif