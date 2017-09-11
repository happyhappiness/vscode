@@ -423,7 +423,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     /* Issue the SYNC command */
-    if (syncWrite(fd,"SYNC \r\n",7,server.repl_syncio_timeout*1000) == -1) {
+    if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
         redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
             strerror(errno));
         goto error;