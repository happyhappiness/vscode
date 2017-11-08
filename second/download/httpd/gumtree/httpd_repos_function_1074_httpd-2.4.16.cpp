static int lua_table_get(lua_State *L)
{
    req_table_t    *t = ap_lua_check_apr_table(L, 1);
    const char     *key = luaL_checkstring(L, 2);
    const char     *val = apr_table_get(t->t, key);
    lua_pushstring(L, val);
    return 1;
}