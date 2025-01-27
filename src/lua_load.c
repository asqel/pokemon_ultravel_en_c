#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "uti.h"
#include "types.h"
#include "world.h"
#include "registers.h"
#include "user_data.h"
#include "ul_errno.h"

lua_State *state;

void add_lua_func(char *name, int (*func) (lua_State *L)) {
	lua_pushcfunction(state, func);
    lua_setglobal(state, name);
}



/* name, texture_category, texture_name, has_hitbox, (on_draw, on_walk, on_interact, tick)
name: string
texture_category: string
texture_name: string
has_hitbox: number / boolean
on_draw: function / nil
on_walk: function / nil
on_interacr: function / nil
on_tick: function / nil
return: temp id of the object
*/
int l_ul_register_obj(lua_State *L) {
    int n = lua_gettop(L);
    if (n < 4) {
        lua_pushstring(L, "ERROR: (Ul_register_obj) needs at least 4 args\n");
        lua_error(L);
    }

    if (lua_type(L, 1) != LUA_TSTRING) {
        lua_pushstring(L, "ERROR: (Ul_register) takes string as arg 1\n");
        lua_error(L);
    }
    if (lua_type(L, 2) != LUA_TSTRING) {
        lua_pushstring(L, "ERROR: (Ul_register) takes string as arg 2\n");
        lua_error(L);
    }
    if (lua_type(L, 3) != LUA_TSTRING) {
        lua_pushstring(L, "ERROR: (Ul_register) takes string as arg 3\n");
        lua_error(L);
    }

    if (lua_type(L, 4) != LUA_TNUMBER && lua_type(L, 4) != LUA_TBOOLEAN) {
        lua_pushstring(L, "ERROR: (Ul_register) takes number or boolean as arg 4\n");
        lua_error(L);
    }

    if (n > 8) {
        lua_pushstring(L, "ERROR: (Ul_register_obj) takes at most 8 args\n");
        lua_error(L);
    }

    for (int i = 5; i <= n; i++) {
        if (lua_type(L, i) != LUA_TNIL && lua_type(L, i) != LUA_TFUNCTION) {
            lua_pushfstring(L, "ERROR: (Ul_register_obj) takes function or nil as arg %d\n", i);
            lua_error(L);
        }
    }

    object_t o = {0};
    o.texture = get_texture_no_error(lua_tostring(L, 2), lua_tostring(L, 3));
    if (UL_LAST_ERRNO() != ERR_NONE) {
        lua_pushfstring(L, "ERROR: (Ul_register_obj) texture %s %s not found\n", lua_tostring(L, 2), lua_tostring(L, 3));
        lua_error(L);
    }
    o.has_hitbox = lua_toboolean(L, 4);
    o.is_funcs_lua = 1;

    if (n >= 5 && lua_type(L, 5) == LUA_TFUNCTION) {
        lua_pushvalue(L, 5);
        o.on_draw.lua = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    if (n >= 6 && lua_type(L, 6) == LUA_TFUNCTION) {
        lua_pushvalue(L, 6);
        o.on_walk.lua = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    if (n >= 7 && lua_type(L, 7) == LUA_TFUNCTION) {
        lua_pushvalue(L, 7);
        o.on_interact.lua = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    if (n >= 8 && lua_type(L, 8) == LUA_TFUNCTION) {
        lua_pushvalue(L, 8);
        o.tick.lua = luaL_ref(L, LUA_REGISTRYINDEX);
    }
    register_obj(lua_tostring(L, 1), o);
    return 0;
}



int l_ul_get_texture(lua_State *L) {
    int n = lua_gettop(L);
    if (n != 2 || lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
        lua_pushstring(L, "ERROR: (Ul_get_texture) requires 2 string arguments\n");
        lua_error(L);
    }
    l_push_texture(L, lua_tostring(L, 1), lua_tostring(L, 2));
    return 1;
}

// object, texture
int l_ul_set_texture(lua_State *L) {
    int n = lua_gettop(L);

    if (n != 2) {
        lua_pushstring(L, "ERROR: (ul_set_texture) requires 2 arguments (object, texture)\n");
        return lua_error(L);
    }
    if (luaL_checkudata(L, 1, "ObjectMeta") == NULL) {
        lua_pushstring(L, "ERROR: First argument (object) must be a userdata\n");
        return lua_error(L);
    }
    if (luaL_checkudata(L, 2, "TextureMeta") == NULL) {
        lua_pushstring(L, "ERROR: Second argument (texture) must be a userdata\n");
        return lua_error(L);
    }
    object_t** object = lua_touserdata(L, 1);
    texture_t* texture = (texture_t*)lua_touserdata(L, 2);
    (*object)->texture = *texture;
    return 0;
}

// name, frame_cooldown, ... (textures)
int l_ul_new_animation(lua_State *L) {
    int n = lua_gettop(L);
    if (n < 3) {
        lua_pushstring(L, "ERROR: ul_new_animation requires at least 3 arguments\n");
        return lua_error(L);
    }
    if (lua_type(L, 1) != LUA_TSTRING) {
        lua_pushstring(L, "ERROR: First argument (name) must be a string\n");
        return lua_error(L);
    }
    if (lua_type(L, 2) != LUA_TNUMBER) {
        lua_pushstring(L, "ERROR: Second argument (frame_cooldown) must be a number\n");
        return lua_error(L);
    }
    for (int i = 3; i <= n; i++) {
        if (luaL_checkudata(L, i, "TextureMeta") == NULL) {
            lua_pushstring(L, "ERROR: Arguments after frame_cooldown must be userdata\n");
            return lua_error(L);
        }
    }
    animation_t anim = {0};
    anim.frame_cooldown = lua_tonumber(L, 2);
    anim.frame_len = n - 2;
    anim.frames = malloc(sizeof(texture_t) * anim.frame_len);
    for (int i = 0; i < anim.frame_len; i++) {
        texture_t* texture = (texture_t*)lua_touserdata(L, i + 3);
        anim.frames[i] = *texture;
    }

    u32 id = new_animation_arr(lua_tostring(L, 1), anim.frame_cooldown, anim.frame_len, anim.frames);
    lua_pushnumber(L, id);
    return 1;

}

void do_luas() {
	state = luaL_newstate();
	luaL_openlibs(state);
	char *path = uti_join_path((char *[]){game_dir, "scripts", "init.lua", NULL});
	//add_lua_func("ul_debug", &l_ul_debug);

	add_lua_func("Ul_register_obj", l_ul_register_obj);
	//add_lua_func("ul_register_obj_animated", l_ul_register_obj_animated);
	add_lua_func("Ul_get_texture", l_ul_get_texture);
	add_lua_func("Ul_set_texture", l_ul_set_texture);
    add_lua_func("Ul_new_animation", l_ul_new_animation);

	if (luaL_dofile(state, path) != 0) {
    	DEBUG("%s\n", lua_tostring(state, -1));
		exit(1);
	}
	free(path);
}
