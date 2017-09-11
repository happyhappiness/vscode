    return 1;
}

/* redis.log() */
int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
