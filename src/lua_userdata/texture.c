#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "textures.h"
#include "user_data.h"

int l_texture_gc(lua_State *L) {
    texture_t* texture = (texture_t*)lua_touserdata(L, 1);
    if (texture && *texture != NULL) {
        *texture = NULL;
    }
    return 0;
}

int l_push_texture(lua_State *L, const char *texture_cat, const char *texture_name) {
    int err = 0;
    texture_t texture = get_texture_no_error(texture_cat, texture_name, &err);
    if (err) {
        lua_pushnil(L);
        return 1;
    }
	return l_push_texture_ptr(L, texture);
}

int l_push_texture_ptr(lua_State *L, texture_t texture) {
    texture_t* udata = (texture_t*)lua_newuserdata(L, sizeof(texture_t));

    *udata = texture;
    if (luaL_newmetatable(L, "TextureMeta")) {
        lua_pushcfunction(L, l_texture_gc);
        lua_setfield(L, -2, "__gc");
    }
    lua_setmetatable(L, -2);
    return 1;
}