void bgsaveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t)-1) {
        addReplyError(c,"Background save already in progress");
    } else if (server.bgrewritechildpid != -1) {
        addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
    } else if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
        addReplyStatus(c,"Background saving started");
    } else {
        addReply(c,shared.err);
    }
}