@@ -1046,8 +1046,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                     (int) server.aof_child_pid);
             } else if (pid == server.rdb_child_pid) {
                 backgroundSaveDoneHandler(exitcode,bysignal);
+                if (!bysignal && exitcode == 0) receiveChildInfo();
             } else if (pid == server.aof_child_pid) {
                 backgroundRewriteDoneHandler(exitcode,bysignal);
+                if (!bysignal && exitcode == 0) receiveChildInfo();
             } else {
                 if (!ldbRemoveChild(pid)) {
                     serverLog(LL_WARNING,
@@ -1056,6 +1058,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                 }
             }
             updateDictResizePolicy();
+            closeChildInfoPipe();
         }
     } else {
         /* If there is not a background saving/rewrite in progress check if
@@ -1794,6 +1797,9 @@ void initServer(void) {
     server.aof_child_pid = -1;
     server.rdb_child_type = RDB_CHILD_TYPE_NONE;
     server.rdb_bgsave_scheduled = 0;
+    server.child_info_pipe[0] = -1;
+    server.child_info_pipe[1] = -1;
+    server.child_info_data.magic = 0;
     aofRewriteBufferReset();
     server.aof_buf = sdsempty();
     server.lastsave = time(NULL); /* At startup we consider the DB saved. */
@@ -1805,6 +1811,8 @@ void initServer(void) {
     /* A few stats we don't want to reset: server startup time, and peak mem. */
     server.stat_starttime = time(NULL);
     server.stat_peak_memory = 0;
+    server.stat_rdb_cow_bytes = 0;
+    server.stat_aof_cow_bytes = 0;
     server.resident_set_size = 0;
     server.lastbgsave_status = C_OK;
     server.aof_last_write_status = C_OK;
@@ -2889,13 +2897,15 @@ sds genRedisInfoString(char *section) {
             "rdb_last_bgsave_status:%s\r\n"
             "rdb_last_bgsave_time_sec:%jd\r\n"
             "rdb_current_bgsave_time_sec:%jd\r\n"
+            "rdb_last_cow_size:%zu\r\n"
             "aof_enabled:%d\r\n"
             "aof_rewrite_in_progress:%d\r\n"
             "aof_rewrite_scheduled:%d\r\n"
             "aof_last_rewrite_time_sec:%jd\r\n"
             "aof_current_rewrite_time_sec:%jd\r\n"
             "aof_last_bgrewrite_status:%s\r\n"
-            "aof_last_write_status:%s\r\n",
+            "aof_last_write_status:%s\r\n"
+            "aof_last_cow_size:%zu\r\n",
             server.loading,
             server.dirty,
             server.rdb_child_pid != -1,
@@ -2904,14 +2914,16 @@ sds genRedisInfoString(char *section) {
             (intmax_t)server.rdb_save_time_last,
             (intmax_t)((server.rdb_child_pid == -1) ?
                 -1 : time(NULL)-server.rdb_save_time_start),
+            server.stat_rdb_cow_bytes,
             server.aof_state != AOF_OFF,
             server.aof_child_pid != -1,
             server.aof_rewrite_scheduled,
             (intmax_t)server.aof_rewrite_time_last,
             (intmax_t)((server.aof_child_pid == -1) ?
                 -1 : time(NULL)-server.aof_rewrite_time_start),
             (server.aof_lastbgrewrite_status == C_OK) ? "ok" : "err",
-            (server.aof_last_write_status == C_OK) ? "ok" : "err");
+            (server.aof_last_write_status == C_OK) ? "ok" : "err",
+            server.stat_aof_cow_bytes);
 
         if (server.aof_state != AOF_OFF) {
             info = sdscatprintf(info,