    return p;
}

int luaRedisCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    struct redisCommand *cmd;
