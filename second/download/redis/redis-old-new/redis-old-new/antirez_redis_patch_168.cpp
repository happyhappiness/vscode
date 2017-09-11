@@ -251,7 +251,10 @@ int startAppendOnly(void) {
             strerror(errno));
         return C_ERR;
     }
-    if (rewriteAppendOnlyFileBackground() == C_ERR) {
+    if (server.rdb_child_pid != -1) {
+        server.aof_rewrite_scheduled = 1;
+        serverLog(LL_WARNING,"AOF was enabled but there is already a child process saving an RDB file on disk. An AOF background was scheduled to start when possible.");
+    } else if (rewriteAppendOnlyFileBackground() == C_ERR) {
         close(server.aof_fd);
         serverLog(LL_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
         return C_ERR;
@@ -1273,7 +1276,7 @@ int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
     long long start;
 
-    if (server.aof_child_pid != -1) return C_ERR;
+    if (server.aof_child_pid != -1 || server.rdb_child_pid != -1) return C_ERR;
     if (aofCreatePipes() != C_OK) return C_ERR;
     start = ustime();
     if ((childpid = fork()) == 0) {