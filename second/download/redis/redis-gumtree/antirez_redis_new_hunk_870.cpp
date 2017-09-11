    int j;

    bugReportStart();
    serverLog(LL_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
    serverLog(LL_WARNING,"client->flags = %d", c->flags);
    serverLog(LL_WARNING,"client->fd = %d", c->fd);
    serverLog(LL_WARNING,"client->argc = %d", c->argc);
    for (j=0; j < c->argc; j++) {
        char buf[128];
        char *arg;
