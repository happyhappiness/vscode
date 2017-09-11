    return C_OK;
}

void evalGenericCommand(client *c, int evalsha) {
    lua_State *lua = server.lua;
    char funcname[43];
