    robj **orig_argv;
    int orig_argc;
    struct redisCommand *orig_cmd;

    if (!(c->flags & REDIS_MULTI)) {
        addReplyError(c,"EXEC without MULTI");
