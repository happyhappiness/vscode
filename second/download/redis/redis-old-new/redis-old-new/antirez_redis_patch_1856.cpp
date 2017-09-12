@@ -306,12 +306,41 @@ void replicationAbortSyncTransfer(void) {
 
 /* Asynchronously read the SYNC payload we receive from a master */
 void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
-    unsigned char buf[4096];
+    char buf[4096];
     ssize_t nread, readlen;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(privdata);
     REDIS_NOTUSED(mask);
 
+    /* If repl_transfer_left == -1 we still have to read the bulk length
+     * from the master reply. */
+    if (server.repl_transfer_left == -1) {
+        if (syncReadLine(fd,buf,1024,3600) == -1) {
+            redisLog(REDIS_WARNING,
+                "I/O error reading bulk count from MASTER: %s",
+                strerror(errno));
+            replicationAbortSyncTransfer();
+            return;
+        }
+        if (buf[0] == '-') {
+            redisLog(REDIS_WARNING,
+                "MASTER aborted replication with an error: %s",
+                buf+1);
+            replicationAbortSyncTransfer();
+            return;
+        } else if (buf[0] != '$') {
+            redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
+            replicationAbortSyncTransfer();
+            return;
+        }
+        server.repl_transfer_left = strtol(buf+1,NULL,10);
+        redisLog(REDIS_NOTICE,
+            "MASTER <-> SLAVE sync: receiving %ld bytes from master",
+            server.repl_transfer_left);
+        return;
+    }
+
+    /* Read bulk data */
     readlen = (server.repl_transfer_left < (signed)sizeof(buf)) ?
         server.repl_transfer_left : (signed)sizeof(buf);
     nread = read(fd,buf,readlen);
@@ -349,12 +378,12 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.master->flags |= REDIS_MASTER;
         server.master->authenticated = 1;
         server.replstate = REDIS_REPL_CONNECTED;
+        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
     }
 }
 
 int syncWithMaster(void) {
     char buf[1024], tmpfile[256], authcmd[1024];
-    off_t dumpsize;
     int fd = anetTcpConnect(NULL,server.masterhost,server.masterport);
     int dfd, maxtries = 5;
 
@@ -394,26 +423,8 @@ int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
-    /* Read the bulk write count */
-    if (syncReadLine(fd,buf,1024,3600) == -1) {
-        close(fd);
-        redisLog(REDIS_WARNING,"I/O error reading bulk count from MASTER: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
-    if (buf[0] == '-') {
-        close(fd);
-        redisLog(REDIS_WARNING,"MASTER aborted replication with an error: %s",
-            buf+1);
-        return REDIS_ERR;
-    } else if (buf[0] != '$') {
-        close(fd);
-        redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
-        return REDIS_ERR;
-    }
-    dumpsize = strtol(buf+1,NULL,10);
-    redisLog(REDIS_NOTICE,"Receiving %ld bytes data dump from MASTER",dumpsize);
-    /* Read the bulk write data on a temp file */
+
+    /* Prepare a suitable temp file for bulk transfer */
     while(maxtries--) {
         snprintf(tmpfile,256,
             "temp-%d.%ld.rdb",(int)time(NULL),(long int)getpid());
@@ -436,7 +447,7 @@ int syncWithMaster(void) {
         return REDIS_ERR;
     }
     server.replstate = REDIS_REPL_TRANSFER;
-    server.repl_transfer_left = dumpsize;
+    server.repl_transfer_left = -1;
     server.repl_transfer_s = fd;
     server.repl_transfer_fd = dfd;
     server.repl_transfer_lastio = time(NULL);
@@ -487,7 +498,7 @@ void replicationCron(void) {
     if (server.replstate == REDIS_REPL_CONNECT) {
         redisLog(REDIS_NOTICE,"Connecting to MASTER...");
         if (syncWithMaster() == REDIS_OK) {
-            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync succeeded");
+            redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started: SYNC sent");
             if (server.appendonly) rewriteAppendOnlyFileBackground();
         }
     }