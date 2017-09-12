void _serverAssertPrintClientInfo(client *c) {
    int j;

    bugReportStart();
    serverLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
    serverLog(REDIS_WARNING,"client->flags = %d", c->flags);
    serverLog(REDIS_WARNING,"client->fd = %d", c->fd);
    serverLog(REDIS_WARNING,"client->argc = %d", c->argc);
    for (j=0; j < c->argc; j++) {
        char buf[128];
        char *arg;

        if (c->argv[j]->type == OBJ_STRING && sdsEncodedObject(c->argv[j])) {
            arg = (char*) c->argv[j]->ptr;
        } else {
            snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
                c->argv[j]->type, c->argv[j]->encoding);
            arg = buf;
        }
        serverLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
            j, arg, c->argv[j]->refcount);
    }
}