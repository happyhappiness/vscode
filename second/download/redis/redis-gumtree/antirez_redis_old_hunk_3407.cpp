    void *obj;
    char *p;
    long elements;

    if ((p = readLine(r,NULL)) != NULL) {
        elements = strtol(p,NULL,10);
        if (elements == -1) {
            obj = r->fn ? r->fn->createNil(cur) :
                (void*)REDIS_REPLY_NIL;
