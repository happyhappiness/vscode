@@ -220,6 +220,7 @@ struct redisCommand redisCommandTable[] = {
     {"exec",execCommand,1,"sM",0,NULL,0,0,0,0,0},
     {"discard",discardCommand,1,"rs",0,NULL,0,0,0,0,0},
     {"sync",syncCommand,1,"ars",0,NULL,0,0,0,0,0},
+    {"psync",syncCommand,3,"ars",0,NULL,0,0,0,0,0},
     {"replconf",replconfCommand,-1,"ars",0,NULL,0,0,0,0,0},
     {"flushdb",flushdbCommand,1,"w",0,NULL,0,0,0,0,0},
     {"flushall",flushallCommand,1,"w",0,NULL,0,0,0,0,0},
@@ -1202,13 +1203,25 @@ void initServerConfig() {
     server.masterhost = NULL;
     server.masterport = 6379;
     server.master = NULL;
+    server.cached_master = NULL;
+    server.repl_master_initial_offset = -1;
     server.repl_state = REDIS_REPL_NONE;
     server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = 1;
     server.repl_slave_ro = 1;
     server.repl_down_since = time(NULL);
     server.repl_disable_tcp_nodelay = 0;
     server.slave_priority = REDIS_DEFAULT_SLAVE_PRIORITY;
+    server.master_repl_offset = 0;
+
+    /* Replication partial resync backlog */
+    server.repl_backlog = NULL;
+    server.repl_backlog_size = REDIS_DEFAULT_REPL_BACKLOG_SIZE;
+    server.repl_backlog_histlen = 0;
+    server.repl_backlog_idx = 0;
+    server.repl_backlog_off = 0;
+    server.repl_backlog_time_limit = REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT;
+    server.repl_no_slaves_since = time(NULL);
 
     /* Client output buffer limits */
     server.client_obuf_limits[REDIS_CLIENT_LIMIT_CLASS_NORMAL].hard_limit_bytes = 0;
@@ -1522,7 +1535,7 @@ void propagate(struct redisCommand *cmd, int dbid, robj **argv, int argc,
 {
     if (server.aof_state != REDIS_AOF_OFF && flags & REDIS_PROPAGATE_AOF)
         feedAppendOnlyFile(cmd,dbid,argv,argc);
-    if (flags & REDIS_PROPAGATE_REPL && listLength(server.slaves))
+    if (flags & REDIS_PROPAGATE_REPL)
         replicationFeedSlaves(server.slaves,dbid,argv,argc);
 }
 
@@ -2151,13 +2164,15 @@ sds genRedisInfoString(char *section) {
                 "master_link_status:%s\r\n"
                 "master_last_io_seconds_ago:%d\r\n"
                 "master_sync_in_progress:%d\r\n"
+                "slave_repl_offset:%lld\r\n"
                 ,server.masterhost,
                 server.masterport,
                 (server.repl_state == REDIS_REPL_CONNECTED) ?
                     "up" : "down",
                 server.master ?
                 ((int)(server.unixtime-server.master->lastinteraction)) : -1,
-                server.repl_state == REDIS_REPL_TRANSFER
+                server.repl_state == REDIS_REPL_TRANSFER,
+                server.master ? server.master->reploff : -1
             );
 
             if (server.repl_state == REDIS_REPL_TRANSFER) {
@@ -2215,6 +2230,17 @@ sds genRedisInfoString(char *section) {
                 slaveid++;
             }
         }
+        info = sdscatprintf(info,
+            "master_repl_offset:%lld\r\n"
+            "repl_backlog_active:%d\r\n"
+            "repl_backlog_size:%lld\r\n"
+            "repl_backlog_first_byte_offset:%lld\r\n"
+            "repl_backlog_histlen:%lld\r\n",
+            server.master_repl_offset,
+            server.repl_backlog != NULL,
+            server.repl_backlog_size,
+            server.repl_backlog_off,
+            server.repl_backlog_histlen);
     }
 
     /* CPU */