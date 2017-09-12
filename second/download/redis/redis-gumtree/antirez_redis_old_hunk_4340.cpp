    dictEntry *de;
    list *l;

    printf("blockForKey %p %s\n", c, key->ptr);
    c->blockingkey = key;
    incrRefCount(key);
    c->blockingto = timeout;
