@@ -1218,6 +1218,14 @@ char *sendSynchronousCommand(int flags, int fd, ...) {
  *                      the caller should fall back to SYNC.
  * PSYNC_WRITE_ERR: There was an error writing the command to the socket.
  * PSYNC_WAIT_REPLY: Call again the function with read_reply set to 1.
+ *
+ * Notable side effects:
+ *
+ * 1) As a side effect of the function call the function removes the readable
+ *    event handler from "fd", unless the return value is PSYNC_WAIT_REPLY.
+ * 2) server.repl_master_initial_offset is set to the right value according
+ *    to the master reply. This will be used to populate the 'server.master'
+ *    structure replication offset.
  */
 
 #define PSYNC_WRITE_ERROR 0
@@ -1254,6 +1262,7 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
         if (reply != NULL) {
             serverLog(LL_WARNING,"Unable to send PSYNC to master: %s",reply);
             sdsfree(reply);
+            aeDeleteFileEvent(server.el,fd,AE_READABLE);
             return PSYNC_WRITE_ERROR;
         }
         return PSYNC_WAIT_REPLY;
@@ -1268,6 +1277,8 @@ int slaveTryPartialResynchronization(int fd, int read_reply) {
         return PSYNC_WAIT_REPLY;
     }
 
+    aeDeleteFileEvent(server.el,fd,AE_READABLE);
+
     if (!strncmp(reply,"+FULLRESYNC",11)) {
         char *runid = NULL, *offset = NULL;
 
@@ -1348,7 +1359,6 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &sockerr, &errlen) == -1)
         sockerr = errno;
     if (sockerr) {
-        aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
         serverLog(LL_WARNING,"Error condition on socket for SYNC: %s",
             strerror(sockerr));
         goto error;
@@ -1490,20 +1500,11 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
         goto error;
     }
 
-    /* Delete the readable event, we no longer need it now that there is
-     * the last reply to read. */
-    aeDeleteFileEvent(server.el,fd,AE_READABLE);
     psync_result = slaveTryPartialResynchronization(fd,1);
-    if (psync_result == PSYNC_WAIT_REPLY) {
-        if (aeCreateFileEvent(server.el,fd,AE_READABLE,
-            syncWithMaster,NULL) == AE_ERR)
-        {
-            serverLog(LL_WARNING,"Failed to reinstall the read event in "
-                                 "PSYNC_WAIT_REPLY state.");
-            goto error;
-        }
-        return; /* Try again later... */
-    }
+    if (psync_result == PSYNC_WAIT_REPLY) return; /* Try again later... */
+
+    /* Note: if PSYNC does not return WAIT_REPLY, it will take care of
+     * uninstalling the read handler from the file descriptor. */
 
     if (psync_result == PSYNC_CONTINUE) {
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
@@ -1562,6 +1563,7 @@ void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
     return;
 
 error:
+    aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
     server.repl_state = REPL_STATE_CONNECT;