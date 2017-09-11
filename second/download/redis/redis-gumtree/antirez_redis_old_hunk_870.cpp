    int j;

    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
    serverLog(REDIS_WARNING,"client->flags = %d", c->flags);
    serverLog(REDIS_WARNING,"client->fd = %d", c->fd);
    serverLog(REDIS_WARNING,"client->argc = %d", c->argc);
    for (j=0; j < c->argc; j++) {
        char buf[128];
        char *arg;
