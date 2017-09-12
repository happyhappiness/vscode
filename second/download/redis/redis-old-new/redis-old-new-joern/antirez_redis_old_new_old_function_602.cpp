void ldbLogStackValue(lua_State *lua, char *prefix) {
    int t = lua_type(lua,-1);
    sds s = sdsnew(prefix);

    switch(t) {
    case LUA_TSTRING:
        s = sdscat(s,lua_tostring(lua,-1));
        break;
    case LUA_TBOOLEAN:
        s = sdscat(s,lua_toboolean(lua,-1) ? "true" : "false");
        break;
    case LUA_TNUMBER:
        s = sdscatprintf(s,"%g",(double)lua_tonumber(lua,-1));
        break;
    case LUA_TNIL:
        s = sdscat(s,"nil");
        break;
    case LUA_TTABLE:
    case LUA_TFUNCTION:
    case LUA_TUSERDATA:
    case LUA_TTHREAD:
    case LUA_TLIGHTUSERDATA:
        {
        const void *p = lua_topointer(lua,-1);
        char *typename = "unknown";
        if (t == LUA_TTABLE) typename = "table";
        else if (t == LUA_TFUNCTION) typename = "function";
        else if (t == LUA_TUSERDATA) typename = "userdata";
        else if (t == LUA_TTHREAD) typename = "thread";
        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
        s = sdscatprintf(s,"%s at %p",typename,p);
        }
        break;
    default:
        s = sdscat(s,"?");
        break;
    }
    ldbLog(s);
    lua_pop(lua,1);
}