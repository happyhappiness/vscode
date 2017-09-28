        /* On success convert the Lua return value into Redis protocol, and
         * send it to * the client. */
        luaReplyToRedisReply(c,lua); /* Convert and consume the reply. */
        lua_pop(lua,1); /* Remove the error handler. */
    }

    /* If we are using single commands replication, emit EXEC if there
     * was at least a write. */
    if (server.lua_replicate_commands) {
        preventCommandPropagation(c);
        if (server.lua_multi_emitted) {
            robj *propargv[1];
            propargv[0] = createStringObject("EXEC",4);
            alsoPropagate(server.execCommand,c->db->id,propargv,1,
                PROPAGATE_AOF|PROPAGATE_REPL);
            decrRefCount(propargv[0]);
        }
    }

    /* EVALSHA should be propagated to Slave and AOF file as full EVAL, unless
     * we are sure that the script was already in the context of all the
     * attached slaves *and* the current AOF file if enabled.
     *
     * To do so we use a cache of SHA1s of scripts that we already propagated
     * as full EVAL, that's called the Replication Script Cache.
     *
     * For repliation, everytime a new slave attaches to the master, we need to
     * flush our cache of scripts that can be replicated as EVALSHA, while
     * for AOF we need to do so every time we rewrite the AOF file. */
    if (evalsha && !server.lua_replicate_commands) {
        if (!replicationScriptCacheExists(c->argv[1]->ptr)) {
            /* This script is not in our script cache, replicate it as
             * EVAL, then add it into the script cache, as from now on
             * slaves and AOF know about it. */
            robj *script = dictFetchValue(server.lua_scripts,c->argv[1]->ptr);

            replicationScriptCacheAdd(c->argv[1]->ptr);
            serverAssertWithInfo(c,NULL,script != NULL);
            rewriteClientCommandArgument(c,0,
                resetRefCount(createStringObject("EVAL",4)));
            rewriteClientCommandArgument(c,1,script);
            forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
        }
    }
}

void evalCommand(client *c) {
    if (!(c->flags & CLIENT_LUA_DEBUG))
        evalGenericCommand(c,0);
    else
        evalGenericCommandWithDebugging(c,0);
}

void evalShaCommand(client *c) {
    if (sdslen(c->argv[1]->ptr) != 40) {
        /* We know that a match is not possible if the provided SHA is
         * not the right length. So we return an error ASAP, this way
         * evalGenericCommand() can be implemented without string length
         * sanity check */
        addReply(c, shared.noscripterr);
        return;
    }
    if (!(c->flags & CLIENT_LUA_DEBUG))
        evalGenericCommand(c,1);
    else {
        addReplyError(c,"Please use EVAL instead of EVALSHA for debugging");
        return;
    }
}

void scriptCommand(client *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
        scriptingReset();
        addReply(c,shared.ok);
        replicationScriptCacheFlush();
        server.dirty++; /* Propagating this command is a good idea. */
    } else if (c->argc >= 2 && !strcasecmp(c->argv[1]->ptr,"exists")) {
