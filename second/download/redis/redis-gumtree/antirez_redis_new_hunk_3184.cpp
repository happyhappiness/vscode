    case LUA_TNUMBER:
        addReplyLongLong(c,(long long)lua_tonumber(lua,1));
        break;
    case LUA_TTABLE:
        /* We need to check if it is an array or an error.
         * Error are returned as a single element table with 'err' field. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            addReplyError(c,(char*)lua_tostring(lua,-1));
            lua_pop(lua,1);
        } else {
            void *replylen = addDeferredMultiBulkLength(c);
            int j = 1, mbulklen = 0;

            lua_pop(lua,1); /* Discard the 'err' field value we popped */
            while(1) {
                lua_pushnumber(lua,j++);
                lua_gettable(lua,-2);
                t = lua_type(lua,-1);
                if (t == LUA_TNIL) {
                    lua_pop(lua,1);
                    break;
                } else if (t == LUA_TSTRING) {
                    size_t len;
                    char *s = (char*) lua_tolstring(lua,-1,&len);

                    addReplyBulkCBuffer(c,s,len);
                    mbulklen++;
                } else if (t == LUA_TNUMBER) {
                    addReplyLongLong(c,(long long)lua_tonumber(lua,-1));
                    mbulklen++;
                }
                lua_pop(lua,1);
            }
            setDeferredMultiBulkLength(c,replylen,mbulklen);
        }
        break;
    default:
        addReply(c,shared.nullbulk);
    }
