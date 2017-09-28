    sds reply;

    /* Cached across calls. */
    static robj **argv = NULL;
    static int argv_size = 0;
    static robj *cached_objects[LUA_CMD_OBJCACHE_SIZE];
    static int cached_objects_len[LUA_CMD_OBJCACHE_SIZE];

    /* Require at least one argument */
    if (argc == 0) {
        luaPushError(lua,
            "Please specify at least one argument for redis.call()");
        return 1;
    }

    /* Build the arguments vector */
    if (!argv) {
        argv = zmalloc(sizeof(robj*)*argc);
    } else if (argv_size < argc) {
        argv = zrealloc(argv,sizeof(robj*)*argc);
        argv_size = argc;
    }

    for (j = 0; j < argc; j++) {
