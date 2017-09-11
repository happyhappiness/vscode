#include "redis.h"
#include "sha1.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <ctype.h>

char *redisProtocolToLuaType_Int(lua_State *lua, char *reply);
char *redisProtocolToLuaType_Bulk(lua_State *lua, char *reply);
char *redisProtocolToLuaType_Status(lua_State *lua, char *reply);
char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);

/* Take a Redis reply in the Redis protocol format and convert it into a
 * Lua type. Thanks to this function, and the introduction of not connected
