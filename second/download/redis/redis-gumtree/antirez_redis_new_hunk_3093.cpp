void bgrewriteaofCommand(redisClient *c) {
    if (server.bgrewritechildpid != -1) {
        addReplyError(c,"Background append only file rewriting already in progress");
    } else if (server.bgsavechildpid != -1) {
        server.aofrewrite_scheduled = 1;
        addReplyStatus(c,"Background append only file rewriting scheduled");
    } else if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
        addReplyStatus(c,"Background append only file rewriting started");
    } else {
        addReply(c,shared.err);
