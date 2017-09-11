    return 1;
}

void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
    long long elapsed;
    REDIS_NOTUSED(ar);

    if (server.lua_time_limit <= 0) return;
    elapsed = (ustime()/1000) - server.lua_time_start;
    if (elapsed >= server.lua_time_limit) {
        lua_pushstring(lua,"Script aborted for max execution time...");
        lua_error(lua);
        redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time",elapsed);
    }
}

void scriptingInit(void) {
    lua_State *lua = lua_open();
    luaL_openlibs(lua);
