        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            addReplyError(c,(char*)lua_tostring(lua,-1));
            lua_pop(lua,1);
        } else {
            void *replylen = addDeferredMultiBulkLength(c);
