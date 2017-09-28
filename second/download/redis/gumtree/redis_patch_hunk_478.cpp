 
             server.client_obuf_limits[class].hard_limit_bytes = hard;
             server.client_obuf_limits[class].soft_limit_bytes = soft;
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
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-size")) {
-        ll = memtoll(o->ptr,&err);
-        if (err || ll < 0) goto badfmt;
-        resizeReplicationBacklog(ll);
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-backlog-ttl")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        server.repl_backlog_time_limit = ll;
-    } else if (!strcasecmp(c->argv[2]->ptr,"watchdog-period")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
-        if (ll)
-            enableWatchdog(ll);
-        else
-            disableWatchdog();
-    } else if (!strcasecmp(c->argv[2]->ptr,"rdbcompression")) {
-        int yn = yesnotoi(o->ptr);
-
-        if (yn == -1) goto badfmt;
-        server.rdb_compression = yn;
-    } else if (!strcasecmp(c->argv[2]->ptr,"notify-keyspace-events")) {
+    } config_set_special_field("notify-keyspace-events") {
         int flags = keyspaceEventsStringToFlags(o->ptr);
 
         if (flags == -1) goto badfmt;
         server.notify_keyspace_events = flags;
-    } else if (!strcasecmp(c->argv[2]->ptr,"repl-disable-tcp-nodelay")) {
-        int yn = yesnotoi(o->ptr);
 
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
+    /* Boolean fields.
+     * config_set_bool_field(name,var). */
+    } config_set_bool_field(
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
+      "protected-mode",server.protected_mode) {
+    } config_set_bool_field(
+      "stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err) {
+    } config_set_bool_field(
+      "no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite) {
+
+    /* Numerical fields.
+     * config_set_numerical_field(name,var,min,max) */
+    } config_set_numerical_field(
+      "tcp-keepalive",server.tcpkeepalive,0,LLONG_MAX) {
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
+      "slowlog-max-len",ll,0,LLONG_MAX) {
+      /* Cast to unsigned. */
+        server.slowlog_max_len = (unsigned)ll;
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
+        if (server.hz < CONFIG_MIN_HZ) server.hz = CONFIG_MIN_HZ;
+        if (server.hz > CONFIG_MAX_HZ) server.hz = CONFIG_MAX_HZ;
+    } config_set_numerical_field(
+      "watchdog-period",ll,0,LLONG_MAX) {
+        if (ll)
+            enableWatchdog(ll);
+        else
+            disableWatchdog();
 
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
-    } else {
+    /* Memory fields.
+     * config_set_memory_field(name,var) */
+    } config_set_memory_field("maxmemory",server.maxmemory) {
+        if (server.maxmemory) {
+            if (server.maxmemory < zmalloc_used_memory()) {
+                serverLog(LL_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
+            }
+            freeMemoryIfNeeded();
+        }
+    } config_set_memory_field("repl-backlog-size",ll) {
+        resizeReplicationBacklog(ll);
+
+    /* Enumeration fields.
+     * config_set_enum_field(name,var,enum_var) */
+    } config_set_enum_field(
+      "loglevel",server.verbosity,loglevel_enum) {
+    } config_set_enum_field(
+      "maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum) {
+    } config_set_enum_field(
+      "appendfsync",server.aof_fsync,aof_fsync_enum) {
+
+    /* Everyhing else is an error... */
+    } config_set_else {
         addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
             (char*)c->argv[2]->ptr);
         return;
     }
+
+    /* On success we just return a generic OK for all the options. */
     addReply(c,shared.ok);
     return;
 
 badfmt: /* Bad format errors */
     addReplyErrorFormat(c,"Invalid argument '%s' for CONFIG SET '%s'",
             (char*)o->ptr,
