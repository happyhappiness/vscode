@@ -565,16 +565,18 @@ int rewriteAppendOnlyFile(char *filename) {
  */
 int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
+    long long start;
 
     if (server.bgrewritechildpid != -1) return REDIS_ERR;
     if (server.ds_enabled != 0) {
         redisLog(REDIS_WARNING,"BGREWRITEAOF called with diskstore enabled: AOF is not supported when diskstore is enabled. Operation not performed.");
         return REDIS_ERR;
     }
+    start = ustime();
     if ((childpid = fork()) == 0) {
-        /* Child */
         char tmpfile[256];
 
+        /* Child */
         if (server.ipfd > 0) close(server.ipfd);
         if (server.sofd > 0) close(server.sofd);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof", (int) getpid());
@@ -585,6 +587,7 @@ int rewriteAppendOnlyFileBackground(void) {
         }
     } else {
         /* Parent */
+        server.stat_fork_time = ustime()-start;
         if (childpid == -1) {
             redisLog(REDIS_WARNING,
                 "Can't rewrite append only file in background: fork: %s",