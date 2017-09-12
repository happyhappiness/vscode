void evalGenericCommand(redisClient *c, int evalsha) {
    lua_State *lua = server.lua;
    char funcname[43];
    long long numkeys;

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
        hashScript(funcname+2,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
    } else {
        /* We already have the SHA if it is a EVALSHA */
        int j;
        char *sha = c->argv[1]->ptr;

        for (j = 0; j < 40; j++)
            funcname[j+2] = tolower(sha[j]);
        funcname[42] = '\0';
    }

    lua_getglobal(lua, funcname);
    if (lua_isnil(lua,1)) {
        sds funcdef;
      
        /* Function not defined... let's define it if we have the
         * body of the funciton. If this is an EVALSHA call we can just
         * return an error. */
        if (evalsha) {
            addReply(c, shared.noscripterr);
            lua_pop(lua,1); /* remove the nil from the stack */
            return;
        }
        funcdef = sdsempty();

        lua_pop(lua,1); /* remove the nil from the stack */
        funcdef = sdscat(funcdef,"function ");
        funcdef = sdscatlen(funcdef,funcname,42);
        funcdef = sdscatlen(funcdef," ()\n",4);
        funcdef = sdscatlen(funcdef,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
        funcdef = sdscatlen(funcdef,"\nend\n",5);
        /* printf("Defining:\n%s\n",funcdef); */

        if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
            addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
                lua_tostring(lua,-1));
            lua_pop(lua,1);
            sdsfree(funcdef);
            return;
        }
        sdsfree(funcdef);
        if (lua_pcall(lua,0,0,0)) {
            addReplyErrorFormat(c,"Error running script (new function): %s\n",
                lua_tostring(lua,-1));
            lua_pop(lua,1);
            return;
        }
        lua_getglobal(lua, funcname);

        /* We also save a SHA1 -> Original script map in a dictionary
         * so that we can replicate / write in the AOF all the
         * EVALSHA commands as EVAL using the original script. */
        {
            int retval = dictAdd(server.lua_scripts,
                                 sdsnewlen(funcname+2,40),c->argv[1]);
            redisAssertWithInfo(c,NULL,retval == DICT_OK);
            incrRefCount(c->argv[1]);
        }
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
            funcname, lua_tostring(lua,-1));
        lua_pop(lua,1);
        lua_gc(lua,LUA_GCCOLLECT,0);
        return;
    }
    selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
    luaReplyToRedisReply(c,lua);
    lua_gc(lua,LUA_GCSTEP,1);

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