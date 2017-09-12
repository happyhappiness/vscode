
void discardCommand(redisClient *c) {
    if (!(c->flags & REDIS_MULTI)) {
        addReplySds(c,sdsnew("-ERR DISCARD without MULTI\r\n"));
        return;
    }

