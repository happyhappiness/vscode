void zaddGenericCommand(redisClient *c, robj *key, robj *ele, double score, int incr) {
    static char *nanerr = "resulting score is not a number (NaN)";
    robj *zobj;
    robj *curobj;
    double curscore = 0.0;

    zobj = lookupKeyWrite(c->db,key);
    if (zobj == NULL) {
        zobj = createZsetZiplistObject();
        dbAdd(c->db,key,zobj);
    } else {
        if (zobj->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
    }

    if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
        unsigned char *eptr;

        if ((eptr = zzlFind(zobj,ele,&curscore)) != NULL) {
            if (incr) {
                score += curscore;
                if (isnan(score)) {
                    addReplyError(c,nanerr);
                    /* Don't need to check if the sorted set is empty, because
                     * we know it has at least one element. */
                    return;
                }
            }

            /* Remove and re-insert when score changed. */
            if (score != curscore) {
                redisAssert(zzlDelete(zobj,eptr) == REDIS_OK);
                redisAssert(zzlInsert(zobj,ele,score) == REDIS_OK);

                signalModifiedKey(c->db,key);
                server.dirty++;
            }

            if (incr) /* ZINCRBY */
                addReplyDouble(c,score);
            else /* ZADD */
                addReply(c,shared.czero);
        } else {
            redisAssert(zzlInsert(zobj,ele,score) == REDIS_OK);

            signalModifiedKey(c->db,key);
            server.dirty++;

            if (incr) /* ZINCRBY */
                addReplyDouble(c,score);
            else /* ZADD */
                addReply(c,shared.cone);
        }
    } else if (zobj->encoding == REDIS_ENCODING_RAW) {
        zset *zs = zobj->ptr;
        zskiplistNode *znode;
        dictEntry *de;

        de = dictFind(zs->dict,ele);
        if (de != NULL) {
            curobj = dictGetEntryKey(de);
            curscore = *(double*)dictGetEntryVal(de);

            if (incr) {
                score += curscore;
                if (isnan(score)) {
                    addReplyError(c,nanerr);
                    /* Don't need to check if the sorted set is empty, because
                     * we know it has at least one element. */
                    return;
                }
            }

            /* Remove and re-insert when score changed. We can safely delete
             * the key object from the skiplist, since the dictionary still has
             * a reference to it. */
            if (score != curscore) {
                redisAssert(zslDelete(zs->zsl,curscore,curobj));
                znode = zslInsert(zs->zsl,score,curobj);
                incrRefCount(curobj); /* Re-inserted in skiplist. */
                dictGetEntryVal(de) = &znode->score; /* Update score ptr. */

                signalModifiedKey(c->db,key);
                server.dirty++;
            }

            if (incr) /* ZINCRBY */
                addReplyDouble(c,score);
            else /* ZADD */
                addReply(c,shared.czero);
        } else {
            znode = zslInsert(zs->zsl,score,ele);
            incrRefCount(ele); /* Inserted in skiplist. */
            redisAssert(dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
            incrRefCount(ele); /* Added to dictionary. */

            signalModifiedKey(c->db,key);
            server.dirty++;

            if (incr) /* ZINCRBY */
                addReplyDouble(c,score);
            else /* ZADD */
                addReply(c,shared.cone);
        }
    } else {
        redisPanic("Unknown sorted set encoding");
    }
}