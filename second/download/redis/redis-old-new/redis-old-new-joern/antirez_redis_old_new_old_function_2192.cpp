void zremrangebyrankCommand(redisClient *c) {
    robj *key = c->argv[1];
    robj *zobj;
    long start;
    long end;
    int llen;
    unsigned long deleted;
    int keyremoved = 0;

    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;

    if ((zobj = lookupKeyWriteOrReply(c,key,shared.czero)) == NULL ||
        checkType(c,zobj,REDIS_ZSET)) return;

    /* Sanitize indexes. */
    llen = zsetLength(zobj);
    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;

    /* Invariant: start >= 0, so this test will be true when end < 0.
     * The range is empty when start > end or start >= length. */
    if (start > end || start >= llen) {
        addReply(c,shared.czero);
        return;
    }
    if (end >= llen) end = llen-1;

    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
        /* Correct for 1-based rank. */
        zobj->ptr = zzlDeleteRangeByRank(zobj->ptr,start+1,end+1,&deleted);
        if (zzlLength(zobj->ptr) == 0) {
            dbDelete(c->db,key);
            keyremoved = 1;
        }
    } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
        zset *zs = zobj->ptr;

        /* Correct for 1-based rank. */
        deleted = zslDeleteRangeByRank(zs->zsl,start+1,end+1,zs->dict);
        if (htNeedsResize(zs->dict)) dictResize(zs->dict);
        if (dictSize(zs->dict) == 0) {
            dbDelete(c->db,key);
            keyremoved = 1;
        }
    } else {
        redisPanic("Unknown sorted set encoding");
    }

    if (deleted) {
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent("zrembyrank",key,c->db->id);
        if (keyremoved) notifyKeyspaceEvent("del",key,c->db->id);
    }
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
}