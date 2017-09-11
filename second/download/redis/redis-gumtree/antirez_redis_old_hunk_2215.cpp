    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
    rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
    rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
    rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
