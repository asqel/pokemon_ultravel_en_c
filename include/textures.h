#ifndef TEXTURES_H
#define TEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef SDL_Surface* texture_t;

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

int register_textures();
void textures_exit();
int add_texture(texture_t texture, const char *category, const char *name);
texture_t get_texture(const char *category, const char *name);
texture_t get_texture_no_error(const char *category, const char *name, int *error);

#endif