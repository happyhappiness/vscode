@@ -370,6 +370,22 @@ void loadServerConfigFromString(char *config) {
             if ((server.activerehashing = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"lazyfree-lazy-eviction") && argc == 2) {
+            if ((server.lazyfree_lazy_eviction = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"lazyfree-lazy-expire") && argc == 2) {
+            if ((server.lazyfree_lazy_expire = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"lazyfree-lazy-server-del") && argc == 2){
+            if ((server.lazyfree_lazy_server_del = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"slave-lazy-flush") && argc == 2) {
+            if ((server.repl_slave_lazy_flush = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"daemonize") && argc == 2) {
             if ((server.daemonize = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -875,6 +891,14 @@ void configSetCommand(client *c) {
       "activerehashing",server.activerehashing) {
     } config_set_bool_field(
       "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
+    } config_set_bool_field(
+      "lazyfree-lazy-eviction",server.lazyfree_lazy_eviction) {
+    } config_set_bool_field(
+      "lazyfree-lazy-expire",server.lazyfree_lazy_expire) {
+    } config_set_bool_field(
+      "lazyfree-lazy-server-del",server.lazyfree_lazy_server_del) {
+    } config_set_bool_field(
+      "slave-lazy-flush",server.repl_slave_lazy_flush) {
 
     /* Numerical fields.
      * config_set_numerical_field(name,var,min,max) */
@@ -1113,6 +1137,14 @@ void configGetCommand(client *c) {
             server.aof_rewrite_incremental_fsync);
     config_get_bool_field("aof-load-truncated",
             server.aof_load_truncated);
+    config_get_bool_field("lazyfree-lazy-eviction",
+            server.lazyfree_lazy_eviction);
+    config_get_bool_field("lazyfree-lazy-expire",
+            server.lazyfree_lazy_expire);
+    config_get_bool_field("lazyfree-lazy-server-del",
+            server.lazyfree_lazy_server_del);
+    config_get_bool_field("slave-lazy-flush",
+            server.repl_slave_lazy_flush);
 
     /* Enum values */
     config_get_enum_field("maxmemory-policy",
@@ -1820,6 +1852,10 @@ int rewriteConfig(char *path) {
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,CONFIG_DEFAULT_AOF_LOAD_TRUNCATED);
     rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,SUPERVISED_NONE);
+    rewriteConfigYesNoOption(state,"lazyfree-lazy-eviction",server.lazyfree_lazy_eviction,CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION);
+    rewriteConfigYesNoOption(state,"lazyfree-lazy-expire",server.lazyfree_lazy_expire,CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE);
+    rewriteConfigYesNoOption(state,"lazyfree-lazy-server-del",server.lazyfree_lazy_server_del,CONFIG_DEFAULT_LAZYFREE_LAZY_SERVER_DEL);
+    rewriteConfigYesNoOption(state,"slave-lazy-flush",server.repl_slave_lazy_flush,CONFIG_DEFAULT_SLAVE_LAZY_FLUSH);
 
     /* Rewrite Sentinel config if in Sentinel mode. */
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);