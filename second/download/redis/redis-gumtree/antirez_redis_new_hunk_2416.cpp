    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
    rewriteConfigStringOption(state,"bindaddr",server.bindaddr,NULL);
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
    rewriteConfigNumericalOption(state,"repl-backlog-size",server.repl_backlog_size,REDIS_DEFAULT_REPL_BACKLOG_SIZE);
    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigBytesOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
    rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
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
    rewriteConfigAppendonlyOption(state);
    rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
        "eveysec", AOF_FSYNC_EVERYSEC,
        "always", AOF_FSYNC_ALWAYS,
        "no", AOF_FSYNC_NO,
        NULL, REDIS_DEFAULT_AOF_FSYNC);
    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
