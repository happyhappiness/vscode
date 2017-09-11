@@ -196,6 +196,10 @@ void loadServerConfigFromString(char *config) {
             if (server.tcpkeepalive < 0) {
                 err = "Invalid tcp-keepalive value"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"protected-mode") && argc == 2) {
+            if ((server.protected_mode = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"port") && argc == 2) {
             server.port = atoi(argv[1]);
             if (server.port < 0 || server.port > 65535) {
@@ -890,6 +894,8 @@ void configSetCommand(client *c) {
     } config_set_bool_field(
       "activerehashing",server.activerehashing) {
     } config_set_bool_field(
+      "protected-mode",server.protected_mode) {
+    } config_set_bool_field(
       "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
     } config_set_bool_field(
       "lazyfree-lazy-eviction",server.lazyfree_lazy_eviction) {
@@ -1129,6 +1135,7 @@ void configGetCommand(client *c) {
     config_get_bool_field("rdbcompression", server.rdb_compression);
     config_get_bool_field("rdbchecksum", server.rdb_checksum);
     config_get_bool_field("activerehashing", server.activerehashing);
+    config_get_bool_field("protected-mode", server.protected_mode);
     config_get_bool_field("repl-disable-tcp-nodelay",
             server.repl_disable_tcp_nodelay);
     config_get_bool_field("repl-diskless-sync",
@@ -1847,6 +1854,7 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,OBJ_ZSET_MAX_ZIPLIST_VALUE);
     rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES);
     rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,CONFIG_DEFAULT_ACTIVE_REHASHING);
+    rewriteConfigYesNoOption(state,"protected-mode",server.protected_mode,CONFIG_DEFAULT_PROTECTED_MODE);
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,CONFIG_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);