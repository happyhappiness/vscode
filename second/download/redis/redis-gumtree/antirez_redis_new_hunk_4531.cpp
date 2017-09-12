}

static void scardCommand(redisClient *c) {
    robj *o;
    dict *s;
    
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.czero);
        return;
    } else {
        if (o->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            s = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",
                dictSize(s)));
        }
    }
}

static int qsortCompareSetsByCardinality(const void *s1, const void *s2) {
    dict **d1 = (void*) s1, **d2 = (void*) s2;

    return dictSize(*d1)-dictSize(*d2);
}

static void sinterGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
