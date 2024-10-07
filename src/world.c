#include "world.h"
#include "uti.h"
#include "registers.h"
#include "save.h"
#include "font.h"
#include "display.h"
#include "world_editor.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_load.h"
#include "user_data.h"


object_t object_air = (object_t){0};

texture_t MISSING_TEXTURE = NULL;

void new_empty_chunk(world_t *world, vec2i_t pos, chunk_t *res) {
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			res->background_obj[i][k] = get_object("grass");
			res->objects[i][k] = object_air;
			res->objects_foreground[i][k] = object_air;
		}
	}
	res->pos = pos;
	res->top_left = (vec2i_t){.x = pos.x * CHUNK_LEN, .y = pos.y * CHUNK_LEN};
}

void load_chunk(world_t *world, vec2i_t chunk_pos, chunk_t *res) {
	res->pos = chunk_pos;
	char *chunk_path = get_chunk_path(world, res);
	char *chunk_content = uti_read_file(chunk_path);
	free(chunk_path);
	if (chunk_content == NULL) {
		new_empty_chunk(world, chunk_pos, res);
		res->is_loaded = 1;
		return ;
	}
	res->top_left.x = chunk_pos.x * CHUNK_LEN;
	res->top_left.y = chunk_pos.y * CHUNK_LEN;
	decode_chunk(world, res, (u8 *)chunk_content);
	res->is_loaded = 1;
	free(chunk_content);
}

// copy name
void load_world(char *name, world_t *world) {
	world->name = uti_strdup(name);
	world->is_outside = 0;
	world->background_colour = (colour3_t){255, 255, 255};
	world->loaded_chunks = malloc(sizeof(chunk_t *) * 3);
	for (int i = 0; i < 3; i++) {
		world->loaded_chunks[i] = malloc(sizeof(chunk_t) * 3);
	}
	world->is_loaded = 1;
}

int world_tick(player_t *player) {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			for (int i = 0; i < CHUNK_LEN; i++) {
				for (int k = 0; k < CHUNK_LEN; k++) {
					object_t *o = &(player->world.loaded_chunks[y][x].objects[i][k]);
					if (o->id == 0)
						continue;
					if (o->is_funcs_lua) {
						if (o->tick.lua != 0) {
							vec2i_t pos = player->world.loaded_chunks[y][x].top_left;
							pos.x += k;
							pos.y += i;
							lua_rawgeti(state, LUA_REGISTRYINDEX, o->tick.lua);
							lua_pushnumber(state, pos.x);
							lua_pushnumber(state, pos.y);
							l_push_object(state, o);
							if (lua_pcall(state, 3, 0, 0) != LUA_OK) {
								PRINT_ERR("ERROR: ticking object at (%d %d)\n", pos.x, pos.y);
								lua_error(state);
    						}
						}
					}
					else {
						if (o->tick.c != NULL) {
							vec2i_t pos = player->world.loaded_chunks[y][x].top_left;
							pos.x += k;
							pos.y += i;
							(*o->tick.c)(o, pos, player);
						}
					}
				}
			}
		}
	}
	return 0;
}

void display_chunk_background(chunk_t *chunk, vec2i_t offset) {
	if (chunk == NULL)
		return ;
	for (int y = 0; y < CHUNK_LEN; y++) {
		for (int x = 0; x < CHUNK_LEN; x++) {
			if (chunk->background_obj[y][x].id && chunk->background_obj[y][x].texture) {
				
				display_blit_at(
					chunk->background_obj[y][x].texture,
					(x + chunk->top_left.x) * TILE_SIZE + offset.x,
					(y + chunk->top_left.y) * TILE_SIZE + offset.y
				);
			}
		}	
	}
}
void display_chunk_object(chunk_t *chunk, vec2i_t offset) {
	if (chunk == NULL)
		return ;
	for (int y = 0; y < CHUNK_LEN; y++) {
		for (int x = 0; x < CHUNK_LEN; x++) {
			if (chunk->objects[y][x].id && chunk->objects[y][x].texture) {
				
				display_blit_at(
					chunk->objects[y][x].texture,
					(x + chunk->top_left.x) * TILE_SIZE + offset.x,
					(y + chunk->top_left.y) * TILE_SIZE + offset.y
				);
			}
		}	
	}
}

void world_display(player_t *player) {
	SDL_FillRect(game_surface, &(SDL_Rect){.h = GAME_HEIGHT, .w = GAME_WIDTH, .x = 0, .y = 0}, 0);
	vec2i_t offset = (vec2i_t) {
		.x = GAME_WIDTH / 2 - player->pos.x * TILE_SIZE -  PLAYER_PX_SIZE / 2 - player->offset.x - player->cam_offset.x,
		.y = GAME_HEIGHT / 2 - player->pos.y * TILE_SIZE -  PLAYER_PX_SIZE / 2 - player->offset.y - player->cam_offset.y
	};
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (player->world.loaded_chunks[y][x].is_loaded)
				display_chunk_background(
					&(player->world.loaded_chunks[y][x]),
					offset
				);
		}
	}
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (player->world.loaded_chunks[y][x].is_loaded)
				display_chunk_object(
					&(player->world.loaded_chunks[y][x]),
					offset
				);
		}
	}
	display_player(player, (vec2i_t){.x = player->pos.x * TILE_SIZE + offset.x + player->offset.x, .y =  player->pos.y * TILE_SIZE + offset.y + player->offset.y});
	#ifdef WORLD_EDITOR

	#endif
}

void display_player(player_t *player, vec2i_t pos) {
	#ifndef WORLD_EDITOR
		for (int i = 0; i < CLOTHE_TYPE_LEN; i++) {
			if (player->clothes[i].id != 0) {
				display_blit_at(player->clothes[i].frames[player->dir][player->frame_idx], pos.x, pos.y);
			}
			else {
				if (i == CLOTHE_TYPE_EXPRESSION)
					continue;
				display_blit_at(default_clothes[i].frames[player->dir][player->frame_idx], pos.x, pos.y);
			}
		}
	#else
		we_target_texture_cooldown -= 1;
		if (we_target_texture_cooldown <= 0) {
			we_target_texture_cooldown = 20;
			if (we_target_texture_idx == 0)
				we_target_texture_idx = 1;
			else
				we_target_texture_idx = 0;
		}
		display_blit_at(we_target_texture[we_target_texture_idx], pos.x, pos.y);
		render_text(get_object_id_str(we_obj_idx), 0, 0);
		if (we_obj_layer == 0) {
			render_text("background", 0, 30);
		}
		if (we_obj_layer == 1) {
			render_text("object", 0, 30);
		}
		if (we_obj_layer == 2) {
			render_text("foreground", 0, 30);
		}
	#endif
}


void free_chunk(chunk_t chunk) {
	// TODO : free chunk
}

void free_world(world_t world) {
	// TODO : free world
}