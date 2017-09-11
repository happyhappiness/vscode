    return p;
}

void luaPushError(lua_State *lua, char *error) {
    lua_Debug dbg;

