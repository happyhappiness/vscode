@@ -138,7 +138,7 @@ int syncRead(int fd, char *ptr, ssize_t size, int timeout) {
     while(size) {
         if (aeWait(fd,AE_READABLE,1000) & AE_READABLE) {
             nread = read(fd,ptr,size);
-            if (nread == -1) return -1;
+            if (nread <= 0) return -1;
             ptr += nread;
             size -= nread;
             totread += nread;
@@ -176,12 +176,19 @@ void syncCommand(redisClient *c) {
     /* ignore SYNC if aleady slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
 
+    /* Refuse SYNC requests if we are a slave but the link with our master
+     * is not ok... */
+    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED) {
+        addReplyError(c,"Can't SYNC while not connected with my master");
+        return;
+    }
+
     /* SYNC can't be issued when the server has pending data to send to
      * the client about already issued commands. We need a fresh reply
      * buffer registering the differences between the BGSAVE and the current
      * dataset, so that we can copy to other slaves if needed. */
     if (listLength(c->reply) != 0) {
-        addReplySds(c,sdsnew("-ERR SYNC is invalid with pending input\r\n"));
+        addReplyError(c,"SYNC is invalid with pending input");
         return;
     }
 
@@ -219,7 +226,7 @@ void syncCommand(redisClient *c) {
         redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
         if (rdbSaveBackground(server.dbfilename) != REDIS_OK) {
             redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
-            addReplySds(c,sdsnew("-ERR Unalbe to perform background save\r\n"));
+            addReplyError(c,"Unable to perform background save");
             return;
         }
         c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
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