    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
    rewriteConfigNotifykeyspaceeventsOption(state);
