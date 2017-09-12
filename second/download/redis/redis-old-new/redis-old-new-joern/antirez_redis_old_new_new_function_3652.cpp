void lastsaveCommand(redisClient *c) {
    addReplyLongLong(c,server.lastsave);
}