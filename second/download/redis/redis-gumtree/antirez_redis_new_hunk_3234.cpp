void selectCommand(redisClient *c) {
    int id = atoi(c->argv[1]->ptr);

    if (server.cluster_enabled && id != 0) {
        addReplyError(c,"SELECT is not allowed in cluster mode");
        return;
    }
