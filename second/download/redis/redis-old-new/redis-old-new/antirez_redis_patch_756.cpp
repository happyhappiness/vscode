@@ -429,6 +429,13 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"cluster-config-file") && argc == 2) {
             zfree(server.cluster_configfile);
             server.cluster_configfile = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"cluster-require-full-coverage") &&
+                    argc == 2)
+        {
+            if ((server.cluster_require_full_coverage = yesnotoi(argv[1])) == -1)
+            {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"cluster-node-timeout") && argc == 2) {
             server.cluster_node_timeout = strtoll(argv[1],NULL,10);
             if (server.cluster_node_timeout <= 0) {
@@ -918,6 +925,11 @@ void configSetCommand(redisClient *c) {
             ll < 0) goto badfmt;
         server.repl_min_slaves_max_lag = ll;
         refreshGoodSlavesCount();
+    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-require-full-coverage")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.cluster_require_full_coverage = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"cluster-node-timeout")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
             ll <= 0) goto badfmt;
@@ -1039,6 +1051,8 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("cluster-slave-validity-factor",server.cluster_slave_validity_factor);
 
     /* Bool (yes/no) values */
+    config_get_bool_field("cluster-require-full-coverage",
+            server.cluster_require_full_coverage);
     config_get_bool_field("no-appendfsync-on-rewrite",
             server.aof_no_fsync_on_rewrite);
     config_get_bool_field("slave-serve-stale-data",
@@ -1806,6 +1820,7 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
     rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
     rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,REDIS_DEFAULT_CLUSTER_CONFIG_FILE);
+    rewriteConfigYesNoOption(state,"cluster-require-full-coverage",server.cluster_require_full_coverage,REDIS_CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE);
     rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
     rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
     rewriteConfigNumericalOption(state,"cluster-slave-validity-factor",server.cluster_slave_validity_factor,REDIS_CLUSTER_DEFAULT_SLAVE_VALIDITY);