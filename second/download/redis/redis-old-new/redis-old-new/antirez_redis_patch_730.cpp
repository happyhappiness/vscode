@@ -918,6 +918,16 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
     server.repl_transfer_read += nread;
 
+    /* Delete the last 40 bytes from the file if we reached EOF. */
+    if (usemark && eof_reached) {
+        if (ftruncate(server.repl_transfer_fd,
+            server.repl_transfer_read - REDIS_RUN_ID_SIZE) == -1)
+        {
+            redisLog(REDIS_WARNING,"Error truncating the RDB file received from the master for SYNC: %s", strerror(errno));
+            goto error;
+        }
+    }
+
     /* Sync data on disk from time to time, otherwise at the end of the transfer
      * we may suffer a big delay as the memory buffers are copied into the
      * actual disk. */