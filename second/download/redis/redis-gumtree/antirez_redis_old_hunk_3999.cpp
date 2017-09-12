     * an empty hash. The reply should then be a series of NULLs. */
    addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",c->argc-2));
    for (i = 2; i < c->argc; i++) {
        if (o != NULL && (value = hashGet(o,c->argv[i])) != NULL) {
            addReplyBulk(c,value);
            decrRefCount(value);
        } else {
