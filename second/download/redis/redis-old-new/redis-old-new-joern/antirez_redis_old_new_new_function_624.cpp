int luaRaiseError(lua_State *lua) {
    lua_pushstring(lua,"err");
    lua_gettable(lua,-2);
    return lua_error(lua);
}