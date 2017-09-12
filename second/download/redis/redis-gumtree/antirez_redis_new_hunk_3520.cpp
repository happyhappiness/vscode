int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele) {
    struct dictEntry *de;
    redisClient *receiver;
    int numclients;
    list *clients;
    listNode *ln;
    robj *dstkey, *dstobj;

    de = dictFind(c->db->blocking_keys,key);
    if (de == NULL) return 0;
    clients = dictGetEntryVal(de);
    numclients = listLength(clients);

    /* Try to handle the push as long as there are clients waiting for a push.
     * Note that "numclients" is used because the list of clients waiting for a
     * push on "key" is deleted by unblockClient() when empty.
     *
     * This loop will have more than 1 iteration when there is a BRPOPLPUSH
     * that cannot push the target list because it does not contain a list. If
     * this happens, it simply tries the next client waiting for a push. */
    while (numclients--) {
        ln = listFirst(clients);
        redisAssert(ln != NULL);
        receiver = ln->value;
        dstkey = receiver->bpop.target;

        /* This should remove the first element of the "clients" list. */
        unblockClientWaitingData(receiver);
        redisAssert(ln != listFirst(clients));

        if (dstkey == NULL) {
            /* BRPOP/BLPOP */
            addReplyMultiBulkLen(receiver,2);
            addReplyBulk(receiver,key);
            addReplyBulk(receiver,ele);
            return 1;
        } else {
            /* BRPOPLPUSH */
            dstobj = lookupKeyWrite(receiver->db,dstkey);
            if (dstobj && checkType(receiver,dstobj,REDIS_LIST)) {
                decrRefCount(dstkey);
            } else {
                rpoplpushHandlePush(receiver,dstkey,dstobj,ele);
                decrRefCount(dstkey);
                return 1;
            }
        }
    }

    return 0;
}

int getTimeoutFromObjectOrReply(redisClient *c, robj *object, time_t *timeout) {
    long tval;

    if (getLongFromObjectOrReply(c,object,&tval,
        "timeout is not an integer or out of range") != REDIS_OK)
        return REDIS_ERR;

    if (tval < 0) {
        addReplyError(c,"timeout is negative");
        return REDIS_ERR;
    }

    if (tval > 0) tval += time(NULL);
    *timeout = tval;

    return REDIS_OK;
}

/* Blocking RPOP/LPOP */
void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
    time_t timeout;
    int j;

    if (getTimeoutFromObjectOrReply(c,c->argv[c->argc-1],&timeout) != REDIS_OK)
        return;

    for (j = 1; j < c->argc-1; j++) {
        o = lookupKeyWrite(c->db,c->argv[j]);
