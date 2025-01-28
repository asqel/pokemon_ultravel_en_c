#ifndef REGISTERS_H
#define REGISTERS_H

#include "world.h"
#include "pokemon.h"
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

typedef union {
	char *s;
	object_t o;
	pokemon_species_info pokemon;
	clothe_t clothe;
	gui_t gui;
} register_value;

enum {
	REGISTER_T_STR,
	REGISTER_T_OBJ,
	REGISTER_T_POKEMON_INFO,
	REGISTER_T_CLOTHE,
	REGISTER_T_GUI
};


typedef struct {
	char **keys;
	int len;
	int *types;
	register_value *values;
} general_register_t;

extern general_register_t obj_register;
extern general_register_t gui_register;

void register_obj(const char *id, object_t o);
void register_simple_obj(const char *id, texture_t texture, u8 has_hitbox, u8 is_toplayer);
object_t get_object(const char *id);
object_t get_object_by_temp_id(int id);
char *get_object_id_str(int id);

void register_gui(const char *id, gui_t gui);
gui_t get_gui(const char *id);

#endif