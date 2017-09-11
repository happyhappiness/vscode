    return luaRedisGenericCommand(lua,0);
}

/* This adds redis.sha1hex(string) to Lua scripts using the same hashing
 * function used for sha1ing lua scripts. */
int luaRedisSha1hexCommand(lua_State *lua) {
    int argc = lua_gettop(lua);
    char digest[41];
    size_t len;
    char *s;

    if (argc != 1) {
        luaPushError(lua, "wrong number of arguments");
        return 1;
    }

    s = (char*)lua_tolstring(lua,1,&len);
    sha1hex(digest,s,len);
    lua_pushstring(lua,digest);
    return 1;
}

int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    int level;
