    }
    server.lua_caller = NULL;
    selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
    lua_gc(lua,LUA_GCSTEP,1);

    if (err) {
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
