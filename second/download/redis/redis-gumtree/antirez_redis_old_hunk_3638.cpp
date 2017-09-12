    zrangeGenericCommand(c,1);
}

/* This command implements both ZRANGEBYSCORE and ZCOUNT.
 * If justcount is non-zero, just the count is returned. */
void genericZrangebyscoreCommand(redisClient *c, int justcount) {
    robj *o;
    double min, max;
    int minex = 0, maxex = 0; /* are min or max exclusive? */
    int offset = 0, limit = -1;
    int withscores = 0;
    int badsyntax = 0;

    /* Parse the min-max interval. If one of the values is prefixed
     * by the "(" character, it's considered "open". For instance
     * ZRANGEBYSCORE zset (1.5 (2.5 will match min < x < max
     * ZRANGEBYSCORE zset 1.5 2.5 will instead match min <= x <= max */
    if (((char*)c->argv[2]->ptr)[0] == '(') {
        min = strtod((char*)c->argv[2]->ptr+1,NULL);
        minex = 1;
    } else {
        min = strtod(c->argv[2]->ptr,NULL);
    }
    if (((char*)c->argv[3]->ptr)[0] == '(') {
        max = strtod((char*)c->argv[3]->ptr+1,NULL);
        maxex = 1;
    } else {
        max = strtod(c->argv[3]->ptr,NULL);
    }

    /* Parse "WITHSCORES": note that if the command was called with
     * the name ZCOUNT then we are sure that c->argc == 4, so we'll never
     * enter the following paths to parse WITHSCORES and LIMIT. */
    if (c->argc == 5 || c->argc == 8) {
        if (strcasecmp(c->argv[c->argc-1]->ptr,"withscores") == 0)
            withscores = 1;
        else
            badsyntax = 1;
    }
    if (c->argc != (4 + withscores) && c->argc != (7 + withscores))
        badsyntax = 1;
    if (badsyntax) {
        addReplyError(c,"wrong number of arguments for ZRANGEBYSCORE");
        return;
    }

    /* Parse "LIMIT" */
    if (c->argc == (7 + withscores) && strcasecmp(c->argv[4]->ptr,"limit")) {
        addReply(c,shared.syntaxerr);
        return;
    } else if (c->argc == (7 + withscores)) {
        offset = atoi(c->argv[5]->ptr);
        limit = atoi(c->argv[6]->ptr);
        if (offset < 0) offset = 0;
    }

    /* Ok, lookup the key and get the range */
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,justcount ? shared.czero : shared.emptymultibulk);
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            zset *zsetobj = o->ptr;
            zskiplist *zsl = zsetobj->zsl;
            zskiplistNode *ln;
            robj *ele;
            void *replylen = NULL;
            unsigned long rangelen = 0;

            /* Get the first node with the score >= min, or with
             * score > min if 'minex' is true. */
            ln = zslFirstWithScore(zsl,min);
            while (minex && ln && ln->score == min) ln = ln->level[0].forward;

            if (ln == NULL) {
                /* No element matching the speciifed interval */
                addReply(c,justcount ? shared.czero : shared.emptymultibulk);
                return;
            }

            /* We don't know in advance how many matching elements there
             * are in the list, so we push this object that will represent
             * the multi-bulk length in the output buffer, and will "fix"
             * it later */
            if (!justcount)
                replylen = addDeferredMultiBulkLength(c);

            while(ln && (maxex ? (ln->score < max) : (ln->score <= max))) {
                if (offset) {
                    offset--;
                    ln = ln->level[0].forward;
                    continue;
                }
                if (limit == 0) break;
                if (!justcount) {
                    ele = ln->obj;
                    addReplyBulk(c,ele);
                    if (withscores)
                        addReplyDouble(c,ln->score);
                }
                ln = ln->level[0].forward;
                rangelen++;
                if (limit > 0) limit--;
            }
            if (justcount) {
                addReplyLongLong(c,(long)rangelen);
            } else {
                setDeferredMultiBulkLength(c,replylen,
                     withscores ? (rangelen*2) : rangelen);
            }
        }
    }
}

void zrangebyscoreCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,0);
}

void zcountCommand(redisClient *c) {
    genericZrangebyscoreCommand(c,1);
}

void zcardCommand(redisClient *c) {
