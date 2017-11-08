static lua_db_result_set *lua_get_result_set(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_rawgeti(L, 1, 0);
    luaL_checktype(L, -1, LUA_TUSERDATA);
    return (lua_db_result_set *) lua_topointer(L, -1);
}