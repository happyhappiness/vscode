    redisClient *c;

    /* Run a fast expire cycle. */
    activeExpireCycle(1);

    /* Try to process pending commands for clients that were just unblocked. */
    while (listLength(server.unblocked_clients)) {
