static void llenCommand(redisClient *c) {
    dictEntry *de;
    list *l;
    
    de = dictFind(c->dict,c->argv[1]);
    if (de == NULL) {
        addReply(c,shared.zero);
        return;
    } else {
        robj *o = dictGetEntryVal(de);
        if (o->type != REDIS_LIST) {
            addReply(c,shared.minus2);
        } else {
            l = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",listLength(l)));
        }
    }
}