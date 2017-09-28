             "temp-%d.%ld.rdb",(int)server.unixtime,(long int)getpid());
         dfd = open(tmpfile,O_CREAT|O_WRONLY|O_EXCL,0644);
         if (dfd != -1) break;
         sleep(1);
     }
     if (dfd == -1) {
-        redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
+        serverLog(LL_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
         goto error;
     }
 
     /* Setup the non blocking download of the bulk file. */
     if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
             == AE_ERR)
     {
-        redisLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Can't create readable event for SYNC: %s (fd=%d)",
             strerror(errno),fd);
         goto error;
     }
 
-    server.repl_state = REDIS_REPL_TRANSFER;
+    server.repl_state = REPL_STATE_TRANSFER;
     server.repl_transfer_size = -1;
     server.repl_transfer_read = 0;
     server.repl_transfer_last_fsync_off = 0;
     server.repl_transfer_fd = dfd;
     server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_tmpfile = zstrdup(tmpfile);
     return;
 
 error:
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
-    server.repl_state = REDIS_REPL_CONNECT;
+    server.repl_state = REPL_STATE_CONNECT;
     return;
 
 write_error: /* Handle sendSynchronousCommand(SYNC_CMD_WRITE) errors. */
-    redisLog(REDIS_WARNING,"Sending command to master in replication handshake: %s", err);
+    serverLog(LL_WARNING,"Sending command to master in replication handshake: %s", err);
     sdsfree(err);
     goto error;
 }
 
 int connectWithMaster(void) {
     int fd;
 
     fd = anetTcpNonBlockBestEffortBindConnect(NULL,
-        server.masterhost,server.masterport,REDIS_BIND_ADDR);
+        server.masterhost,server.masterport,NET_FIRST_BIND_ADDR);
     if (fd == -1) {
-        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
+        serverLog(LL_WARNING,"Unable to connect to MASTER: %s",
             strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,syncWithMaster,NULL) ==
             AE_ERR)
     {
         close(fd);
-        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
-        return REDIS_ERR;
+        serverLog(LL_WARNING,"Can't create readable event for SYNC");
+        return C_ERR;
     }
 
     server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_s = fd;
-    server.repl_state = REDIS_REPL_CONNECTING;
-    return REDIS_OK;
+    server.repl_state = REPL_STATE_CONNECTING;
+    return C_OK;
 }
 
 /* This function can be called when a non blocking connection is currently
- * in progress to undo it. */
+ * in progress to undo it.
+ * Never call this function directly, use cancelReplicationHandshake() instead.
+ */
 void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
-    redisAssert(server.repl_state == REDIS_REPL_CONNECTING ||
-                slaveIsInHandshakeState());
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
-    server.repl_state = REDIS_REPL_CONNECT;
+}
+
+/* Abort the async download of the bulk dataset while SYNC-ing with master.
+ * Never call this function directly, use cancelReplicationHandshake() instead.
+ */
+void replicationAbortSyncTransfer(void) {
+    serverAssert(server.repl_state == REPL_STATE_TRANSFER);
+    undoConnectWithMaster();
+    close(server.repl_transfer_fd);
+    unlink(server.repl_transfer_tmpfile);
+    zfree(server.repl_transfer_tmpfile);
 }
 
 /* This function aborts a non blocking replication attempt if there is one
  * in progress, by canceling the non-blocking connect attempt or
  * the initial bulk transfer.
  *
  * If there was a replication handshake in progress 1 is returned and
- * the replication state (server.repl_state) set to REDIS_REPL_CONNECT.
+ * the replication state (server.repl_state) set to REPL_STATE_CONNECT.
  *
  * Otherwise zero is returned and no operation is perforemd at all. */
 int cancelReplicationHandshake(void) {
-    if (server.repl_state == REDIS_REPL_TRANSFER) {
+    if (server.repl_state == REPL_STATE_TRANSFER) {
         replicationAbortSyncTransfer();
-    } else if (server.repl_state == REDIS_REPL_CONNECTING ||
+        server.repl_state = REPL_STATE_CONNECT;
+    } else if (server.repl_state == REPL_STATE_CONNECTING ||
                slaveIsInHandshakeState())
     {
         undoConnectWithMaster();
+        server.repl_state = REPL_STATE_CONNECT;
     } else {
         return 0;
     }
     return 1;
 }
 
