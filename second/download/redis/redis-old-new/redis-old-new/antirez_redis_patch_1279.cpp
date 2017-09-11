@@ -2079,9 +2079,10 @@ sds genRedisInfoString(char *section) {
 
             if (server.repl_state == REDIS_REPL_TRANSFER) {
                 info = sdscatprintf(info,
-                    "master_sync_left_bytes:%ld\r\n"
+                    "master_sync_left_bytes:%lld\r\n"
                     "master_sync_last_io_seconds_ago:%d\r\n"
-                    ,(long)server.repl_transfer_left,
+                    , (long long)
+                        (server.repl_transfer_size - server.repl_transfer_read),
                     (int)(server.unixtime-server.repl_transfer_lastio)
                 );
             }