void replicationCacheMaster(client *c) {
    listNode *ln;

    serverAssert(server.master != NULL && server.cached_master == NULL);
    serverLog(REDIS_NOTICE,"Caching the disconnected master state.");

    /* Remove from the list of clients, we don't want this client to be
     * listed by CLIENT LIST or processed in any way by batch operations. */
    ln = listSearchKey(server.clients,c);
    serverAssert(ln != NULL);
    listDelNode(server.clients,ln);

    /* Save the master. Server.master will be set to null later by
