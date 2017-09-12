    /* Note the check for o != NULL happens inside the loop. This is
     * done because objects that cannot be found are considered to be
     * an empty hash. The reply should then be a series of NULLs. */
    addReplyMultiBulkLen(c,c->argc-2);
    for (i = 2; i < c->argc; i++) {
        if (o != NULL && (value = hashTypeGet(o,c->argv[i])) != NULL) {
            addReplyBulk(c,value);
