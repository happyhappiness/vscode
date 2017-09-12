void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double scoreval, int doincrement) {
    robj *zsetobj;
    zset *zs;
    double *score;

    zsetobj = lookupKeyWrite(c->db,key);
    if (zsetobj == NULL) {
        zsetobj = createZsetObject();
        dbAdd(c->db,key,zsetobj);
    } else {
        if (zsetobj->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }
    zs = zsetobj->ptr;

    /* Ok now since we implement both ZADD and ZINCRBY here the code
     * needs to handle the two different conditions. It's all about setting
     * '*score', that is, the new score to set, to the right value. */
    score = zmalloc(sizeof(double));
    if (doincrement) {
        dictEntry *de;

        /* Read the old score. If the element was not present starts from 0 */
        de = dictFind(zs->dict,ele);
        if (de) {
            double *oldscore = dictGetEntryVal(de);
            *score = *oldscore + scoreval;
        } else {
            *score = scoreval;
        }
        if (isnan(*score)) {
            addReplySds(c,
                sdsnew("-ERR resulting score is not a number (NaN)\r\n"));
            zfree(score);
            /* Note that we don't need to check if the zset may be empty and
             * should be removed here, as we can only obtain Nan as score if
             * there was already an element in the sorted set. */
            return;
        }
    } else {
        *score = scoreval;
    }

    /* What follows is a simple remove and re-insert operation that is common
     * to both ZADD and ZINCRBY... */
    if (dictAdd(zs->dict,ele,score) == DICT_OK) {
        /* case 1: New element */
        incrRefCount(ele); /* added to hash */
        zslInsert(zs->zsl,*score,ele);
        incrRefCount(ele); /* added to skiplist */
        touchWatchedKey(c->db,c->argv[1]);
        server.dirty++;
        if (doincrement)
            addReplyDouble(c,*score);
        else
            addReply(c,shared.cone);
    } else {
        dictEntry *de;
        double *oldscore;

        /* case 2: Score update operation */
        de = dictFind(zs->dict,ele);
        redisAssert(de != NULL);
        oldscore = dictGetEntryVal(de);
        if (*score != *oldscore) {
            int deleted;

            /* Remove and insert the element in the skip list with new score */
            deleted = zslDelete(zs->zsl,*oldscore,ele);
            redisAssert(deleted != 0);
            zslInsert(zs->zsl,*score,ele);
            incrRefCount(ele);
            /* Update the score in the hash table */
            dictReplace(zs->dict,ele,score);
            touchWatchedKey(c->db,c->argv[1]);
            server.dirty++;
        } else {
            zfree(score);
        }
        if (doincrement)
            addReplyDouble(c,*score);
        else
            addReply(c,shared.czero);
    }
}