#include "world.h"
#include "uti.h"
#include "display.h"

object_t object_air = (object_t){
				.data = NULL,
				.has_hitbox = 0,
				.id = 0,
				.is_top_layer = 0,
				.texture = NULL,
				.tick = NULL
};

texture_t MISSING_TEXTURE = NULL;

void new_empty_chunk(world_t *world, vec2i_t pos, chunk_t *res) {
	if (MISSING_TEXTURE == NULL) {
		MISSING_TEXTURE = get_texture("obj", "grass0");
		object_air.texture = MISSING_TEXTURE;
	}
	for (int i = 0; i < 20; i++) {
		for (int k = 0; k < 20; k++) {
			res->background_obj[i][k] = object_air;
			res->objects[i][k] = object_air;
			res->objects_foreground[i][k] = object_air;
			res->dyn_objects[i][k] = object_air;
			res->dyn_objects_foreground[i][k] = object_air;
		}
	}
	res->pos = pos;
	res->top_left = (vec2i_t){.x = pos.x * TILE_SIZE, .y = pos.y * TILE_SIZE};
}

void load_chunk(world_t *world, vec2i_t chunk_pos, chunk_t *res) {
	new_empty_chunk(world, chunk_pos, res);
	res->is_loaded = 1;
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

	return 0;
}

void display_chunk_background(chunk_t *chunk, vec2i_t offset, vec2i_t relative_pos) {
	if (chunk == NULL)
		return ;
	for (int y = 0; y < CHUNK_LEN; y++) {
		for (int x = 0; x < CHUNK_LEN; x++) {
			if (chunk->background_obj[y][x].texture) {
				
				display_blit_at(
					chunk->background_obj[y][x].texture,
					x * TILE_SIZE + offset.x + relative_pos.x,
					y * TILE_SIZE + offset.y + relative_pos.y
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
					offset,
					(vec2i_t){
						.x = (x - 1) * CHUNK_LEN * TILE_SIZE,
						.y = (y - 1) * CHUNK_LEN * TILE_SIZE
					}
				);
		}
	}
	display_player(player, (vec2i_t){.x = player->pos.x * TILE_SIZE + offset.x + player->offset.x, .y =  player->pos.y * TILE_SIZE + offset.y + player->offset.y});
}

void display_player(player_t *player, vec2i_t pos) {
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
}


void free_chunk(chunk_t chunk) {
	// TODO : free chunk
}

void free_world(world_t world) {
	// TODO : free world
}