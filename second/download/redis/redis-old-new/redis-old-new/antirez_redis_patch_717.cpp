@@ -270,6 +270,16 @@ void loadServerConfigFromString(char *config) {
             if ((server.repl_disable_tcp_nodelay = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"repl-diskless-sync") && argc==2) {
+            if ((server.repl_diskless_sync = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"repl-diskless-sync-delay") && argc==2) {
+            server.repl_diskless_sync_delay = atoi(argv[1]);
+            if (server.repl_diskless_sync_delay < 0) {
+                err = "repl-diskless-sync-delay can't be negative";
+                goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"repl-backlog-size") && argc == 2) {
             long long size = memtoll(argv[1],NULL);
             if (size <= 0) {
@@ -284,7 +294,7 @@ void loadServerConfigFromString(char *config) {
                 goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"masterauth") && argc == 2) {
-        	server.masterauth = zstrdup(argv[1]);
+            server.masterauth = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"slave-serve-stale-data") && argc == 2) {
             if ((server.repl_serve_stale_data = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -911,6 +921,15 @@ void configSetCommand(redisClient *c) {
 
         if (yn == -1) goto badfmt;
         server.repl_disable_tcp_nodelay = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"repl-diskless-sync")) {
+        int yn = yesnotoi(o->ptr);
+
+        if (yn == -1) goto badfmt;
+        server.repl_diskless_sync = yn;
+    } else if (!strcasecmp(c->argv[2]->ptr,"repl-diskless-sync-delay")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.repl_diskless_sync_delay = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"slave-priority")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
             ll < 0) goto badfmt;
@@ -1049,6 +1068,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("cluster-node-timeout",server.cluster_node_timeout);
     config_get_numerical_field("cluster-migration-barrier",server.cluster_migration_barrier);
     config_get_numerical_field("cluster-slave-validity-factor",server.cluster_slave_validity_factor);
+    config_get_numerical_field("repl-diskless-sync-delay",server.repl_diskless_sync_delay);
 
     /* Bool (yes/no) values */
     config_get_bool_field("cluster-require-full-coverage",
@@ -1067,6 +1087,8 @@ void configGetCommand(redisClient *c) {
     config_get_bool_field("activerehashing", server.activerehashing);
     config_get_bool_field("repl-disable-tcp-nodelay",
             server.repl_disable_tcp_nodelay);
+    config_get_bool_field("repl-diskless-sync",
+            server.repl_diskless_sync);
     config_get_bool_field("aof-rewrite-incremental-fsync",
             server.aof_rewrite_incremental_fsync);
     config_get_bool_field("aof-load-truncated",
@@ -1792,6 +1814,8 @@ int rewriteConfig(char *path) {
     rewriteConfigBytesOption(state,"repl-backlog-size",server.repl_backlog_size,REDIS_DEFAULT_REPL_BACKLOG_SIZE);
     rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
     rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
+    rewriteConfigYesNoOption(state,"repl-diskless-sync",server.repl_diskless_sync,REDIS_DEFAULT_REPL_DISKLESS_SYNC);
+    rewriteConfigNumericalOption(state,"repl-diskless-sync-delay",server.repl_diskless_sync_delay,REDIS_DEFAULT_REPL_DISKLESS_SYNC_DELAY);
     rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
     rewriteConfigNumericalOption(state,"min-slaves-to-write",server.repl_min_slaves_to_write,REDIS_DEFAULT_MIN_SLAVES_TO_WRITE);
     rewriteConfigNumericalOption(state,"min-slaves-max-lag",server.repl_min_slaves_max_lag,REDIS_DEFAULT_MIN_SLAVES_MAX_LAG);