    rangelen = (end-start)+1;

    /* Return the result in form of a multi-bulk reply */
    addReplyMultiBulkLen(c,rangelen);
    listTypeIterator *li = listTypeInitIterator(o,start,REDIS_TAIL);
    for (j = 0; j < rangelen; j++) {
        redisAssert(listTypeNext(li,&entry));
