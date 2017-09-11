@@ -40,15 +40,15 @@
 void replicationDiscardCachedMaster(void);
 void replicationResurrectCachedMaster(int newfd);
 void replicationSendAck(void);
-void putSlaveOnline(redisClient *slave);
+void putSlaveOnline(client *slave);
 
 /* --------------------------- Utility functions ---------------------------- */
 
 /* Return the pointer to a string representing the slave ip:listening_port
  * pair. Mostly useful for logging, since we want to log a slave using its
  * IP address and it's listening port which is more clear for the user, for
  * example: "Closing connection with slave 10.1.2.3:6380". */
-char *replicationGetSlaveName(redisClient *c) {
+char *replicationGetSlaveName(client *c) {
     static char buf[REDIS_PEER_ID_LEN];
     char ip[REDIS_IP_STR_LEN];
 
@@ -200,7 +200,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
         /* Send it to slaves. */
         listRewind(slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
+            client *slave = ln->value;
             addReply(slave,selectcmd);
         }
 
@@ -239,7 +239,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     /* Write the command to every slave. */
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
 
         /* Don't feed slaves that are still waiting for BGSAVE to start */
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) continue;
@@ -258,7 +258,7 @@ void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc) {
     }
 }
 
-void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
+void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
     int j;
@@ -291,15 +291,15 @@ void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **
 
     listRewind(monitors,&li);
     while((ln = listNext(&li))) {
-        redisClient *monitor = ln->value;
+        client *monitor = ln->value;
         addReply(monitor,cmdobj);
     }
     decrRefCount(cmdobj);
 }
 
 /* Feed the slave 'c' with the replication backlog starting from the
  * specified 'offset' up to the end of the backlog. */
-long long addReplyReplicationBacklog(redisClient *c, long long offset) {
+long long addReplyReplicationBacklog(client *c, long long offset) {
     long long j, skip, len;
 
     serverLog(REDIS_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
@@ -354,7 +354,7 @@ long long addReplyReplicationBacklog(redisClient *c, long long offset) {
  *
  * On success return REDIS_OK, otherwise REDIS_ERR is returned and we proceed
  * with the usual full resync. */
-int masterTryPartialResynchronization(redisClient *c) {
+int masterTryPartialResynchronization(client *c) {
     long long psync_offset, psync_len;
     char *master_runid = c->argv[1]->ptr;
     char buf[128];
@@ -460,7 +460,7 @@ int startBgsaveForReplication(void) {
 }
 
 /* SYNC and PSYNC command implemenation. */
-void syncCommand(redisClient *c) {
+void syncCommand(client *c) {
     /* ignore SYNC if already slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
 
@@ -523,7 +523,7 @@ void syncCommand(redisClient *c) {
         /* Ok a background save is in progress. Let's check if it is a good
          * one for replication, i.e. if there is another slave that is
          * registering differences since the server forked to save. */
-        redisClient *slave;
+        client *slave;
         listNode *ln;
         listIter li;
 
@@ -594,7 +594,7 @@ void syncCommand(redisClient *c) {
  * In the future the same command can be used in order to configure
  * the replication to initiate an incremental replication instead of a
  * full resync. */
-void replconfCommand(redisClient *c) {
+void replconfCommand(client *c) {
     int j;
 
     if ((c->argc % 2) == 0) {
@@ -658,7 +658,7 @@ void replconfCommand(redisClient *c) {
  *    command disables it, so that we can accumulate output buffer without
  *    sending it to the slave.
  * 3) Update the count of good slaves. */
-void putSlaveOnline(redisClient *slave) {
+void putSlaveOnline(client *slave) {
     slave->replstate = REDIS_REPL_ONLINE;
     slave->repl_put_online_on_ack = 0;
     slave->repl_ack_time = server.unixtime; /* Prevent false timeout. */
@@ -674,7 +674,7 @@ void putSlaveOnline(redisClient *slave) {
 }
 
 void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
-    redisClient *slave = privdata;
+    client *slave = privdata;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
     char buf[REDIS_IOBUF_LEN];
@@ -750,7 +750,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
 
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
             startbgsave = 1;
@@ -808,7 +808,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
             listRewind(server.slaves,&li);
             serverLog(REDIS_WARNING,"SYNC failed. BGSAVE failed");
             while((ln = listNext(&li))) {
-                redisClient *slave = ln->value;
+                client *slave = ln->value;
 
                 if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
                     freeClient(slave);
@@ -1477,7 +1477,7 @@ void replicationUnsetMaster(void) {
     server.repl_state = REDIS_REPL_NONE;
 }
 
-void slaveofCommand(redisClient *c) {
+void slaveofCommand(client *c) {
     /* SLAVEOF is not allowed in cluster mode as replication is automatically
      * configured using the current address of the master node. */
     if (server.cluster_enabled) {
@@ -1518,7 +1518,7 @@ void slaveofCommand(redisClient *c) {
 /* ROLE command: provide information about the role of the instance
  * (master or slave) and additional information related to replication
  * in an easy to process format. */
-void roleCommand(redisClient *c) {
+void roleCommand(client *c) {
     if (server.masterhost == NULL) {
         listIter li;
         listNode *ln;
@@ -1531,7 +1531,7 @@ void roleCommand(redisClient *c) {
         mbcount = addDeferredMultiBulkLength(c);
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
+            client *slave = ln->value;
             char ip[REDIS_IP_STR_LEN];
 
             if (anetPeerToString(slave->fd,ip,sizeof(ip),NULL) == -1) continue;
@@ -1568,7 +1568,7 @@ void roleCommand(redisClient *c) {
  * processed offset. If we are not connected with a master, the command has
  * no effects. */
 void replicationSendAck(void) {
-    redisClient *c = server.master;
+    client *c = server.master;
 
     if (c != NULL) {
         c->flags |= REDIS_MASTER_FORCE_REPLY;
@@ -1600,7 +1600,7 @@ void replicationSendAck(void) {
  * replicationResurrectCachedMaster() that is used after a successful PSYNC
  * handshake in order to reactivate the cached master.
  */
-void replicationCacheMaster(redisClient *c) {
+void replicationCacheMaster(client *c) {
     listNode *ln;
 
     redisAssert(server.master != NULL && server.cached_master == NULL);
@@ -1697,7 +1697,7 @@ void refreshGoodSlavesCount(void) {
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
         time_t lag = server.unixtime - slave->repl_ack_time;
 
         if (slave->replstate == REDIS_REPL_ONLINE &&
@@ -1833,7 +1833,7 @@ int replicationCountAcksByOffset(long long offset) {
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
 
         if (slave->replstate != REDIS_REPL_ONLINE) continue;
         if (slave->repl_ack_off >= offset) count++;
@@ -1843,7 +1843,7 @@ int replicationCountAcksByOffset(long long offset) {
 
 /* WAIT for N replicas to acknowledge the processing of our latest
  * write command (and all the previous commands). */
-void waitCommand(redisClient *c) {
+void waitCommand(client *c) {
     mstime_t timeout;
     long numreplicas, ackreplicas;
     long long offset = c->woff;
@@ -1878,7 +1878,7 @@ void waitCommand(redisClient *c) {
  * specific cleanup. We just remove the client from the list of clients
  * waiting for replica acks. Never call it directly, call unblockClient()
  * instead. */
-void unblockClientWaitingReplicas(redisClient *c) {
+void unblockClientWaitingReplicas(client *c) {
     listNode *ln = listSearchKey(server.clients_waiting_acks,c);
     redisAssert(ln != NULL);
     listDelNode(server.clients_waiting_acks,ln);
@@ -1895,7 +1895,7 @@ void processClientsWaitingReplicas(void) {
 
     listRewind(server.clients_waiting_acks,&li);
     while((ln = listNext(&li))) {
-        redisClient *c = ln->value;
+        client *c = ln->value;
 
         /* Every time we find a client that is satisfied for a given
          * offset and number of replicas, we remember it so the next client
@@ -2005,7 +2005,7 @@ void replicationCron(void) {
          * last-io timer preventing a timeout. */
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
+            client *slave = ln->value;
 
             if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START ||
                 (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END &&
@@ -2025,7 +2025,7 @@ void replicationCron(void) {
 
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
+            client *slave = ln->value;
 
             if (slave->replstate != REDIS_REPL_ONLINE) continue;
             if (slave->flags & REDIS_PRE_PSYNC) continue;
@@ -2079,7 +2079,7 @@ void replicationCron(void) {
 
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = ln->value;
+            client *slave = ln->value;
             if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
                 idle = server.unixtime - slave->lastinteraction;
                 if (idle > max_idle) max_idle = idle;
@@ -2098,7 +2098,7 @@ void replicationCron(void) {
                  * startBgsaveForReplication(). */
                 listRewind(server.slaves,&li);
                 while((ln = listNext(&li))) {
-                    redisClient *slave = ln->value;
+                    client *slave = ln->value;
                     if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START)
                         slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
                 }