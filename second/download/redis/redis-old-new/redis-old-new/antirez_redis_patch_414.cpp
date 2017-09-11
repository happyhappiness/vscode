@@ -362,16 +362,30 @@ long long getPsyncInitialOffset(void) {
     return psync_offset;
 }
 
-/* Send a PSYNC reply in the specific case of a full resynchronization.
- * As a side effect, set into the slave client structure the offset
- * we sent here, so that if new slaves will later attach to the same
- * background RDB saving process (by duplicating this client output
- * buffer), we can get the right offset from this slave. */
-int replicationSendFullresyncReply(client *slave, long long offset) {
+/* Send a FULLRESYNC reply in the specific case of a full resynchronization,
+ * as a side effect setup the slave for a full sync in different ways:
+ *
+ * 1) Remember, into the slave client structure, the offset we sent
+ *    here, so that if new slaves will later attach to the same
+ *    background RDB saving process (by duplicating this client output
+ *    buffer), we can get the right offset from this slave.
+ * 2) Set the replication state of the slave to WAIT_BGSAVE_END so that
+ *    we start accumulating differences from this point.
+ * 3) Force the replication stream to re-emit a SELECT statement so
+ *    the new slave incremental differences will start selecting the
+ *    right database number.
+ */
+int replicationSetupSlaveForFullResync(client *slave, long long offset) {
     char buf[128];
     int buflen;
 
     slave->psync_initial_offset = offset;
+    slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
+    /* We are going to accumulate the incremental changes for this
+     * slave as well. Set slaveseldb to -1 in order to force to re-emit
+     * a SLEECT statement in the replication stream. */
+    server.slaveseldb = -1;
+
     /* Don't send this reply to slaves that approached us with
      * the old SYNC command. */
     if (!(slave->flags & CLIENT_PRE_PSYNC)) {
@@ -566,8 +580,7 @@ void syncCommand(client *c) {
             /* Perfect, the server is already registering differences for
              * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
-            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
-            replicationSendFullresyncReply(c,slave->psync_initial_offset);
+            replicationSetupSlaveForFullResync(c,slave->psync_initial_offset);
             serverLog(LL_NOTICE,"Waiting for end of BGSAVE for SYNC");
         } else {
             /* No way, we need to wait for the next BGSAVE in order to
@@ -603,16 +616,14 @@ void syncCommand(client *c) {
                 addReplyError(c,"Unable to perform background save");
                 return;
             }
-            c->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
-            replicationSendFullresyncReply(c,getPsyncInitialOffset());
+            replicationSetupSlaveForFullResync(c,getPsyncInitialOffset());
         }
     }
 
     if (server.repl_disable_tcp_nodelay)
         anetDisableTcpNoDelay(NULL, c->fd); /* Non critical if it fails. */
     c->repldbfd = -1;
     c->flags |= CLIENT_SLAVE;
-    server.slaveseldb = -1; /* Force to re-emit the SELECT command. */
     listAddNodeTail(server.slaves,c);
     if (listLength(server.slaves) == 1 && server.repl_backlog == NULL)
         createReplicationBacklog();
@@ -791,8 +802,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
 
         if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
             startbgsave = 1;
-            slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
-            replicationSendFullresyncReply(slave,getPsyncInitialOffset());
+            replicationSetupSlaveForFullResync(slave,getPsyncInitialOffset());
         } else if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_END) {
             struct redis_stat buf;
 
@@ -2156,8 +2166,7 @@ void replicationCron(void) {
                 while((ln = listNext(&li))) {
                     client *slave = ln->value;
                     if (slave->replstate == SLAVE_STATE_WAIT_BGSAVE_START) {
-                        slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
-                        replicationSendFullresyncReply(slave,
+                        replicationSetupSlaveForFullResync(slave,
                             getPsyncInitialOffset());
                     }
                 }