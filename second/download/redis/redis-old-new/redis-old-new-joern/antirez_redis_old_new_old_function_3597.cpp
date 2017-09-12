void lrangeCommand(redisClient *c) {
    robj *o, *value;
    int start = atoi(c->argv[2]->ptr);
    int end = atoi(c->argv[3]->ptr);
    int llen;
    int rangelen, j;
    listTypeEntry entry;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.emptymultibulk)) == NULL
         || checkType(c,o,REDIS_LIST)) return;
    llen = listTypeLength(o);

    /* convert negative indexes */
    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;

    /* Invariant: start >= 0, so this test will be true when end < 0.
     * The range is empty when start > end or start >= length. */
    if (start > end || start >= llen) {
        addReply(c,shared.emptymultibulk);
        return;
    }
    if (end >= llen) end = llen-1;
    rangelen = (end-start)+1;

    /* Return the result in form of a multi-bulk reply */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
    listTypeIterator *li = listTypeInitIterator(o,start,REDIS_TAIL);
    for (j = 0; j < rangelen; j++) {
        redisAssert(listTypeNext(li,&entry));
        value = listTypeGet(&entry);
        addReplyBulk(c,value);
        decrRefCount(value);
    }
    listTypeReleaseIterator(li);
}