void evalGenericCommand(redisClient *c, int evalsha) {
    lua_State *lua = server.lua;
    char funcname[43];
    long long numkeys;
    int delhook = 0, err;

    /* We want the same PRNG sequence at every call so that our PRNG is
     * not affected by external state. */
    redisSrand48(0);

    /* We set this flag to zero to remember that so far no random command
     * was called. This way we can allow the user to call commands like
     * SRANDMEMBER or RANDOMKEY from Lua scripts as far as no write command
     * is called (otherwise the replication and AOF would end with non
     * deterministic sequences).
     *
     * Thanks to this flag we'll raise an error every time a write command
     * is called after a random command was used. */
    server.lua_random_dirty = 0;
    server.lua_write_dirty = 0;

    /* Get the number of arguments that are keys */
    if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
        return;
    if (numkeys > (c->argc - 3)) {
        addReplyError(c,"Number of keys can't be greater than number of args");
        return;
    }

    /* We obtain the script SHA1, then check if this function is already
     * defined into the Lua state */
    funcname[0] = 'f';
    funcname[1] = '_';
    if (!evalsha) {
        /* Hash the code if this is an EVAL call */
        sha1hex(funcname+2,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
    } else {
        /* We already have the SHA if it is a EVALSHA */
        int j;
        char *sha = c->argv[1]->ptr;

        for (j = 0; j < 40; j++)
            funcname[j+2] = tolower(sha[j]);
        funcname[42] = '\0';
    }

    /* Try to lookup the Lua function */
    lua_getglobal(lua, funcname);
    if (lua_isnil(lua,1)) {
        lua_pop(lua,1); /* remove the nil from the stack */
        /* Function not defined... let's define it if we have the
         * body of the funciton. If this is an EVALSHA call we can just
         * return an error. */
        if (evalsha) {
            addReply(c, shared.noscripterr);
            return;
        }
        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) return;
        /* Now the following is guaranteed to return non nil */
        lua_getglobal(lua, funcname);
        redisAssert(!lua_isnil(lua,1));
    }

    /* Populate the argv and keys table accordingly to the arguments that
     * EVAL received. */
    luaSetGlobalArray(lua,"KEYS",c->argv+3,numkeys);
    luaSetGlobalArray(lua,"ARGV",c->argv+3+numkeys,c->argc-3-numkeys);

    /* Select the right DB in the context of the Lua client */
    selectDb(server.lua_client,c->db->id);
    
    /* Set an hook in order to be able to stop the script execution if it
     * is running for too much time.
     * We set the hook only if the time limit is enabled as the hook will
     * make the Lua script execution slower. */
    server.lua_caller = c;
    server.lua_time_start = ustime()/1000;
    server.lua_kill = 0;
    if (server.lua_time_limit > 0 && server.masterhost == NULL) {
        lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
        delhook = 1;
    }

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