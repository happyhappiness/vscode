    char *s;

    if (argc != 1) {
        lua_pushstring(lua, "wrong number of arguments");
        return lua_error(lua);
    }

    s = (char*)lua_tolstring(lua,1,&len);
