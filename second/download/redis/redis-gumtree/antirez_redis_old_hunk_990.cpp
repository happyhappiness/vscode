    time_t now = now_ms/1000;

    if (server.maxidletime &&
        !(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
        !(c->flags & REDIS_MASTER) &&   /* no timeout for masters */
        !(c->flags & REDIS_BLOCKED) &&  /* no timeout for BLPOP */
        !(c->flags & REDIS_PUBSUB) &&   /* no timeout for Pub/Sub clients */
        (now - c->lastinteraction > server.maxidletime))
    {
        serverLog(REDIS_VERBOSE,"Closing idle client");
        freeClient(c);
        return 1;
    } else if (c->flags & REDIS_BLOCKED) {
        /* Blocked OPS timeout is handled with milliseconds resolution.
         * However note that the actual resolution is limited by
         * server.hz. */
