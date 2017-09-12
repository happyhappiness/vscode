void luaReplyToRedisReply(redisClient *c, lua_State *lua) {
    int t = lua_type(lua,1);

    switch(t) {
    case LUA_TSTRING:
        addReplyBulkCBuffer(c,(char*)lua_tostring(lua,1),lua_strlen(lua,1));
        break;
    case LUA_TBOOLEAN:
        addReply(c,lua_toboolean(lua,1) ? shared.cone : shared.czero);
        break;
    case LUA_TNUMBER:
        addReplyLongLong(c,(long long)lua_tonumber(lua,1));
        break;
    default:
        addReply(c,shared.nullbulk);
    }
    lua_pop(lua,1);
}