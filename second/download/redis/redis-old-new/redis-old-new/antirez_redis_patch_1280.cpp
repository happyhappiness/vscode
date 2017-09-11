@@ -311,16 +311,18 @@ void replicationAbortSyncTransfer(void) {
 }
 
 /* Asynchronously read the SYNC payload we receive from a master */
+#define REPL_MAX_WRITTEN_BEFORE_FSYNC (1024*1024*8) /* 8 MB */
 void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     char buf[4096];
     ssize_t nread, readlen;
+    off_t left;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(privdata);
     REDIS_NOTUSED(mask);
 
-    /* If repl_transfer_left == -1 we still have to read the bulk length
+    /* If repl_transfer_size == -1 we still have to read the bulk length
      * from the master reply. */
-    if (server.repl_transfer_left == -1) {
+    if (server.repl_transfer_size == -1) {
         if (syncReadLine(fd,buf,1024,server.repl_syncio_timeout*1000) == -1) {
             redisLog(REDIS_WARNING,
                 "I/O error reading bulk count from MASTER: %s",
@@ -343,16 +345,16 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
             goto error;
         }
-        server.repl_transfer_left = strtol(buf+1,NULL,10);
+        server.repl_transfer_size = strtol(buf+1,NULL,10);
         redisLog(REDIS_NOTICE,
             "MASTER <-> SLAVE sync: receiving %ld bytes from master",
-            server.repl_transfer_left);
+            server.repl_transfer_size);
         return;
     }
 
     /* Read bulk data */
-    readlen = (server.repl_transfer_left < (signed)sizeof(buf)) ?
-        server.repl_transfer_left : (signed)sizeof(buf);
+    left = server.repl_transfer_size - server.repl_transfer_read;
+    readlen = (left < (signed)sizeof(buf)) ? left : (signed)sizeof(buf);
     nread = read(fd,buf,readlen);
     if (nread <= 0) {
         redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
@@ -365,9 +367,23 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
         goto error;
     }
-    server.repl_transfer_left -= nread;
+    server.repl_transfer_read += nread;
+
+    /* Sync data on disk from time to time, otherwise at the end of the transfer
+     * we may suffer a big delay as the memory buffers are copied into the
+     * actual disk. */
+    if (server.repl_transfer_read >=
+        server.repl_transfer_last_fsync_off + REPL_MAX_WRITTEN_BEFORE_FSYNC)
+    {
+        off_t sync_size = server.repl_transfer_read -
+                          server.repl_transfer_last_fsync_off;
+        rdb_fsync_range(server.repl_transfer_fd,
+            server.repl_transfer_last_fsync_off, sync_size);
+        server.repl_transfer_last_fsync_off += sync_size;
+    }
+
     /* Check if the transfer is now complete */
-    if (server.repl_transfer_left == 0) {
+    if (server.repl_transfer_read == server.repl_transfer_size) {
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             replicationAbortSyncTransfer();
@@ -538,7 +554,9 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     server.repl_state = REDIS_REPL_TRANSFER;
-    server.repl_transfer_left = -1;
+    server.repl_transfer_size = -1;
+    server.repl_transfer_read = 0;
+    server.repl_transfer_last_fsync_off = 0;
     server.repl_transfer_fd = dfd;
     server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_tmpfile = zstrdup(tmpfile);