        return;
    }

    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullmultibulk);
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            zset *zsetobj = o->ptr;
            zskiplist *zsl = zsetobj->zsl;
            zskiplistNode *ln;

            int llen = zsl->length;
            int rangelen, j;
            robj *ele;

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
                ln = start == 0 ? zsl->header->forward[0] : zslGetElementByRank(zsl, start+1);
            }

            /* Return the result in form of a multi-bulk reply */
            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",
                withscores ? (rangelen*2) : rangelen));
            for (j = 0; j < rangelen; j++) {
                ele = ln->obj;
                addReplyBulkLen(c,ele);
                addReply(c,ele);
                addReply(c,shared.crlf);
                if (withscores)
                    addReplyDouble(c,ln->score);
                ln = reverse ? ln->backward : ln->forward[0];
            }
        }
    }
}

