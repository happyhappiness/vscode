     }
 }
 
 /* Called when the user switches from "appendonly no" to "appendonly yes"
  * at runtime using the CONFIG command. */
 int startAppendOnly(void) {
+    char cwd[MAXPATHLEN]; /* Current working dir path for error messages. */
+
     server.aof_last_fsync = server.unixtime;
     server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
-    redisAssert(server.aof_state == REDIS_AOF_OFF);
+    serverAssert(server.aof_state == AOF_OFF);
     if (server.aof_fd == -1) {
-        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
-        return REDIS_ERR;
+        char *cwdp = getcwd(cwd,MAXPATHLEN);
+
+        serverLog(LL_WARNING,
+            "Redis needs to enable the AOF but can't open the "
+            "append only file %s (in server root dir %s): %s",
+            server.aof_filename,
+            cwdp ? cwdp : "unknown",
+            strerror(errno));
+        return C_ERR;
     }
-    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
+    if (rewriteAppendOnlyFileBackground() == C_ERR) {
         close(server.aof_fd);
-        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
-        return REDIS_ERR;
+        serverLog(LL_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
+        return C_ERR;
     }
     /* We correctly switched on AOF, now wait for the rewrite to be complete
      * in order to append data on disk. */
-    server.aof_state = REDIS_AOF_WAIT_REWRITE;
-    return REDIS_OK;
+    server.aof_state = AOF_WAIT_REWRITE;
+    return C_OK;
 }
 
 /* Write the append only file buffer on disk.
  *
  * Since we are required to write the AOF before replying to the client,
  * and the only way the client socket can get a write is entering when the
