    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
    rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
    rewriteConfigNumericalOption(state,"cluster-slave-validity-factor",server.cluster_slave_validity_factor,REDIS_CLUSTER_DEFAULT_SLAVE_VALIDITY);
