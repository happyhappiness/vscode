void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double score, int incr) {
    robj *zsetobj;
    zset *zs;
    zskiplistNode *znode;

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

    /* Since both ZADD and ZINCRBY are implemented here, we need to increment
     * the score first by the current score if ZINCRBY is called. */
    if (incr) {
        /* Read the old score. If the element was not present starts from 0 */
        dictEntry *de = dictFind(zs->dict,ele);
        if (de != NULL)
            score += *(double*)dictGetEntryVal(de);

        if (isnan(score)) {
            addReplyError(c,"resulting score is not a number (NaN)");
            /* Note that we don't need to check if the zset may be empty and
             * should be removed here, as we can only obtain Nan as score if
             * there was already an element in the sorted set. */
            return;
        }
    }

    /* We need to remove and re-insert the element when it was already present
     * in the dictionary, to update the skiplist. Note that we delay adding a
     * pointer to the score because we want to reference the score in the
     * skiplist node. */
    if (dictAdd(zs->dict,ele,NULL) == DICT_OK) {
        dictEntry *de;

        /* New element */
        incrRefCount(ele); /* added to hash */
        znode = zslInsert(zs->zsl,score,ele);
        incrRefCount(ele); /* added to skiplist */

        /* Update the score in the dict entry */
        de = dictFind(zs->dict,ele);
        redisAssert(de != NULL);
        dictGetEntryVal(de) = &znode->score;
        touchWatchedKey(c->db,c->argv[1]);
        server.dirty++;
        if (incr)
            addReplyDouble(c,score);
        else
            addReply(c,shared.cone);
    } else {
        dictEntry *de;
        robj *curobj;
        double *curscore;
        int deleted;

        /* Update score */
        de = dictFind(zs->dict,ele);
        redisAssert(de != NULL);
        curobj = dictGetEntryKey(de);
        curscore = dictGetEntryVal(de);

        /* When the score is updated, reuse the existing string object to
         * prevent extra alloc/dealloc of strings on ZINCRBY. */
        if (score != *curscore) {
            deleted = zslDelete(zs->zsl,*curscore,curobj);
            redisAssert(deleted != 0);
            znode = zslInsert(zs->zsl,score,curobj);
            incrRefCount(curobj);

            /* Update the score in the current dict entry */
            dictGetEntryVal(de) = &znode->score;
            touchWatchedKey(c->db,c->argv[1]);
            server.dirty++;
        }
        if (incr)
            addReplyDouble(c,score);
        else
            addReply(c,shared.czero);
    }
}