
    elapsed = (ustime()/1000) - server.lua_time_start;
    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
        server.lua_timedout = 1;
        /* Once the script timeouts we reenter the event loop to permit others
         * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
         * we need to mask the client executing the script from the event loop.
         * If we don't do that the client may disconnect and could no longer be
         * here when the EVAL command will return. */
         aeDeleteFileEvent(server.el, server.lua_caller->fd, AE_READABLE);
    }
    if (server.lua_timedout)
        aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
    if (server.lua_kill) {
        redisLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
        lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
        lua_error(lua);
    }
}

void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
