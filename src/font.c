#include <SDL2/SDL.h>
#include "textures.h"
#include "types.h"
#include "uti.h"
#include "display.h"
#include "font.h"
#include <wchar.h>


void render_char_utf8(char c[5], int x, int y) {
	char *texture_name = malloc(sizeof(char) * (strlen("std_") + 5 + 1));
	texture_name[0] = '\0';
	strcat(texture_name, "std_");
	strcat(texture_name, c);
	int error = 0;
	texture_t to_render = get_texture_no_error("fonts", texture_name, &error);
	if (error)
		to_render = get_texture("fonts", "std_?!");
	display_blit_at(to_render, x, y);
	free(texture_name);
}

void render_text(char *text, int x, int y) {
	int i = 0;

	while (text[i] != '\0') {
		if (!(0b10000000 & text[i])) {
			if (text[i] == ' ') {
				x += TEXT_CHAR_SIZE;
				i++;
				continue;
			}
			char c[5] = {text[i], 0, 0, 0, 0};
			render_char_utf8(c, x, y);
			i++;
			x += TEXT_CHAR_SIZE;
		}
		else if (0b110 == (((u8)text[i]) >> 5)) {
			char c[5] = {text[i], text[i + 1], 0, 0, 0};
			render_char_utf8(c, x, y);
			i += 2;
			x += TEXT_CHAR_SIZE;

		}
		else if (0b1110 ==  (((u8)text[i]) >> 4)) {
			char c[5] = {text[i], text[i + 1], text[i + 2], 0, 0};
			render_char_utf8(c, x, y);
			i += 3;
			x += TEXT_CHAR_SIZE;

		}
		else if (0b11110 ==  (((u8)text[i]) >> 3)) {
			char c[5] = {text[i], text[i + 1], text[i + 2], text[i + 3], 0};
			render_char_utf8(c, x, y);
			i += 4;
			x += TEXT_CHAR_SIZE;

		}
		else {
			i++;
			x += TEXT_CHAR_SIZE;
		}
	}

}