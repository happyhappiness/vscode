       "cluster-require-full-coverage",server.cluster_require_full_coverage) {
     } config_set_bool_field(
       "aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync) {
     } config_set_bool_field(
       "aof-load-truncated",server.aof_load_truncated) {
     } config_set_bool_field(
+      "aof-use-rdb-preamble",server.aof_use_rdb_preamble) {
+    } config_set_bool_field(
       "slave-serve-stale-data",server.repl_serve_stale_data) {
     } config_set_bool_field(
       "slave-read-only",server.repl_slave_ro) {
     } config_set_bool_field(
       "activerehashing",server.activerehashing) {
     } config_set_bool_field(
+      "activedefrag",server.active_defrag_enabled) {
+#ifndef HAVE_DEFRAG
+        if (server.active_defrag_enabled) {
+            server.active_defrag_enabled = 0;
+            addReplyError(c,
+                "Active defragmentation cannot be enabled: it requires a "
+                "Redis server compiled with a modified Jemalloc like the "
+                "one shipped by default with the Redis source distribution");
+            return;
+        }
+#endif
+    } config_set_bool_field(
       "protected-mode",server.protected_mode) {
     } config_set_bool_field(
       "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
     } config_set_bool_field(
+      "lazyfree-lazy-eviction",server.lazyfree_lazy_eviction) {
+    } config_set_bool_field(
+      "lazyfree-lazy-expire",server.lazyfree_lazy_expire) {
+    } config_set_bool_field(
+      "lazyfree-lazy-server-del",server.lazyfree_lazy_server_del) {
+    } config_set_bool_field(
+      "slave-lazy-flush",server.repl_slave_lazy_flush) {
+    } config_set_bool_field(
       "no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite) {
 
     /* Numerical fields.
      * config_set_numerical_field(name,var,min,max) */
     } config_set_numerical_field(
       "tcp-keepalive",server.tcpkeepalive,0,LLONG_MAX) {
     } config_set_numerical_field(
       "maxmemory-samples",server.maxmemory_samples,1,LLONG_MAX) {
     } config_set_numerical_field(
+      "lfu-log-factor",server.lfu_log_factor,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "lfu-decay-time",server.lfu_decay_time,0,LLONG_MAX) {
+    } config_set_numerical_field(
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
+      "auto-aof-rewrite-min-size",server.aof_rewrite_min_size,0,LLONG_MAX) {
+    } config_set_numerical_field(
       "hash-max-ziplist-entries",server.hash_max_ziplist_entries,0,LLONG_MAX) {
     } config_set_numerical_field(
       "hash-max-ziplist-value",server.hash_max_ziplist_value,0,LLONG_MAX) {
     } config_set_numerical_field(
       "list-max-ziplist-size",server.list_max_ziplist_size,INT_MIN,INT_MAX) {
     } config_set_numerical_field(
