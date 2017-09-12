
void bgrewriteaofCommand(redisClient *c) {
    if (server.bgrewritechildpid != -1) {
        addReplySds(c,sdsnew("-ERR background append only file rewriting already in progress\r\n"));
        return;
    }
    if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
        char *status = "+Background append only file rewriting started\r\n";
        addReplySds(c,sdsnew(status));
    } else {
        addReply(c,shared.err);
    }
