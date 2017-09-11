void luaPushError(lua_State *lua, char *error) {
    lua_Debug dbg;

    lua_newtable(lua);
    lua_pushstring(lua,"err");

