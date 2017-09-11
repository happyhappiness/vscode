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

int luaRedisCallCommand(lua_State *lua) {
    return luaRedisGenericCommand(lua,1);
}

int luaRedisPCallCommand(lua_State *lua) {
    return luaRedisGenericCommand(lua,0);
}

int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    int level;
