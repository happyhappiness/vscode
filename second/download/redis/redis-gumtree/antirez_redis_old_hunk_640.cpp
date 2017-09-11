    char *s;

    if (argc != 1) {
        luaPushError(lua, "wrong number of arguments");
        return 1;
    }

    s = (char*)lua_tolstring(lua,1,&len);
