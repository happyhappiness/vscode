addReplySds(c,sdscatprintf(sdsempty(),
                    "-%s\r\n",(char*)lua_tostring(lua,-1)));