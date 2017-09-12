void luaPushError(lua_State *lua, char *error) {
    lua_newtable(lua);
    lua_pushstring(lua,"err");
    lua_pushstring(lua, error);
    lua_settable(lua,-3);
}