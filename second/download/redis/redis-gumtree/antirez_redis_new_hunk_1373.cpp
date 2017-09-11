void replicationDiscardCachedMaster(void) {
    if (server.cached_master == NULL) return;

    serverLog(REDIS_NOTICE,"Discarding previously cached master state.");
    server.cached_master->flags &= ~REDIS_MASTER;
    freeClient(server.cached_master);
    server.cached_master = NULL;
