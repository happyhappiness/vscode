        if (offset < 0) offset = 0;
    }

    /* Ok, lookup the key and get the range */
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,justcount ? shared.czero : shared.nullmultibulk);
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            zset *zsetobj = o->ptr;
            zskiplist *zsl = zsetobj->zsl;
            zskiplistNode *ln;
            robj *ele, *lenobj = NULL;
            unsigned long rangelen = 0;

            /* Get the first node with the score >= min, or with
             * score > min if 'minex' is true. */
            ln = zslFirstWithScore(zsl,min);
            while (minex && ln && ln->score == min) ln = ln->forward[0];

            if (ln == NULL) {
                /* No element matching the speciifed interval */
                addReply(c,justcount ? shared.czero : shared.emptymultibulk);
                return;
            }

            /* We don't know in advance how many matching elements there
             * are in the list, so we push this object that will represent
             * the multi-bulk length in the output buffer, and will "fix"
             * it later */
            if (!justcount) {
                lenobj = createObject(REDIS_STRING,NULL);
                addReply(c,lenobj);
                decrRefCount(lenobj);
            }

            while(ln && (maxex ? (ln->score < max) : (ln->score <= max))) {
                if (offset) {
                    offset--;
                    ln = ln->forward[0];
                    continue;
                }
                if (limit == 0) break;
                if (!justcount) {
                    ele = ln->obj;
                    addReplyBulkLen(c,ele);
                    addReply(c,ele);
                    addReply(c,shared.crlf);
                    if (withscores)
                        addReplyDouble(c,ln->score);
                }
                ln = ln->forward[0];
                rangelen++;
                if (limit > 0) limit--;
            }
            if (justcount) {
                addReplyLong(c,(long)rangelen);
            } else {
                lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",
                     withscores ? (rangelen*2) : rangelen);
            }
        }
    }
}

static void zrangebyscoreCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,0);
}

static void zcountCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,1);
}

static void zcardCommand(redisClient *c) {
    robj *o;
    zset *zs;
