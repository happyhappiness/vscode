void zaddGenericCommand(redisClient *c, int flags) {
    static char *nanerr = "resulting score is not a number (NaN)";
    robj *key = c->argv[1];
    robj *ele;
    robj *zobj;
    robj *curobj;
    double score = 0, *scores = NULL, curscore = 0.0;
    int j, elements;
    int added = 0, updated = 0, scoreidx = 0;

    /* Parse options. At the end 'scoreidx' is set to the argument position
     * of the score of the first score-element pair. */
    scoreidx = 2;
    while(scoreidx < c->argc) {
        char *opt = c->argv[scoreidx]->ptr;
        if (!strcasecmp(opt,"nx")) flags |= ZADD_NX;
        else if (!strcasecmp(opt,"xx")) flags |= ZADD_XX;
        else if (!strcasecmp(opt,"incr")) flags |= ZADD_INCR;
        else break;
        scoreidx++;
    }

    /* Turn options into simple to check vars. */
    int incr = (flags & ZADD_INCR) != 0;
    int nx = (flags & ZADD_NX) != 0;
    int xx = (flags & ZADD_XX) != 0;

    /* After the options, we expect to have an even number of args, since
     * we expect any number of score-element pairs. */
    elements = c->argc-scoreidx;
    if (elements % 2) {
        addReply(c,shared.syntaxerr);
        return;
    }
    elements /= 2; /* Now this holds the number of score-element pairs. */

    /* Check for incompatible options. */
    if (nx && xx) {
        addReplyError(c,
            "XX and NX options at the same time are not compatible");
        return;
    }

    if (incr && elements > 1) {
        addReplyError(c,
            "INCR option supports a single increment-element pair");
        return;
    }

    /* Start parsing all the scores, we need to emit any syntax error
     * before executing additions to the sorted set, as the command should
     * either execute fully or nothing at all. */
    scores = zmalloc(sizeof(double)*elements);
    for (j = 0; j < elements; j++) {
        if (getDoubleFromObjectOrReply(c,c->argv[scoreidx+j*2],&scores[j],NULL)
            != REDIS_OK) goto cleanup;
    }

    /* Lookup the key and create the sorted set if does not exist. */
    zobj = lookupKeyWrite(c->db,key);
    if (zobj == NULL) {
        if (server.zset_max_ziplist_entries == 0 ||
            server.zset_max_ziplist_value < sdslen(c->argv[3]->ptr))
        {
            zobj = createZsetObject();
        } else {
            zobj = createZsetZiplistObject();
        }
        dbAdd(c->db,key,zobj);
    } else {
        if (zobj->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
            goto cleanup;
        }
    }

    for (j = 0; j < elements; j++) {
        score = scores[j];

        if (zobj->encoding == REDIS_ENCODING_ZIPLIST) {
            unsigned char *eptr;

            /* Prefer non-encoded element when dealing with ziplists. */
            ele = c->argv[scoreidx+1+j*2];
            if ((eptr = zzlFind(zobj->ptr,ele,&curscore)) != NULL) {
                if (incr) {
                    score += curscore;
                    if (isnan(score)) {
                        addReplyError(c,nanerr);
                        goto cleanup;
                    }
                }

                /* Remove and re-insert when score changed. */
                if (score != curscore) {
                    zobj->ptr = zzlDelete(zobj->ptr,eptr);
                    zobj->ptr = zzlInsert(zobj->ptr,ele,score);
                    server.dirty++;
                    updated++;
                }
            } else {
                /* Optimize: check if the element is too large or the list
                 * becomes too long *before* executing zzlInsert. */
                zobj->ptr = zzlInsert(zobj->ptr,ele,score);
                if (zzlLength(zobj->ptr) > server.zset_max_ziplist_entries)
                    zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
                if (sdslen(ele->ptr) > server.zset_max_ziplist_value)
                    zsetConvert(zobj,REDIS_ENCODING_SKIPLIST);
                server.dirty++;
                added++;
            }
        } else if (zobj->encoding == REDIS_ENCODING_SKIPLIST) {
            zset *zs = zobj->ptr;
            zskiplistNode *znode;
            dictEntry *de;

            ele = c->argv[scoreidx+1+j*2] =
                tryObjectEncoding(c->argv[scoreidx+1+j*2]);
            de = dictFind(zs->dict,ele);
            if (de != NULL) {
                curobj = dictGetKey(de);
                curscore = *(double*)dictGetVal(de);

                if (incr) {
                    score += curscore;
                    if (isnan(score)) {
                        addReplyError(c,nanerr);
                        /* Don't need to check if the sorted set is empty
                         * because we know it has at least one element. */
                        goto cleanup;
                    }
                }

                /* Remove and re-insert when score changed. We can safely
                 * delete the key object from the skiplist, since the
                 * dictionary still has a reference to it. */
                if (score != curscore) {
                    redisAssertWithInfo(c,curobj,zslDelete(zs->zsl,curscore,curobj));
                    znode = zslInsert(zs->zsl,score,curobj);
                    incrRefCount(curobj); /* Re-inserted in skiplist. */
                    dictGetVal(de) = &znode->score; /* Update score ptr. */
                    server.dirty++;
                    updated++;
                }
            } else {
                znode = zslInsert(zs->zsl,score,ele);
                incrRefCount(ele); /* Inserted in skiplist. */
                redisAssertWithInfo(c,NULL,dictAdd(zs->dict,ele,&znode->score) == DICT_OK);
                incrRefCount(ele); /* Added to dictionary. */
                server.dirty++;
                added++;
            }
        } else {
            redisPanic("Unknown sorted set encoding");
        }
    }
    if (incr) /* ZINCRBY */
        addReplyDouble(c,score);
    else /* ZADD */
        addReplyLongLong(c,added);

cleanup:
    zfree(scores);
    if (added || updated) {
        signalModifiedKey(c->db,key);
        notifyKeyspaceEvent(REDIS_NOTIFY_ZSET,
            incr ? "zincr" : "zadd", key, c->db->id);
    }
}