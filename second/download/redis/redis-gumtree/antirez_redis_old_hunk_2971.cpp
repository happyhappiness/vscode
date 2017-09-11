     * make the Lua script execution slower. */
    if (server.lua_time_limit > 0 && server.masterhost == NULL) {
        lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
        server.lua_time_start = ustime()/1000;
    } else {
        lua_sethook(lua,luaMaskCountHook,0,0);
    }

    /* At this point whatever this script was never seen before or if it was
     * already defined, we can call it. We have zero arguments and expect
     * a single return value. */
    if (lua_pcall(lua,0,1,0)) {
        server.lua_timedout = 0;
        selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
            funcname, lua_tostring(lua,-1));
