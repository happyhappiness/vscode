        !(c->flags & REDIS_PUBSUB) &&   /* no timeout for Pub/Sub clients */
        (now - c->lastinteraction > server.maxidletime))
    {
        serverLog(REDIS_VERBOSE,"Closing idle client");
        freeClient(c);
        return 1;
    } else if (c->flags & REDIS_BLOCKED) {
