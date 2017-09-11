static void acceptCommonHandler(int fd, int flags) {
    redisClient *c;
    if ((c = createClient(fd)) == NULL) {
        redisLog(REDIS_WARNING,"Error allocating resources for the client");
        close(fd); /* May be already closed, just ignore errors */
        return;
    }
