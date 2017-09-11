}

int showThroughput(struct aeEventLoop *eventLoop, long long id, void *clientData) {
    UNUSED(eventLoop);
    UNUSED(id);
    UNUSED(clientData);

    if (config.liveclients == 0) {
        fprintf(stderr,"All clients disconnected... aborting.\n");
