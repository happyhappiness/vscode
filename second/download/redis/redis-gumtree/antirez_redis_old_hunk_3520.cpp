int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
    struct dictEntry *de;
    redisClient *receiver;
    list *l;
    listNode *ln;

    de = dictFind(c->db->blocking_keys,key);
    if (de == NULL) return 0;
    l = dictGetEntryVal(de);
    ln = listFirst(l);
    redisAssert(ln != NULL);
    receiver = ln->value;

    addReplyMultiBulkLen(receiver,2);
    addReplyBulk(receiver,key);
    addReplyBulk(receiver,ele);
    unblockClientWaitingData(receiver);
    return 1;
}

/* Blocking RPOP/LPOP */
void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
    long long lltimeout;
    time_t timeout;
    int j;

    /* Make sure timeout is an integer value */
    if (getLongLongFromObjectOrReply(c,c->argv[c->argc-1],&lltimeout,
            "timeout is not an integer") != REDIS_OK) return;

    /* Make sure the timeout is not negative */
    if (lltimeout < 0) {
        addReplyError(c,"timeout is negative");
        return;
    }

    for (j = 1; j < c->argc-1; j++) {
        o = lookupKeyWrite(c->db,c->argv[j]);
