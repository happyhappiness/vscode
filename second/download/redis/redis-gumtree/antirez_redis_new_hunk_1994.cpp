int luaRedisGenericCommand(lua_State *lua, int raise_error) {
    int j, argc = lua_gettop(lua);
    struct redisCommand *cmd;
    redisClient *c = server.lua_client;
    sds reply;

    /* Cached across calls. */
    static robj **argv = NULL;
    static int argv_size = 0;

    /* Require at least one argument */
    if (argc == 0) {
        luaPushError(lua,
