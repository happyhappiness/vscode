void aofUpdateCurrentSize(void) {
    struct redis_stat sb;

    if (redis_fstat(server.aof_fd,&sb) == -1) {
        redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
            strerror(errno));
    } else {
