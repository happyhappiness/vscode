@@ -319,15 +319,14 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             redisLog(REDIS_WARNING,
                 "I/O error reading bulk count from MASTER: %s",
                 strerror(errno));
-            replicationAbortSyncTransfer();
-            return;
+            goto error;
         }
+
         if (buf[0] == '-') {
             redisLog(REDIS_WARNING,
                 "MASTER aborted replication with an error: %s",
                 buf+1);
-            replicationAbortSyncTransfer();
-            return;
+            goto error;
         } else if (buf[0] == '\0') {
             /* At this stage just a newline works as a PING in order to take
              * the connection live. So we refresh our last interaction
@@ -336,8 +335,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             return;
         } else if (buf[0] != '$') {
             redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
-            replicationAbortSyncTransfer();
-            return;
+            goto error;
         }
         server.repl_transfer_left = strtol(buf+1,NULL,10);
         redisLog(REDIS_NOTICE,
@@ -359,8 +357,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     server.repl_transfer_lastio = time(NULL);
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
         redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
-        replicationAbortSyncTransfer();
-        return;
+        goto error;
     }
     server.repl_transfer_left -= nread;
     /* Check if the transfer is now complete */
@@ -391,6 +388,12 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.replstate = REDIS_REPL_CONNECTED;
         redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
     }
+
+    return;
+
+error:
+    replicationAbortSyncTransfer();
+    return;
 }
 
 void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -400,8 +403,10 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(privdata);
     REDIS_NOTUSED(mask);
 
-    /* Remove this event before anything else. */
-    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
+    /* This event should only be triggered once since it is used to have a
+     * non-blocking connect(2) to the master. It has been triggered when this
+     * function is called, so we can delete it. */
+    aeDeleteFileEvent(server.el,fd,AE_WRITABLE);
 
     /* AUTH with the master if required. */
     if(server.masterauth) {
@@ -477,8 +482,8 @@ int connectWithMaster(void) {
         return REDIS_ERR;
     }
 
-    if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,
-            syncWithMaster,NULL) == AE_ERR)
+    if (aeCreateFileEvent(server.el,fd,AE_WRITABLE,syncWithMaster,NULL) ==
+            AE_ERR)
     {
         close(fd);
         redisLog(REDIS_WARNING,"Can't create readable event for SYNC");