sds ldbCatStackValue(sds s, lua_State *lua, int idx) {
    int t = lua_type(lua,idx);

    switch(t) {
    case LUA_TSTRING:
        {
        size_t strl;
        char *strp = (char*)lua_tolstring(lua,idx,&strl);
        s = sdscatrepr(s,strp,strl);
        }
        break;
    case LUA_TBOOLEAN:
        s = sdscat(s,lua_toboolean(lua,idx) ? "true" : "false");
        break;
    case LUA_TNUMBER:
        s = sdscatprintf(s,"%g",(double)lua_tonumber(lua,idx));
        break;
    case LUA_TNIL:
        s = sdscatlen(s,"nil",3);
        break;
    case LUA_TTABLE:
        {
        int expected_index = 1; /* First index we expect in an array. */
        int is_array = 1; /* Will be set to null if check fails. */
        /* Note: we create two representations at the same time, one
         * assuming the table is an array, one assuming it is not. At the
         * end we know what is true and select the right one. */
        sds repr1 = sdsempty();
        sds repr2 = sdsempty();
        lua_pushnil(lua); /* The first key to start the iteration is nil. */
        while (lua_next(lua,idx-1)) {
            /* Test if so far the table looks like an array. */
            if (is_array &&
                (lua_type(lua,-2) != LUA_TNUMBER ||
                 lua_tonumber(lua,-2) != expected_index)) is_array = 0;
            /* Stack now: table, key, value */
            /* Array repr. */
            repr1 = ldbCatStackValue(repr1,lua,-1);
            repr1 = sdscatlen(repr1,"; ",2);
            /* Full repr. */
            repr2 = ldbCatStackValue(repr2,lua,-2);
            repr2 = sdscatlen(repr2,"=",1);
            repr2 = ldbCatStackValue(repr2,lua,-1);
            repr2 = sdscatlen(repr2,"; ",2);
            lua_pop(lua,1); /* Stack: table, key. Ready for next iteration. */
            expected_index++;
        }
        /* Strip the last " ;" from both the representations. */
        if (sdslen(repr1)) sdsrange(repr1,0,-3);
        if (sdslen(repr2)) sdsrange(repr2,0,-3);
        /* Select the right one and discard the other. */
        s = sdscatlen(s,"{",1);
        s = sdscatsds(s,is_array ? repr1 : repr2);
        s = sdscatlen(s,"}",1);
        sdsfree(repr1);
        sdsfree(repr2);
        }
        break;
    case LUA_TFUNCTION:
    case LUA_TUSERDATA:
    case LUA_TTHREAD:
    case LUA_TLIGHTUSERDATA:
        {
        const void *p = lua_topointer(lua,idx);
        char *typename = "unknown";
        if (t == LUA_TFUNCTION) typename = "function";
        else if (t == LUA_TUSERDATA) typename = "userdata";
        else if (t == LUA_TTHREAD) typename = "thread";
        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
        s = sdscatprintf(s,"\"%s@%p\"",typename,p);
        }
        break;
    default:
        s = sdscat(s,"\"<unknown-lua-type>\"");
        break;
    }
    return s;
}