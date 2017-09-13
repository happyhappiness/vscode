static void spopCommand(redisClient *c) {
    robj *set;
    dictEntry *de;

    set = lookupKeyWrite(c->db,c->argv[1]);
    if (set == NULL) {
        addReply(c,shared.nullbulk);
    } else {
        if (set->type != REDIS_SET) {
            addReply(c,shared.wrongtypeerr);
            return;
        }
        de = dictGetRandomKey(set->ptr);
        if (de == NULL) {
            addReply(c,shared.nullbulk);
        } else {
            robj *ele = dictGetEntryKey(de);

            addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n",sdslen(ele->ptr)));
            addReply(c,ele);
            addReply(c,shared.crlf);
            dictDelete(set->ptr,ele);
            if (htNeedsResize(set->ptr)) dictResize(set->ptr);
            server.dirty++;
        }
    }
}