@@ -636,7 +636,9 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
             == AE_ERR)
     {
-        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
+        redisLog(REDIS_WARNING,
+            "Can't create readable event for SYNC: %s (fd=%d)",
+            strerror(errno),fd);
         goto error;
     }
 