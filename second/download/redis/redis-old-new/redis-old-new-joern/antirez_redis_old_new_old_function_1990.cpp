void configGetCommand(redisClient *c) {
    robj *o = c->argv[2];
    void *replylen = addDeferredMultiBulkLength(c);
    char *pattern = o->ptr;
    char buf[128];
    int matches = 0;
    redisAssertWithInfo(c,o,o->encoding == REDIS_ENCODING_RAW);

    /* String values */
    config_get_string_field("dbfilename",server.rdb_filename);
    config_get_string_field("requirepass",server.requirepass);
    config_get_string_field("masterauth",server.masterauth);
    config_get_string_field("bind",server.bindaddr);
    config_get_string_field("unixsocket",server.unixsocket);
    config_get_string_field("logfile",server.logfile);
    config_get_string_field("pidfile",server.pidfile);

    /* Numerical values */
    config_get_numerical_field("maxmemory",server.maxmemory);
    config_get_numerical_field("maxmemory-samples",server.maxmemory_samples);
    config_get_numerical_field("timeout",server.maxidletime);
    config_get_numerical_field("tcp-keepalive",server.tcpkeepalive);
    config_get_numerical_field("auto-aof-rewrite-percentage",
            server.aof_rewrite_perc);
    config_get_numerical_field("auto-aof-rewrite-min-size",
            server.aof_rewrite_min_size);
    config_get_numerical_field("hash-max-ziplist-entries",
            server.hash_max_ziplist_entries);
    config_get_numerical_field("hash-max-ziplist-value",
            server.hash_max_ziplist_value);
    config_get_numerical_field("list-max-ziplist-entries",
            server.list_max_ziplist_entries);
    config_get_numerical_field("list-max-ziplist-value",
            server.list_max_ziplist_value);
    config_get_numerical_field("set-max-intset-entries",
            server.set_max_intset_entries);
    config_get_numerical_field("zset-max-ziplist-entries",
            server.zset_max_ziplist_entries);
    config_get_numerical_field("zset-max-ziplist-value",
            server.zset_max_ziplist_value);
    config_get_numerical_field("lua-time-limit",server.lua_time_limit);
    config_get_numerical_field("slowlog-log-slower-than",
            server.slowlog_log_slower_than);
    config_get_numerical_field("slowlog-max-len",
            server.slowlog_max_len);
    config_get_numerical_field("port",server.port);
    config_get_numerical_field("databases",server.dbnum);
    config_get_numerical_field("repl-ping-slave-period",server.repl_ping_slave_period);
    config_get_numerical_field("repl-timeout",server.repl_timeout);
    config_get_numerical_field("repl-backlog-size",server.repl_backlog_size);
    config_get_numerical_field("repl-backlog-ttl",server.repl_backlog_time_limit);
    config_get_numerical_field("maxclients",server.maxclients);
    config_get_numerical_field("watchdog-period",server.watchdog_period);
    config_get_numerical_field("slave-priority",server.slave_priority);
    config_get_numerical_field("hz",server.hz);
    config_get_numerical_field("cluster-node-timeout",server.cluster_node_timeout);

    /* Bool (yes/no) values */
    config_get_bool_field("no-appendfsync-on-rewrite",
            server.aof_no_fsync_on_rewrite);
    config_get_bool_field("slave-serve-stale-data",
            server.repl_serve_stale_data);
    config_get_bool_field("slave-read-only",
            server.repl_slave_ro);
    config_get_bool_field("stop-writes-on-bgsave-error",
            server.stop_writes_on_bgsave_err);
    config_get_bool_field("daemonize", server.daemonize);
    config_get_bool_field("rdbcompression", server.rdb_compression);
    config_get_bool_field("rdbchecksum", server.rdb_checksum);
    config_get_bool_field("activerehashing", server.activerehashing);
    config_get_bool_field("repl-disable-tcp-nodelay",
            server.repl_disable_tcp_nodelay);
    config_get_bool_field("aof-rewrite-incremental-fsync",
            server.aof_rewrite_incremental_fsync);

    /* Everything we can't handle with macros follows. */

    if (stringmatch(pattern,"appendonly",0)) {
        addReplyBulkCString(c,"appendonly");
        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
        matches++;
    }
    if (stringmatch(pattern,"dir",0)) {
        char buf[1024];

        if (getcwd(buf,sizeof(buf)) == NULL)
            buf[0] = '\0';

        addReplyBulkCString(c,"dir");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"maxmemory-policy",0)) {
        char *s;

        switch(server.maxmemory_policy) {
        case REDIS_MAXMEMORY_VOLATILE_LRU: s = "volatile-lru"; break;
        case REDIS_MAXMEMORY_VOLATILE_TTL: s = "volatile-ttl"; break;
        case REDIS_MAXMEMORY_VOLATILE_RANDOM: s = "volatile-random"; break;
        case REDIS_MAXMEMORY_ALLKEYS_LRU: s = "allkeys-lru"; break;
        case REDIS_MAXMEMORY_ALLKEYS_RANDOM: s = "allkeys-random"; break;
        case REDIS_MAXMEMORY_NO_EVICTION: s = "noeviction"; break;
        default: s = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"maxmemory-policy");
        addReplyBulkCString(c,s);
        matches++;
    }
    if (stringmatch(pattern,"appendfsync",0)) {
        char *policy;

        switch(server.aof_fsync) {
        case AOF_FSYNC_NO: policy = "no"; break;
        case AOF_FSYNC_EVERYSEC: policy = "everysec"; break;
        case AOF_FSYNC_ALWAYS: policy = "always"; break;
        default: policy = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"appendfsync");
        addReplyBulkCString(c,policy);
        matches++;
    }
    if (stringmatch(pattern,"save",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < server.saveparamslen; j++) {
            buf = sdscatprintf(buf,"%ld %d",
                    server.saveparams[j].seconds,
                    server.saveparams[j].changes);
            if (j != server.saveparamslen-1)
                buf = sdscatlen(buf," ",1);
        }
        addReplyBulkCString(c,"save");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"loglevel",0)) {
        char *s;

        switch(server.verbosity) {
        case REDIS_WARNING: s = "warning"; break;
        case REDIS_VERBOSE: s = "verbose"; break;
        case REDIS_NOTICE: s = "notice"; break;
        case REDIS_DEBUG: s = "debug"; break;
        default: s = "unknown"; break; /* too harmless to panic */
        }
        addReplyBulkCString(c,"loglevel");
        addReplyBulkCString(c,s);
        matches++;
    }
    if (stringmatch(pattern,"client-output-buffer-limit",0)) {
        sds buf = sdsempty();
        int j;

        for (j = 0; j < REDIS_CLIENT_LIMIT_NUM_CLASSES; j++) {
            buf = sdscatprintf(buf,"%s %llu %llu %ld",
                    getClientLimitClassName(j),
                    server.client_obuf_limits[j].hard_limit_bytes,
                    server.client_obuf_limits[j].soft_limit_bytes,
                    (long) server.client_obuf_limits[j].soft_limit_seconds);
            if (j != REDIS_CLIENT_LIMIT_NUM_CLASSES-1)
                buf = sdscatlen(buf," ",1);
        }
        addReplyBulkCString(c,"client-output-buffer-limit");
        addReplyBulkCString(c,buf);
        sdsfree(buf);
        matches++;
    }
    if (stringmatch(pattern,"unixsocketperm",0)) {
        char buf[32];
        snprintf(buf,sizeof(buf),"%o",server.unixsocketperm);
        addReplyBulkCString(c,"unixsocketperm");
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"slaveof",0)) {
        char buf[256];

        addReplyBulkCString(c,"slaveof");
        if (server.masterhost)
            snprintf(buf,sizeof(buf),"%s %d",
                server.masterhost, server.masterport);
        else
            buf[0] = '\0';
        addReplyBulkCString(c,buf);
        matches++;
    }
    if (stringmatch(pattern,"notify-keyspace-events",0)) {
        robj *flagsobj = createObject(REDIS_STRING,
            keyspaceEventsFlagsToString(server.notify_keyspace_events));

        addReplyBulkCString(c,"notify-keyspace-events");
        addReplyBulk(c,flagsobj);
        decrRefCount(flagsobj);
        matches++;
    }
    setDeferredMultiBulkLength(c,replylen,matches*2);
}