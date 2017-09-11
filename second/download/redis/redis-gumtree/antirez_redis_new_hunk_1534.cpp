    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,REDIS_DEFAULT_TCP_KEEPALIVE);
    rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,REDIS_DEFAULT_VERBOSITY);
    rewriteConfigStringOption(state,"logfile",server.logfile,REDIS_DEFAULT_LOGFILE);
    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,REDIS_DEFAULT_SYSLOG_ENABLED);
    rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,REDIS_DEFAULT_SYSLOG_IDENT);
