             server.aof_state != REDIS_AOF_OFF,
             server.aof_child_pid != -1,
             server.aof_rewrite_scheduled,
             (intmax_t)server.aof_rewrite_time_last,
             (intmax_t)((server.aof_child_pid == -1) ?
                 -1 : time(NULL)-server.aof_rewrite_time_start),
-            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err");
+            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err",
+            (server.aof_last_write_status == REDIS_OK) ? "ok" : "err");
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,
                 "aof_current_size:%lld\r\n"
                 "aof_base_size:%lld\r\n"
                 "aof_pending_rewrite:%d\r\n"
