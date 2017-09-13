static void unblockClient(redisClient *c) {
    dictEntry *de;
    list *l;

    printf("unblockClient %p %s\n", c, c->blockingkey->ptr);
    /* Remove this client from the list of clients waiting for this key. */
    assert(c->blockingkey != NULL);
    de = dictFind(c->db->blockingkeys,c->blockingkey);
    assert(de != NULL);
    l = dictGetEntryVal(de);
    listDelNode(l,listSearchKey(l,c));
    /* If the list is empty we need to remove it to avoid wasting memory */
    if (listLength(l) == 0)
        dictDelete(c->db->blockingkeys,c->blockingkey);
    /* Finally set the right flags in the client structure */
    decrRefCount(c->blockingkey);
    c->blockingkey = NULL;
    c->flags &= (~REDIS_BLOCKED);
    /* Ok now we are ready to get read events from socket, note that we
     * can't trap errors here as it's possible that unblockClients() is
     * called from freeClient() itself, and the only thing we can do
     * if we failed to register the READABLE event is to kill the client.
     * Still the following function should never fail in the real world as
     * we are sure the file descriptor is sane, and we exit on out of mem. */
    aeCreateFileEvent(server.el, c->fd, AE_READABLE, readQueryFromClient, c);
    /* As a final step we want to process data if there is some command waiting
     * in the input buffer. Note that this is safe even if unblockClient()
     * gets called from freeClient() because freeClient() will be smart
     * enough to call this function *after* c->querybuf was set to NULL. */
    if (c->querybuf && sdslen(c->querybuf) > 0) processInputBuffer(c);
}