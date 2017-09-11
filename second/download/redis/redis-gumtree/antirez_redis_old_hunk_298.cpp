    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,CONFIG_DEFAULT_RDB_FILENAME);
    rewriteConfigDirOption(state);
    rewriteConfigSlaveofOption(state);
    rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
    rewriteConfigStringOption(state,"cluster-announce-ip",server.cluster_announce_ip,NULL);
    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
