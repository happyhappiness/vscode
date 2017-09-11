    }
    if (server.lua_timedout) processEventsWhileBlocked();
    if (server.lua_kill) {
        serverLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
        lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
        lua_error(lua);
    }
