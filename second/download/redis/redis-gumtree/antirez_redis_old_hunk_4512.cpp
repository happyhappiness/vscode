    c->start = mstime();
}

static void clientDone(client c) {
    long long latency;
    config.donerequests ++;
