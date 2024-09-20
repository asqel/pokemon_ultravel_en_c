#ifndef DISPLAY_H
#define DISPLAY_H


#include <SDL2/SDL.h>

#include <SDL2/SDL.h>
#include <stdio.h>
#include "types.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *game_texture;
extern SDL_Surface *game_surface;

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

int display_init();
void display_exit();
void display_fill_screen(colour3_t col);
void display_update_screen();
/*
SDL_Surface *
int
int
*/
#define display_blit_at(surface, x, y) \
	{ \
    	SDL_Rect dest_rect = {x, y, surface->w, surface->h}; \
    	SDL_BlitSurface(surface, NULL, game_surface, &dest_rect); \
	}

#define FPS_MAX 60

#endif