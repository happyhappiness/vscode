static void llenCommand(redisClient *c) {
    robj *o;
    list *l;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    
    l = o->ptr;
    addReplyUlong(c,listLength(l));
}

static void lindexCommand(redisClient *c) {
    robj *o;
    int index = atoi(c->argv[2]->ptr);
    list *list;
    listNode *ln;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;

    ln = listIndex(list, index);
    if (ln == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        robj *ele = listNodeValue(ln);
        addReplyBulk(c,ele);
    }
}

static void lsetCommand(redisClient *c) {
    robj *o;
    int index = atoi(c->argv[2]->ptr);
    list *list;
    listNode *ln;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nokeyerr)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;

    ln = listIndex(list, index);
    if (ln == NULL) {
        addReply(c,shared.outofrangeerr);
    } else {
        robj *ele = listNodeValue(ln);

        decrRefCount(ele);
        listNodeValue(ln) = c->argv[3];
        incrRefCount(c->argv[3]);
        addReply(c,shared.ok);
        server.dirty++;
    }
}

static void popGenericCommand(redisClient *c, int where) {
    robj *o;
    list *list;
    listNode *ln;

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_LIST)) return;
    list = o->ptr;

    if (where == REDIS_HEAD)
        ln = listFirst(list);
    else
        ln = listLast(list);

    if (ln == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        robj *ele = listNodeValue(ln);
        addReplyBulk(c,ele);
        listDelNode(list,ln);
        server.dirty++;
    }
}

