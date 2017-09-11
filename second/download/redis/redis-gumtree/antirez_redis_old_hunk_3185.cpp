    lua_pop(lua,1);
}

void evalCommand(redisClient *c) {
    lua_State *lua = server.lua;
    char funcname[43];

    /* We obtain the script SHA1, then check if this function is already
     * defined into the Lua state */
