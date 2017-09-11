@@ -1121,6 +1121,7 @@ void initServerConfig() {
     server.aof_last_fsync = time(NULL);
     server.aof_rewrite_time_last = -1;
     server.aof_rewrite_time_start = -1;
+    server.aof_lastbgrewrite_status = REDIS_OK;
     server.aof_delayed_fsync = 0;
     server.aof_fd = -1;
     server.aof_selected_db = -1; /* Make sure the first time will not match */
@@ -1967,12 +1968,13 @@ sds genRedisInfoString(char *section) {
             "aof_rewrite_in_progress:%d\r\n"
             "aof_rewrite_scheduled:%d\r\n"
             "aof_last_rewrite_time_sec:%ld\r\n"
-            "aof_current_rewrite_time_sec:%ld\r\n",
+            "aof_current_rewrite_time_sec:%ld\r\n"
+            "aof_last_bgrewrite_status:%s\r\n",
             server.loading,
             server.dirty,
             server.rdb_child_pid != -1,
             server.lastsave,
-            server.lastbgsave_status == REDIS_OK ? "ok" : "err",
+            (server.lastbgsave_status == REDIS_OK) ? "ok" : "err",
             server.rdb_save_time_last,
             (server.rdb_child_pid == -1) ?
                 -1 : time(NULL)-server.rdb_save_time_start,
@@ -1981,7 +1983,8 @@ sds genRedisInfoString(char *section) {
             server.aof_rewrite_scheduled,
             server.aof_rewrite_time_last,
             (server.aof_child_pid == -1) ?
-                -1 : time(NULL)-server.aof_rewrite_time_start);
+                -1 : time(NULL)-server.aof_rewrite_time_start,
+            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err");
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,