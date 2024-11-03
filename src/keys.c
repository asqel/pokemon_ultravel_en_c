#include "keys.h"
#include "types.h"
#include <SDL2/SDL.h>
#include "uti.h"

pk_uint_t key_pressed[KEY_T_LEN] = {0};
int key_map[KEY_T_LEN] = {
	SDL_SCANCODE_W,
	SDL_SCANCODE_D,
	SDL_SCANCODE_S,
	SDL_SCANCODE_A,
	SDL_SCANCODE_LSHIFT,
	SDL_SCANCODE_LCTRL,
	SDL_SCANCODE_E,
	SDL_SCANCODE_Q
};


int is_key_eq_event(SDL_Event event, u8 key) {
	if (key < 0 || key >= KEY_T_LEN)
		return 0;
	return key_map[key] == event.key.keysym.scancode;
}

void update_keys() {
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
		}
	}
}
