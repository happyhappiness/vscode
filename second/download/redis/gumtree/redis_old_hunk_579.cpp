        lua_call(lua,2,0);
    }
    /* Stack: array (sorted), table */
    lua_pop(lua,1);             /* Stack: array (sorted) */
}

#define LUA_CMD_OBJCACHE_SIZE 32
#define LUA_CMD_OBJCACHE_MAX_LEN 64
int luaRedisGenericCommand(lua_State *lua, int raise_error) {
    int j, argc = lua_gettop(lua);
    struct redisCommand *cmd;
    redisClient *c = server.lua_client;
    sds reply;

    /* Cached across calls. */
    static robj **argv = NULL;
    static int argv_size = 0;
    static robj *cached_objects[LUA_CMD_OBJCACHE_SIZE];
