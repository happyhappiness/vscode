    } else if (!strcasecmp(c->argv[2]->ptr,"repl-ping-slave-period")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_ping_slave_period = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_timeout = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"watchdog-period")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        if (ll)
            enableWatchdog(ll);
        else
            disableWatchdog();
    } else if (!strcasecmp(c->argv[2]->ptr,"rdbcompression")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.rdb_compression = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"rdbchecksum")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.rdb_checksum = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-disable-tcp-nodelay")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_disable_tcp_nodelay = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-priority")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll <= 0) goto badfmt;
        server.slave_priority = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
        return;
    }
    addReply(c,shared.ok);
