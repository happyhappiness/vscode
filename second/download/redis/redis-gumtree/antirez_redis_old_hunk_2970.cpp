
    elapsed = (ustime()/1000) - server.lua_time_start;
    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can shut down the server using the SHUTDOWN command.",elapsed);
        server.lua_timedout = 1;
    }
    if (server.lua_timedout)
        aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
}

void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
