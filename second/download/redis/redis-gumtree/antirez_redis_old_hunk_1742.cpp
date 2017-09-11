    switch(t) {
    case LUA_TSTRING: mp_encode_lua_string(L,buf); break;
    case LUA_TBOOLEAN: mp_encode_lua_bool(L,buf); break;
    case LUA_TNUMBER: mp_encode_lua_number(L,buf); break;
    case LUA_TTABLE: mp_encode_lua_table(L,buf,level); break;
    default: mp_encode_lua_null(L,buf); break;
    }
    lua_pop(L,1);
}

static int mp_pack(lua_State *L) {
    mp_buf *buf = mp_buf_new();

    mp_encode_lua_type(L,buf,0);
    lua_pushlstring(L,(char*)buf->b,buf->len);
    mp_buf_free(buf);
    return 1;
}

/* --------------------------------- Decoding --------------------------------- */

void mp_decode_to_lua_type(lua_State *L, mp_cur *c);

