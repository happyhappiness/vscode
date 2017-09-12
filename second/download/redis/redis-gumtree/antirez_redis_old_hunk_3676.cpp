void shutdownCommand(redisClient *c) {
    if (prepareForShutdown() == REDIS_OK)
        exit(0);
    addReplySds(c, sdsnew("-ERR Errors trying to SHUTDOWN. Check logs.\r\n"));
}

void renameGenericCommand(redisClient *c, int nx) {
