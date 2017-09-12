int luaRedisGenericCommand(lua_State *lua, int raise_error) {
    int j, argc = lua_gettop(lua);
    struct redisCommand *cmd;
    robj **argv;
    redisClient *c = server.lua_client;
    sds reply;

    /* Build the arguments vector */
    argv = zmalloc(sizeof(robj*)*argc);
    for (j = 0; j < argc; j++) {
        if (!lua_isstring(lua,j+1)) break;
        argv[j] = createStringObject((char*)lua_tostring(lua,j+1),
                                     lua_strlen(lua,j+1));
    }
    
    /* Check if one of the arguments passed by the Lua script
     * is not a string or an integer (lua_isstring() return true for
     * integers as well). */
    if (j != argc) {
        j--;
        while (j >= 0) {
            decrRefCount(argv[j]);
            j--;
        }
        zfree(argv);
        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        return 1;
    }

    /* Setup our fake client for command execution */
    c->argv = argv;
    c->argc = argc;

    /* Command lookup */
    cmd = lookupCommand(argv[0]->ptr);
    if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
                   (argc < -cmd->arity)))
    {
        if (cmd)
            luaPushError(lua,
                "Wrong number of args calling Redis command From Lua script");
        else
            luaPushError(lua,"Unknown Redis command called from Lua script");
        goto cleanup;
    }

    /* There are commands that are not allowed inside scripts. */
    if (cmd->flags & REDIS_CMD_NOSCRIPT) {
        luaPushError(lua, "This Redis command is not allowed from scripts");
        goto cleanup;
    }

    /* Write commands are forbidden against read-only slaves, or if a
     * command marked as non-deterministic was already called in the context
     * of this script. */
    if (cmd->flags & REDIS_CMD_WRITE) {
        if (server.lua_random_dirty) {
            luaPushError(lua,
                "Write commands not allowed after non deterministic commands");
            goto cleanup;
        } else if (server.masterhost && server.repl_slave_ro &&
                   !(server.lua_caller->flags & REDIS_MASTER))
        {
            luaPushError(lua, shared.roslaveerr->ptr);
            goto cleanup;
        } else if (server.stop_writes_on_bgsave_err &&
                   server.saveparamslen > 0 &&
                   server.lastbgsave_status == REDIS_ERR)
        {
            luaPushError(lua, shared.bgsaveerr->ptr);
            goto cleanup;
        }
    }

    /* If we reached the memory limit configured via maxmemory, commands that
     * could enlarge the memory usage are not allowed, but only if this is the
     * first write in the context of this script, otherwise we can't stop
     * in the middle. */
    if (server.maxmemory && server.lua_write_dirty == 0 &&
        (cmd->flags & REDIS_CMD_DENYOOM))
    {
        if (freeMemoryIfNeeded() == REDIS_ERR) {
            luaPushError(lua, shared.oomerr->ptr);
            goto cleanup;
        }
    }

    if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;
    if (cmd->flags & REDIS_CMD_WRITE) server.lua_write_dirty = 1;

    /* Run the command */
    c->cmd = cmd;
    call(c,REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);

    /* Convert the result of the Redis command into a suitable Lua type.
     * The first thing we need is to create a single string from the client
     * output buffers. */
    reply = sdsempty();
    if (c->bufpos) {
        reply = sdscatlen(reply,c->buf,c->bufpos);
        c->bufpos = 0;
    }
    while(listLength(c->reply)) {
        robj *o = listNodeValue(listFirst(c->reply));

        reply = sdscatlen(reply,o->ptr,sdslen(o->ptr));
        listDelNode(c->reply,listFirst(c->reply));
    }
    if (raise_error && reply[0] != '-') raise_error = 0;
    redisProtocolToLuaType(lua,reply);
    /* Sort the output array if needed, assuming it is a non-null multi bulk
     * reply as expected. */
    if ((cmd->flags & REDIS_CMD_SORT_FOR_SCRIPT) &&
        (reply[0] == '*' && reply[1] != '-')) {
        /* Skip this step if command is SORT but output was already sorted */
        if (cmd->proc != sortCommand || server.sort_dontsort)
            luaSortArray(lua);
    }
    sdsfree(reply);

cleanup:
    /* Clean up. Command code may have changed argv/argc so we use the
     * argv/argc of the client instead of the local variables. */
    for (j = 0; j < c->argc; j++)
        decrRefCount(c->argv[j]);
    zfree(c->argv);

    if (raise_error) {
        /* If we are here we should have an error in the stack, in the
         * form of a table with an "err" field. Extract the string to
         * return the plain error. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        return lua_error(lua);
    }
    return 1;
}