    rewriteConfigDirOption(state);
    rewriteConfigSlaveofOption(state);
    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,CONFIG_DEFAULT_SLAVE_READ_ONLY);
    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD);
