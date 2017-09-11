        if (yn == -1) goto badfmt;
        server.no_appendfsync_on_rewrite = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
        int enable = yesnotoi(o->ptr);

        if (enable == -1) goto badfmt;
        if (enable == 0 && server.aof_state != REDIS_AOF_OFF) {
            stopAppendOnly();
        } else if (enable && server.aof_state == REDIS_AOF_OFF) {
            if (startAppendOnly() == REDIS_ERR) {
                addReplyError(c,
                    "Unable to turn on AOF. Check server logs.");
                return;
            }
        }
    } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-percentage")) {
