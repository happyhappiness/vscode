    scriptingInit();
}

/* Perform the SHA1 of the input string. We use this both for hashing script
 * bodies in order to obtain the Lua function name, and in the implementation
 * of redis.sha1().
 *
 * 'digest' should point to a 41 bytes buffer: 40 for SHA1 converted into an
 * hexadecimal number, plus 1 byte for null term. */
void sha1hex(char *digest, char *script, size_t len) {
    SHA1_CTX ctx;
    unsigned char hash[20];
    char *cset = "0123456789abcdef";
    int j;

    SHA1Init(&ctx);
    SHA1Update(&ctx,(unsigned char*)script,len);
    SHA1Final(hash,&ctx);

    for (j = 0; j < 20; j++) {
        digest[j*2] = cset[((hash[j]&0xF0)>>4)];
        digest[j*2+1] = cset[(hash[j]&0xF)];
    }
    digest[40] = '\0';
}

void luaReplyToRedisReply(client *c, lua_State *lua) {
    int t = lua_type(lua,-1);

    switch(t) {
    case LUA_TSTRING:
        addReplyBulkCBuffer(c,(char*)lua_tostring(lua,-1),lua_strlen(lua,-1));
        break;
    case LUA_TBOOLEAN:
        addReply(c,lua_toboolean(lua,-1) ? shared.cone : shared.nullbulk);
        break;
    case LUA_TNUMBER:
        addReplyLongLong(c,(long long)lua_tonumber(lua,-1));
        break;
    case LUA_TTABLE:
        /* We need to check if it is an array, an error, or a status reply.
         * Error are returned as a single element table with 'err' field.
         * Status replies are returned as single element table with 'ok'
         * field. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            sds err = sdsnew(lua_tostring(lua,-1));
            sdsmapchars(err,"\r\n","  ",2);
            addReplySds(c,sdscatprintf(sdsempty(),"-%s\r\n",err));
            sdsfree(err);
            lua_pop(lua,2);
            return;
        }

        lua_pop(lua,1);
        lua_pushstring(lua,"ok");
        lua_gettable(lua,-2);
        t = lua_type(lua,-1);
        if (t == LUA_TSTRING) {
            sds ok = sdsnew(lua_tostring(lua,-1));
            sdsmapchars(ok,"\r\n","  ",2);
            addReplySds(c,sdscatprintf(sdsempty(),"+%s\r\n",ok));
            sdsfree(ok);
            lua_pop(lua,1);
        } else {
            void *replylen = addDeferredMultiBulkLength(c);
            int j = 1, mbulklen = 0;

            lua_pop(lua,1); /* Discard the 'ok' field value we popped */
            while(1) {
                lua_pushnumber(lua,j++);
                lua_gettable(lua,-2);
                t = lua_type(lua,-1);
                if (t == LUA_TNIL) {
                    lua_pop(lua,1);
                    break;
                }
                luaReplyToRedisReply(c, lua);
                mbulklen++;
            }
            setDeferredMultiBulkLength(c,replylen,mbulklen);
        }
        break;
    default:
        addReply(c,shared.nullbulk);
    }
    lua_pop(lua,1);
}

/* Set an array of Redis String Objects as a Lua array (table) stored into a
 * global variable. */
void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
