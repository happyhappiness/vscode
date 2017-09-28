    else
        mp_encode_lua_table_as_map(L,buf,level);
}

static void mp_encode_lua_null(lua_State *L, mp_buf *buf) {
    unsigned char b[1];

    b[0] = 0xc0;
    mp_buf_append(buf,b,1);
}

static void mp_encode_lua_type(lua_State *L, mp_buf *buf, int level) {
    int t = lua_type(L,-1);

    /* Limit the encoding of nested tables to a specfiied maximum depth, so that
     * we survive when called against circular references in tables. */
    if (t == LUA_TTABLE && level == LUACMSGPACK_MAX_NESTING) t = LUA_TNIL;
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

void mp_decode_to_lua_array(lua_State *L, mp_cur *c, size_t len) {
    int index = 1;

