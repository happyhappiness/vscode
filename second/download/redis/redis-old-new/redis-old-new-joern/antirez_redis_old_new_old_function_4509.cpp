static void mgetCommand(redisClient *c) {
    dictEntry *de;
    int j;
  
    addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",c->argc-1));
    for (j = 1; j < c->argc; j++) {
        de = dictFind(c->dict,c->argv[j]);
        if (de == NULL) {
            addReply(c,shared.minus1);
        } else {
            robj *o = dictGetEntryVal(de);
            
            if (o->type != REDIS_STRING) {
                addReply(c,shared.minus1);
            } else {
                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(o->ptr)));
                addReply(c,o);
                addReply(c,shared.crlf);
            }
        }
    }
}