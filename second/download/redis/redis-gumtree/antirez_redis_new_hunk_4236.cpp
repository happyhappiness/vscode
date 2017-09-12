    robj *o;
    int start = atoi(c->argv[2]->ptr);
    int end = atoi(c->argv[3]->ptr);
    int llen;
    int rangelen, j;
    list *list;
    listNode *ln;
    robj *ele;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullmultibulk)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;
    llen = listLength(list);

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
        addReplyBulk(c,ele);
        ln = ln->next;
    }
}

static void ltrimCommand(redisClient *c) {
    robj *o;
    int start = atoi(c->argv[2]->ptr);
    int end = atoi(c->argv[3]->ptr);
    int llen;
    int j, ltrim, rtrim;
    list *list;
    listNode *ln;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.ok)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;
    llen = listLength(list);

    /* convert negative indexes */
    if (start < 0) start = llen+start;
    if (end < 0) end = llen+end;
    if (start < 0) start = 0;
    if (end < 0) end = 0;

    /* indexes sanity checks */
    if (start > end || start >= llen) {
        /* Out of range start or start > end result in empty list */
        ltrim = llen;
        rtrim = 0;
    } else {
        if (end >= llen) end = llen-1;
        ltrim = start;
        rtrim = llen-end-1;
    }

    /* Remove list elements to perform the trim */
    for (j = 0; j < ltrim; j++) {
        ln = listFirst(list);
        listDelNode(list,ln);
    }
    for (j = 0; j < rtrim; j++) {
        ln = listLast(list);
        listDelNode(list,ln);
    }
    server.dirty++;
    addReply(c,shared.ok);
}

static void lremCommand(redisClient *c) {
    robj *o;
    list *list;
    listNode *ln, *next;
    int toremove = atoi(c->argv[2]->ptr);
    int removed = 0;
    int fromtail = 0;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;

    if (toremove < 0) {
        toremove = -toremove;
        fromtail = 1;
    }
    ln = fromtail ? list->tail : list->head;
    while (ln) {
        robj *ele = listNodeValue(ln);

        next = fromtail ? ln->prev : ln->next;
        if (compareStringObjects(ele,c->argv[3]) == 0) {
            listDelNode(list,ln);
            server.dirty++;
            removed++;
            if (toremove && removed == toremove) break;
        }
        ln = next;
    }
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
}

/* This is the semantic of this command:
