        decrRefCount(c->argv[j]);
    zfree(c->argv);

    return 1;
}

int luaLogCommand(lua_State *lua) {
    int j, argc = lua_gettop(lua);
    int level;
