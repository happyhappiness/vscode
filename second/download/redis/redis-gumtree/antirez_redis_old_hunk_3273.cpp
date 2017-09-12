    return REDIS_OK;
}


/*-----------------------------------------------------------------------------
 * Sorted set commands 
 *----------------------------------------------------------------------------*/

/* This generic command implements both ZADD and ZINCRBY. */
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
        signalModifiedKey(c->db,c->argv[1]);
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
            signalModifiedKey(c->db,c->argv[1]);
            server.dirty++;
        }
        if (incr)
            addReplyDouble(c,score);
        else
            addReply(c,shared.czero);
    }
}

void zaddCommand(redisClient *c) {
    double scoreval;
    if (getDoubleFromObjectOrReply(c,c->argv[2],&scoreval,NULL) != REDIS_OK) return;
    c->argv[3] = tryObjectEncoding(c->argv[3]);
    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,0);
}

void zincrbyCommand(redisClient *c) {
    double scoreval;
    if (getDoubleFromObjectOrReply(c,c->argv[2],&scoreval,NULL) != REDIS_OK) return;
    c->argv[3] = tryObjectEncoding(c->argv[3]);
    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,1);
}

void zremCommand(redisClient *c) {
    robj *zsetobj;
    zset *zs;
    dictEntry *de;
    double curscore;
    int deleted;

    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,zsetobj,REDIS_ZSET)) return;

    zs = zsetobj->ptr;
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    de = dictFind(zs->dict,c->argv[2]);
    if (de == NULL) {
        addReply(c,shared.czero);
        return;
    }
    /* Delete from the skiplist */
    curscore = *(double*)dictGetEntryVal(de);
    deleted = zslDelete(zs->zsl,curscore,c->argv[2]);
    redisAssert(deleted != 0);

    /* Delete from the hash table */
    dictDelete(zs->dict,c->argv[2]);
    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.cone);
}

void zremrangebyscoreCommand(redisClient *c) {
    zrangespec range;
    long deleted;
    robj *o;
    zset *zs;

    /* Parse the range arguments. */
    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
        addReplyError(c,"min or max is not a double");
        return;
    }

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_ZSET)) return;

    zs = o->ptr;
    deleted = zslDeleteRangeByScore(zs->zsl,range,zs->dict);
    if (htNeedsResize(zs->dict)) dictResize(zs->dict);
    if (dictSize(zs->dict) == 0) dbDelete(c->db,c->argv[1]);
    if (deleted) signalModifiedKey(c->db,c->argv[1]);
    server.dirty += deleted;
    addReplyLongLong(c,deleted);
}

void zremrangebyrankCommand(redisClient *c) {
    long start;
    long end;
    int llen;
    long deleted;
    robj *zsetobj;
    zset *zs;

    if ((getLongFromObjectOrReply(c, c->argv[2], &start, NULL) != REDIS_OK) ||
        (getLongFromObjectOrReply(c, c->argv[3], &end, NULL) != REDIS_OK)) return;

    if ((zsetobj = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,zsetobj,REDIS_ZSET)) return;
    zs = zsetobj->ptr;
    llen = zs->zsl->length;

    /* convert negative indexes */
    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;
