@@ -1111,6 +1111,8 @@ void initServerConfig() {
     server.aof_rewrite_base_size = 0;
     server.aof_rewrite_scheduled = 0;
     server.aof_last_fsync = time(NULL);
+    server.aof_rewrite_time_last = -1;
+    server.aof_rewrite_time_start = -1;
     server.aof_delayed_fsync = 0;
     server.aof_fd = -1;
     server.aof_selected_db = -1; /* Make sure the first time will not match */
@@ -1304,6 +1306,8 @@ void initServer() {
     aofRewriteBufferReset();
     server.aof_buf = sdsempty();
     server.lastsave = time(NULL);
+    server.rdb_save_time_last = -1;
+    server.rdb_save_time_start = -1;
     server.dirty = 0;
     server.stat_numcommands = 0;
     server.stat_numconnections = 0;
@@ -1900,21 +1904,31 @@ sds genRedisInfoString(char *section) {
         info = sdscatprintf(info,
             "# Persistence\r\n"
             "loading:%d\r\n"
+            "rdb_changes_since_last_save:%lld\r\n"
+            "rdb_bgsave_in_progress:%d\r\n"
+            "rdb_last_save_time:%ld\r\n"
+            "rdb_last_bgsave_status:%s\r\n"
+            "rdb_last_bgsave_time_sec:%ld\r\n"
+            "rdb_current_bgsave_time_sec:%ld\r\n"
             "aof_enabled:%d\r\n"
-            "changes_since_last_save:%lld\r\n"
-            "bgsave_in_progress:%d\r\n"
-            "last_save_time:%ld\r\n"
-            "last_bgsave_status:%s\r\n"
-            "bgrewriteaof_in_progress:%d\r\n"
-            "bgrewriteaof_scheduled:%d\r\n",
+            "aof_rewrite_in_progress:%d\r\n"
+            "aof_rewrite_scheduled:%d\r\n"
+            "aof_last_rewrite_time_sec:%ld\r\n"
+            "aof_current_rewrite_time_sec:%ld\r\n",
             server.loading,
-            server.aof_state != REDIS_AOF_OFF,
             server.dirty,
             server.rdb_child_pid != -1,
             server.lastsave,
             server.lastbgsave_status == REDIS_OK ? "ok" : "err",
+            server.rdb_save_time_last,
+            (server.rdb_child_pid == -1) ?
+                -1 : time(NULL)-server.rdb_save_time_start,
+            server.aof_state != REDIS_AOF_OFF,
             server.aof_child_pid != -1,
-            server.aof_rewrite_scheduled);
+            server.aof_rewrite_scheduled,
+            server.aof_rewrite_time_last,
+            (server.aof_child_pid == -1) ?
+                -1 : time(NULL)-server.aof_rewrite_time_start);
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,