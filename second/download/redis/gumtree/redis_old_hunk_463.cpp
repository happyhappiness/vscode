}

/* -----------------------------------------------------------------------------
 * CLUSTER command
 * -------------------------------------------------------------------------- */

int getSlotOrReply(redisClient *c, robj *o) {
    long long slot;

    if (getLongLongFromObject(o,&slot) != REDIS_OK ||
        slot < 0 || slot >= REDIS_CLUSTER_SLOTS)
    {
        addReplyError(c,"Invalid or out of range slot");
        return -1;
    }
    return (int) slot;
}

void clusterReplyMultiBulkSlots(redisClient *c) {
    /* Format: 1) 1) start slot
     *            2) end slot
     *            3) 1) master IP
     *               2) master port
     *            4) 1) replica IP
     *               2) replica port
     *           ... continued until done
     */

    int num_masters = 0;
    void *slot_replylen = addDeferredMultiBulkLength(c);

