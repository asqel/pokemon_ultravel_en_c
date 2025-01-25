#include "uti.h"
#include "registers.h"

general_register_t obj_register = {.keys = NULL, .len = 0, .types = NULL, .values = NULL};

void register_obj(const char *id, object_t o) {
	for (int i = 0; i < obj_register.len; i++) {
		if (!strcmp(obj_register.keys[i], id)) {
			PRINT_ERR("ERROR: duplicate entry in registered objects\n\t%s\n", id);
			exit(1);
		}
	}
	o.id = obj_register.len;
	obj_register.keys = realloc(obj_register.keys, sizeof(char *) * (obj_register.len + 1));
	obj_register.values = realloc(obj_register.values, sizeof(register_value) * (obj_register.len + 1));
	obj_register.keys[obj_register.len] = strdup(id);
	obj_register.values[obj_register.len].o = o;
	obj_register.len++;
}

object_t get_object(const char *id) {
	for (int i = 0; i < obj_register.len; i++) {
		if (!strcmp(obj_register.keys[i], id)) {
			return obj_register.values[i].o;
		}
	}
	PRINT_ERR("ERROR: cannot get object\n\t%s\n", id);
	exit(1);
}

object_t get_object_by_temp_id(int id) {
	if (id >= obj_register.len) {
		PRINT_ERR("ERROR: cannot get object of id\n\t%d\n", id);
		exit(1);
	}
	return obj_register.values[id].o;
}

// do not free return value
char *get_object_id_str(int id) {
	if (id >= obj_register.len) {
		PRINT_ERR("ERROR: cannot get str id\n\t%d\n", id);
		exit(1);
	}
	return obj_register.keys[id];
}


void register_simple_obj(const char *id, texture_t texture, u8 has_hitbox, u8 is_toplayer) {
	object_t o = {0};
	o.is_funcs_lua = 0;
	o.has_hitbox = has_hitbox;
	o.texture = texture;
	o.animation_id = 0;
	o.frame_idx = 0;
	o.frame_cooldown = 0;
	register_obj(id, o);
}

void register_simple_obj_animated(const char *id, u32 animation_id, u8 has_hitbox, u8 is_toplayer) {
	object_t o = {0};
	o.texture = (texture_t){0};
	o.is_funcs_lua = 0;
	o.has_hitbox = has_hitbox;
	o.animation_id = animation_id;
	o.frame_idx = 0;
	o.frame_cooldown = 0;
	register_obj(id, o);
}

void register_pokemon_simple() {

}