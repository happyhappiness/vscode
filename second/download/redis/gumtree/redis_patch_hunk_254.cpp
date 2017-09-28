         "no", AOF_FSYNC_NO,
         NULL, REDIS_DEFAULT_AOF_FSYNC);
     rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
     rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
     rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
     rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
+    rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
+    rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
+    rewriteConfigYesNoOption(state,"cluster-require-full-coverage",server.cluster_require_full_coverage,REDIS_CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE);
+    rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
+    rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
+    rewriteConfigNumericalOption(state,"cluster-slave-validity-factor",server.cluster_slave_validity_factor,REDIS_CLUSTER_DEFAULT_SLAVE_VALIDITY);
     rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
     rewriteConfigNumericalOption(state,"latency-monitor-threshold",server.latency_monitor_threshold,REDIS_DEFAULT_LATENCY_MONITOR_THRESHOLD);
     rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
     rewriteConfigNotifykeyspaceeventsOption(state);
     rewriteConfigNumericalOption(state,"hash-max-ziplist-entries",server.hash_max_ziplist_entries,REDIS_HASH_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,REDIS_HASH_MAX_ZIPLIST_VALUE);
