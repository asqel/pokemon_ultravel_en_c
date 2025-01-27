#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "textures.h"
#include "world.h"

int l_object_gc(lua_State *L) {
    object_t** texture = (object_t**)lua_touserdata(L, 1);
    if (texture && *texture != NULL) {
        *texture = NULL;
    }
    return 0;
}

int l_push_object(lua_State *L, object_t *obj) {
	object_t** udata = (object_t**)lua_newuserdata(L, sizeof(object_t *));
    *udata = obj;
    if (luaL_newmetatable(L, "ObjectMeta")) {
        lua_pushcfunction(L, l_object_gc);
        lua_setfield(L, -2, "__gc");
    }
    lua_setmetatable(L, -2);
    return 1;
}
