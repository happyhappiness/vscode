static int lua_table_set(lua_State *L)
{
    apr_table_t *t = ap_lua_check_apr_table(L, 1);
    const char *key = luaL_checkstring(L, 2);
    const char *val = luaL_checkstring(L, 3);

    apr_table_set(t, key, val);
    return 0;
}