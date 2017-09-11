 * On failure the function logs a warning on the Redis log. */
void sentinelFlushConfig(void) {
    int fd;

    if (rewriteConfig(server.configfile) == -1) {
        redisLog(REDIS_WARNING,"WARNING: Senitnel was not able to save the new configuration on disk!!!: %s", strerror(errno));
        return;
    }
    if ((fd = open(server.configfile,O_RDONLY)) != -1) {
        fsync(fd);
        close(fd);
    }
    return;
}

