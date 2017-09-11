    {
        for (j = 0; j < argc; j++) decrRefCount(argv[j]);
        zfree(argv);
        if (cmd)
            luaPushError(lua,
                "Wrong number of args calling Redis command From Lua script");
        else
            luaPushError(lua,"Unknown Redis command called from Lua script");
        return 1;
    }

