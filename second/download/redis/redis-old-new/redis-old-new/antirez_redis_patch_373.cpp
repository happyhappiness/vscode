@@ -909,6 +909,13 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
 
 /* ----------------------------------- SLAVE -------------------------------- */
 
+/* Returns 1 if the given replication state is a handshake state,
+ * 0 otherwise. */
+int slaveIsInHandshakeState(void) {
+    return server.repl_state >= REPL_STATE_RECEIVE_PONG &&
+           server.repl_state <= REPL_STATE_RECEIVE_PSYNC;
+}
+
 /* Abort the async download of the bulk dataset while SYNC-ing with master */
 void replicationAbortSyncTransfer(void) {
     serverAssert(server.repl_state == REPL_STATE_TRANSFER);
@@ -1206,6 +1213,7 @@ char *sendSynchronousCommand(int flags, int fd, ...) {
             return sdscatprintf(sdsempty(),"-Reading from master: %s",
                     strerror(errno));
         }
+        server.repl_transfer_lastio = server.unixtime;
         return sdsnew(buf);
     }
     return NULL;
@@ -1636,7 +1644,7 @@ void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
     serverAssert(server.repl_state == REPL_STATE_CONNECTING ||
-                server.repl_state == REPL_STATE_RECEIVE_PONG);
+                 slaveIsInHandshakeState());
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
@@ -1655,7 +1663,7 @@ int cancelReplicationHandshake(void) {
     if (server.repl_state == REPL_STATE_TRANSFER) {
         replicationAbortSyncTransfer();
     } else if (server.repl_state == REPL_STATE_CONNECTING ||
-             server.repl_state == REPL_STATE_RECEIVE_PONG)
+               slaveIsInHandshakeState())
     {
         undoConnectWithMaster();
     } else {
@@ -1790,22 +1798,17 @@ void roleCommand(client *c) {
         addReplyBulkCBuffer(c,"slave",5);
         addReplyBulkCString(c,server.masterhost);
         addReplyLongLong(c,server.masterport);
-        switch(server.repl_state) {
-        case REPL_STATE_NONE: slavestate = "none"; break;
-        case REPL_STATE_CONNECT: slavestate = "connect"; break;
-        case REPL_STATE_CONNECTING: slavestate = "connecting"; break;
-        case REPL_STATE_RECEIVE_PONG:
-        case REPL_STATE_SEND_AUTH:
-        case REPL_STATE_RECEIVE_AUTH:
-        case REPL_STATE_SEND_PORT:
-        case REPL_STATE_RECEIVE_PORT:
-        case REPL_STATE_SEND_CAPA:
-        case REPL_STATE_RECEIVE_CAPA:
-        case REPL_STATE_SEND_PSYNC:
-        case REPL_STATE_RECEIVE_PSYNC: slavestate = "handshake"; break;
-        case REPL_STATE_TRANSFER: slavestate = "sync"; break;
-        case REPL_STATE_CONNECTED: slavestate = "connected"; break;
-        default: slavestate = "unknown"; break;
+        if (slaveIsInHandshakeState()) {
+            slavestate = "handshake";
+        } else {
+            switch(server.repl_state) {
+            case REPL_STATE_NONE: slavestate = "none"; break;
+            case REPL_STATE_CONNECT: slavestate = "connect"; break;
+            case REPL_STATE_CONNECTING: slavestate = "connecting"; break;
+            case REPL_STATE_TRANSFER: slavestate = "sync"; break;
+            case REPL_STATE_CONNECTED: slavestate = "connected"; break;
+            default: slavestate = "unknown"; break;
+            }
         }
         addReplyBulkCString(c,slavestate);
         addReplyLongLong(c,server.master ? server.master->reploff : -1);
@@ -2182,8 +2185,8 @@ void replicationCron(void) {
     /* Non blocking connection timeout? */
     if (server.masterhost &&
         (server.repl_state == REPL_STATE_CONNECTING ||
-         server.repl_state == REPL_STATE_RECEIVE_PONG) &&
-        (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
+         slaveIsInHandshakeState()) &&
+         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
         serverLog(LL_WARNING,"Timeout connecting to the MASTER...");
         undoConnectWithMaster();