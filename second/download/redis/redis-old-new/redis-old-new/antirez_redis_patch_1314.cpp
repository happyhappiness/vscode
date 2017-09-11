@@ -323,7 +323,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
     server.repl_transfer_lastio = server.unixtime;
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
-        redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
+        redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchronization: %s", strerror(errno));
         goto error;
     }
     server.repl_transfer_left -= nread;