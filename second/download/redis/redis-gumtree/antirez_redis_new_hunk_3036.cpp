        return 1;
    }

    /* Setup our fake client for command execution */
    c->argv = argv;
    c->argc = argc;

    /* Command lookup */
    cmd = lookupCommand(argv[0]->ptr);
    if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
                   (argc < -cmd->arity)))
    {
        if (cmd)
            luaPushError(lua,
                "Wrong number of args calling Redis command From Lua script");
        else
            luaPushError(lua,"Unknown Redis command called from Lua script");
        goto cleanup;
    }

    if (cmd->flags & REDIS_CMD_NOSCRIPT) {
        luaPushError(lua, "This Redis command is not allowed from scripts");
        goto cleanup;
    }

    /* Run the command */
    cmd->proc(c);

    /* Convert the result of the Redis command into a suitable Lua type.
