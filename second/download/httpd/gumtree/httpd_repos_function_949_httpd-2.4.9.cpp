static lua_db_handle *lua_get_db_handle(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    lua_rawgeti(L, 1, 0);
    luaL_checktype(L, -1, LUA_TUSERDATA);
    return (lua_db_handle *) lua_topointer(L, -1);
}