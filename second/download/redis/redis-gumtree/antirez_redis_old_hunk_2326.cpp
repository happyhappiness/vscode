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
