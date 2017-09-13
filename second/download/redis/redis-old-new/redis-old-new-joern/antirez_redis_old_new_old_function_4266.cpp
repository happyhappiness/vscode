static void blockForKey(redisClient *c, robj *key, time_t timeout) {
    dictEntry *de;
    list *l;

    printf("blockForKey %p %s\n", c, key->ptr);
    c->blockingkey = key;
    incrRefCount(key);
    c->blockingto = timeout;
    de = dictFind(c->db->blockingkeys,key);
    if (de == NULL) {
        int retval;

        l = listCreate();
        retval = dictAdd(c->db->blockingkeys,key,l);
        incrRefCount(key);
        assert(retval == DICT_OK);
    } else {
        l = dictGetEntryVal(de);
    }
    listAddNodeTail(l,c);
    c->flags |= REDIS_BLOCKED;
    aeDeleteFileEvent(server.el,c->fd,AE_READABLE);
}