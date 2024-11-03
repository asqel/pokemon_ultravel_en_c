#ifndef SIMPLE_DIALOG_H
#define SIMPLE_DIALOG_H

#include "world.h"

typedef struct {
	char **text;
	int len;
	int idx;
} simple_dialago_info;

void new_simple_dialog(player_t *player, char **text, int text_len);

#endif