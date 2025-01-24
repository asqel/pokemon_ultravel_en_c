#include "simple_dialog.h"
#include "world.h"
#include "player.h"
#include "uti.h"
#include "keys.h"


void simple_dialog_draw_func(gui_t *self) {

}

void simple_dialog_end_func(gui_t *self) {
	simple_dialago_info *info = self->data;
	for (int i = 0; i < info->len; i++)
		free(info->text[i]);
	free(info->text);
	free(self->data);
}

void simple_dialog_tick_func(gui_t *self) {
	if (key_pressed[KEY_T_INTERACT]) {

	}
}


void new_simple_dialog(player_t *player, char **text, int text_len) {
	player_close_gui(player);
	player->gui = malloc(sizeof(gui_t));
	player->gui->player = player;
	player->gui->data = malloc(sizeof(simple_dialago_info));
	player->gui->draw = &simple_dialog_draw_func;
	player->gui->end = &simple_dialog_end_func;
	player->gui->start = NULL;
	player->gui->tick = &simple_dialog_tick_func;
	((simple_dialago_info *)player->gui->data)->len = text_len;
	((simple_dialago_info *)player->gui->data)->idx = 0;
	((simple_dialago_info *)player->gui->data)->text = malloc(sizeof(char *) * text_len);
	for (int i = 0; i < text_len; i++) {
		((simple_dialago_info *)player->gui->data)->text[i] = uti_strdup(text[i]);
	}
}
