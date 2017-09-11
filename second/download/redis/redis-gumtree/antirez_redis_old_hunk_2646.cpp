    redisClient *c = server.lua_client;
    sds reply;

    /* Build the arguments vector */
    argv = zmalloc(sizeof(robj*)*argc);
    for (j = 0; j < argc; j++) {
