    listNode *ln;

    redisAssert(server.master != NULL && server.cached_master == NULL);
    redisLog(REDIS_NOTICE,"Caching the disconnected master state.");

    /* Remove from the list of clients, we don't want this client to be
     * listed by CLIENT LIST or processed in any way by batch operations. */
