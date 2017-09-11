    addReply(c,shared.ok);
}

void discardCommand(client *c) {
    if (!(c->flags & REDIS_MULTI)) {
        addReplyError(c,"DISCARD without MULTI");
        return;
