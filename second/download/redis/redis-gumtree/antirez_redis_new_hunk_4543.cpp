    
    de = dictFind(c->dict,c->argv[1]);
    if (de == NULL) {
        addReply(c,shared.czero);
        return;
    } else {
        robj *o = dictGetEntryVal(de);
        if (o->type != REDIS_LIST) {
            addReply(c,shared.wrongtypeerr);
        } else {
            l = o->ptr;
            addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",listLength(l)));
        }
    }
}
