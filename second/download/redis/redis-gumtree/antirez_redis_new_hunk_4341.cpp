    dictEntry *de;
    list *l;

    /* Remove this client from the list of clients waiting for this key. */
    assert(c->blockingkey != NULL);
    de = dictFind(c->db->blockingkeys,c->blockingkey);
