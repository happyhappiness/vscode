    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,CONFIG_DEFAULT_RDB_FILENAME);
    rewriteConfigDirOption(state);
    rewriteConfigSlaveofOption(state);
    rewriteConfigStringOption(state,"slave-announce-ip",server.slave_announce_ip,CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP);
    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigStringOption(state,"cluster-announce-ip",server.cluster_announce_ip,NULL);
    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
