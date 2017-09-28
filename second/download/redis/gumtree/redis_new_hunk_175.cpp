        luaPushError(lua,
            "Please specify at least one argument for redis.call()");
        return 1;
    }

    /* Build the arguments vector */
    if (argv_size < argc) {
        argv = zrealloc(argv,sizeof(robj*)*argc);
        argv_size = argc;
    }

    for (j = 0; j < argc; j++) {
        char *obj_s;
