
void multiCommand(redisClient *c) {
    if (c->flags & REDIS_MULTI) {
        addReplySds(c,sdsnew("-ERR MULTI calls can not be nested\r\n"));
        return;
    }
    c->flags |= REDIS_MULTI;
