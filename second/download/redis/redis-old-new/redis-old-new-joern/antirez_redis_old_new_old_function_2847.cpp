void scriptingInit(void) {
    lua_State *lua = lua_open();
    luaL_openlibs(lua);

    /* Register the 'r' command */
    lua_pushcfunction(lua,luaRedisCommand);
    lua_setglobal(lua,"redis");

    /* Create the (non connected) client that we use to execute Redis commands
     * inside the Lua interpreter */
    server.lua_client = createClient(-1);
    server.lua_client->flags |= REDIS_LUA_CLIENT;

    server.lua = lua;
}