#ifndef REGISTERS_H
#define REGISTERS_H

#include "world.h"
#include "pokemon.h"

typedef union {
	char *s;
	object_t o;
	pokemon_species_info pokemon;
	pokemon_t (*new_pokemon)(int gender, int shiny);
	clothe_t clothe;
} register_value;

enum {
	REGISTER_T_STR,
	REGISTER_T_OBJ,
	REGISTER_T_POKEMON_INFO,
	REGISTER_T_POKEMON,
	REGISTER_T_CLOTHE
};


typedef struct {
	char **keys;
	int len;
	int *types;
	register_value *values;
} general_register_t;




#endif