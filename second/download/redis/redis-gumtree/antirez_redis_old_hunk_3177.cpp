    {
        for (j = 0; j < argc; j++) decrRefCount(argv[j]);
        zfree(argv);
        lua_newtable(lua);
        lua_pushstring(lua,"err");
        if (cmd)
            lua_pushstring(lua,
                "Wrong number of args calling Redis command From Lua script");
        else
            lua_pushstring(lua,"Unknown Redis command called from Lua script");
        lua_settable(lua,-3);
        return 1;
    }

