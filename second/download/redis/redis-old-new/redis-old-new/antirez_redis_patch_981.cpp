@@ -613,9 +613,11 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
     if ((nwritten = write(fd,buf,buflen)) == -1) {
-        redisLog(REDIS_VERBOSE,"Write error sending DB to slave: %s",
-            strerror(errno));
-        freeClient(slave);
+        if (errno != EAGAIN) {
+            redisLog(REDIS_WARNING,"Write error sending DB to slave: %s",
+                strerror(errno));
+            freeClient(slave);
+        }
         return;
     }
     slave->repldboff += nwritten;
@@ -627,6 +629,7 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
         slave->repl_ack_time = server.unixtime;
         if (aeCreateFileEvent(server.el, slave->fd, AE_WRITABLE,
             sendReplyToClient, slave) == AE_ERR) {
+            redisLog(REDIS_WARNING,"Unable to register writable event for slave bulk transfer: %s", strerror(errno));
             freeClient(slave);
             return;
         }