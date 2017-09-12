static int processMultiBulkItem(redisReader *r) {
    redisReadTask *cur = &(r->rstack[r->ridx]);
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
            moveToNextTask(r);
        } else {
            obj = r->fn ? r->fn->createArray(cur,elements) :
                (void*)REDIS_REPLY_ARRAY;

            /* Modify task stack when there are more than 0 elements. */
            if (elements > 0) {
                cur->elements = elements;
                cur->obj = obj;
                r->ridx++;
                r->rstack[r->ridx].type = -1;
                r->rstack[r->ridx].elements = -1;
                r->rstack[r->ridx].idx = 0;
                r->rstack[r->ridx].obj = NULL;
                r->rstack[r->ridx].parent = cur;
                r->rstack[r->ridx].privdata = r->privdata;
            } else {
                moveToNextTask(r);
            }
        }

        /* Set reply if this is the root object. */
        if (root) r->reply = obj;
        return 0;
    }
    return -1;
}