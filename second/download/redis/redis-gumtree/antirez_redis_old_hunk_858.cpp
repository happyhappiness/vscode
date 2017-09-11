    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,CONFIG_DEFAULT_SLAVE_READ_ONLY);
    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,REDIS_REPL_PING_SLAVE_PERIOD);
    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,REDIS_REPL_TIMEOUT);
    rewriteConfigBytesOption(state,"repl-backlog-size",server.repl_backlog_size,CONFIG_DEFAULT_REPL_BACKLOG_SIZE);
    rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY);
