    int flags;

    if (server.lua_replicate_commands == 0) {
        luaPushError(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
        return 1;
    } else if (argc != 1) {
        luaPushError(lua, "redis.set_repl() requires two arguments.");
        return 1;
    }

    flags = lua_tonumber(lua,-1);
    if ((flags & ~(PROPAGATE_AOF|PROPAGATE_REPL)) != 0) {
        luaPushError(lua, "Invalid replication flags. Use REPL_AOF, REPL_SLAVE, REPL_ALL or REPL_NONE.");
        return 1;
    }
    server.lua_repl = flags;
    return 0;
