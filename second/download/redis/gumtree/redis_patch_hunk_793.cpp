             "rdb_changes_since_last_save:%lld\r\n"
             "rdb_bgsave_in_progress:%d\r\n"
             "rdb_last_save_time:%jd\r\n"
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
             (intmax_t)server.lastsave,
             (server.lastbgsave_status == C_OK) ? "ok" : "err",
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
                 "aof_current_size:%lld\r\n"
                 "aof_base_size:%lld\r\n"
                 "aof_pending_rewrite:%d\r\n"
