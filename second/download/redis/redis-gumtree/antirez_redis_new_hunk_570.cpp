
    /* Free the current command argv if we break inside the while loop. */
    sdsfreesplitres(argv,argc);
    return C_OK;
}

/* This is the core of our Lua debugger, called each time Lua is about
 * to start executing a new line. */
void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    ldb.currentline = ar->currentline;

    int bp = ldbIsBreakpoint(ldb.currentline) || ldb.luabp;
    int timeout = 0;

    /* Events outside our script are not interesting. */
    if(strstr(ar->short_src,"user_script") == NULL) return;

    /* Check if a timeout occurred. */
    if (ar->event == LUA_HOOKCOUNT && ldb.step == 0 && bp == 0) {
        mstime_t elapsed = mstime() - server.lua_time_start;
        mstime_t timelimit = server.lua_time_limit ?
                             server.lua_time_limit : 5000;
        if (elapsed >= timelimit) {
            timeout = 1;
            ldb.step = 1;
        } else {
            return; /* No timeout, ignore the COUNT event. */
        }
    }

    if (ldb.step || bp) {
        char *reason = "step over";
        if (bp) reason = ldb.luabp ? "redis.breakpoint() called" :
                                     "break point";
        else if (timeout) reason = "timeout reached, infinite loop?";
        ldb.step = 0;
        ldb.luabp = 0;
        ldbLog(sdscatprintf(sdsempty(),
            "* Stopped at %d, stop reason = %s",
            ldb.currentline, reason));
        ldbLogSourceLine(ldb.currentline);
        ldbSendLogs();
        if (ldbRepl(lua) == C_ERR && timeout) {
            /* If the client closed the connection and we have a timeout
             * connection, let's kill the script otherwise the process
             * will remain blocked indefinitely. */
            lua_pushstring(lua, "timeout during Lua debugging with client closing connection");
            lua_error(lua);
        }
        server.lua_time_start = mstime();
    }
}

