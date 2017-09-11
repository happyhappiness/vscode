    lua_pop(lua,1);             /* Stack: array (sorted) */
}

#define LUA_CMD_OBJCACHE_SIZE 32
#define LUA_CMD_OBJCACHE_MAX_LEN 64
int luaRedisGenericCommand(lua_State *lua, int raise_error) {
