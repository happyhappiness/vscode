void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
    zrangespec range;
    robj *o, *emptyreply;
    zset *zsetobj;
    zskiplist *zsl;
    zskiplistNode *ln;
    int offset = 0, limit = -1;
    int withscores = 0;
    unsigned long rangelen = 0;
    void *replylen = NULL;

    /* Parse the range arguments. */
    zslParseRange(c->argv[2],c->argv[3],&range);

    /* Parse optional extra arguments. Note that ZCOUNT will exactly have
     * 4 arguments, so we'll never enter the following code path. */
    if (c->argc > 4) {
        int remaining = c->argc - 4;
        int pos = 4;

        while (remaining) {
            if (remaining >= 1 && !strcasecmp(c->argv[pos]->ptr,"withscores")) {
                pos++; remaining--;
                withscores = 1;
            } else if (remaining >= 3 && !strcasecmp(c->argv[pos]->ptr,"limit")) {
                offset = atoi(c->argv[pos+1]->ptr);
                limit = atoi(c->argv[pos+2]->ptr);
                pos += 3; remaining -= 3;
            } else {
                addReply(c,shared.syntaxerr);
                return;
            }
        }
    }

    /* Ok, lookup the key and get the range */
    emptyreply = justcount ? shared.czero : shared.emptymultibulk;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],emptyreply)) == NULL ||
        checkType(c,o,REDIS_ZSET)) return;
    zsetobj = o->ptr;
    zsl = zsetobj->zsl;

    /* If reversed, assume the elements are sorted from high to low score. */
    ln = zslFirstWithScore(zsl,range.min);
    if (reverse) {
        /* If range.min is out of range, ln will be NULL and we need to use
         * the tail of the skiplist as first node of the range. */
        if (ln == NULL) ln = zsl->tail;

        /* zslFirstWithScore returns the first element with where with
         * score >= range.min, so backtrack to make sure the element we use
         * here has score <= range.min. */
        while (ln && ln->score > range.min) ln = ln->backward;

        /* Move to the right element according to the range spec. */
        if (range.minex) {
            /* Find last element with score < range.min */
            while (ln && ln->score == range.min) ln = ln->backward;
        } else {
            /* Find last element with score <= range.min */
            while (ln && ln->level[0].forward &&
                         ln->level[0].forward->score == range.min)
                ln = ln->level[0].forward;
        }
    } else {
        if (range.minex) {
            /* Find first element with score > range.min */
            while (ln && ln->score == range.min) ln = ln->level[0].forward;
        }
    }

    /* No "first" element in the specified interval. */
    if (ln == NULL) {
        addReply(c,emptyreply);
        return;
    }

    /* We don't know in advance how many matching elements there
     * are in the list, so we push this object that will represent
     * the multi-bulk length in the output buffer, and will "fix"
     * it later */
    if (!justcount)
        replylen = addDeferredMultiBulkLength(c);

    /* If there is an offset, just traverse the number of elements without
     * checking the score because that is done in the next loop. */
    while(ln && offset--) {
        if (reverse)
            ln = ln->backward;
        else
            ln = ln->level[0].forward;
    }

    while (ln && limit--) {
        /* Check if this this element is in range. */
        if (reverse) {
            if (range.maxex) {
                /* Element should have score > range.max */
                if (ln->score <= range.max) break;
            } else {
                /* Element should have score >= range.max */
                if (ln->score < range.max) break;
            }
        } else {
            if (range.maxex) {
                /* Element should have score < range.max */
                if (ln->score >= range.max) break;
            } else {
                /* Element should have score <= range.max */
                if (ln->score > range.max) break;
            }
        }

        /* Do our magic */
        rangelen++;
        if (!justcount) {
            addReplyBulk(c,ln->obj);
            if (withscores)
                addReplyDouble(c,ln->score);
        }

        if (reverse)
            ln = ln->backward;
        else
            ln = ln->level[0].forward;
    }

    if (justcount) {
        addReplyLongLong(c,(long)rangelen);
    } else {
        setDeferredMultiBulkLength(c,replylen,
             withscores ? (rangelen*2) : rangelen);
    }
}