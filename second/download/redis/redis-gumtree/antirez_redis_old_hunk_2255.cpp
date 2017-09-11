    setDeferredMultiBulkLength(c,replylen,numkeys);
}

void scanCallback(void *privdata, const dictEntry *de) {
    list *keys = (list *)privdata;
    sds key = dictGetKey(de);
    robj *kobj = createStringObject(key, sdslen(key));
    listAddNodeTail(keys, kobj);
}

void scanCommand(redisClient *c) {
    int rv;
    int i, j;
    char buf[REDIS_LONGSTR_SIZE];
    list *keys = listCreate();
    listNode *node, *nextnode;
    unsigned long cursor = 0;
    long count = 1;
    sds pat;
    int patlen, patnoop = 1;

    /* Use sscanf because we need an *unsigned* long */
    rv = sscanf(c->argv[1]->ptr, "%lu", &cursor);
    if (rv != 1) {
        addReplyError(c, "invalid cursor");
        goto cleanup;
    }

    i = 2;
    while (i < c->argc) {
        j = c->argc - i;
        if (!strcasecmp(c->argv[i]->ptr, "count") && j >= 2) {
