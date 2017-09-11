    sds log;

    if (argc < 2) {
        lua_pushstring(lua, "redis.log() requires two arguments or more.");
        return lua_error(lua);
    } else if (!lua_isnumber(lua,-argc)) {
        lua_pushstring(lua, "First argument must be a number (log level).");
        return lua_error(lua);
    }
    level = lua_tonumber(lua,-argc);
    if (level < LL_DEBUG || level > LL_WARNING) {
        lua_pushstring(lua, "Invalid debug level.");
        return lua_error(lua);
    }

    /* Glue together all the arguments */
