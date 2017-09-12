void beforeSleep(struct aeEventLoop *eventLoop) {
    REDIS_NOTUSED(eventLoop);
    listNode *ln;
    redisClient *c;

    /* Run a fast expire cycle. */
    {
        long long totalex = server.stat_expiredkeys;
        activeExpireCycle(1);
        if (server.stat_expiredkeys - totalex)
            printf("EXPIRED FAST: %lld\n", server.stat_expiredkeys - totalex);
    }

    /* Try to process pending commands for clients that were just unblocked. */
    while (listLength(server.unblocked_clients)) {
        ln = listFirst(server.unblocked_clients);
        redisAssert(ln != NULL);
        c = ln->value;
        listDelNode(server.unblocked_clients,ln);
        c->flags &= ~REDIS_UNBLOCKED;

        /* Process remaining data in the input buffer. */
        if (c->querybuf && sdslen(c->querybuf) > 0) {
            server.current_client = c;
            processInputBuffer(c);
            server.current_client = NULL;
        }
    }

    /* Write the AOF buffer on disk */
    flushAppendOnlyFile(0);
}