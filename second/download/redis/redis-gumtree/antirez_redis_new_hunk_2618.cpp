    /* At this point whatever this script was never seen before or if it was
     * already defined, we can call it. We have zero arguments and expect
     * a single return value. */
    err = lua_pcall(lua,0,1,0);

    /* Perform some cleanup that we need to do both on error and success. */
    if (delhook) lua_sethook(lua,luaMaskCountHook,0,0); /* Disable hook */
    if (server.lua_timedout) {
        server.lua_timedout = 0;
        /* Restore the readable handler that was unregistered when the
         * script timeout was detected. */
        aeCreateFileEvent(server.el,c->fd,AE_READABLE,
                          readQueryFromClient,c);
    }
    server.lua_caller = NULL;
    selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
    lua_gc(lua,LUA_GCSTEP,1);

    if (err) {
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
            funcname, lua_tostring(lua,-1));
        lua_pop(lua,1); /* Consume the Lua reply. */
    } else {
        /* On success convert the Lua return value into Redis protocol, and
         * send it to * the client. */
        luaReplyToRedisReply(c,lua);
    }

    /* If we have slaves attached we want to replicate this command as
     * EVAL instead of EVALSHA. We do this also in the AOF as currently there
     * is no easy way to propagate a command in a different way in the AOF
