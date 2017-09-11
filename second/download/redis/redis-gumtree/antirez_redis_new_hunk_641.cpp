    int flags;

    if (server.lua_replicate_commands == 0) {
        lua_pushstring(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
        return lua_error(lua);
    } else if (argc != 1) {
        lua_pushstring(lua, "redis.set_repl() requires two arguments.");
        return lua_error(lua);
    }

    flags = lua_tonumber(lua,-1);
    if ((flags & ~(PROPAGATE_AOF|PROPAGATE_REPL)) != 0) {
        lua_pushstring(lua, "Invalid replication flags. Use REPL_AOF, REPL_SLAVE, REPL_ALL or REPL_NONE.");
        return lua_error(lua);
    }
    server.lua_repl = flags;
    return 0;
