@@ -423,6 +423,10 @@ void loadServerConfigFromString(char *config) {
             if ((server.repl_slave_lazy_flush = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
+        } else if (!strcasecmp(argv[0],"activedefrag") && argc == 2) {
+            if ((server.active_defrag_enabled = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"daemonize") && argc == 2) {
             if ((server.daemonize = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
@@ -499,6 +503,36 @@ void loadServerConfigFromString(char *config) {
             }
             zfree(server.rdb_filename);
             server.rdb_filename = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"active-defrag-threshold-lower") && argc == 2) {
+            server.active_defrag_threshold_lower = atoi(argv[1]);
+            if (server.active_defrag_threshold_lower < 0) {
+                err = "active-defrag-threshold-lower must be 0 or greater";
+                goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"active-defrag-threshold-upper") && argc == 2) {
+            server.active_defrag_threshold_upper = atoi(argv[1]);
+            if (server.active_defrag_threshold_upper < 0) {
+                err = "active-defrag-threshold-upper must be 0 or greater";
+                goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"active-defrag-ignore-bytes") && argc == 2) {
+            server.active_defrag_ignore_bytes = memtoll(argv[1], NULL);
+            if (server.active_defrag_ignore_bytes <= 0) {
+                err = "active-defrag-ignore-bytes must above 0";
+                goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"active-defrag-cycle-min") && argc == 2) {
+            server.active_defrag_cycle_min = atoi(argv[1]);
+            if (server.active_defrag_cycle_min < 1 || server.active_defrag_cycle_min > 99) {
+                err = "active-defrag-cycle-min must be between 1 and 99";
+                goto loaderr;
+            }
+        } else if (!strcasecmp(argv[0],"active-defrag-cycle-max") && argc == 2) {
+            server.active_defrag_cycle_max = atoi(argv[1]);
+            if (server.active_defrag_cycle_max < 1 || server.active_defrag_cycle_max > 99) {
+                err = "active-defrag-cycle-max must be between 1 and 99";
+                goto loaderr;
+            }
         } else if (!strcasecmp(argv[0],"hash-max-ziplist-entries") && argc == 2) {
             server.hash_max_ziplist_entries = memtoll(argv[1], NULL);
         } else if (!strcasecmp(argv[0],"hash-max-ziplist-value") && argc == 2) {
@@ -972,6 +1006,8 @@ void configSetCommand(client *c) {
     } config_set_bool_field(
       "activerehashing",server.activerehashing) {
     } config_set_bool_field(
+      "activedefrag",server.active_defrag_enabled) {
+    } config_set_bool_field(
       "protected-mode",server.protected_mode) {
     } config_set_bool_field(
       "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
@@ -999,6 +1035,16 @@ void configSetCommand(client *c) {
     } config_set_numerical_field(
       "timeout",server.maxidletime,0,LONG_MAX) {
     } config_set_numerical_field(
+      "active-defrag-threshold-lower",server.active_defrag_threshold_lower,0,1000) {
+    } config_set_numerical_field(
+      "active-defrag-threshold-upper",server.active_defrag_threshold_upper,0,1000) {
+    } config_set_memory_field(
+      "active-defrag-ignore-bytes",server.active_defrag_ignore_bytes) {
+    } config_set_numerical_field(
+      "active-defrag-cycle-min",server.active_defrag_cycle_min,1,99) {
+    } config_set_numerical_field(
+      "active-defrag-cycle-max",server.active_defrag_cycle_max,1,99) {
+    } config_set_numerical_field(
       "auto-aof-rewrite-percentage",server.aof_rewrite_perc,0,LLONG_MAX){
     } config_set_numerical_field(
       "auto-aof-rewrite-min-size",server.aof_rewrite_min_size,0,LLONG_MAX) {
@@ -1166,6 +1212,11 @@ void configGetCommand(client *c) {
     config_get_numerical_field("maxmemory",server.maxmemory);
     config_get_numerical_field("maxmemory-samples",server.maxmemory_samples);
     config_get_numerical_field("timeout",server.maxidletime);
+    config_get_numerical_field("active-defrag-threshold-lower",server.active_defrag_threshold_lower);
+    config_get_numerical_field("active-defrag-threshold-upper",server.active_defrag_threshold_upper);
+    config_get_numerical_field("active-defrag-ignore-bytes",server.active_defrag_ignore_bytes);
+    config_get_numerical_field("active-defrag-cycle-min",server.active_defrag_cycle_min);
+    config_get_numerical_field("active-defrag-cycle-max",server.active_defrag_cycle_max);
     config_get_numerical_field("auto-aof-rewrite-percentage",
             server.aof_rewrite_perc);
     config_get_numerical_field("auto-aof-rewrite-min-size",
@@ -1230,6 +1281,7 @@ void configGetCommand(client *c) {
     config_get_bool_field("rdbcompression", server.rdb_compression);
     config_get_bool_field("rdbchecksum", server.rdb_checksum);
     config_get_bool_field("activerehashing", server.activerehashing);
+    config_get_bool_field("activedefrag", server.active_defrag_enabled);
     config_get_bool_field("protected-mode", server.protected_mode);
     config_get_bool_field("repl-disable-tcp-nodelay",
             server.repl_disable_tcp_nodelay);
@@ -1930,6 +1982,11 @@ int rewriteConfig(char *path) {
     rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,CONFIG_DEFAULT_MAXMEMORY);
     rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum,CONFIG_DEFAULT_MAXMEMORY_POLICY);
     rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,CONFIG_DEFAULT_MAXMEMORY_SAMPLES);
+    rewriteConfigNumericalOption(state,"active-defrag-threshold-lower",server.active_defrag_threshold_lower,CONFIG_DEFAULT_DEFRAG_THRESHOLD_LOWER);
+    rewriteConfigNumericalOption(state,"active-defrag-threshold-upper",server.active_defrag_threshold_upper,CONFIG_DEFAULT_DEFRAG_THRESHOLD_UPPER);
+    rewriteConfigBytesOption(state,"active-defrag-ignore-bytes",server.active_defrag_ignore_bytes,CONFIG_DEFAULT_DEFRAG_IGNORE_BYTES);
+    rewriteConfigNumericalOption(state,"active-defrag-cycle-min",server.active_defrag_cycle_min,CONFIG_DEFAULT_DEFRAG_CYCLE_MIN);
+    rewriteConfigNumericalOption(state,"active-defrag-cycle-max",server.active_defrag_cycle_max,CONFIG_DEFAULT_DEFRAG_CYCLE_MAX);
     rewriteConfigYesNoOption(state,"appendonly",server.aof_state != AOF_OFF,0);
     rewriteConfigStringOption(state,"appendfilename",server.aof_filename,CONFIG_DEFAULT_AOF_FILENAME);
     rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,aof_fsync_enum,CONFIG_DEFAULT_AOF_FSYNC);
@@ -1956,6 +2013,7 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,OBJ_ZSET_MAX_ZIPLIST_VALUE);
     rewriteConfigNumericalOption(state,"hll-sparse-max-bytes",server.hll_sparse_max_bytes,CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES);
     rewriteConfigYesNoOption(state,"activerehashing",server.activerehashing,CONFIG_DEFAULT_ACTIVE_REHASHING);
+    rewriteConfigYesNoOption(state,"activedefrag",server.active_defrag_enabled,CONFIG_DEFAULT_ACTIVE_DEFRAG);
     rewriteConfigYesNoOption(state,"protected-mode",server.protected_mode,CONFIG_DEFAULT_PROTECTED_MODE);
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,CONFIG_DEFAULT_HZ);