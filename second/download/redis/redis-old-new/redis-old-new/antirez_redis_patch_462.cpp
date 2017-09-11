@@ -352,7 +352,7 @@ long long addReplyReplicationBacklog(client *c, long long offset) {
 /* This function handles the PSYNC command from the point of view of a
  * master receiving a request for partial resynchronization.
  *
- * On success return REDIS_OK, otherwise REDIS_ERR is returned and we proceed
+ * On success return C_OK, otherwise C_ERR is returned and we proceed
  * with the usual full resync. */
 int masterTryPartialResynchronization(client *c) {
     long long psync_offset, psync_len;
@@ -378,7 +378,7 @@ int masterTryPartialResynchronization(client *c) {
 
     /* We still have the data our slave is asking for? */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&psync_offset,NULL) !=
-       REDIS_OK) goto need_full_resync;
+       C_OK) goto need_full_resync;
     if (!server.repl_backlog ||
         psync_offset < server.repl_backlog_off ||
         psync_offset > (server.repl_backlog_off + server.repl_backlog_histlen))
@@ -407,7 +407,7 @@ int masterTryPartialResynchronization(client *c) {
     buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
     if (write(c->fd,buf,buflen) != buflen) {
         freeClientAsync(c);
-        return REDIS_OK;
+        return C_OK;
     }
     psync_len = addReplyReplicationBacklog(c,psync_offset);
     serverLog(REDIS_NOTICE,
@@ -419,7 +419,7 @@ int masterTryPartialResynchronization(client *c) {
      * has this state from the previous connection with the master. */
 
     refreshGoodSlavesCount();
-    return REDIS_OK; /* The caller can return, no full resync needed. */
+    return C_OK; /* The caller can return, no full resync needed. */
 
 need_full_resync:
     /* We need a full resync for some reason... notify the client. */
@@ -432,16 +432,16 @@ int masterTryPartialResynchronization(client *c) {
                       server.runid,psync_offset);
     if (write(c->fd,buf,buflen) != buflen) {
         freeClientAsync(c);
-        return REDIS_OK;
+        return C_OK;
     }
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* Start a BGSAVE for replication goals, which is, selecting the disk or
  * socket target depending on the configuration, and making sure that
  * the script cache is flushed before to start.
  *
- * Returns REDIS_OK on success or REDIS_ERR otherwise. */
+ * Returns C_OK on success or C_ERR otherwise. */
 int startBgsaveForReplication(void) {
     int retval;
 
@@ -455,7 +455,7 @@ int startBgsaveForReplication(void) {
 
     /* Flush the script cache, since we need that slave differences are
      * accumulated without requiring slaves to match our cached scripts. */
-    if (retval == REDIS_OK) replicationScriptCacheFlush();
+    if (retval == C_OK) replicationScriptCacheFlush();
     return retval;
 }
 
@@ -493,7 +493,7 @@ void syncCommand(client *c) {
      * So the slave knows the new runid and offset to try a PSYNC later
      * if the connection with the master is lost. */
     if (!strcasecmp(c->argv[0]->ptr,"psync")) {
-        if (masterTryPartialResynchronization(c) == REDIS_OK) {
+        if (masterTryPartialResynchronization(c) == C_OK) {
             server.stat_sync_partial_ok++;
             return; /* No full resync needed, return. */
         } else {
@@ -562,7 +562,7 @@ void syncCommand(client *c) {
                 serverLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
             /* Ok we don't have a BGSAVE in progress, let's start one. */
-            if (startBgsaveForReplication() != REDIS_OK) {
+            if (startBgsaveForReplication() != C_OK) {
                 serverLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
                 addReplyError(c,"Unable to perform background save");
                 return;
@@ -610,7 +610,7 @@ void replconfCommand(client *c) {
             long port;
 
             if ((getLongFromObjectOrReply(c,c->argv[j+1],
-                    &port,NULL) != REDIS_OK))
+                    &port,NULL) != C_OK))
                 return;
             c->slave_listening_port = port;
         } else if (!strcasecmp(c->argv[j]->ptr,"ack")) {
@@ -620,7 +620,7 @@ void replconfCommand(client *c) {
             long long offset;
 
             if (!(c->flags & REDIS_SLAVE)) return;
-            if ((getLongLongFromObject(c->argv[j+1], &offset) != REDIS_OK))
+            if ((getLongLongFromObject(c->argv[j+1], &offset) != C_OK))
                 return;
             if (offset > c->repl_ack_off)
                 c->repl_ack_off = offset;
@@ -739,8 +739,8 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
  * BGSAVE was in progress, but it was not a good one for replication (no
  * other slave was accumulating differences).
  *
- * The argument bgsaveerr is REDIS_OK if the background saving succeeded
- * otherwise REDIS_ERR is passed to the function.
+ * The argument bgsaveerr is C_OK if the background saving succeeded
+ * otherwise C_ERR is passed to the function.
  * The 'type' argument is the type of the child that terminated
  * (if it had a disk or socket target). */
 void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
@@ -776,7 +776,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
                 slave->repl_put_online_on_ack = 1;
                 slave->repl_ack_time = server.unixtime; /* Timeout otherwise. */
             } else {
-                if (bgsaveerr != REDIS_OK) {
+                if (bgsaveerr != C_OK) {
                     freeClient(slave);
                     serverLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
                     continue;
@@ -802,7 +802,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
         }
     }
     if (startbgsave) {
-        if (startBgsaveForReplication() != REDIS_OK) {
+        if (startBgsaveForReplication() != C_OK) {
             listIter li;
 
             listRewind(server.slaves,&li);
@@ -1028,7 +1028,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
         serverLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
-        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
+        if (rdbLoad(server.rdb_filename) != C_OK) {
             serverLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             replicationAbortSyncTransfer();
             return;
@@ -1045,7 +1045,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
             int retry = 10;
 
             stopAppendOnly();
-            while (retry-- && startAppendOnly() == REDIS_ERR) {
+            while (retry-- && startAppendOnly() == C_ERR) {
                 serverLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                 sleep(1);
             }
@@ -1389,21 +1389,21 @@ int connectWithMaster(void) {
     if (fd == -1) {
         serverLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
             strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,syncWithMaster,NULL) ==
             AE_ERR)
     {
         close(fd);
         serverLog(REDIS_WARNING,"Can't create readable event for SYNC");
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     server.repl_transfer_lastio = server.unixtime;
     server.repl_transfer_s = fd;
     server.repl_state = REDIS_REPL_CONNECTING;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* This function can be called when a non blocking connection is currently
@@ -1496,7 +1496,7 @@ void slaveofCommand(client *c) {
     } else {
         long port;
 
-        if ((getLongFromObjectOrReply(c, c->argv[2], &port, NULL) != REDIS_OK))
+        if ((getLongFromObjectOrReply(c, c->argv[2], &port, NULL) != C_OK))
             return;
 
         /* Check if we are already attached to the specified slave */
@@ -1849,10 +1849,10 @@ void waitCommand(client *c) {
     long long offset = c->woff;
 
     /* Argument parsing. */
-    if (getLongFromObjectOrReply(c,c->argv[1],&numreplicas,NULL) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[1],&numreplicas,NULL) != C_OK)
         return;
     if (getTimeoutFromObjectOrReply(c,c->argv[2],&timeout,UNIT_MILLISECONDS)
-        != REDIS_OK) return;
+        != C_OK) return;
 
     /* First try without blocking at all. */
     ackreplicas = replicationCountAcksByOffset(c->woff);
@@ -1973,7 +1973,7 @@ void replicationCron(void) {
     if (server.repl_state == REDIS_REPL_CONNECT) {
         serverLog(REDIS_NOTICE,"Connecting to MASTER %s:%d",
             server.masterhost, server.masterport);
-        if (connectWithMaster() == REDIS_OK) {
+        if (connectWithMaster() == C_OK) {
             serverLog(REDIS_NOTICE,"MASTER <-> SLAVE sync started");
         }
     }
@@ -2090,7 +2090,7 @@ void replicationCron(void) {
         if (slaves_waiting && max_idle > server.repl_diskless_sync_delay) {
             /* Start a BGSAVE. Usually with socket target, or with disk target
              * if there was a recent socket -> disk config change. */
-            if (startBgsaveForReplication() == REDIS_OK) {
+            if (startBgsaveForReplication() == C_OK) {
                 /* It started! We need to change the state of slaves
                  * from WAIT_BGSAVE_START to WAIT_BGSAVE_END in case
                  * the current target is disk. Otherwise it was already done