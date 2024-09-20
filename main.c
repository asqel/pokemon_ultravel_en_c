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

	int quit = 0;
	player_t *player;
	player = malloc(sizeof(player_t));
	init_player_and_world(player, "");
	while (!quit) {
		pk_uint_t time_start = SDL_GetTicks();

		update_keys();
		do_key_actions(player);

		tick_player(player);
		world_tick(player);

		world_display(player);
		render_text("", 0, 0);
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
