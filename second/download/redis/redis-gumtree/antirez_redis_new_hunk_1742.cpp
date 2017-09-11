    switch(t) {
    case LUA_TSTRING: mp_encode_lua_string(L,buf); break;
    case LUA_TBOOLEAN: mp_encode_lua_bool(L,buf); break;
    case LUA_TNUMBER:
    #if LUA_VERSION_NUM < 503
        mp_encode_lua_number(L,buf); break;
    #else
        if (lua_isinteger(L, -1)) {
            mp_encode_lua_integer(L, buf);
        } else {
            mp_encode_lua_number(L, buf);
        }
        break;
    #endif
    case LUA_TTABLE: mp_encode_lua_table(L,buf,level); break;
    default: mp_encode_lua_null(L,buf); break;
    }
    lua_pop(L,1);
}

/*
 * Packs all arguments as a stream for multiple upacking later.
 * Returns error if no arguments provided.
 */
static int mp_pack(lua_State *L) {
    int nargs = lua_gettop(L);
    int i;
    mp_buf *buf;

    if (nargs == 0)
        return luaL_argerror(L, 0, "MessagePack pack needs input.");

    buf = mp_buf_new(L);
    for(i = 1; i <= nargs; i++) {
        /* Copy argument i to top of stack for _encode processing;
         * the encode function pops it from the stack when complete. */
        lua_pushvalue(L, i);

        mp_encode_lua_type(L,buf,0);

        lua_pushlstring(L,(char*)buf->b,buf->len);

        /* Reuse the buffer for the next operation by
         * setting its free count to the total buffer size
         * and the current position to zero. */
        buf->free += buf->len;
        buf->len = 0;
    }
    mp_buf_free(buf);

    /* Concatenate all nargs buffers together */
    lua_concat(L, nargs);
    return 1;
}

/* ------------------------------- Decoding --------------------------------- */

void mp_decode_to_lua_type(lua_State *L, mp_cur *c);

