}

static void scardCommand(redisClient *c) {
    dictEntry *de;
    dict *s;
    
    de = dictFind(c->dict,c->argv[1]);
    if (de == NULL) {
        addReply(c,shared.czero);
        return;
    } else {
        robj *o = dictGetEntryVal(de);
        if (o->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            s = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
                dictGetHashTableUsed(s)));
        }
    }
}

static int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
    dict **d1 = (void*) s1, **d2 = (void*) s2;

    return dictGetHashTableUsed(*d1)-dictGetHashTableUsed(*d2);
}

static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
