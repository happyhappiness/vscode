@@ -621,6 +621,19 @@ void loadServerConfig(char *filename, char *options) {
  * CONFIG SET implementation
  *----------------------------------------------------------------------------*/
 
+#define config_set_bool_field(_name,_var) \
+    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
+        int yn = yesnotoi(o->ptr); \
+        if (yn == -1) goto badfmt; \
+        _var = yn; \
+
+#define config_set_numerical_field(_name,_var,min,max) \
+    } else if (!strcasecmp(c->argv[2]->ptr,_name)) { \
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt; \
+        if (min != LLONG_MIN && ll < min) goto badfmt; \
+        if (max != LLONG_MAX && ll > max) goto badfmt; \
+        _var = ll; \
+
 void configSetCommand(redisClient *c) {
     robj *o;
     long long ll;
@@ -679,11 +692,6 @@ void configSetCommand(redisClient *c) {
                 }
             }
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"hz")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hz = ll;
-        if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
-        if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
     } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-policy")) {
         if (!strcasecmp(o->ptr,"volatile-lru")) {
             server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
@@ -700,18 +708,6 @@ void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-samples")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll <= 0) goto badfmt;
-        server.maxmemory_samples = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"timeout")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0 || ll > LONG_MAX) goto badfmt;
-        server.maxidletime = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"tcp-keepalive")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0 || ll > INT_MAX) goto badfmt;
-        server.tcpkeepalive = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"appendfsync")) {
         if (!strcasecmp(o->ptr,"no")) {
             server.aof_fsync = AOF_FSYNC_NO;
@@ -722,11 +718,6 @@ void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"no-appendfsync-on-rewrite")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.aof_no_fsync_on_rewrite = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
         int enable = yesnotoi(o->ptr);
 
@@ -740,22 +731,6 @@ void configSetCommand(redisClient *c) {
                 return;
             }
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-percentage")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.aof_rewrite_perc = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"auto-aof-rewrite-min-size")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.aof_rewrite_min_size = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"aof-rewrite-incremental-fsync")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.aof_rewrite_incremental_fsync = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"aof-load-truncated")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.aof_load_truncated = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
@@ -790,62 +765,14 @@ void configSetCommand(redisClient *c) {
             appendServerSaveParams(seconds, changes);
         }
         sdsfreesplitres(v,vlen);
-    } else if (!strcasecmp(c->argv[2]->ptr,"slave-serve-stale-data")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.repl_serve_stale_data = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"slave-read-only")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.repl_slave_ro = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"activerehashing")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.activerehashing = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"dir")) {
         if (chdir((char*)o->ptr) == -1) {
             addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
             return;
         }
-    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-entries")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hash_max_ziplist_entries = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"hash-max-ziplist-value")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hash_max_ziplist_value = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"list-max-ziplist-size")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.list_max_ziplist_size = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"list-compress-depth")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.list_compress_depth = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"set-max-intset-entries")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.set_max_intset_entries = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-entries")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.zset_max_ziplist_entries = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"zset-max-ziplist-value")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.zset_max_ziplist_value = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"hll-sparse-max-bytes")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.hll_sparse_max_bytes = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"lua-time-limit")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.lua_time_limit = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-log-slower-than")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR) goto badfmt;
-        server.slowlog_log_slower_than = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"slowlog-max-len")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         server.slowlog_max_len = (unsigned)ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"latency-monitor-threshold")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.latency_monitor_threshold = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"loglevel")) {
         if (!strcasecmp(o->ptr,"warning")) {
             server.verbosity = REDIS_WARNING;
@@ -903,85 +830,110 @@ void configSetCommand(redisClient *c) {
             server.client_obuf_limits[class].soft_limit_seconds = soft_seconds;
         }
         sdsfreesplitres(v,vlen);
-    } else if (!strcasecmp(c->argv[2]->ptr,"stop-writes-on-bgsave-error")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.stop_writes_on_bgsave_err = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-ping-slave-period")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
-        server.repl_ping_slave_period = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-timeout")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0) goto badfmt;
-        server.repl_timeout = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-size")) {
         ll = memtoll(o->ptr,&err);
         if (err || ll < 0) goto badfmt;
         resizeReplicationBacklog(ll);
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-ttl")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.repl_backlog_time_limit = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"watchdog-period")) {
         if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
         if (ll)
             enableWatchdog(ll);
         else
             disableWatchdog();
-    } else if (!strcasecmp(c->argv[2]->ptr,"rdbcompression")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.rdb_compression = yn;
     } else if (!strcasecmp(c->argv[2]->ptr,"notify-keyspace-events")) {
         int flags = keyspaceEventsStringToFlags(o->ptr);
 
         if (flags == -1) goto badfmt;
         server.notify_keyspace_events = flags;
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-disable-tcp-nodelay")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.repl_disable_tcp_nodelay = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-diskless-sync")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.repl_diskless_sync = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-diskless-sync-delay")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.repl_diskless_sync_delay = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"slave-priority")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.slave_priority = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"min-slaves-to-write")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.repl_min_slaves_to_write = ll;
+
+    /* Boolean fields.
+     * config_set_bool_field(name,var). */
+    config_set_bool_field(
+      "rdbcompression", server.rdb_compression) {
+    } config_set_bool_field(
+      "repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay) {
+    } config_set_bool_field(
+      "repl-diskless-sync",server.repl_diskless_sync) {
+    } config_set_bool_field(
+      "cluster-require-full-coverage",server.cluster_require_full_coverage) {
+    } config_set_bool_field(
+      "aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync) {
+    } config_set_bool_field(
+      "aof-load-truncated",server.aof_load_truncated) {
+    } config_set_bool_field(
+      "slave-serve-stale-data",server.repl_serve_stale_data) {
+    } config_set_bool_field(
+      "slave-read-only",server.repl_slave_ro) {
+    } config_set_bool_field(
+      "activerehashing",server.activerehashing) {
+    } config_set_bool_field(
+      "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
+    } config_set_bool_field(
+      "tcp-keepalive",server.tcpkeepalive) {
+
+    /* Numerical fields.
+     * config_set_numerical_field(name,var,min,max) */
+    } config_set_numerical_field(
+      "maxmemory-samples",server.maxmemory_samples,1,LLONG_MAX) {
+    } config_set_numerical_field(
+      "timeout",server.maxidletime,0,LONG_MAX) {
+    } config_set_numerical_field(
+      "auto-aof-rewrite-percentage",server.aof_rewrite_perc,0,LLONG_MAX){
+    } config_set_numerical_field(
+      "auto-aof-rewrite-min-size",server.aof_rewrite_min_size,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "hash-max-ziplist-entries",server.hash_max_ziplist_entries,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "hash-max-ziplist-value",server.hash_max_ziplist_value,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "list-max-ziplist-size",server.list_max_ziplist_size,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "list-compress-depth",server.list_compress_depth,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "set-max-intset-entries",server.set_max_intset_entries,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "zset-max-ziplist-entries",server.zset_max_ziplist_entries,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "zset-max-ziplist-value",server.zset_max_ziplist_value,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "hll-sparse-max-bytes",server.hll_sparse_max_bytes,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "lua-time-limit",server.lua_time_limit,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "slowlog-log-slower-than",server.slowlog_log_slower_than,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "latency-monitor-threshold",server.latency_monitor_threshold,0,LLONG_MAX){
+    } config_set_numerical_field(
+      "repl-ping-slave-period",server.repl_ping_slave_period,1,LLONG_MAX) {
+    } config_set_numerical_field(
+      "repl-timeout",server.repl_timeout,1,LLONG_MAX) {
+    } config_set_numerical_field(
+      "repl-backlog-ttl",server.repl_backlog_time_limit,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "repl-diskless-sync-delay",server.repl_diskless_sync_delay,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "slave-priority",server.slave_priority,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "min-slaves-to-write",server.repl_min_slaves_to_write,0,LLONG_MAX) {
         refreshGoodSlavesCount();
-    } else if (!strcasecmp(c->argv[2]->ptr,"min-slaves-max-lag")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.repl_min_slaves_max_lag = ll;
+    } config_set_numerical_field(
+      "min-slaves-max-lag",server.repl_min_slaves_max_lag,0,LLONG_MAX) {
         refreshGoodSlavesCount();
-    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-require-full-coverage")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.cluster_require_full_coverage = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-node-timeout")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll <= 0) goto badfmt;
-        server.cluster_node_timeout = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-migration-barrier")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.cluster_migration_barrier = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"cluster-slave-validity-factor")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.cluster_slave_validity_factor = ll;
+    } config_set_numerical_field(
+      "cluster-node-timeout",server.cluster_node_timeout,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "cluster-migration-barrier",server.cluster_migration_barrier,0,LLONG_MAX){
+    } config_set_numerical_field(
+      "cluster-slave-validity-factor",server.cluster_slave_validity_factor,0,LLONG_MAX) {
+    } config_set_numerical_field(
+      "hz",server.hz,0,LLONG_MAX) {
+        /* Hz is more an hint from the user, so we accept values out of range
+         * but cap them to reasonable values. */
+        if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
+        if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
+    }
+
+    /* Everyhing else is an error... */
     } else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
@@ -1086,7 +1038,6 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("maxmemory",server.maxmemory);
     config_get_numerical_field("maxmemory-samples",server.maxmemory_samples);
     config_get_numerical_field("timeout",server.maxidletime);
-    config_get_numerical_field("tcp-keepalive",server.tcpkeepalive);
     config_get_numerical_field("auto-aof-rewrite-percentage",
             server.aof_rewrite_perc);
     config_get_numerical_field("auto-aof-rewrite-min-size",
@@ -1133,6 +1084,7 @@ void configGetCommand(redisClient *c) {
     config_get_numerical_field("repl-diskless-sync-delay",server.repl_diskless_sync_delay);
 
     /* Bool (yes/no) values */
+    config_get_bool_field("tcp-keepalive",server.tcpkeepalive);
     config_get_bool_field("cluster-require-full-coverage",
             server.cluster_require_full_coverage);
     config_get_bool_field("no-appendfsync-on-rewrite",