    dictEntry *de;
    list *l;

    c->blockingkey = key;
    incrRefCount(key);
    c->blockingto = timeout;
