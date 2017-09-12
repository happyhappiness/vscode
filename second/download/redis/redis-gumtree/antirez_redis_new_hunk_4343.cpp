    dictEntry *de;
    list *l;

    printf("unblockClient %p %s\n", c, c->blockingkey->ptr);
    /* Remove this client from the list of clients waiting for this key. */
    assert(c->blockingkey != NULL);
    de = dictFind(c->db->blockingkeys,c->blockingkey);
