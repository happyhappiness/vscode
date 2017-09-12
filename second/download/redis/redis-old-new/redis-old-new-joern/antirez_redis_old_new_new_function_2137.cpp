void zunionInterGenericCommand(redisClient *c, robj *dstkey, int op) {
    int i, j;
    long setnum;
    int aggregate = REDIS_AGGR_SUM;
    zsetopsrc *src;
    zsetopval zval;
    robj *tmp;
    unsigned int maxelelen = 0;
    robj *dstobj;
    zset *dstzset;
    zskiplistNode *znode;
    int touched = 0;

    /* expect setnum input keys to be given */
    if ((getLongFromObjectOrReply(c, c->argv[2], &setnum, NULL) != REDIS_OK))
        return;

    if (setnum < 1) {
        addReplyError(c,
            "at least 1 input key is needed for ZUNIONSTORE/ZINTERSTORE");
        return;
    }

    /* test if the expected number of keys would overflow */
    if (setnum > c->argc-3) {
        addReply(c,shared.syntaxerr);
        return;
    }

    /* read keys to be used for input */
    src = zcalloc(sizeof(zsetopsrc) * setnum);
    for (i = 0, j = 3; i < setnum; i++, j++) {
        robj *obj = lookupKeyWrite(c->db,c->argv[j]);
        if (obj != NULL) {
            if (obj->type != REDIS_ZSET && obj->type != REDIS_SET) {
                zfree(src);
                addReply(c,shared.wrongtypeerr);
                return;
            }

            src[i].subject = obj;
            src[i].type = obj->type;
            src[i].encoding = obj->encoding;
        } else {
            src[i].subject = NULL;
        }

        /* Default all weights to 1. */
        src[i].weight = 1.0;
    }

    /* parse optional extra arguments */
    if (j < c->argc) {
        int remaining = c->argc - j;

        while (remaining) {
            if (remaining >= (setnum + 1) && !strcasecmp(c->argv[j]->ptr,"weights")) {
                j++; remaining--;
                for (i = 0; i < setnum; i++, j++, remaining--) {
                    if (getDoubleFromObjectOrReply(c,c->argv[j],&src[i].weight,
                            "weight value is not a float") != REDIS_OK)
                    {
                        zfree(src);
                        return;
                    }
                }
            } else if (remaining >= 2 && !strcasecmp(c->argv[j]->ptr,"aggregate")) {
                j++; remaining--;
                if (!strcasecmp(c->argv[j]->ptr,"sum")) {
                    aggregate = REDIS_AGGR_SUM;
                } else if (!strcasecmp(c->argv[j]->ptr,"min")) {
                    aggregate = REDIS_AGGR_MIN;
                } else if (!strcasecmp(c->argv[j]->ptr,"max")) {
                    aggregate = REDIS_AGGR_MAX;
                } else {
                    zfree(src);
                    addReply(c,shared.syntaxerr);
                    return;
                }
                j++; remaining--;
            } else {
                zfree(src);
                addReply(c,shared.syntaxerr);
                return;
            }
        }
    }

    for (i = 0; i < setnum; i++)
        zuiInitIterator(&src[i]);

    /* sort sets from the smallest to largest, this will improve our
     * algorithm's performance */
    qsort(src,setnum,sizeof(zsetopsrc),zuiCompareByCardinality);

    dstobj = createZsetObject();
    dstzset = dstobj->ptr;
    memset(&zval, 0, sizeof(zval));

    if (op == REDIS_OP_INTER) {
        /* Skip everything if the smallest input is empty. */
        if (zuiLength(&src[0]) > 0) {
            /* Precondition: as src[0] is non-empty and the inputs are ordered
             * by size, all src[i > 0] are non-empty too. */
            while (zuiNext(&src[0],&zval)) {
                double score, value;

                score = src[0].weight * zval.score;
                if (isnan(score)) score = 0;

                for (j = 1; j < setnum; j++) {
                    /* It is not safe to access the zset we are
                     * iterating, so explicitly check for equal object. */
                    if (src[j].subject == src[0].subject) {
                        value = zval.score*src[j].weight;
                        zunionInterAggregate(&score,value,aggregate);
                    } else if (zuiFind(&src[j],&zval,&value)) {
                        value *= src[j].weight;
                        zunionInterAggregate(&score,value,aggregate);
                    } else {
                        break;
                    }
                }

                /* Only continue when present in every input. */
                if (j == setnum) {
                    tmp = zuiObjectFromValue(&zval);
                    znode = zslInsert(dstzset->zsl,score,tmp);
                    incrRefCount(tmp); /* added to skiplist */
                    dictAdd(dstzset->dict,tmp,&znode->score);
                    incrRefCount(tmp); /* added to dictionary */

                    if (tmp->encoding == REDIS_ENCODING_RAW)
                        if (sdslen(tmp->ptr) > maxelelen)
                            maxelelen = sdslen(tmp->ptr);
                }
            }
        }
    } else if (op == REDIS_OP_UNION) {
        for (i = 0; i < setnum; i++) {
            if (zuiLength(&src[i]) == 0)
                continue;

            while (zuiNext(&src[i],&zval)) {
                double score, value;

                /* Skip key when already processed */
                if (dictFind(dstzset->dict,zuiObjectFromValue(&zval)) != NULL)
                    continue;

                /* Initialize score */
                score = src[i].weight * zval.score;
                if (isnan(score)) score = 0;

                /* Because the inputs are sorted by size, it's only possible
                 * for sets at larger indices to hold this element. */
                for (j = (i+1); j < setnum; j++) {
                    /* It is not safe to access the zset we are
                     * iterating, so explicitly check for equal object. */
                    if(src[j].subject == src[i].subject) {
                        value = zval.score*src[j].weight;
                        zunionInterAggregate(&score,value,aggregate);
                    } else if (zuiFind(&src[j],&zval,&value)) {
                        value *= src[j].weight;
                        zunionInterAggregate(&score,value,aggregate);
                    }
                }

                tmp = zuiObjectFromValue(&zval);
                znode = zslInsert(dstzset->zsl,score,tmp);
                incrRefCount(zval.ele); /* added to skiplist */
                dictAdd(dstzset->dict,tmp,&znode->score);
                incrRefCount(zval.ele); /* added to dictionary */

                if (tmp->encoding == REDIS_ENCODING_RAW)
                    if (sdslen(tmp->ptr) > maxelelen)
                        maxelelen = sdslen(tmp->ptr);
            }
        }
    } else {
        redisPanic("Unknown operator");
    }

    for (i = 0; i < setnum; i++)
        zuiClearIterator(&src[i]);

    if (dbDelete(c->db,dstkey)) {
        signalModifiedKey(c->db,dstkey);
        touched = 1;
        server.dirty++;
    }
    if (dstzset->zsl->length) {
        /* Convert to ziplist when in limits. */
        if (dstzset->zsl->length <= server.zset_max_ziplist_entries &&
            maxelelen <= server.zset_max_ziplist_value)
                zsetConvert(dstobj,REDIS_ENCODING_ZIPLIST);

        dbAdd(c->db,dstkey,dstobj);
        addReplyLongLong(c,zsetLength(dstobj));
        if (!touched) signalModifiedKey(c->db,dstkey);
        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
            (op == REDIS_OP_UNION) ? "zunionstore" : "zinterstore",
            dstkey,c->db->id);
        server.dirty++;
    } else {
        decrRefCount(dstobj);
        addReply(c,shared.czero);
        if (touched)
            notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,"del",dstkey,c->db->id);
    }
    zfree(src);
}