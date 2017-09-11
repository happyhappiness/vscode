
    /* Build the arguments vector */
    argv = zmalloc(sizeof(robj*)*argc);
    for (j = 0; j < argc; j++) {
        if (!lua_isstring(lua,j+1)) break;
        argv[j] = createStringObject((char*)lua_tostring(lua,j+1),
                                     lua_strlen(lua,j+1));
    }
    
    /* Check if one of the arguments passed by the Lua script
     * is not a string or an integer (lua_isstring() return true for
     * integers as well). */
    if (j != argc) {
        j--;
        while (j >= 0) {
            decrRefCount(argv[j]);
            j--;
        }
        zfree(argv);
        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        return 1;
    }

    /* Command lookup */
    cmd = lookupCommand(argv[0]->ptr);
