int getSlotOrReply(client *c, robj *o) {
    long long slot;

    if (getLongLongFromObject(o,&slot) != REDIS_OK ||
        slot < 0 || slot >= REDIS_CLUSTER_SLOTS)
    {
        addReplyError(c,"Invalid or out of range slot");
