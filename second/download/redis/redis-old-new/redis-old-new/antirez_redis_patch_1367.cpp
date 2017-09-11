@@ -307,7 +307,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             /* At this stage just a newline works as a PING in order to take
              * the connection live. So we refresh our last interaction
              * timestamp. */
-            server.repl_transfer_lastio = time(NULL);
+            server.repl_transfer_lastio = server.unixtime;
             return;
         } else if (buf[0] != '$') {
             redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
@@ -330,7 +330,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         replicationAbortSyncTransfer();
         return;
     }
-    server.repl_transfer_lastio = time(NULL);
+    server.repl_transfer_lastio = server.unixtime;
     if (write(server.repl_transfer_fd,buf,nread) != nread) {
         redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
         goto error;
@@ -441,7 +441,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     /* Prepare a suitable temp file for bulk transfer */
     while(maxtries--) {
         snprintf(tmpfile,256,
-            "temp-%d.%ld.rdb",(int)time(NULL),(long int)getpid());
+            "temp-%d.%ld.rdb",(int)server.unixtime,(long int)getpid());
         dfd = open(tmpfile,O_CREAT|O_WRONLY|O_EXCL,0644);
         if (dfd != -1) break;
         sleep(1);
@@ -462,7 +462,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     server.repl_state = REDIS_REPL_TRANSFER;
     server.repl_transfer_left = -1;
     server.repl_transfer_fd = dfd;
-    server.repl_transfer_lastio = time(NULL);
+    server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_tmpfile = zstrdup(tmpfile);
     return;
 
@@ -490,7 +490,7 @@ int connectWithMaster(void) {
         return REDIS_ERR;
     }
 
-    server.repl_transfer_lastio = time(NULL);
+    server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_s = fd;
     server.repl_state = REDIS_REPL_CONNECTING;
     return REDIS_OK;