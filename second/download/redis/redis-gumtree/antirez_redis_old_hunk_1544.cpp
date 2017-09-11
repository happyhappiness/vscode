            server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
        }
        sdsfreesplitres(v,vlen);
    } else if (!strcasecmp(c->argv[2]->ptr,"stop-writes-on-bgsave-error")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.stop_writes_on_bgsave_err = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-ping-slave-period")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_ping_slave_period = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
        server.repl_timeout = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-size")) {
        ll = memtoll(o->ptr,&err);
        if (err || ll < 0) goto badfmt;
        resizeReplicationBacklog(ll);
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-ttl")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
        server.repl_backlog_time_limit = ll;
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
    } else if (!strcasecmp(c->argv[2]->ptr,"notify-keyspace-events")) {
        int flags = keyspaceEventsStringToFlags(o->ptr);

        if (flags == -1) goto badfmt;
        server.notify_keyspace_events = flags;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-disable-tcp-nodelay")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_disable_tcp_nodelay = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-diskless-sync")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.repl_diskless_sync = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"repl-diskless-sync-delay")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.repl_diskless_sync_delay = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"slave-priority")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.slave_priority = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"min-slaves-to-write")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.repl_min_slaves_to_write = ll;
        refreshGoodSlavesCount();
    } else if (!strcasecmp(c->argv[2]->ptr,"min-slaves-max-lag")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.repl_min_slaves_max_lag = ll;
        refreshGoodSlavesCount();
    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-require-full-coverage")) {
        int yn = yesnotoi(o->ptr);

        if (yn == -1) goto badfmt;
        server.cluster_require_full_coverage = yn;
    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-node-timeout")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll <= 0) goto badfmt;
        server.cluster_node_timeout = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-migration-barrier")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.cluster_migration_barrier = ll;
    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-slave-validity-factor")) {
        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
            ll < 0) goto badfmt;
        server.cluster_slave_validity_factor = ll;
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
