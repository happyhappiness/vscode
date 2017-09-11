@@ -2070,8 +2070,8 @@ sds genRedisInfoString(char *section) {
             "process_id:%ld\r\n"
             "run_id:%s\r\n"
             "tcp_port:%d\r\n"
-            "uptime_in_seconds:%ld\r\n"
-            "uptime_in_days:%ld\r\n"
+            "uptime_in_seconds:%jd\r\n"
+            "uptime_in_days:%jd\r\n"
             "hz:%d\r\n"
             "lru_clock:%ld\r\n"
             "config_file:%s\r\n",
@@ -2091,8 +2091,8 @@ sds genRedisInfoString(char *section) {
             (long) getpid(),
             server.runid,
             server.port,
-            uptime,
-            uptime/(3600*24),
+            (intmax_t)uptime,
+            (intmax_t)(uptime/(3600*24)),
             server.hz,
             (unsigned long) server.lruclock,
             server.configfile ? server.configfile : "");
@@ -2149,30 +2149,30 @@ sds genRedisInfoString(char *section) {
             "loading:%d\r\n"
             "rdb_changes_since_last_save:%lld\r\n"
             "rdb_bgsave_in_progress:%d\r\n"
-            "rdb_last_save_time:%ld\r\n"
+            "rdb_last_save_time:%jd\r\n"
             "rdb_last_bgsave_status:%s\r\n"
-            "rdb_last_bgsave_time_sec:%ld\r\n"
-            "rdb_current_bgsave_time_sec:%ld\r\n"
+            "rdb_last_bgsave_time_sec:%jd\r\n"
+            "rdb_current_bgsave_time_sec:%jd\r\n"
             "aof_enabled:%d\r\n"
             "aof_rewrite_in_progress:%d\r\n"
             "aof_rewrite_scheduled:%d\r\n"
-            "aof_last_rewrite_time_sec:%ld\r\n"
-            "aof_current_rewrite_time_sec:%ld\r\n"
+            "aof_last_rewrite_time_sec:%jd\r\n"
+            "aof_current_rewrite_time_sec:%jd\r\n"
             "aof_last_bgrewrite_status:%s\r\n",
             server.loading,
             server.dirty,
             server.rdb_child_pid != -1,
-            server.lastsave,
+            (intmax_t)server.lastsave,
             (server.lastbgsave_status == REDIS_OK) ? "ok" : "err",
-            server.rdb_save_time_last,
-            (server.rdb_child_pid == -1) ?
-                -1 : time(NULL)-server.rdb_save_time_start,
+            (intmax_t)server.rdb_save_time_last,
+            (intmax_t)((server.rdb_child_pid == -1) ?
+                -1 : time(NULL)-server.rdb_save_time_start),
             server.aof_state != REDIS_AOF_OFF,
             server.aof_child_pid != -1,
             server.aof_rewrite_scheduled,
-            server.aof_rewrite_time_last,
-            (server.aof_child_pid == -1) ?
-                -1 : time(NULL)-server.aof_rewrite_time_start,
+            (intmax_t)server.aof_rewrite_time_last,
+            (intmax_t)((server.aof_child_pid == -1) ?
+                -1 : time(NULL)-server.aof_rewrite_time_start),
             (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err");
 
         if (server.aof_state != REDIS_AOF_OFF) {
@@ -2211,16 +2211,16 @@ sds genRedisInfoString(char *section) {
             }
 
             info = sdscatprintf(info,
-                "loading_start_time:%ld\r\n"
+                "loading_start_time:%jd\r\n"
                 "loading_total_bytes:%llu\r\n"
                 "loading_loaded_bytes:%llu\r\n"
                 "loading_loaded_perc:%.2f\r\n"
-                "loading_eta_seconds:%ld\r\n"
-                ,(unsigned long) server.loading_start_time,
+                "loading_eta_seconds:%jd\r\n",
+                (intmax_t) server.loading_start_time,
                 (unsigned long long) server.loading_total_bytes,
                 (unsigned long long) server.loading_loaded_bytes,
                 perc,
-                eta
+                (intmax_t)eta
             );
         }
     }
@@ -2299,8 +2299,8 @@ sds genRedisInfoString(char *section) {
 
             if (server.repl_state != REDIS_REPL_CONNECTED) {
                 info = sdscatprintf(info,
-                    "master_link_down_since_seconds:%ld\r\n",
-                    (long)server.unixtime-server.repl_down_since);
+                    "master_link_down_since_seconds:%jd\r\n",
+                    (intmax_t)server.unixtime-server.repl_down_since);
             }
             info = sdscatprintf(info,
                 "slave_priority:%d\r\n"