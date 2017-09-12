static void sismemberCommand(redisClient *c) {
    robj *set;

    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,set,REDIS_SET)) return;

    if (dictFind(set->ptr,c->argv[2]))
        addReply(c,shared.cone);
    else
        addReply(c,shared.czero);
}

static void scardCommand(redisClient *c) {
    robj *o;
    dict *s;

    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_SET)) return;
    
    s = o->ptr;
    addReplyUlong(c,dictSize(s));
}

static void spopCommand(redisClient *c) {
    robj *set;
    dictEntry *de;

    if ((set = lookupKeyWriteOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,set,REDIS_SET)) return;

    de = dictGetRandomKey(set->ptr);
    if (de == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        robj *ele = dictGetEntryKey(de);

        addReplyBulk(c,ele);
        dictDelete(set->ptr,ele);
        if (htNeedsResize(set->ptr)) dictResize(set->ptr);
        server.dirty++;
    }
}

static void srandmemberCommand(redisClient *c) {
    robj *set;
    dictEntry *de;

    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,set,REDIS_SET)) return;

    de = dictGetRandomKey(set->ptr);
    if (de == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        robj *ele = dictGetEntryKey(de);

        addReplyBulk(c,ele);
    }
}

