
    /* Return the result in form of a multi-bulk reply */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
    lIterator *li = lInitIterator(o,start,REDIS_TAIL);
    for (j = 0; j < rangelen; j++) {
        redisAssert(lNext(li,&entry));
        value = lGet(&entry);
        addReplyBulk(c,value);
        decrRefCount(value);
    }
    lReleaseIterator(li);
}

static void ltrimCommand(redisClient *c) {
