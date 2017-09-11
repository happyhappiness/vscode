    int j;
    robj **orig_argv;
    int orig_argc;

    if (!(c->flags & REDIS_MULTI)) {
        addReplyError(c,"EXEC without MULTI");
