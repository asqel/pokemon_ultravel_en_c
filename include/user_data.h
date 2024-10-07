#ifndef PK_USER_DATA_H
#define PK_USER_DATA_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "textures.h"
#include "world.h"

int l_push_texture(lua_State *L, const char *texture_name, const char *texture_type);
int l_push_object(lua_State *L, object_t *obj);

#endif