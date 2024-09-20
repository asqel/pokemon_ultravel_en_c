
#include <SDL2/SDL.h>
#include <stdio.h>
#include "types.h"
#include "uti.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *game_texture = NULL;
SDL_Surface *game_surface = NULL;

const int GAME_WIDTH = 960;
const int GAME_HEIGHT = 540;

int display_init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		PRINT_ERR("Error while initializing SDL2: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Fenêtre SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		PRINT_ERR("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		PRINT_ERR("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	game_surface = SDL_CreateRGBSurface(0, GAME_WIDTH, GAME_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (game_surface == NULL) {
		PRINT_ERR("Error creating game surface: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	game_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, GAME_WIDTH, GAME_HEIGHT);
	if (game_texture == NULL) {
		PRINT_ERR("Erreur lors de la création de la texture: %s\n", SDL_GetError());
		SDL_FreeSurface(game_surface);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	return 0;
}

void display_exit() {
	if (game_texture != NULL) {
		SDL_DestroyTexture(game_texture);
	}
	if (game_surface != NULL) {
		SDL_FreeSurface(game_surface);
	}
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if (window != NULL) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

void display_fill_screen(colour3_t col) {
	SDL_FillRect(game_surface, NULL, SDL_MapRGB(game_surface->format, col.r, col.g, col.b));
}

void display_update_screen() {
   // Copier la surface de jeu dans la texture
    SDL_UpdateTexture(game_texture, NULL, game_surface->pixels, game_surface->pitch);

    // Obtenir la taille actuelle de la fenêtre
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    // Calculer le facteur d'échelle pour maintenir le rapport d'aspect
    double scale_factor_width = (double)window_width / (double)GAME_WIDTH;
    double scale_factor_height = (double)window_height / (double)GAME_HEIGHT;

    // Utiliser le plus petit facteur d'échelle pour maintenir le rapport d'aspect
    double scale_factor = (scale_factor_width < scale_factor_height) ? scale_factor_width : scale_factor_height;

    // Calculer les nouvelles dimensions du jeu
    int adjusted_width = (int)(GAME_WIDTH * scale_factor);
    int adjusted_height = (int)(GAME_HEIGHT * scale_factor);

    // Centrer le jeu dans la fenêtre
    int x_offset = (window_width - adjusted_width) / 2;
    int y_offset = (window_height - adjusted_height) / 2;

    // Définir le rectangle de destination avec les bonnes dimensions et offsets
    SDL_Rect dst_rect = {x_offset, y_offset, adjusted_width, adjusted_height};

    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
    SDL_RenderClear(renderer);

    // Rendre la texture du jeu redimensionnée sur l'écran
    SDL_RenderCopy(renderer, game_texture, NULL, &dst_rect);

    // Afficher le rendu
    SDL_RenderPresent(renderer);
}

