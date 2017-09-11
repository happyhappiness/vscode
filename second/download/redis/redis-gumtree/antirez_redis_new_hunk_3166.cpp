    return 1;
}

int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    int level;
    sds log;

    if (argc < 2) {
        luaPushError(lua, "redis.log() requires two arguments or more.");
        return 1;
    } else if (!lua_isnumber(lua,-argc)) {
        luaPushError(lua, "First argument must be a number.");
        return 1;
    }
    level = lua_tonumber(lua,-argc);
    if (level < REDIS_DEBUG && level > REDIS_WARNING) {
        luaPushError(lua, "Invalid debug level.");
        return 1;
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
    redisLogRaw(level,log);
    sdsfree(log);
    return 0;
}

void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
    long long elapsed;
    REDIS_NOTUSED(ar);
