        return;
    }

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullmultibulk)) == NULL ||
        checkType(c,o,REDIS_ZSET)) return;
    zsetobj = o->ptr;
    zsl = zsetobj->zsl;
    llen = zsl->length;

    /* convert negative indexes */
    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;
    if (end < 0) end = 0;

    /* indexes sanity checks */
    if (start > end || start >= llen) {
        /* Out of range start or start > end result in empty list */
        addReply(c,shared.emptymultibulk);
        return;
    }
    if (end >= llen) end = llen-1;
    rangelen = (end-start)+1;

    /* check if starting point is trivial, before searching
     * the element in log(N) time */
    if (reverse) {
        ln = start == 0 ? zsl->tail : zslGetElementByRank(zsl, llen-start);
    } else {
        ln = start == 0 ?
            zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
    }

    /* Return the result in form of a multi-bulk reply */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
        withscores ? (rangelen*2) : rangelen));
    for (j = 0; j < rangelen; j++) {
        ele = ln->obj;
        addReplyBulk(c,ele);
        if (withscores)
            addReplyDouble(c,ln->score);
        ln = reverse ? ln->backward : ln->forward[0];
    }
}

