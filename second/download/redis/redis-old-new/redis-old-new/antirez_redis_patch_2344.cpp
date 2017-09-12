@@ -1879,6 +1879,11 @@ static int rdbSaveBackground(char *filename) {
         }
     } else {
         /* Parent */
+        if (childpid == -1) {
+            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
+                strerror(errno));
+            return REDIS_ERR;
+        }
         redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
         server.bgsaveinprogress = 1;
         return REDIS_OK;