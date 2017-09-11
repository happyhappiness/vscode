@@ -1835,14 +1835,16 @@ sds genRedisInfoString(char *section) {
             "bgsave_in_progress:%d\r\n"
             "last_save_time:%ld\r\n"
             "last_bgsave_status:%s\r\n"
-            "bgrewriteaof_in_progress:%d\r\n",
+            "bgrewriteaof_in_progress:%d\r\n"
+            "bgrewriteaof_scheduled:%d\r\n",
             server.loading,
             server.aof_state != REDIS_AOF_OFF,
             server.dirty,
             server.rdb_child_pid != -1,
             server.lastsave,
             server.lastbgsave_status == REDIS_OK ? "ok" : "err",
-            server.aof_child_pid != -1);
+            server.aof_child_pid != -1,
+            server.aof_rewrite_scheduled);
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,