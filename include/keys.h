#ifndef KEYS_H
#define KEYS_H

#include <SDL2/SDL.h>
#include "types.h"

enum {
	KEY_T_UP,
	KEY_T_RIGHT,
	KEY_T_DOWN,
	KEY_T_LEFT,
	KEY_T_STAY,
	KEY_T_SPRINT,
	KEY_T_INTERACT,
	KEY_T_CANCEL,

	KEY_T_LEN,
};

extern pk_uint_t key_pressed[KEY_T_LEN];
extern int key_map[KEY_T_LEN];


void update_keys();

#endif