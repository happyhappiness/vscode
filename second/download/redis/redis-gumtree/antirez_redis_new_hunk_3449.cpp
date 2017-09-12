    void *obj;
    char *p;
    long elements;
    int root = 0;

    /* Set error for nested multi bulks with depth > 1 */
    if (r->ridx == 2) {
        redisSetReplyReaderError(r,sdscatprintf(sdsempty(),
            "No support for nested multi bulk replies with depth > 1"));
        return -1;
    }

    if ((p = readLine(r,NULL)) != NULL) {
        elements = readLongLong(p);
        root = (r->ridx == 0);

        if (elements == -1) {
            obj = r->fn ? r->fn->createNil(cur) :
                (void*)REDIS_REPLY_NIL;
