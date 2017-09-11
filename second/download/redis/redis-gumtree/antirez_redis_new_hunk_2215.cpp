    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
    rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
    rewriteConfigNumericalOption(state,"min-slaves-to-write",server.repl_min_slaves_to_write,REDIS_DEFAULT_MIN_SLAVES_TO_WRITE);
    rewriteConfigNumericalOption(state,"min-slaves-max-lag",server.repl_min_slaves_max_lag,REDIS_DEFAULT_MIN_SLAVES_MAX_LAG);
    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
