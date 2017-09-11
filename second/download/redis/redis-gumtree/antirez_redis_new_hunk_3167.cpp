    /* Select the right DB in the context of the Lua client */
    selectDb(server.lua_client,c->db->id);
    
    /* Set an hook in order to be able to stop the script execution if it
     * is running for too much time.
     * We set the hook only if the time limit is enabled as the hook will
     * make the Lua script execution slower. */
    if (server.lua_time_limit > 0) {
        lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
        server.lua_time_start = ustime()/1000;
    } else {
        lua_sethook(lua,luaMaskCountHook,0,0);
    }

    /* At this point whatever this script was never seen before or if it was
     * already defined, we can call it. We have zero arguments and expect
     * a single return value. */
    if (lua_pcall(lua,0,1,0)) {
        selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
