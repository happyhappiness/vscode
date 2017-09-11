    struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
        redisLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
            strerror(errno));
        server.maxclients = 1024-REDIS_MIN_RESERVED_FDS;
    } else {
