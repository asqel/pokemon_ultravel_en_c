#ifndef WORLD_H
#define WORLD_H

typedef struct world_t world_t;
typedef struct chunk_t chunk_t;
typedef struct player_t player_t;
typedef struct object_t object_t;
typedef struct clothe_t clothe_t;
typedef struct gui_t gui_t;

#include <stdint.h>
#include "types.h"
#include "vec.h"
#include "textures.h"
#include "pokemon.h"

#define TILE_SIZE 60
#define CHUNK_LEN 20

// the ids are run time ids
// to get real id as str use the registers

struct object_t{
	pk_uint_t id; // 0 for air, assigned by registers

	texture_t texture;

	u8 is_funcs_lua;
	union {
		void (*c)(object_t *self, vec2i_t pos, vec2i_t screen_pos, player_t *player, SDL_Surface screen);
		int lua;
	} on_draw;
	union {
		void (*c)(object_t *self, vec2i_t pos, player_t *player);
		int lua;
	} on_walk;
	union {
		void (*c)(object_t *self, vec2i_t pos, player_t *player);
		int lua;
	} on_interact;
	union {
		void (*c)(object_t *self, vec2i_t pos, player_t *player);
		int lua;
	} tick;

	u8 has_hitbox;
	u32 extra_data;
};

typedef struct chunk_t{
	vec2i_t pos;
	vec2i_t top_left;

	object_t background_obj[CHUNK_LEN][CHUNK_LEN];
	object_t objects[CHUNK_LEN][CHUNK_LEN];
	object_t objects_foreground[CHUNK_LEN][CHUNK_LEN];

	u8 is_loaded;
} chunk_t;


typedef struct world_t{
	colour3_t background_colour;
	chunk_t **loaded_chunks; // 3 * 3
	char *name; // freed
	uint8_t is_outside;
	u8 is_loaded;
} world_t;

struct clothe_t {
	u8 type;
	pk_uint_t id;
	texture_t frames[4][3]; // [u, r, d, l][frame]
};

enum CLOTH_TYPES {
	CLOTHE_TYPE_FEET,
	CLOTHE_TYPE_HAND,
	CLOTHE_TYPE_HEAD,
	CLOTHE_TYPE_TORSO,
	CLOTHE_TYPE_BACKPACK,
	CLOTHE_TYPE_EXPRESSION,
	CLOTHE_TYPE_LEN,
};

enum DIRECTIONS {
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,
	DIR_LEFT
};

#define PLAYER_PX_SIZE 60

struct player_t{
	vec2i_t pos;
	vec2i_t cam_offset;
	vec2i_t offset;
	u8 dir;

	pokemon_t *team;
	u8 team_idx;

	world_t world;
	data_dict_t *data;

	u8 frame_idx;
	u8 frame_cooldown;
	clothe_t clothes[CLOTHE_TYPE_LEN];
	
	u8 is_moving;
	vec2i_t moving_from;
	u8 is_sprinting;

	gui_t *gui; // will be freed
};

struct gui_t {
	player_t *player;
	void (*start)(gui_t *self);
	void (*tick)(gui_t *self);
	void (*draw)(gui_t *self);
	void (*end)(gui_t *self);
	void *data; // handled by .end
};

extern object_t object_air;

#define object_is_air(X) ((X).id == 0)

// copy name
void load_chunk(world_t *world, vec2i_t chunk_pos, chunk_t *res);
void load_world(char *name, world_t *world);
int world_tick(player_t *player);
void world_display(player_t *player);
void display_player(player_t *player, vec2i_t pos);
int init_player_and_world(player_t *player, char *world_name);
void free_chunk(chunk_t chunk);
void free_world(world_t world);
void new_empty_chunk(world_t *world, vec2i_t pos, chunk_t *res);

extern clothe_t default_clothes[CLOTHE_TYPE_LEN];

#endif