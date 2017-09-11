     * make the Lua script execution slower. */
    if (server.lua_time_limit > 0 && server.masterhost == NULL) {
        lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
    } else {
        lua_sethook(lua,luaMaskCountHook,0,0);
    }

    /* At this point whatever this script was never seen before or if it was
     * already defined, we can call it. We have zero arguments and expect
     * a single return value. */
    server.lua_caller = c;
    server.lua_time_start = ustime()/1000;
    server.lua_kill = 0;
    if (lua_pcall(lua,0,1,0)) {
        if (server.lua_timedout) {
            server.lua_timedout = 0;
            /* Restore the readable handler that was unregistered when the
             * script timeout was detected. */
            aeCreateFileEvent(server.el,c->fd,AE_READABLE,
                              readQueryFromClient,c);
        }
        server.lua_caller = NULL;
        selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
            funcname, lua_tostring(lua,-1));
