    c->mstate.count++;
}

void discardTransaction(redisClient *c) {
    freeClientMultiState(c);
    initClientMultiState(c);
    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS);;
    unwatchAllKeys(c);
}

void multiCommand(redisClient *c) {
    if (c->flags & REDIS_MULTI) {
        addReplyError(c,"MULTI calls can not be nested");
