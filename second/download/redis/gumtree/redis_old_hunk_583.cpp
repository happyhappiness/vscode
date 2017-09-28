    lua_pushstring(lua, field);
    lua_pushvalue(lua, -3);
    lua_settable(lua, -3);
    return 1;
}

int luaRedisErrorReplyCommand(lua_State *lua) {
    return luaRedisReturnSingleFieldTable(lua,"err");
}

int luaRedisStatusReplyCommand(lua_State *lua) {
    return luaRedisReturnSingleFieldTable(lua,"ok");
}

int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    int level;
    sds log;

    if (argc < 2) {
        luaPushError(lua, "redis.log() requires two arguments or more.");
        return 1;
    } else if (!lua_isnumber(lua,-argc)) {
        luaPushError(lua, "First argument must be a number (log level).");
        return 1;
    }
    level = lua_tonumber(lua,-argc);
    if (level < REDIS_DEBUG || level > REDIS_WARNING) {
        luaPushError(lua, "Invalid debug level.");
        return 1;
    }

    /* Glue together all the arguments */
    log = sdsempty();
    for (j = 1; j < argc; j++) {
        size_t len;
