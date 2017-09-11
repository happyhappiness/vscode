    clusterNode *sender;

    server.cluster->stats_bus_messages_received++;
    serverLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
        type, (unsigned long) totlen);

    /* Perform sanity checks */
