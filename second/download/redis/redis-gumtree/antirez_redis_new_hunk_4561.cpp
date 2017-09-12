    
    de = dictFind(c->dict,c->argv[1]);
    if (de == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        robj *o = dictGetEntryVal(de);
        
        if (o->type != REDIS_STRING) {
            addReply(c,shared.wrongtypeerr);
        } else {
            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",(int)sdslen(o->ptr)));
            addReply(c,o);
            addReply(c,shared.crlf);
        }
