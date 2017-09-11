@@ -422,6 +422,14 @@ void loadServerConfigFromString(char *config) {
             if (server.cluster_node_timeout <= 0) {
                 err = "cluster node timeout must be 1 or greater"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"cluster-migration-barrier")
+                   && argc == 2)
+        {
+            server.cluster_migration_barrier = atoi(argv[1]);
+            if (server.cluster_migration_barrier < 0) {
+                err = "cluster migration barrier must be positive";
+                goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"lua-time-limit") && argc == 2) {
             server.lua_time_limit = strtoll(argv[1],NULL,10);
         } else if (!strcasecmp(argv[0],"slowlog-log-slower-than") &&
@@ -875,6 +883,10 @@ void configSetCommand(redisClient *c) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
             ll <= 0) goto badfmt;
         server.cluster_node_timeout = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-migration-barrier")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.cluster_migration_barrier = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -975,6 +987,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("min-slaves-max-lag",server.repl_min_slaves_max_lag);
     config_get_numerical_field("hz",server.hz);
     config_get_numerical_field("cluster-node-timeout",server.cluster_node_timeout);
+    config_get_numerical_field("cluster-migration-barrier",server.cluster_migration_barrier);
 
     /* Bool (yes/no) values */
     config_get_bool_field("no-appendfsync-on-rewrite",
@@ -1742,6 +1755,7 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
     rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
     rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
+    rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
     rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
     rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
     rewriteConfigNotifykeyspaceeventsOption(state);