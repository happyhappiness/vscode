static void lindexCommand(redisClient *c) {
    dictEntry *de;
    int index = atoi(c->argv[2]->ptr);
    
    de = dictFind(c->dict,c->argv[1]);
    if (de == NULL) {
        addReply(c,shared.nil);
    } else {
        robj *o = dictGetEntryVal(de);
        
        if (o->type != REDIS_LIST) {
            addReply(c,shared.wrongtypeerrbulk);
        } else {
            list *list = o->ptr;
            listNode *ln;
            
            ln = listIndex(list, index);
            if (ln == NULL) {
                addReply(c,shared.nil);
            } else {
                robj *ele = listNodeValue(ln);
                addReplySds(c,sdscatprintf(sdsempty(),"%d\r\n",(int)sdslen(ele->ptr)));
                addReply(c,ele);
                addReply(c,shared.crlf);
            }
        }
    }
}