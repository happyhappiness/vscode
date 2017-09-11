void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
    long long elapsed;
    REDIS_NOTUSED(ar);

    elapsed = (ustime()/1000) - server.lua_time_start;
    if (elapsed >= server.lua_time_limit) {
        redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time.",elapsed);
        lua_pushstring(lua,"Script aborted for max execution time.");
        lua_error(lua);
    }
}

void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
