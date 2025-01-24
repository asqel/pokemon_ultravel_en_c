#include "textures.h"
#include "types.h"
#include <stdlib.h>
#include "uti.h"
#include "display.h"

texture_dict_dict_t textures = {.keys = NULL, .len = 0, .values = NULL};
char *assets_path = NULL;

// info: (x, y, width, height, new_width, new_height)
void add_image_cut(int info[6], const char *name, SDL_Surface *png, const char *category) {

	SDL_Rect srcRect = {info[0], info[1], info[2], info[3]};
	SDL_Surface *before_resize = SDL_CreateRGBSurface(0, info[2], info[3], game_surface->format->BitsPerPixel,
			game_surface->format->Rmask, game_surface->format->Gmask, game_surface->format->Bmask, game_surface->format->Amask);


	if (before_resize == NULL) {
		PRINT_ERR("ERROR: could not allocate memory for image cutting\n%s\n", SDL_GetError());
		exit(1);
	}

	SDL_BlitSurface(png, &srcRect, before_resize, NULL);

	SDL_Surface *resized_image = SDL_CreateRGBSurface(0, info[4], info[5], game_surface->format->BitsPerPixel,
			game_surface->format->Rmask, game_surface->format->Gmask, game_surface->format->Bmask, game_surface->format->Amask);
	if (resized_image == NULL) {
		PRINT_ERR("ERROR: could not allocate memory for resizing\n");
		SDL_FreeSurface(before_resize);
		exit(1);
	}
	for (int y = 0; y < info[5]; y++) {
		for (int x = 0; x < info[4]; x++) {
			int srcX = x * info[2] / info[4];
			int srcY = y * info[3] / info[5];

			Uint32 pixel = ((Uint32*)before_resize->pixels)[srcY * before_resize->w + srcX];

			((Uint32*)resized_image->pixels)[y * resized_image->w + x] = pixel;
		}
	}

    // Libérer la mémoire
    SDL_FreeSurface(before_resize);
	add_texture(resized_image, category, name);
}

void do_tx_file(char *full_path, SDL_Surface *png, const char *tx_text, const char *category) {
	int p = 0;
	while (tx_text[p] != '\0') {
		if (tx_text[p] == '\n' || tx_text[p] == '\r') {
			p++;
			continue;
		}
		if (isblank(tx_text[p])) {
			p++;
			continue;
		}
		if (tx_text[p] == '-') {
			while (tx_text[p] != '\n' && tx_text[p] != '\r' && tx_text[p] != '\0')
				p++;
			continue;
		}

		int tx_info[6] = {-1, -1 , -1, -1, -1, -1};
		int tx_info_end = 0;
		int sep_pos = p;

		while (tx_text[sep_pos] != '\0' && tx_text[sep_pos] != '$' && tx_text[sep_pos] != '\n' && tx_text[sep_pos] != '\r')
			sep_pos++;
		if (tx_text[sep_pos] != '$') {
			PRINT_ERR("ERROR: missing separator '$' in file:\n\t%s\n", full_path);
			exit(1);
		}
		for (int i = p; i < sep_pos; i++) {
			if (!isblank(tx_text[i]) && !('0' <= tx_text[i] && tx_text[i] <= '9')) {
				PRINT_ERR("ERROR: only spaces or digits (0-9) allowed on the left side of separator ($) in file:\n\t%s\n", full_path);
				exit(1);
			}
		}
		while (p < sep_pos) {
			if (isblank(tx_text[p]) && (p - 1 >= 0 && ('0' <= tx_text[p - 1] && tx_text[p - 1] <= '9'))) {
				p++;
				tx_info_end++;
				continue;
			}
			if ('0' <= tx_text[p] && tx_text[p] <= '9') {
				if (tx_info[tx_info_end] == -1)
					tx_info[tx_info_end] = 0;
				tx_info[tx_info_end] *= 10;
				tx_info[tx_info_end] += tx_text[p] - '0';
				p++;
				continue;
			}
			p++;
		}
		for (int i = 0; i < 6; i++) {
			if (tx_info[i] == -1) {
				PRINT_ERR("ERROR: missing information (expected 6 number)\n\t%s\n", full_path);
				exit(1);
			}
		}

		int name_start = sep_pos + 1;
		int name_end = name_start;

		while (tx_text[name_end] != '\0' && tx_text[name_end] != '\n' && tx_text[name_end] != '\r')
			name_end++;
		while (isblank(tx_text[name_start]))
			name_start++;
		while (isblank(tx_text[name_end - 1]))
			name_end--;
		if (name_end <= name_start) {
			PRINT_ERR("ERROR: missing information (expected a name)\n\t%s\n", full_path);
			exit(1);
		}
		char *name = malloc(sizeof(char) * (name_end - name_start + 1));

		name[name_end - name_start] = '\0';
		for (int i = name_start; i < name_end; i++)
			name[i - name_start] = tx_text[i];
		add_image_cut(tx_info, name, png, category);
		free(name);
		p = name_end;
	}
}

texture_dict_t *get_category_or_create(const char *category) {
	for (int i = 0; i < textures.len; i++) {
		if (!strcmp(category, textures.keys[i]))
			return &(textures.values[i]);
	}
	textures.len++;
	textures.keys = realloc(textures.keys, sizeof(char *) * (textures.len));
	textures.keys[textures.len - 1] = uti_strdup(category);
	textures.values = realloc(textures.values, sizeof(texture_dict_t) * (textures.len));
	textures.values[textures.len - 1].keys = NULL;
	textures.values[textures.len - 1].len = 0;
	textures.values[textures.len - 1].values = NULL;
	return &(textures.values[textures.len - 1]);
}

int add_texture(texture_t texture, const char *category, const char *name) {
	texture_dict_t *dict = get_category_or_create(category);
	for (int i = 0; i < dict->len; i++) {
		if (!strcmp(dict->keys[i], name))
			return 1;
	}
	dict->len++;
	dict->keys = realloc(dict->keys, sizeof(char *) * (dict->len));
	dict->values = realloc(dict->values, sizeof(texture_t) * (dict->len));
	dict->keys[dict->len - 1] = uti_strdup(name);
	dict->values[dict->len - 1] = texture;
	return 0;
}


int register_textures() {
	if (assets_path == NULL) {
		char *tmp[3] = {game_dir, "assets", NULL};
		assets_path = uti_join_path(tmp);
		if (assets_path == NULL)
			return 1;
	}
	char **categories = uti_dir_content(assets_path);
	if (categories == NULL)
		return 1;

	for (int i = 0; categories[i] != NULL; i++) {
			char *category_full = uti_join_path((char *[]){assets_path, categories[i], NULL});
			if (category_full == NULL) continue;

			char **textures_files = uti_dir_content(category_full);
			if (textures_files == NULL) {
				free(category_full);
				continue;
			}
			char *png_path = NULL;
			char *tx_path = NULL;
			for (int k = 0; textures_files[k] != NULL; k++) {
				if (uti_ends_with(textures_files[k], ".tx")) {
					tx_path = uti_join_path((char *[]){category_full, textures_files[k], NULL});
					if (tx_path == NULL) continue;
					png_path = uti_path_replace_ext(tx_path, ".png");
					if (png_path == NULL) continue;

					SDL_Surface *png = uti_read_png(png_path);
					if (png == NULL) {
						PRINT_ERR("ERROR: could not load %s\n", png_path);
						exit(1);
					}
					char *tx_text = uti_read_file(tx_path);
					if (tx_text == NULL) {
						PRINT_ERR("ERROR: could not load %s\n", tx_path);
						exit(1);
					}
					do_tx_file(tx_path, png, tx_text, categories[i]);
					free(tx_text);
					free(png_path);
					SDL_FreeSurface(png);
				}
			}
	}


	for (int i = 0; categories[i] != NULL; i++)
		free(categories[i]);
	free(categories);

	//for (int i = 0; i < textures.len; i++) {
	//	DEBUG("%s:\n", textures.keys[i]);
	//	for (int k = 0; k < textures.values[i].len; k++) {
	//		DEBUG("\t%s\n", textures.values[i].keys[k]);
	//	}
	//}
	return 0;
}


void textures_exit() {
	if (assets_path != NULL)
		free(assets_path);

	for (int i = 0; i < textures.len; i++) {
		for (int k = 0; k < textures.values[i].len; k++) {
			free(textures.values[i].keys[k]);
			SDL_FreeSurface(textures.values[i].values[k]);
		}
		free(textures.values[i].keys);
		free(textures.values[i].values);

	}
	free(textures.keys);
	free(textures.values);
}

texture_t get_texture(const char *category, const char *name) {
	texture_dict_t *category_dict = get_category_or_create(category);

	for (int i = 0; i < category_dict->len; i++) {
		if (!strcmp(category_dict->keys[i], name))
			return category_dict->values[i];
	}

	PRINT_ERR("ERROR: texture %s / %s doesnt exists\n", category, name);
	exit(1);
}