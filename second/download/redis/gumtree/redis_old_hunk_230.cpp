        while (j >= 0) {
            decrRefCount(argv[j]);
            j--;
        }
        luaPushError(lua,
            "Lua redis() command arguments must be strings or integers");
        return 1;
    }

    /* Setup our fake client for command execution */
    c->argv = argv;
    c->argc = argc;
