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
     * and in the replication link.
     *
     * IMPROVEMENT POSSIBLE:
     * 1) Replicate this command as EVALSHA in the AOF.
     * 2) Remember what slave already received a given script, and replicate
     *    the EVALSHA against this slaves when possible.
     */
    if (evalsha) {
        robj *script = dictFetchValue(server.lua_scripts,c->argv[1]->ptr);

        redisAssertWithInfo(c,NULL,script != NULL);
        rewriteClientCommandArgument(c,0,
            resetRefCount(createStringObject("EVAL",4)));
        rewriteClientCommandArgument(c,1,script);
    }
}

void evalCommand(redisClient *c) {
    evalGenericCommand(c,0);
}
