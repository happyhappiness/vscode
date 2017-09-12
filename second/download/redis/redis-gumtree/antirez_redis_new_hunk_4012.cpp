
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

static void ltrimCommand(redisClient *c) {
