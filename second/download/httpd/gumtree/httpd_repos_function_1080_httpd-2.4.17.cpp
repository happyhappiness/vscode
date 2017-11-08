int ap_lua_init(lua_State *L, apr_pool_t *p)
{
    luaL_newmetatable(L, "Apr.Table");
    luaL_register(L, "apr_table", lua_table_methods);
    lua_pushstring(L, "__index");
    lua_pushstring(L, "get");
    lua_gettable(L, 2);
    lua_settable(L, 1);

    lua_pushstring(L, "__newindex");
    lua_pushstring(L, "set");
    lua_gettable(L, 2);
    lua_settable(L, 1);

    return 0;
}