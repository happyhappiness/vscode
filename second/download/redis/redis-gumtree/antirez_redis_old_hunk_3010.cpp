    lua_setglobal(lua,var);
}

void evalGenericCommand(redisClient *c, int evalsha) {
    lua_State *lua = server.lua;
    char funcname[43];
