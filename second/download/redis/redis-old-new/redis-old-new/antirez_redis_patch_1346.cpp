@@ -1614,7 +1614,7 @@ void migrateCommand(redisClient *c) {
         return;
     }
     if ((aeWait(fd,AE_WRITABLE,timeout*1000) & AE_WRITABLE) == 0) {
-        addReplyError(c,"Timeout connecting to the client");
+        addReplySds(c,sdsnew("-IOERR error or timeout connecting to the client\r\n"));
         return;
     }
 
@@ -1685,19 +1685,13 @@ void migrateCommand(redisClient *c) {
     return;
 
 socket_wr_err:
-    redisLog(REDIS_NOTICE,"Can't write to target node for MIGRATE: %s",
-        strerror(errno));
-    addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
-        strerror(errno));
+    addReplySds(c,sdsnew("-IOERR error or timeout writing to target instance\r\n"));
     sdsfree(cmd.io.buffer.ptr);
     close(fd);
     return;
 
 socket_rd_err:
-    redisLog(REDIS_NOTICE,"Can't read from target node for MIGRATE: %s",
-        strerror(errno));
-    addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
-        strerror(errno));
+    addReplySds(c,sdsnew("-IOERR error or timeout reading from target node\r\n"));
     sdsfree(cmd.io.buffer.ptr);
     close(fd);
     return;