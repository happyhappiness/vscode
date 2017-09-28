             last_write_error_log = server.unixtime;
         }
 
         /* Log the AOF write error and record the error code. */
         if (nwritten == -1) {
             if (can_log) {
-                redisLog(REDIS_WARNING,"Error writing to the AOF file: %s",
+                serverLog(LL_WARNING,"Error writing to the AOF file: %s",
                     strerror(errno));
                 server.aof_last_write_errno = errno;
             }
         } else {
             if (can_log) {
-                redisLog(REDIS_WARNING,"Short write while writing to "
+                serverLog(LL_WARNING,"Short write while writing to "
                                        "the AOF file: (nwritten=%lld, "
                                        "expected=%lld)",
                                        (long long)nwritten,
                                        (long long)sdslen(server.aof_buf));
             }
 
             if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
                 if (can_log) {
-                    redisLog(REDIS_WARNING, "Could not remove short write "
+                    serverLog(LL_WARNING, "Could not remove short write "
                              "from the append-only file.  Redis may refuse "
                              "to load the AOF the next time it starts.  "
                              "ftruncate: %s", strerror(errno));
                 }
             } else {
                 /* If the ftruncate() succeeded we can set nwritten to
