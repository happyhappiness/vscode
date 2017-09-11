@@ -1375,6 +1375,16 @@ void replicationResurrectCachedMaster(int newfd) {
         redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the readable handler: %s", strerror(errno));
         freeClientAsync(server.master); /* Close ASAP. */
     }
+
+    /* We may also need to install the write handler as well if there is
+     * pending data in the write buffers. */
+    if (server.master->bufpos || listLength(server.master->reply)) {
+        if (aeCreateFileEvent(server.el, newfd, AE_WRITABLE,
+                          sendReplyToClient, server.master)) {
+            redisLog(REDIS_WARNING,"Error resurrecting the cached master, impossible to add the writable handler: %s", strerror(errno));
+            freeClientAsync(server.master); /* Close ASAP. */
+        }
+    }
 }
 
 /* ------------------------- MIN-SLAVES-TO-WRITE  --------------------------- */