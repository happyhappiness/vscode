
void bgsaveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
    if (rdbSaveBackground(server.dbfilename) == REDIS_OK) {
        addReplyStatus(c,"Background saving started");
    } else {
        addReply(c,shared.err);
    }
