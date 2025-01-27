#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "types.h"

typedef SDL_Surface* texture_t;

typedef struct {
	texture_t *frames;
	u16 frame_len;
	u16 frame_cooldown;
} animation_t;

typedef struct {
	int len;
	char **keys;
	texture_t *values;
} texture_dict_t;

typedef struct {
	int len;
	char **keys;
	texture_dict_t *values;
} texture_dict_dict_t;

extern texture_dict_dict_t textures;
extern char *assets_path;

extern animation_t *animations;
extern int animations_len;
extern char **animations_names;

int register_textures();
void textures_exit();
int add_texture(texture_t texture, const char *category, const char *name);
texture_t get_texture(const char *category, const char *name);
texture_t get_texture_no_error(const char *category, const char *name);

u32 new_animation(const char *name, u32 frame_cooldown, u32 frame_len, ...);
u32 new_animation_arr(const char *name, u32 frame_cooldown, u32 frame_len, texture_t *frames);
u32 get_animation_id(const char *name);
animation_t *get_animation(u32 id);


#endif