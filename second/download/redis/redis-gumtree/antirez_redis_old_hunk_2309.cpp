    if (err) {
        addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
            funcname, lua_tostring(lua,-1));
        lua_pop(lua,1); /* Consume the Lua reply. */
    } else {
        /* On success convert the Lua return value into Redis protocol, and
         * send it to * the client. */
        luaReplyToRedisReply(c,lua);
    }

    /* EVALSHA should be propagated to Slave and AOF file as full EVAL, unless
