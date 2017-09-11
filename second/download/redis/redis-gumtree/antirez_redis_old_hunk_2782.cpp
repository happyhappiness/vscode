    c->mstate.count++;
}

void multiCommand(redisClient *c) {
    if (c->flags & REDIS_MULTI) {
        addReplyError(c,"MULTI calls can not be nested");
