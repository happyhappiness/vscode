int luaRedisGenericCommand(lua_State *lua, int raise_error) {
    int j, argc = lua_gettop(lua);
    struct redisCommand *cmd;
    client *c = server.lua_client;
    sds reply;

    /* Cached across calls. */
    static robj **argv = NULL;
    static int argv_size = 0;
    static robj *cached_objects[LUA_CMD_OBJCACHE_SIZE];
    static size_t cached_objects_len[LUA_CMD_OBJCACHE_SIZE];
    static int inuse = 0;   /* Recursive calls detection. */

    /* By using Lua debug hooks it is possible to trigger a recursive call
     * to luaRedisGenericCommand(), which normally should never happen.
     * To make this function reentrant is futile and makes it slower, but
     * we should at least detect such a misuse, and abort. */
    if (inuse) {
        char *recursion_warning =
            "luaRedisGenericCommand() recursive call detected. "
            "Are you doing funny stuff with Lua debug hooks?";
        serverLog(LL_WARNING,"%s",recursion_warning);
        luaPushError(lua,recursion_warning);
        return 1;
    }
    inuse++;

    /* Require at least one argument */
    if (argc == 0) {
        luaPushError(lua,
            "Please specify at least one argument for redis.call()");
        inuse--;
        return 1;
    }

    /* Build the arguments vector */
    if (argv_size < argc) {
        argv = zrealloc(argv,sizeof(robj*)*argc);
        argv_size = argc;
    }

    for (j = 0; j < argc; j++) {
        char *obj_s;
        size_t obj_len;
        char dbuf[64];

        if (lua_type(lua,j+1) == LUA_TNUMBER) {
            /* We can't use lua_tolstring() for number -> string conversion
             * since Lua uses a format specifier that loses precision. */
            lua_Number num = lua_tonumber(lua,j+1);

            obj_len = snprintf(dbuf,sizeof(dbuf),"%.17g",(double)num);
            obj_s = dbuf;
        } else {
            obj_s = (char*)lua_tolstring(lua,j+1,&obj_len);
            if (obj_s == NULL) break; /* Not a string. */
        }

        /* Try to use a cached object. */
        if (j < LUA_CMD_OBJCACHE_SIZE && cached_objects[j] &&
            cached_objects_len[j] >= obj_len)
        {
            sds s = cached_objects[j]->ptr;
            argv[j] = cached_objects[j];
            cached_objects[j] = NULL;
            memcpy(s,obj_s,obj_len+1);
            sdssetlen(s, obj_len);
        } else {
            argv[j] = createStringObject(obj_s, obj_len);
        }
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
        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        inuse--;
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
    c->cmd = cmd;

    /* There are commands that are not allowed inside scripts. */
    if (cmd->flags & CMD_NOSCRIPT) {
        luaPushError(lua, "This Redis command is not allowed from scripts");
        goto cleanup;
    }

    /* Write commands are forbidden against read-only slaves, or if a
     * command marked as non-deterministic was already called in the context
     * of this script. */
    if (cmd->flags & CMD_WRITE) {
        if (server.lua_random_dirty && !server.lua_replicate_commands) {
            luaPushError(lua,
                "Write commands not allowed after non deterministic commands. Call redis.replicate_commands() at the start of your script in order to switch to single commands replication mode.");
            goto cleanup;
        } else if (server.masterhost && server.repl_slave_ro &&
                   !server.loading &&
                   !(server.lua_caller->flags & CLIENT_MASTER))
        {
            luaPushError(lua, shared.roslaveerr->ptr);
            goto cleanup;
        } else if (server.stop_writes_on_bgsave_err &&
                   server.saveparamslen > 0 &&
                   server.lastbgsave_status == C_ERR)
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
        (cmd->flags & CMD_DENYOOM))
    {
        if (freeMemoryIfNeeded() == C_ERR) {
            luaPushError(lua, shared.oomerr->ptr);
            goto cleanup;
        }
    }

    if (cmd->flags & CMD_RANDOM) server.lua_random_dirty = 1;
    if (cmd->flags & CMD_WRITE) server.lua_write_dirty = 1;

    /* If this is a Redis Cluster node, we need to make sure Lua is not
     * trying to access non-local keys, with the exception of commands
     * received from our master. */
    if (server.cluster_enabled && !(server.lua_caller->flags & CLIENT_MASTER)) {
        /* Duplicate relevant flags in the lua client. */
        c->flags &= ~(CLIENT_READONLY|CLIENT_ASKING);
        c->flags |= server.lua_caller->flags & (CLIENT_READONLY|CLIENT_ASKING);
        if (getNodeByQuery(c,c->cmd,c->argv,c->argc,NULL,NULL) !=
                           server.cluster->myself)
        {
            luaPushError(lua,
                "Lua script attempted to access a non local key in a "
                "cluster node");
            goto cleanup;
        }
    }

    /* If we are using single commands replication, we need to wrap what
     * we propagate into a MULTI/EXEC block, so that it will be atomic like
     * a Lua script in the context of AOF and slaves. */
    if (server.lua_replicate_commands &&
        !server.lua_multi_emitted &&
        server.lua_write_dirty &&
        server.lua_repl != PROPAGATE_NONE)
    {
        execCommandPropagateMulti(server.lua_caller);
        server.lua_multi_emitted = 1;
    }

    /* Run the command */
    int call_flags = CMD_CALL_SLOWLOG | CMD_CALL_STATS;
    if (server.lua_replicate_commands) {
        /* Set flags according to redis.set_repl() settings. */
        if (server.lua_repl & PROPAGATE_AOF)
            call_flags |= CMD_CALL_PROPAGATE_AOF;
        if (server.lua_repl & PROPAGATE_REPL)
            call_flags |= CMD_CALL_PROPAGATE_REPL;
    }
    call(c,call_flags);

    /* Convert the result of the Redis command into a suitable Lua type.
     * The first thing we need is to create a single string from the client
     * output buffers. */
    if (listLength(c->reply) == 0 && c->bufpos < PROTO_REPLY_CHUNK_BYTES) {
        /* This is a fast path for the common case of a reply inside the
         * client static buffer. Don't create an SDS string but just use
         * the client buffer directly. */
        c->buf[c->bufpos] = '\0';
        reply = c->buf;
        c->bufpos = 0;
    } else {
        reply = sdsnewlen(c->buf,c->bufpos);
        c->bufpos = 0;
        while(listLength(c->reply)) {
            sds o = listNodeValue(listFirst(c->reply));

            reply = sdscatsds(reply,o);
            listDelNode(c->reply,listFirst(c->reply));
        }
    }
    if (raise_error && reply[0] != '-') raise_error = 0;
    redisProtocolToLuaType(lua,reply);
    /* Sort the output array if needed, assuming it is a non-null multi bulk
     * reply as expected. */
    if ((cmd->flags & CMD_SORT_FOR_SCRIPT) &&
        (server.lua_replicate_commands == 0) &&
        (reply[0] == '*' && reply[1] != '-')) {
            luaSortArray(lua);
    }
    if (reply != c->buf) sdsfree(reply);
    c->reply_bytes = 0;

cleanup:
    /* Clean up. Command code may have changed argv/argc so we use the
     * argv/argc of the client instead of the local variables. */
    for (j = 0; j < c->argc; j++) {
        robj *o = c->argv[j];

        /* Try to cache the object in the cached_objects array.
         * The object must be small, SDS-encoded, and with refcount = 1
         * (we must be the only owner) for us to cache it. */
        if (j < LUA_CMD_OBJCACHE_SIZE &&
            o->refcount == 1 &&
            (o->encoding == OBJ_ENCODING_RAW ||
             o->encoding == OBJ_ENCODING_EMBSTR) &&
            sdslen(o->ptr) <= LUA_CMD_OBJCACHE_MAX_LEN)
        {
            sds s = o->ptr;
            if (cached_objects[j]) decrRefCount(cached_objects[j]);
            cached_objects[j] = o;
            cached_objects_len[j] = sdsalloc(s);
        } else {
            decrRefCount(o);
        }
    }

    if (c->argv != argv) {
        zfree(c->argv);
        argv = NULL;
        argv_size = 0;
    }

    if (raise_error) {
        /* If we are here we should have an error in the stack, in the
         * form of a table with an "err" field. Extract the string to
         * return the plain error. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        inuse--;
        return lua_error(lua);
    }
    inuse--;
    return 1;
}