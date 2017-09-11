@@ -475,6 +475,10 @@ void loadServerConfigFromString(char *config) {
             if ((server.aof_load_truncated = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"aof-use-rdb-preamble") && argc == 2) {
+            if ((server.aof_use_rdb_preamble = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
             if (strlen(argv[1]) > CONFIG_AUTHPASS_MAX_LEN) {
                 err = "Password is longer than CONFIG_AUTHPASS_MAX_LEN";
@@ -954,6 +958,8 @@ void configSetCommand(client *c) {
     } config_set_bool_field(
       "aof-load-truncated",server.aof_load_truncated) {
     } config_set_bool_field(
+      "aof-use-rdb-preamble",server.aof_use_rdb_preamble) {
+    } config_set_bool_field(
       "slave-serve-stale-data",server.repl_serve_stale_data) {
     } config_set_bool_field(
       "slave-read-only",server.repl_slave_ro) {
@@ -1227,6 +1233,8 @@ void configGetCommand(client *c) {
             server.aof_rewrite_incremental_fsync);
     config_get_bool_field("aof-load-truncated",
             server.aof_load_truncated);
+    config_get_bool_field("aof-use-rdb-preamble",
+            server.aof_use_rdb_preamble);
     config_get_bool_field("lazyfree-lazy-eviction",
             server.lazyfree_lazy_eviction);
     config_get_bool_field("lazyfree-lazy-expire",
@@ -1947,6 +1955,7 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"hz",server.hz,CONFIG_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,CONFIG_DEFAULT_AOF_LOAD_TRUNCATED);
+    rewriteConfigYesNoOption(state,"aof-use-rdb-preamble",server.aof_use_rdb_preamble,CONFIG_DEFAULT_AOF_USE_RDB_PREAMBLE);
     rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,SUPERVISED_NONE);
     rewriteConfigYesNoOption(state,"lazyfree-lazy-eviction",server.lazyfree_lazy_eviction,CONFIG_DEFAULT_LAZYFREE_LAZY_EVICTION);
     rewriteConfigYesNoOption(state,"lazyfree-lazy-expire",server.lazyfree_lazy_expire,CONFIG_DEFAULT_LAZYFREE_LAZY_EXPIRE);