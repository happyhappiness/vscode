     * already defined, we can call it. We have zero arguments and expect
     * a single return value. */
    if (lua_pcall(lua,0,1,0)) {
        selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
            funcname, lua_tostring(lua,-1));
        lua_pop(lua,1);
        lua_gc(lua,LUA_GCCOLLECT,0);
        return;
    }
    selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
    luaReplyToRedisReply(c,lua);
    lua_gc(lua,LUA_GCSTEP,1);
