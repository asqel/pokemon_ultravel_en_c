#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "textures.h"

int l_texture_gc(lua_State *L) {
    texture_t* texture = (texture_t*)lua_touserdata(L, 1);
    if (texture && *texture != NULL) {
        *texture = NULL;
    }
    return 0;
}

int l_push_texture(lua_State *L, const char *texture_name, const char *texture_type) {
	texture_t* udata = (texture_t*)lua_newuserdata(L, sizeof(texture_t));
    
	*udata = get_texture(texture_name, texture_type);
    if (luaL_newmetatable(L, "TextureMeta")) {
        lua_pushcfunction(L, l_texture_gc);
        lua_setfield(L, -2, "__gc");
    }
    lua_setmetatable(L, -2);
    return 1;
}
