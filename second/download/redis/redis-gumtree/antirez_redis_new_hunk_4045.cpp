    rangelen = (end-start)+1;

    /* Return the result in form of a multi-bulk reply */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
    lIterator *li = lInitIterator(o,start);
    for (j = 0; j < rangelen; j++) {
        value = lGet(li);
        redisAssert(value != NULL);
        addReplyBulk(c,value);
        lMove(li,REDIS_TAIL);
    }
    lReleaseIterator(li);
}

static void ltrimCommand(redisClient *c) {
