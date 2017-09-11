@@ -89,7 +89,7 @@ void syncCommand(redisClient *c) {
 
     /* Refuse SYNC requests if we are a slave but the link with our master
      * is not ok... */
-    if (server.masterhost && server.replstate != REDIS_REPL_CONNECTED) {
+    if (server.masterhost && server.repl_state != REDIS_REPL_CONNECTED) {
         addReplyError(c,"Can't SYNC while not connected with my master");
         return;
     }
@@ -265,14 +265,14 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
 
 /* Abort the async download of the bulk dataset while SYNC-ing with master */
 void replicationAbortSyncTransfer(void) {
-    redisAssert(server.replstate == REDIS_REPL_TRANSFER);
+    redisAssert(server.repl_state == REDIS_REPL_TRANSFER);
 
     aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
     close(server.repl_transfer_s);
     close(server.repl_transfer_fd);
     unlink(server.repl_transfer_tmpfile);
     zfree(server.repl_transfer_tmpfile);
-    server.replstate = REDIS_REPL_CONNECT;
+    server.repl_state = REDIS_REPL_CONNECT;
 }
 
 /* Asynchronously read the SYNC payload we receive from a master */
@@ -356,7 +356,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         server.master = createClient(server.repl_transfer_s);
         server.master->flags |= REDIS_MASTER;
         server.master->authenticated = 1;
-        server.replstate = REDIS_REPL_CONNECTED;
+        server.repl_state = REDIS_REPL_CONNECTED;
         redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
@@ -392,7 +392,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     /* If this event fired after the user turned the instance into a master
      * with SLAVEOF NO ONE we must just return ASAP. */
-    if (server.replstate == REDIS_REPL_NONE) {
+    if (server.repl_state == REDIS_REPL_NONE) {
         close(fd);
         return;
     }
@@ -454,15 +454,15 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         goto error;
     }
 
-    server.replstate = REDIS_REPL_TRANSFER;
+    server.repl_state = REDIS_REPL_TRANSFER;
     server.repl_transfer_left = -1;
     server.repl_transfer_fd = dfd;
     server.repl_transfer_lastio = time(NULL);
     server.repl_transfer_tmpfile = zstrdup(tmpfile);
     return;
 
 error:
-    server.replstate = REDIS_REPL_CONNECT;
+    server.repl_state = REDIS_REPL_CONNECT;
     close(fd);
     return;
 }
@@ -487,7 +487,7 @@ int connectWithMaster(void) {
 
     server.repl_transfer_lastio = time(NULL);
     server.repl_transfer_s = fd;
-    server.replstate = REDIS_REPL_CONNECTING;
+    server.repl_state = REDIS_REPL_CONNECTING;
     return REDIS_OK;
 }
 
@@ -496,11 +496,11 @@ int connectWithMaster(void) {
 void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
-    redisAssert(server.replstate == REDIS_REPL_CONNECTING);
+    redisAssert(server.repl_state == REDIS_REPL_CONNECTING);
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
-    server.replstate = REDIS_REPL_CONNECT;
+    server.repl_state = REDIS_REPL_CONNECT;
 }
 
 void slaveofCommand(redisClient *c) {
@@ -510,21 +510,21 @@ void slaveofCommand(redisClient *c) {
             sdsfree(server.masterhost);
             server.masterhost = NULL;
             if (server.master) freeClient(server.master);
-            if (server.replstate == REDIS_REPL_TRANSFER)
+            if (server.repl_state == REDIS_REPL_TRANSFER)
                 replicationAbortSyncTransfer();
-            else if (server.replstate == REDIS_REPL_CONNECTING)
+            else if (server.repl_state == REDIS_REPL_CONNECTING)
                 undoConnectWithMaster();
-            server.replstate = REDIS_REPL_NONE;
+            server.repl_state = REDIS_REPL_NONE;
             redisLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
         }
     } else {
         sdsfree(server.masterhost);
         server.masterhost = sdsdup(c->argv[1]->ptr);
         server.masterport = atoi(c->argv[2]->ptr);
         if (server.master) freeClient(server.master);
-        if (server.replstate == REDIS_REPL_TRANSFER)
+        if (server.repl_state == REDIS_REPL_TRANSFER)
             replicationAbortSyncTransfer();
-        server.replstate = REDIS_REPL_CONNECT;
+        server.repl_state = REDIS_REPL_CONNECT;
         redisLog(REDIS_NOTICE,"SLAVE OF %s:%d enabled (user request)",
             server.masterhost, server.masterport);
     }
@@ -535,31 +535,31 @@ void slaveofCommand(redisClient *c) {
 
 void replicationCron(void) {
     /* Non blocking connection timeout? */
-    if (server.masterhost && server.replstate == REDIS_REPL_CONNECTING &&
+    if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTING &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
         redisLog(REDIS_WARNING,"Timeout connecting to the MASTER...");
         undoConnectWithMaster();
     }
 
     /* Bulk transfer I/O timeout? */
-    if (server.masterhost && server.replstate == REDIS_REPL_TRANSFER &&
+    if (server.masterhost && server.repl_state == REDIS_REPL_TRANSFER &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
         redisLog(REDIS_WARNING,"Timeout receiving bulk data from MASTER...");
         replicationAbortSyncTransfer();
     }
 
     /* Timed out master when we are an already connected slave? */
-    if (server.masterhost && server.replstate == REDIS_REPL_CONNECTED &&
+    if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTED &&
         (time(NULL)-server.master->lastinteraction) > server.repl_timeout)
     {
         redisLog(REDIS_WARNING,"MASTER time out: no data nor PING received...");
         freeClient(server.master);
     }
 
     /* Check if we should connect to a MASTER */
-    if (server.replstate == REDIS_REPL_CONNECT) {
+    if (server.repl_state == REDIS_REPL_CONNECT) {
         redisLog(REDIS_NOTICE,"Connecting to MASTER...");
         if (connectWithMaster() == REDIS_OK) {
             redisLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");