static int mp_unpack_limit(lua_State *L) {
    int limit = luaL_checkint(L, 2);
    int offset = luaL_optint(L, 3, 0);
    /* Variable pop because offset may not exist */
    lua_pop(L, lua_gettop(L)-1);

    return mp_unpack_full(L, limit, offset);
}