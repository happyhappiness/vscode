    if ((state = rewriteConfigReadOldFile(path)) == NULL) return -1;

    /* Step 2: rewrite every single option, replacing or appending it inside
     * the rewrite state. */

    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,REDIS_TCP_BACKLOG);
    rewriteConfigBindOption(state);
    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,REDIS_DEFAULT_TCP_KEEPALIVE);
    rewriteConfigEnumOption(state,"loglevel",server.verbosity,
        "debug", REDIS_DEBUG,
        "verbose", REDIS_VERBOSE,
        "notice", REDIS_NOTICE,
        "warning", REDIS_WARNING,
        NULL, REDIS_DEFAULT_VERBOSITY);
    rewriteConfigStringOption(state,"logfile",server.logfile,REDIS_DEFAULT_LOGFILE);
    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,REDIS_DEFAULT_SYSLOG_ENABLED);
    rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,REDIS_DEFAULT_SYSLOG_IDENT);
    rewriteConfigSyslogfacilityOption(state);
    rewriteConfigSaveOption(state);
    rewriteConfigNumericalOption(state,"databases",server.dbnum,REDIS_DEFAULT_DBNUM);
    rewriteConfigYesNoOption(state,"stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err,REDIS_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR);
    rewriteConfigYesNoOption(state,"rdbcompression",server.rdb_compression,REDIS_DEFAULT_RDB_COMPRESSION);
    rewriteConfigYesNoOption(state,"rdbchecksum",server.rdb_checksum,REDIS_DEFAULT_RDB_CHECKSUM);
    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,REDIS_DEFAULT_RDB_FILENAME);
    rewriteConfigDirOption(state);
    rewriteConfigSlaveofOption(state);
    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,REDIS_DEFAULT_SLAVE_SERVE_STALE_DATA);
    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,REDIS_DEFAULT_SLAVE_READ_ONLY);
    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,REDIS_REPL_PING_SLAVE_PERIOD);
    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,REDIS_REPL_TIMEOUT);
    rewriteConfigBytesOption(state,"repl-backlog-size",server.repl_backlog_size,REDIS_DEFAULT_REPL_BACKLOG_SIZE);
    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
    rewriteConfigYesNoOption(state,"repl-diskless-sync",server.repl_diskless_sync,REDIS_DEFAULT_REPL_DISKLESS_SYNC);
    rewriteConfigNumericalOption(state,"repl-diskless-sync-delay",server.repl_diskless_sync_delay,REDIS_DEFAULT_REPL_DISKLESS_SYNC_DELAY);
    rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
    rewriteConfigNumericalOption(state,"min-slaves-to-write",server.repl_min_slaves_to_write,REDIS_DEFAULT_MIN_SLAVES_TO_WRITE);
    rewriteConfigNumericalOption(state,"min-slaves-max-lag",server.repl_min_slaves_max_lag,REDIS_DEFAULT_MIN_SLAVES_MAX_LAG);
    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
    rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,
        "volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU,
        "allkeys-lru", REDIS_MAXMEMORY_ALLKEYS_LRU,
        "volatile-random", REDIS_MAXMEMORY_VOLATILE_RANDOM,
        "allkeys-random", REDIS_MAXMEMORY_ALLKEYS_RANDOM,
        "volatile-ttl", REDIS_MAXMEMORY_VOLATILE_TTL,
        "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != REDIS_AOF_OFF,0);
    rewriteConfigStringOption(state,"appendfilename",server.aof_filename,REDIS_DEFAULT_AOF_FILENAME);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
        "everysec", AOF_FSYNC_EVERYSEC,
        "always", AOF_FSYNC_ALWAYS,
        "no", AOF_FSYNC_NO,
        NULL, REDIS_DEFAULT_AOF_FSYNC);
    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
    rewriteConfigYesNoOption(state,"cluster-require-full-coverage",server.cluster_require_full_coverage,REDIS_CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE);
    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
    rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
    rewriteConfigNumericalOption(state,"cluster-slave-validity-factor",server.cluster_slave_validity_factor,REDIS_CLUSTER_DEFAULT_SLAVE_VALIDITY);
    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
    rewriteConfigNumericalOption(state,"latency-monitor-threshold",server.latency_monitor_threshold,REDIS_DEFAULT_LATENCY_MONITOR_THRESHOLD);
    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
    rewriteConfigNotifykeyspaceeventsOption(state);
    rewriteConfigNumericalOption(state,"hash-max-ziplist-entries",server.hash_max_ziplist_entries,REDIS_HASH_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,REDIS_HASH_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"list-max-ziplist-entries",server.list_max_ziplist_entries,REDIS_LIST_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"list-max-ziplist-value",server.list_max_ziplist_value,REDIS_LIST_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,REDIS_SET_MAX_INTSET_ENTRIES);
    rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,REDIS_ZSET_MAX_ZIPLIST_ENTRIES);
    rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,REDIS_ZSET_MAX_ZIPLIST_VALUE);
    rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,REDIS_DEFAULT_HLL_SPARSE_MAX_BYTES);
    rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,REDIS_DEFAULT_ACTIVE_REHASHING);
    rewriteConfigClientoutputbufferlimitOption(state);
    rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
    rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,REDIS_DEFAULT_AOF_LOAD_TRUNCATED);
    if (server.sentinel_mode) rewriteConfigSentinelOption(state);

    /* Step 3: remove all the orphaned lines in the old file, that is, lines
     * that were used by a config option and are no longer used, like in case
     * of multiple "save" options or duplicated options. */
    rewriteConfigRemoveOrphaned(state);
