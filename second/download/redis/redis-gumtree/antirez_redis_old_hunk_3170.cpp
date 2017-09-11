    return 1;
}

void scriptingInit(void) {
    lua_State *lua = lua_open();
    luaL_openlibs(lua);
