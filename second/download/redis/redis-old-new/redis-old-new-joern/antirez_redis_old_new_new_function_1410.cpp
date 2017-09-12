static int mp_unpack_one(lua_State *L) {
    int offset = luaL_optint(L, 2, 0);
    /* Variable pop because offset may not exist */
    lua_pop(L, lua_gettop(L)-1);
    return mp_unpack_full(L, 1, offset);
}