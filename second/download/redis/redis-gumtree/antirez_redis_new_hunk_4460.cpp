}

static void echoCommand(redisClient *c) {
    addReplyBulkLen(c,c->argv[1]);
    addReply(c,c->argv[1]);
    addReply(c,shared.crlf);
}
