#include "redis.h"
#include "sha1.h"
#include "rand.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <ctype.h>
#include <math.h>

char *redisProtocolToLuaType_Int(lua_State *lua, char *reply);
char *redisProtocolToLuaType_Bulk(lua_State *lua, char *reply);
char *redisProtocolToLuaType_Status(lua_State *lua, char *reply);
char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);
int redis_math_random (lua_State *L);
int redis_math_randomseed (lua_State *L);

/* Take a Redis reply in the Redis protocol format and convert it into a
 * Lua type. Thanks to this function, and the introduction of not connected
