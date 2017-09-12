void sentinelFlushConfig(void) {
    int fd;
    int saved_hz = server.hz;

    server.hz = REDIS_DEFAULT_HZ;
    if (rewriteConfig(server.configfile) != -1) {
        /* Rewrite succeded, fsync it. */
        if ((fd = open(server.configfile,O_RDONLY)) != -1) {
            fsync(fd);
            close(fd);
        }
    } else {
        redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
    }
    server.hz = saved_hz;
    return;
}