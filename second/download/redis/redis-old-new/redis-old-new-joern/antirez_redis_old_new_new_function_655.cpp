int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    int level;
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
    log = sdsempty();
    for (j = 1; j < argc; j++) {
        size_t len;
        char *s;

        s = (char*)lua_tolstring(lua,(-argc)+j,&len);
        if (s) {
            if (j != 1) log = sdscatlen(log," ",1);
            log = sdscatlen(log,s,len);
        }
    }
    serverLogRaw(level,log);
    sdsfree(log);
    return 0;
}