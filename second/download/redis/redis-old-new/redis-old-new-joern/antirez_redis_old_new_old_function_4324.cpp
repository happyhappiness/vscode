static void zscoreCommand(redisClient *c) {
    robj *o;
    zset *zs;
    
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o == NULL) {
        addReply(c,shared.nullbulk);
        return;
    } else {
        if (o->type != REDIS_ZSET) {
            addReply(c,shared.wrongtypeerr);
        } else {
            dictEntry *de;

            zs = o->ptr;
            de = dictFind(zs->dict,c->argv[2]);
            if (!de) {
                addReply(c,shared.nullbulk);
            } else {
                char buf[128];
                double *score = dictGetEntryVal(de);

                snprintf(buf,sizeof(buf),"%.17g",*score);
                addReplySds(c,sdscatprintf(sdsempty(),"$%d\r\n%s\r\n",
                    strlen(buf),buf));
            }
        }
    }
}