static void hmgetCommand(redisClient *c) {
    int i;
    robj *o, *value;
    o = lookupKeyRead(c->db,c->argv[1]);
    if (o != NULL && o->type != REDIS_HASH) {
        addReply(c,shared.wrongtypeerr);
    }

    /* Note the check for o != NULL happens inside the loop. This is
     * done because objects that cannot be found are considered to be
     * an empty hash. The reply should then be a series of NULLs. */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
    for (i = 2; i < c->argc; i++) {
        if (o != NULL && (value = hashGet(o,c->argv[i])) != NULL) {
            addReplyBulk(c,value);
            decrRefCount(value);
        } else {
            addReply(c,shared.nullbulk);
        }
    }
}