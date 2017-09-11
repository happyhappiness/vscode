@@ -349,6 +349,41 @@ long long addReplyReplicationBacklog(client *c, long long offset) {
     return server.repl_backlog_histlen - skip;
 }
 
+/* Return the offset to provide as reply to the PSYNC command received
+ * from the slave. The returned value is only valid immediately after
+ * the BGSAVE process started and before executing any other command
+ * from clients. */
+long long getPsyncInitialOffset(void) {
+    long long psync_offset = server.master_repl_offset;
+    /* Add 1 to psync_offset if it the replication backlog does not exists
+     * as when it will be created later we'll increment the offset by one. */
+    if (server.repl_backlog == NULL) psync_offset++;
+    return psync_offset;
+}
+
+/* Send a PSYNC reply in the specific case of a full resynchronization.
+ * As a side effect, set into the slave client structure the offset
+ * we sent here, so that if new slaves will later attach to the same
+ * background RDB saving process (by duplicating this client output
+ * buffer), we can get the right offset from this slave. */
+int replicationSendFullresyncReply(client *slave, long long offset) {
+    char buf[128];
+    int buflen;
+
+    slave->psync_initial_offset = offset;
+    /* Don't send this reply to slaves that approached us with
+     * the old SYNC command. */
+    if (!(slave->flags & CLIENT_PRE_PSYNC)) {
+        buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
+                          server.runid,offset);
+        if (write(slave->fd,buf,buflen) != buflen) {
+            freeClientAsync(slave);
+            return C_ERR;
+        }
+    }
+    return C_OK;
+}
+
 /* This function handles the PSYNC command from the point of view of a
  * master receiving a request for partial resynchronization.
  *
@@ -422,18 +457,10 @@ int masterTryPartialResynchronization(client *c) {
     return C_OK; /* The caller can return, no full resync needed. */
 
 need_full_resync:
-    /* We need a full resync for some reason... notify the client. */
-    psync_offset = server.master_repl_offset;
-    /* Add 1 to psync_offset if it the replication backlog does not exists
-     * as when it will be created later we'll increment the offset by one. */
-    if (server.repl_backlog == NULL) psync_offset++;
-    /* Again, we can't use the connection buffers (see above). */
-    buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
-                      server.runid,psync_offset);
-    if (write(c->fd,buf,buflen) != buflen) {
-        freeClientAsync(c);
-        return C_OK;
-    }
+    /* We need a full resync for some reason... Note that we can't
+     * reply to PSYNC right now if a full SYNC is needed. The reply
+     * must include the master offset at the time the RDB file we transfer
+     * is generated, so we need to delay the reply to that moment. */
     return C_ERR;
 }
 
@@ -537,6 +564,7 @@ void syncCommand(client *c) {
              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
             c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+            replicationSendFullresyncReply(c,slave->psync_initial_offset);
             serverLog(LL_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
@@ -568,6 +596,7 @@ void syncCommand(client *c) {
                 return;
             }
             c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+            replicationSendFullresyncReply(c,getPsyncInitialOffset());
         }
     }
 
@@ -755,6 +784,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
         if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
             startbgsave = 1;
             slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+            replicationSendFullresyncReply(slave,getPsyncInitialOffset());
         } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
@@ -2117,8 +2147,11 @@ void replicationCron(void) {
                 listRewind(server.slaves,&li);
                 while((ln = listNext(&li))) {
                     client *slave = ln->value;
-                    if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START)
+                    if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
                         slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+                        replicationSendFullresyncReply(slave,
+                            getPsyncInitialOffset());
+                    }
                 }
             }
         }