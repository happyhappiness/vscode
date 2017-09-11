@@ -483,6 +483,8 @@ char *sendSynchronousCommand(int fd, ...) {
 void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     char tmpfile[256], *err;
     int dfd, maxtries = 5;
+    int sockerr = 0;
+    socklen_t errlen = sizeof(sockerr);
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(privdata);
     REDIS_NOTUSED(mask);
@@ -494,11 +496,62 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         return;
     }
 
-    redisLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
-    /* This event should only be triggered once since it is used to have a
-     * non-blocking connect(2) to the master. It has been triggered when this
-     * function is called, so we can delete it. */
-    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
+    /* Check for errors in the socket. */
+    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &sockerr, &errlen) == -1)
+        sockerr = errno;
+    if (sockerr) {
+        aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
+        redisLog(REDIS_WARNING,"Error condition on socket for SYNC: %s",
+            strerror(sockerr));
+        goto error;
+    }
+
+    /* If we were connecting, it's time to send a non blocking PING, we want to
+     * make sure the master is able to reply before going into the actual
+     * replication process where we have long timeouts in the order of
+     * seconds (in the meantime the slave would block). */
+    if (server.repl_state == REDIS_REPL_CONNECTING) {
+        redisLog(REDIS_NOTICE,"Non blocking connect for SYNC fired the event.");
+        /* Delete the writable event so that the readable event remains
+         * registered and we can wait for the PONG reply. */
+        aeDeleteFileEvent(server.el,fd,AE_WRITABLE);
+        server.repl_state = REDIS_REPL_RECEIVE_PONG;
+        /* Send the PING, don't check for errors at all, we have the timeout
+         * that will take care about this. */
+        syncWrite(fd,"PING\r\n",6,100);
+        return;
+    }
+
+    /* Receive the PONG command. */
+    if (server.repl_state == REDIS_REPL_RECEIVE_PONG) {
+        char buf[1024];
+
+        /* Delete the readable event, we no longer need it now that there is
+         * the PING reply to read. */
+        aeDeleteFileEvent(server.el,fd,AE_READABLE);
+
+        /* Read the reply with explicit timeout. */
+        buf[0] = '\0';
+        if (syncReadLine(fd,buf,sizeof(buf),
+            server.repl_syncio_timeout*1000) == -1)
+        {
+            redisLog(REDIS_WARNING,
+                "I/O error reading PING reply from master: %s",
+                strerror(errno));
+            goto error;
+        }
+
+        /* We don't care about the reply, it can be +PONG or an error since
+         * the server requires AUTH. As long as it replies correctly, it's
+         * fine from our point of view. */
+        if (buf[0] != '-' && buf[0] != '+') {
+            redisLog(REDIS_WARNING,"Unexpected reply to PING from master.");
+            goto error;
+        } else {
+            redisLog(REDIS_NOTICE,
+                "Master replied to PING, replication can continue...");
+        }
+    }
 
     /* AUTH with the master if required. */
     if(server.masterauth) {
@@ -563,8 +616,9 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     return;
 
 error:
-    server.repl_state = REDIS_REPL_CONNECT;
     close(fd);
+    server.repl_transfer_s = -1;
+    server.repl_state = REDIS_REPL_CONNECT;
     return;
 }
 
@@ -597,7 +651,8 @@ int connectWithMaster(void) {
 void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
-    redisAssert(server.repl_state == REDIS_REPL_CONNECTING);
+    redisAssert(server.repl_state == REDIS_REPL_CONNECTING ||
+                server.repl_state == REDIS_REPL_RECEIVE_PONG);
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
@@ -613,7 +668,8 @@ void slaveofCommand(redisClient *c) {
             if (server.master) freeClient(server.master);
             if (server.repl_state == REDIS_REPL_TRANSFER)
                 replicationAbortSyncTransfer();
-            else if (server.repl_state == REDIS_REPL_CONNECTING)
+            else if (server.repl_state == REDIS_REPL_CONNECTING ||
+                     server.repl_state == REDIS_REPL_RECEIVE_PONG)
                 undoConnectWithMaster();
             server.repl_state = REDIS_REPL_NONE;
             redisLog(REDIS_NOTICE,"MASTER MODE enabled (user request)");
@@ -651,7 +707,9 @@ void slaveofCommand(redisClient *c) {
 
 void replicationCron(void) {
     /* Non blocking connection timeout? */
-    if (server.masterhost && server.repl_state == REDIS_REPL_CONNECTING &&
+    if (server.masterhost &&
+        (server.repl_state == REDIS_REPL_CONNECTING ||
+         server.repl_state == REDIS_REPL_RECEIVE_PONG) &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
         redisLog(REDIS_WARNING,"Timeout connecting to the MASTER...");