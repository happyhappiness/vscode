void genericHgetallCommand(redisClient *c, int flags) {
    robj *o, *obj;
    unsigned long count = 0;
    hashTypeIterator *hi;
    void *replylen = NULL;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
        || checkType(c,o,REDIS_HASH)) return;

    replylen = addDeferredMultiBulkLength(c);
    hi = hashTypeInitIterator(o);
    while (hashTypeNext(hi) != REDIS_ERR) {
        if (flags & REDIS_HASH_KEY) {
            obj = hashTypeCurrent(hi,REDIS_HASH_KEY);
            addReplyBulk(c,obj);
            decrRefCount(obj);
            count++;
        }
        if (flags & REDIS_HASH_VALUE) {
            obj = hashTypeCurrent(hi,REDIS_HASH_VALUE);
            addReplyBulk(c,obj);
            decrRefCount(obj);
            count++;
        }
    }
    hashTypeReleaseIterator(hi);
    setDeferredMultiBulkLength(c,replylen,count);
}