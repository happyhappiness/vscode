void discardTransaction(client *c) {
    freeClientMultiState(c);
    initClientMultiState(c);
    c->flags &= ~(REDIS_MULTI|REDIS_DIRTY_CAS|REDIS_DIRTY_EXEC);
    unwatchAllKeys(c);
}

/* Flag the transacation as DIRTY_EXEC so that EXEC will fail.
 * Should be called every time there is an error while queueing a command. */
void flagTransaction(client *c) {
    if (c->flags & REDIS_MULTI)
        c->flags |= REDIS_DIRTY_EXEC;
}

void multiCommand(client *c) {
    if (c->flags & REDIS_MULTI) {
        addReplyError(c,"MULTI calls can not be nested");
        return;
    }
    c->flags |= REDIS_MULTI;
    addReply(c,shared.ok);
}

void discardCommand(client *c) {
    if (!(c->flags & REDIS_MULTI)) {
        addReplyError(c,"DISCARD without MULTI");
        return;
    }
