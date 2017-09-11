
    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,CONFIG_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,REDIS_TCP_BACKLOG);
    rewriteConfigBindOption(state);
    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,CONFIG_DEFAULT_UNIX_SOCKET_PERM);
    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,CONFIG_DEFAULT_TCP_KEEPALIVE);
    rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,CONFIG_DEFAULT_VERBOSITY);
    rewriteConfigStringOption(state,"logfile",server.logfile,CONFIG_DEFAULT_LOGFILE);
