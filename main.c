#if defined(_WIN32)
	#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "uti.h"
#include <stdio.h>
#include "display.h"
#include "textures.h"
#include <signal.h>
#include "pokemon.h"
#include "world.h"
#include "player.h"
#include "keys.h"
#include "font.h"
#include "object.h"
#include "world_editor.h"
#include "lua_load.h"


int main(int argc, char* argv[]) {
	if (display_init() != 0) {
		return -1;
	}
	if (uti_init() != 0) {
		display_exit();
		return -1;
	}
	if (register_textures()) {
		display_exit();
		uti_exit();
		return -1;
	}
	register_objects();
	do_luas();
	#ifdef WORLD_EDITOR
		init_we();
	#endif

	int quit = 0;
	player_t *player;
	player = malloc(sizeof(player_t));
	init_player_and_world(player, "start");
	while (!quit) {
		pk_uint_t time_start = SDL_GetTicks();

		#ifndef WORLD_EDITOR
			update_keys();
			do_key_actions(player);
		#else
			we_keys(player);
		#endif
		if (player->gui == NULL) {
			tick_player(player);
			world_tick(player);
		}
		else
			(*player->gui->tick)(player->gui);

		world_display(player);
		if (player->gui != NULL)
			(*player->gui->draw)(player->gui);
		display_update_screen();

		pk_uint_t time_end = SDL_GetTicks();
		if (time_end - time_start < 1000 / FPS_MAX)
			SDL_Delay(1000 / FPS_MAX - (time_end - time_start));
	}
	free_world(player->world);
	free(player);
	uti_init();
	textures_exit();
	display_exit();
	return 0;
}
