char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply) {
    char *p = strchr(reply+1,'\r');
    long long mbulklen;
    int j = 0;

    printf("--%s-- (%d)\n", reply,(int)(p-reply-1));
    string2ll(reply+1,p-reply-1,&mbulklen);
    p += 2;
    if (mbulklen == -1) {
        lua_pushnil(lua);
        return p;
    }
    printf("BL: %lld\n", mbulklen);
    lua_newtable(lua);
    for (j = 0; j < mbulklen; j++) {
        lua_pushnumber(lua,j);
        p = redisProtocolToLuaType(lua,p);
        lua_settable(lua,-3);
    }
    return p;
}