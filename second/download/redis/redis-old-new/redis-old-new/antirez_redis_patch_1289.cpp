@@ -250,6 +250,13 @@ void flushAppendOnlyFile(int force) {
                                    strerror(errno),
                                    (long)nwritten,
                                    (long)sdslen(server.aof_buf));
+
+            if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
+                redisLog(REDIS_WARNING, "Could not remove short write "
+                         "from the append-only file.  Redis may refuse "
+                         "to load the AOF the next time it starts.  "
+                         "ftruncate: %s", strerror(errno));
+            }
         }
         exit(1);
     }
@@ -1093,6 +1100,8 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             server.aof_buf = sdsempty();
         }
 
+        server.aof_lastbgrewrite_status = REDIS_OK;
+
         redisLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
         /* Change state from WAIT_REWRITE to ON if needed */
         if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
@@ -1104,9 +1113,13 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         redisLog(REDIS_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);
     } else if (!bysignal && exitcode != 0) {
+        server.aof_lastbgrewrite_status = REDIS_ERR;
+
         redisLog(REDIS_WARNING,
             "Background AOF rewrite terminated with error");
     } else {
+        server.aof_lastbgrewrite_status = REDIS_ERR;
+
         redisLog(REDIS_WARNING,
             "Background AOF rewrite terminated by signal %d", bysignal);
     }