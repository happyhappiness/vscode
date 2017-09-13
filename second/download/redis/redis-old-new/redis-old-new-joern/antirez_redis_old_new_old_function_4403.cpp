static void lrangeCommand(redisClient *c) {
    robj *o;
    int start = atoi(c->argv[2]->ptr);
    int end = atoi(c->argv[3]->ptr);

    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullmultibulk);
    } else {
        if (o->type != REDIS_LIST) {
            addReply(c,shared.wrongtypeerr);
        } else {
            list *list = o->ptr;
            listNode *ln;
            int llen = listLength(list);
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

            /* Return the result in form of a multi-bulk reply */
            ln = listIndex(list, start);
            addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",rangelen));
            for (j = 0; j < rangelen; j++) {
                ele = listNodeValue(ln);
                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(ele->ptr)));
                addReply(c,ele);
                addReply(c,shared.crlf);
                ln = ln->next;
            }
        }
    }
}