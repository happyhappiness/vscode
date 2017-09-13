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