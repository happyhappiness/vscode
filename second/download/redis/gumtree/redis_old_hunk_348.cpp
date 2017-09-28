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
        lua_pop(lua,2); /* Consume the Lua reply and remove error handler. */
    } else {
