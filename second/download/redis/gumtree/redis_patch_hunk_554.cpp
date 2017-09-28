  *    the new slave incremental differences will start selecting the
  *    right database number.
  *
  * Normally this function should be called immediately after a successful
  * BGSAVE for replication was started, or when there is one already in
  * progress that we attached our slave to. */
-int replicationSetupSlaveForFullResync(redisClient *slave, long long offset) {
+int replicationSetupSlaveForFullResync(client *slave, long long offset) {
     char buf[128];
     int buflen;
 
     slave->psync_initial_offset = offset;
-    slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
+    slave->replstate = SLAVE_STATE_WAIT_BGSAVE_END;
     /* We are going to accumulate the incremental changes for this
      * slave as well. Set slaveseldb to -1 in order to force to re-emit
      * a SLEECT statement in the replication stream. */
     server.slaveseldb = -1;
 
     /* Don't send this reply to slaves that approached us with
      * the old SYNC command. */
-    if (!(slave->flags & REDIS_PRE_PSYNC)) {
+    if (!(slave->flags & CLIENT_PRE_PSYNC)) {
         buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
                           server.runid,offset);
         if (write(slave->fd,buf,buflen) != buflen) {
             freeClientAsync(slave);
-            return REDIS_ERR;
+            return C_ERR;
         }
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* This function handles the PSYNC command from the point of view of a
  * master receiving a request for partial resynchronization.
  *
- * On success return REDIS_OK, otherwise REDIS_ERR is returned and we proceed
+ * On success return C_OK, otherwise C_ERR is returned and we proceed
  * with the usual full resync. */
-int masterTryPartialResynchronization(redisClient *c) {
+int masterTryPartialResynchronization(client *c) {
     long long psync_offset, psync_len;
     char *master_runid = c->argv[1]->ptr;
     char buf[128];
     int buflen;
 
     /* Is the runid of this master the same advertised by the wannabe slave
      * via PSYNC? If runid changed this master is a different instance and
      * there is no way to continue. */
     if (strcasecmp(master_runid, server.runid)) {
         /* Run id "?" is used by slaves that want to force a full resync. */
         if (master_runid[0] != '?') {
-            redisLog(REDIS_NOTICE,"Partial resynchronization not accepted: "
+            serverLog(LL_NOTICE,"Partial resynchronization not accepted: "
                 "Runid mismatch (Client asked for runid '%s', my runid is '%s')",
                 master_runid, server.runid);
         } else {
-            redisLog(REDIS_NOTICE,"Full resync requested by slave %s",
+            serverLog(LL_NOTICE,"Full resync requested by slave %s",
                 replicationGetSlaveName(c));
         }
         goto need_full_resync;
     }
 
     /* We still have the data our slave is asking for? */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&psync_offset,NULL) !=
-       REDIS_OK) goto need_full_resync;
+       C_OK) goto need_full_resync;
     if (!server.repl_backlog ||
         psync_offset < server.repl_backlog_off ||
         psync_offset > (server.repl_backlog_off + server.repl_backlog_histlen))
     {
-        redisLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Unable to partial resync with slave %s for lack of backlog (Slave request was: %lld).", replicationGetSlaveName(c), psync_offset);
         if (psync_offset > server.master_repl_offset) {
-            redisLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Warning: slave %s tried to PSYNC with an offset that is greater than the master replication offset.", replicationGetSlaveName(c));
         }
         goto need_full_resync;
     }
 
     /* If we reached this point, we are able to perform a partial resync:
      * 1) Set client state to make it a slave.
      * 2) Inform the client we can continue with +CONTINUE
      * 3) Send the backlog data (from the offset to the end) to the slave. */
-    c->flags |= REDIS_SLAVE;
-    c->replstate = REDIS_REPL_ONLINE;
+    c->flags |= CLIENT_SLAVE;
+    c->replstate = SLAVE_STATE_ONLINE;
     c->repl_ack_time = server.unixtime;
     c->repl_put_online_on_ack = 0;
     listAddNodeTail(server.slaves,c);
     /* We can't use the connection buffers since they are used to accumulate
      * new commands at this stage. But we are sure the socket send buffer is
      * empty so this write will never fail actually. */
     buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
     if (write(c->fd,buf,buflen) != buflen) {
         freeClientAsync(c);
-        return REDIS_OK;
+        return C_OK;
     }
     psync_len = addReplyReplicationBacklog(c,psync_offset);
-    redisLog(REDIS_NOTICE,
+    serverLog(LL_NOTICE,
         "Partial resynchronization request from %s accepted. Sending %lld bytes of backlog starting from offset %lld.",
             replicationGetSlaveName(c),
             psync_len, psync_offset);
     /* Note that we don't need to set the selected DB at server.slaveseldb
      * to -1 to force the master to emit SELECT, since the slave already
      * has this state from the previous connection with the master. */
 
     refreshGoodSlavesCount();
-    return REDIS_OK; /* The caller can return, no full resync needed. */
+    return C_OK; /* The caller can return, no full resync needed. */
 
 need_full_resync:
     /* We need a full resync for some reason... Note that we can't
      * reply to PSYNC right now if a full SYNC is needed. The reply
      * must include the master offset at the time the RDB file we transfer
      * is generated, so we need to delay the reply to that moment. */
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* Start a BGSAVE for replication goals, which is, selecting the disk or
  * socket target depending on the configuration, and making sure that
  * the script cache is flushed before to start.
  *
