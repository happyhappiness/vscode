    rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
    rewriteConfigStringOption(state,"pidfile",server.pidfile,CONFIG_DEFAULT_PID_FILE);
    rewriteConfigNumericalOption(state,"port",server.port,CONFIG_DEFAULT_SERVER_PORT);
    rewriteConfigNumericalOption(state,"cluster-announce-port",server.cluster_announce_port,CONFIG_DEFAULT_CLUSTER_ANNOUNCE_PORT);
    rewriteConfigNumericalOption(state,"cluster-announce-bus-port",server.cluster_announce_bus_port,CONFIG_DEFAULT_CLUSTER_ANNOUNCE_BUS_PORT);
    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,CONFIG_DEFAULT_TCP_BACKLOG);
    rewriteConfigBindOption(state);
    rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
