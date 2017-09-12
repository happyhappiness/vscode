static int processMultiBulkItem(redisReader *r) {
    redisReadTask *cur = &(r->rstack[r->ridx]);
    void *obj;
    char *p;
    long elements;

    if ((p = readLine(r,NULL)) != NULL) {
        elements = strtol(p,NULL,10);
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
                r->ridx++;
                r->rstack[r->ridx].type = -1;
                r->rstack[r->ridx].elements = -1;
                r->rstack[r->ridx].parent = obj;
                r->rstack[r->ridx].idx = 0;
            } else {
                moveToNextTask(r);
            }
        }

        /* Object was created, so we can always continue. */
        if (r->reply == NULL)
            r->reply = obj;
        return 0;
    }
    return -1;
}