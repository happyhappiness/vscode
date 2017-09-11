@@ -128,7 +128,12 @@ void flushAppendOnlyFile(int force) {
         if (nwritten == -1) {
             redisLog(REDIS_WARNING,"Exiting on error writing to the append-only file: %s",strerror(errno));
         } else {
-            redisLog(REDIS_WARNING,"Exiting on short write while writing to the append-only file: %s",strerror(errno));
+            redisLog(REDIS_WARNING,"Exiting on short write while writing to "
+                                   "the append-only file: %s (nwritten=%ld, "
+                                   "expected=%ld)",
+                                   strerror(errno),
+                                   (long)nwritten,
+                                   (long)sdslen(server.aof_buf));
         }
         exit(1);
     }
@@ -673,7 +678,7 @@ int rewriteAppendOnlyFile(char *filename) {
     snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        redisLog(REDIS_WARNING, "Failed rewriting the append only file: %s", strerror(errno));
+        redisLog(REDIS_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
         return REDIS_ERR;
     }
 
@@ -842,7 +847,7 @@ void aofUpdateCurrentSize(void) {
     struct redis_stat sb;
 
     if (redis_fstat(server.aof_fd,&sb) == -1) {
-        redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
+        redisLog(REDIS_WARNING,"Unable to obtain the AOF file length. stat: %s",
             strerror(errno));
     } else {
         server.aof_current_size = sb.st_size;
@@ -931,7 +936,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
          * it exists, because we reference it with "oldfd". */
         if (rename(tmpfile,server.aof_filename) == -1) {
             redisLog(REDIS_WARNING,
-                "Error trying to rename the temporary AOF: %s", strerror(errno));
+                "Error trying to rename the temporary AOF file: %s", strerror(errno));
             close(newfd);
             if (oldfd != -1) close(oldfd);
             goto cleanup;
@@ -959,7 +964,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             server.aof_buf = sdsempty();
         }
 
-        redisLog(REDIS_NOTICE, "Background AOF rewrite successful");
+        redisLog(REDIS_NOTICE, "Background AOF rewrite finished successfully");
         /* Change state from WAIT_REWRITE to ON if needed */
         if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
             server.aof_state = REDIS_AOF_ON;