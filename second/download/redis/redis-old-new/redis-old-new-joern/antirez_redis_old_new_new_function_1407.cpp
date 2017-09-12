static int mp_safe(lua_State *L) {
    int argc, err, total_results;

    argc = lua_gettop(L);

    /* This adds our function to the bottom of the stack
     * (the "call this function" position) */
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_insert(L, 1);

    err = lua_pcall(L, argc, LUA_MULTRET, 0);
    total_results = lua_gettop(L);

    if (!err) {
        return total_results;
    } else {
        lua_pushnil(L);
        lua_insert(L,-2);
        return 2;
    }
}