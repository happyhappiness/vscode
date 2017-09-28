}

/*
 * Packs all arguments as a stream for multiple upacking later.
 * Returns error if no arguments provided.
 */
int mp_pack(lua_State *L) {
    int nargs = lua_gettop(L);
    int i;
    mp_buf *buf;

    if (nargs == 0)
        return luaL_argerror(L, 0, "MessagePack pack needs input.");
