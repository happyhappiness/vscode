@@ -517,7 +517,9 @@ void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
 static void acceptCommonHandler(int fd, int flags) {
     redisClient *c;
     if ((c = createClient(fd)) == NULL) {
-        redisLog(REDIS_WARNING,"Error allocating resources for the client");
+        redisLog(REDIS_WARNING,
+            "Error registering fd event for the new client: %s (fd=%d)",
+            strerror(errno),fd);
         close(fd); /* May be already closed, just ignore errors */
         return;
     }