static void hincrbyCommand(redisClient *c) {
    long long value, incr;
    robj *o, *current, *new;

    if (getLongLongFromObject(c,c->argv[3],&incr) != REDIS_OK) return;
    if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
    if ((current = hashGet(o,c->argv[2])) != NULL) {
        if (current->encoding == REDIS_ENCODING_RAW)
            value = strtoll(current->ptr,NULL,10);
        else if (current->encoding == REDIS_ENCODING_INT)
            value = (long)current->ptr;
        else
            redisAssert(1 != 1);
        decrRefCount(current);
    } else {
        value = 0;
    }

    value += incr;
    new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
    hashReplace(o,c->argv[2],new);
    decrRefCount(new);
    addReplyLongLong(c,value);
    server.dirty++;
}