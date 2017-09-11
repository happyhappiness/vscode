@@ -434,7 +434,15 @@ void loadServerConfigFromString(char *config) {
         {
             server.cluster_migration_barrier = atoi(argv[1]);
             if (server.cluster_migration_barrier < 0) {
-                err = "cluster migration barrier must be positive";
+                err = "cluster migration barrier must zero or positive";
+                goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"cluster-slave-validity-factor")
+                   && argc == 2)
+        {
+            server.cluster_slave_validity_factor = atoi(argv[1]);
+            if (server.cluster_slave_validity_factor < 0) {
+                err = "cluster slave validity factor must be zero or positive";
                 goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"lua-time-limit") && argc == 2) {
@@ -897,6 +905,10 @@ void configSetCommand(redisClient *c) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
             ll < 0) goto badfmt;
         server.cluster_migration_barrier = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-slave-validity-factor")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.cluster_slave_validity_factor = ll;
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -1001,6 +1013,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("hz",server.hz);
     config_get_numerical_field("cluster-node-timeout",server.cluster_node_timeout);
     config_get_numerical_field("cluster-migration-barrier",server.cluster_migration_barrier);
+    config_get_numerical_field("cluster-slave-validity-factor",server.cluster_slave_validity_factor);
 
     /* Bool (yes/no) values */
     config_get_bool_field("no-appendfsync-on-rewrite",
@@ -1770,6 +1783,7 @@ int rewriteConfig(char *path) {
     rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
     rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
     rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
+    rewriteConfigNumericalOption(state,"cluster-slave-validity-factor",server.cluster_slave_validity_factor,REDIS_CLUSTER_DEFAULT_SLAVE_VALIDITY);
     rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
     rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
     rewriteConfigNotifykeyspaceeventsOption(state);