@@ -484,10 +484,18 @@ int masterTryPartialResynchronization(client *c) {
     {
         /* Run id "?" is used by slaves that want to force a full resync. */
         if (master_replid[0] != '?') {
-            serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
-                "Replication ID mismatch (Slave asked for '%s', my replication "
-                "ID is '%s')",
-                master_replid, server.replid);
+            if (strcasecmp(master_replid, server.replid) &&
+                strcasecmp(master_replid, server.replid2))
+            {
+                serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
+                    "Replication ID mismatch (Slave asked for '%s', my "
+                    "replication IDs are '%s' and '%s')",
+                    master_replid, server.replid, server.replid2);
+            } else {
+                serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
+                    "Requested offset for second ID was %lld, but I can reply "
+                    "up to %lld", psync_offset, server.second_replid_offset);
+            }
         } else {
             serverLog(LL_NOTICE,"Full resync requested by slave %s",
                 replicationGetSlaveName(c));
@@ -638,7 +646,7 @@ void syncCommand(client *c) {
     /* Refuse SYNC requests if we are a slave but the link with our master
      * is not ok... */
     if (server.masterhost && server.repl_state != REPL_STATE_CONNECTED) {
-        addReplyError(c,"Can't SYNC while not connected with my master");
+        addReplySds(c,sdsnew("-NOMASTERLINK Can't SYNC while not connected with my master\r\n"));
         return;
     }
 
@@ -1393,8 +1401,9 @@ char *sendSynchronousCommand(int flags, int fd, ...) {
  *                   offset is saved.
  * PSYNC_NOT_SUPPORTED: If the server does not understand PSYNC at all and
  *                      the caller should fall back to SYNC.
- * PSYNC_WRITE_ERR: There was an error writing the command to the socket.
+ * PSYNC_WRITE_ERROR: There was an error writing the command to the socket.
  * PSYNC_WAIT_REPLY: Call again the function with read_reply set to 1.
+ * PSYNC_TRY_LATER: Master is currently in a transient error condition.
  *
  * Notable side effects:
  *
@@ -1410,6 +1419,7 @@ char *sendSynchronousCommand(int flags, int fd, ...) {
 #define PSYNC_CONTINUE 2
 #define PSYNC_FULLRESYNC 3
 #define PSYNC_NOT_SUPPORTED 4
+#define PSYNC_TRY_LATER 5
 int slaveTryPartialResynchronization(int fd, int read_reply) {
     char *psync_replid;
     char psync_offset[32];
@@ -1529,9 +1539,21 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
         return PSYNC_CONTINUE;
     }
 
-    /* If we reach this point we received either an error since the master does
-     * not understand PSYNC, or an unexpected reply from the master.
-     * Return PSYNC_NOT_SUPPORTED to the caller in both cases. */
+    /* If we reach this point we received either an error (since the master does
+     * not understand PSYNC or because it is in a special state and cannot
+     * serve our request), or an unexpected reply from the master.
+     *
+     * Return PSYNC_NOT_SUPPORTED on errors we don't understand, otherwise
+     * return PSYNC_TRY_LATER if we believe this is a transient error. */
+
+    if (!strncmp(reply,"-NOMASTERLINK",13) ||
+        !strncmp(reply,"-LOADING",8))
+    {
+        serverLog(LL_NOTICE,
+            "Master is currently unable to PSYNC "
+            "but should be in the future: %s", reply);
+        return PSYNC_TRY_LATER;
+    }
 
     if (strncmp(reply,"-ERR",4)) {
         /* If it's not an error, log the unexpected event. */
@@ -1748,6 +1770,12 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     psync_result = slaveTryPartialResynchronization(fd,1);
     if (psync_result == PSYNC_WAIT_REPLY) return; /* Try again later... */
 
+    /* If the master is in an transient error, we should try to PSYNC
+     * from scratch later, so go to the error path. This happens when
+     * the server is loading the dataset or is not connected with its
+     * master and so forth. */
+    if (psync_result == PSYNC_TRY_LATER) goto write_error;
+
     /* Note: if PSYNC does not return WAIT_REPLY, it will take care of
      * uninstalling the read handler from the file descriptor. */
 
@@ -1757,7 +1785,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     /* PSYNC failed or is not supported: we want our slaves to resync with us
-     * as well, if we have any sub-slaves. The mater may transfer us an
+     * as well, if we have any sub-slaves. The master may transfer us an
      * entirely different data set and we have no way to incrementally feed
      * our slaves after that. */
     disconnectSlaves(); /* Force our slaves to resync with us as well. */
@@ -1911,7 +1939,6 @@ void replicationSetMaster(char *ip, int port) {
      * our own parameters, to later PSYNC with the new master. */
     if (was_master) replicationCacheMasterUsingMyself();
     server.repl_state = REPL_STATE_CONNECT;
-    server.master_repl_offset = 0;
     server.repl_down_since = 0;
 }
 