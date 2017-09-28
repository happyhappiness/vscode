
    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
        addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
            lua_tostring(lua,-1));
        lua_pop(lua,1);
        sdsfree(funcdef);
        return REDIS_ERR;
    }
    sdsfree(funcdef);
    if (lua_pcall(lua,0,0,0)) {
        addReplyErrorFormat(c,"Error running script (new function): %s\n",
            lua_tostring(lua,-1));
        lua_pop(lua,1);
        return REDIS_ERR;
    }

    /* We also save a SHA1 -> Original script map in a dictionary
     * so that we can replicate / write in the AOF all the
     * EVALSHA commands as EVAL using the original script. */
    {
        int retval = dictAdd(server.lua_scripts,
                             sdsnewlen(funcname+2,40),body);
        redisAssertWithInfo(c,NULL,retval == DICT_OK);
        incrRefCount(body);
    }
    return REDIS_OK;
}

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
    } else if (numkeys < 0) {
        addReplyError(c,"Number of keys can't be negative");
