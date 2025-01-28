#include "uti.h"
#include "registers.h"
#include "ul_errno.h"

general_register_t obj_register = {.keys = NULL, .len = 0, .types = NULL, .values = NULL};
general_register_t gui_register = {.keys = NULL, .len = 0, .types = NULL, .values = NULL};

void register_obj(const char *id, object_t o) {
	for (int i = 0; i < obj_register.len; i++) {
		if (!strcmp(obj_register.keys[i], id)) {
			ul_add_errno(ERR_OBJ_EXIST);
			return ;
		}
	}
	o.id = obj_register.len;
	obj_register.keys = realloc(obj_register.keys, sizeof(char *) * (obj_register.len + 1));
	obj_register.values = realloc(obj_register.values, sizeof(register_value) * (obj_register.len + 1));
	obj_register.keys[obj_register.len] = strdup(id);
	obj_register.values[obj_register.len].o = o;
	obj_register.len++;
	ul_add_errno(ERR_NONE);
}

object_t get_object(const char *id) {
	for (int i = 0; i < obj_register.len; i++) {
		if (!strcmp(obj_register.keys[i], id)) {
			ul_add_errno(ERR_NONE);
			return obj_register.values[i].o;
		}
	}
	ul_add_errno(ERR_OBJ_NOT_FOUND);
	return object_air;
}

object_t get_object_by_temp_id(int id) {
	if (id >= obj_register.len) {
		ul_add_errno(ERR_OBJ_NOT_FOUND);
		return object_air;
	}
	ul_add_errno(ERR_NONE);
	return obj_register.values[id].o;
}

// do not free return value
char *get_object_id_str(int id) {
	if (id >= obj_register.len) {
		ul_add_errno(ERR_OBJ_NOT_FOUND);
		return NULL;
	}
	ul_add_errno(ERR_NONE);
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

void register_gui(const char *id, void (*start)(gui_t *self), void (*tick)(gui_t *self), void (*draw)(gui_t *self), void (*end)(gui_t *self)) {
	gui_t gui = {0};
	gui.start = start;
	gui.tick = tick;
	gui.draw = draw;
	gui.end = end;
	gui_register.keys = realloc(gui_register.keys, sizeof(char *) * (gui_register.len + 1));
	gui_register.values = realloc(gui_register.values, sizeof(register_value) * (gui_register.len + 1));
	gui_register.keys[gui_register.len] = strdup(id);
	gui_register.values[gui_register.len].gui = gui;
	gui_register.len++;
}

gui_t get_gui(const char *id) {
	for (int i = 0; i < gui_register.len; i++) {
		if (!strcmp(gui_register.keys[i], id)) {
			ul_add_errno(ERR_NONE);
			return gui_register.values[i].gui;
		}
	}
	ul_add_errno(ERR_GUI_NOT_FOUND);
	return (gui_t){0};
}