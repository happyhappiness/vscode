@@ -888,7 +888,6 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     nread = read(fd,buf,readlen);
-    printf("NREAD %d (%d)\n", (int)nread, (int)readlen);
     if (nread <= 0) {
         redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
             (nread == -1) ? strerror(errno) : "connection lost");