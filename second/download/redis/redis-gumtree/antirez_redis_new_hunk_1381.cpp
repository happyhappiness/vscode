
    elapsed = mstime() - server.lua_time_start;
    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
        serverLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
        server.lua_timedout = 1;
        /* Once the script timeouts we reenter the event loop to permit others
         * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
