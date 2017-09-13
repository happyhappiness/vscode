static void clientDone(client c) {
    long long latency;
    config.donerequests ++;
    latency = mstime() - c->start;
    if (latency > MAX_LATENCY) latency = MAX_LATENCY;
    config.latency[latency]++;

    if (config.donerequests == config.requests) {
        freeClient(c);
        aeStop(config.el);
        return;
    }
    if (config.keepalive) {
        resetClient(c);
        if (config.randomkeys) randomizeClientKey(c);
    } else {
        config.liveclients--;
        createMissingClients(c);
        config.liveclients++;
        freeClient(c);
    }
}