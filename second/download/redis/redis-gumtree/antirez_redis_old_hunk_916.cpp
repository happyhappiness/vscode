}

int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    REDIS_NOTUSED(eventLoop);
    REDIS_NOTUSED(id);
    REDIS_NOTUSED(clientData);

    if (config.liveclients == 0) {
        fprintf(stderr,"All clients disconnected... aborting.\n");
