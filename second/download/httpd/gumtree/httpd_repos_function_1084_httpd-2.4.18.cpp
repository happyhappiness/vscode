req_table_t *ap_lua_check_apr_table(lua_State *L, int index)
{
    req_table_t* t;
    luaL_checkudata(L, index, "Apr.Table");
    t = lua_unboxpointer(L, index);
    return t;
}