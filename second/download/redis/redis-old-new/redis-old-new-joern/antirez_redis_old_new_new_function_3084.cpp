void saveCommand(redisClient *c) {
    if (server.bgsavechildpid != -1 || server.bgsavethread != (pthread-t)-1) {
        addReplyError(c,"Background save already in progress");
        return;
    }
    if (rdbSave(server.dbfilename) == REDIS_OK) {
        addReply(c,shared.ok);
    } else {
        addReply(c,shared.err);
    }
}