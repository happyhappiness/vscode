        return 1;
    }

    /* Command lookup */
    cmd = lookupCommand(argv[0]->ptr);
    if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
                   (argc < -cmd->arity)))
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

    /* Run the command in the context of a fake client */
    c->argv = argv;
    c->argc = argc;
    cmd->proc(c);

    /* Convert the result of the Redis command into a suitable Lua type.
