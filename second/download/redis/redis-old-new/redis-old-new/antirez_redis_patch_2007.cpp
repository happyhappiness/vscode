@@ -176,6 +176,13 @@ void syncCommand(redisClient *c) {
     /* ignore SYNC if aleady slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
 
+    /* Refuse SYNC requests if we are a slave but the link with our master
+     * is not ok... */
+    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED) {
+        addReplySds(c,sdsnew("-ERR Can't SYNC while not connected with my master\r\n"));
+        return;
+    }
+
     /* SYNC can't be issued when the server has pending data to send to
      * the client about already issued commands. We need a fresh reply
      * buffer registering the differences between the BGSAVE and the current
@@ -392,7 +399,12 @@ int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
-    if (buf[0] != '$') {
+    if (buf[0] == '-') {
+        close(fd);
+        redisLog(REDIS_WARNING,"MASTER aborted replication with an error: %s",
+            buf+1);
+        return REDIS_ERR;
+    } else if (buf[0] != '$') {
         close(fd);
         redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
         return REDIS_ERR;
@@ -416,9 +428,9 @@ int syncWithMaster(void) {
         int nread, nwritten;
 
         nread = read(fd,buf,(dumpsize < 1024)?dumpsize:1024);
-        if (nread == -1) {
+        if (nread <= 0) {
             redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
-                strerror(errno));
+                (nread == -1) ? strerror(errno) : "connection lost");
             close(fd);
             close(dfd);
             return REDIS_ERR;