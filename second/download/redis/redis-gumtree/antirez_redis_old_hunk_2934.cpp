        if (yn == -1) goto badfmt;
        server.no_appendfsync_on_rewrite = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
        int old = server.appendonly;
        int new = yesnotoi(o->ptr);

        if (new == -1) goto badfmt;
        if (old != new) {
            if (new == 0) {
                stopAppendOnly();
            } else {
                if (startAppendOnly() == REDIS_ERR) {
                    addReplyError(c,
                        "Unable to turn on AOF. Check server logs.");
                    return;
                }
            }
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-percentage")) {
