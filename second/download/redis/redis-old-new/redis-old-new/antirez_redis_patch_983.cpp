@@ -67,6 +67,7 @@ void clusterHandleSlaveMigration(int max_slaves);
 int bitmapTestBit(unsigned char *bitmap, int pos);
 void clusterDoBeforeSleep(int flags);
 void clusterSendUpdate(clusterLink *link, clusterNode *node);
+void resetManualFailover(void);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -344,6 +345,7 @@ void clusterInit(void) {
 
     /* The slots -> keys map is a sorted set. Init it. */
     server.cluster->slots_to_keys = zslCreate();
+    resetManualFailover();
 }
 
 /* -----------------------------------------------------------------------------
@@ -1167,7 +1169,9 @@ int clusterProcessPacket(clusterLink *link) {
                 ntohl(hdr->data.publish.msg.message_len);
         if (totlen != explen) return 1;
     } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST ||
-               type == CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK) {
+               type == CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK ||
+               type == CLUSTERMSG_TYPE_MFSTART)
+    {
         uint32_t explen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
 
         if (totlen != explen) return 1;
@@ -1194,6 +1198,17 @@ int clusterProcessPacket(clusterLink *link) {
         /* Update the replication offset info for this node. */
         sender->repl_offset = ntohu64(hdr->offset);
         sender->repl_offset_time = mstime();
+        /* If we are a slave performing a manual failover and our master
+         * sent its offset while already paused, populate the MF state. */
+        if (server.cluster->mf_end &&
+            nodeIsSlave(myself) &&
+            myself->slaveof == sender &&
+            hdr->mflags[0] & CLUSTERMSG_FLAG0_PAUSED &&
+            server.cluster->mf_master_offset == 0)
+        {
+            server.cluster->mf_master_offset = sender->repl_offset;
+            redisLog(REDIS_WARNING,"Received replication offset for paused master manual failover: %lld", server.cluster->mf_master_offset);
+        }
     }
 
     /* Process packets by type. */
@@ -1464,6 +1479,18 @@ int clusterProcessPacket(clusterLink *link) {
              * we check ASAP. */
             clusterDoBeforeSleep(CLUSTER_TODO_HANDLE_FAILOVER);
         }
+    } else if (type == CLUSTERMSG_TYPE_MFSTART) {
+        /* This message is acceptable only if I'm a master and the sender
+         * is one of my slaves. */
+        if (!sender || sender->slaveof != myself) return 1;
+        /* Manual failover requested from slaves. Initialize the state
+         * accordingly. */
+        resetManualFailover();
+        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
+        server.cluster->mf_slave = sender;
+        pauseClients(mstime()+(REDIS_CLUSTER_MF_TIMEOUT*2));
+        redisLog(REDIS_WARNING,"Manual failover requested by slave %.40s.",
+            sender->name);
     } else if (type == CLUSTERMSG_TYPE_UPDATE) {
         clusterNode *n; /* The node the update is about. */
         uint64_t reportedConfigEpoch = ntohu64(hdr->data.update.nodecfg.configEpoch);
@@ -1651,6 +1678,10 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
         offset = server.master_repl_offset;
     hdr->offset = htonu64(offset);
 
+    /* Set the message flags. */
+    if (nodeIsMaster(myself) && server.cluster->mf_end)
+        hdr->mflags[0] |= CLUSTERMSG_FLAG0_PAUSED;
+
     /* Compute the message length for certain messages. For other messages
      * this is up to the caller. */
     if (type == CLUSTERMSG_TYPE_FAIL) {
@@ -1883,6 +1914,19 @@ void clusterSendFailoverAuth(clusterNode *node) {
     clusterSendMessage(node->link,buf,totlen);
 }
 
+/* Send a MFSTART message to the specified node. */
+void clusterSendMFStart(clusterNode *node) {
+    unsigned char buf[sizeof(clusterMsg)];
+    clusterMsg *hdr = (clusterMsg*) buf;
+    uint32_t totlen;
+
+    if (!node->link) return;
+    clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_MFSTART);
+    totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
+    hdr->totlen = htonl(totlen);
+    clusterSendMessage(node->link,buf,totlen);
+}
+
 /* Vote for the node asking for our vote if there are the conditions. */
 void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     clusterNode *master = node->slaveof;
@@ -1975,11 +2019,11 @@ void clusterHandleSlaveFailover(void) {
 
     /* Pre conditions to run the function:
      * 1) We are a slave.
-     * 2) Our master is flagged as FAIL.
+     * 2) Our master is flagged as FAIL, or this is a manual failover.
      * 3) It is serving slots. */
     if (nodeIsMaster(myself) ||
         myself->slaveof == NULL ||
-        !nodeFailed(myself->slaveof) ||
+        (!nodeFailed(myself->slaveof) && server.cluster->mf_end == 0) ||
         myself->slaveof->numslots == 0) return;
 
     /* Set data_age to the number of seconds we are disconnected from
@@ -2019,6 +2063,11 @@ void clusterHandleSlaveFailover(void) {
          * less updated replication offset, are penalized. */
         server.cluster->failover_auth_time +=
             server.cluster->failover_auth_rank * 1000;
+        /* However if this is a manual failover, no delay is needed. */
+        if (server.cluster->mf_end) {
+            server.cluster->failover_auth_time = mstime();
+            server.cluster->failover_auth_rank = 0;
+        }
         redisLog(REDIS_WARNING,
             "Start of election delayed for %lld milliseconds "
             "(rank #%d, offset %lld).",
@@ -2035,7 +2084,9 @@ void clusterHandleSlaveFailover(void) {
     /* It is possible that we received more updated offsets from other
      * slaves for the same master since we computed our election delay.
      * Update the delay if our rank changed. */
-    if (server.cluster->failover_auth_sent == 0) {
+    if (server.cluster->failover_auth_sent == 0 &&
+        server.cluster->mf_end == 0)
+    {
         int newrank = clusterGetSlaveRank();
         if (newrank > server.cluster->failover_auth_rank) {
             long long added_delay =
@@ -2102,6 +2153,9 @@ void clusterHandleSlaveFailover(void) {
         /* 5) Pong all the other nodes so that they can update the state
          *    accordingly and detect that we switched to master role. */
         clusterBroadcastPong(CLUSTER_BROADCAST_ALL);
+
+        /* 6) If there was a manual failover in progress, clear the state. */
+        resetManualFailover();
     }
 }
 
@@ -2191,6 +2245,79 @@ void clusterHandleSlaveMigration(int max_slaves) {
 }
 
 /* -----------------------------------------------------------------------------
+ * CLUSTER manual failover
+ *
+ * This are the important steps performed by slaves during a manual failover:
+ * 1) User send CLUSTER FAILOVER command. The failover state is initialized
+ *    setting mf_end to the millisecond unix time at which we'll abort the
+ *    attempt.
+ * 2) Slave sends a MFSTART message to the master requesting to pause clients
+ *    for two times the manual failover timeout REDIS_CLUSTER_MF_TIMEOUT.
+ *    When master is paused for manual failover, it also starts to flag
+ *    packets with CLUSTERMSG_FLAG0_PAUSED.
+ * 3) Slave waits for master to send its replication offset flagged as PAUSED.
+ * 4) If slave received the offset from the master, and its offset matches,
+ *    mf_can_start is set to 1, and clusterHandleSlaveFailover() will perform
+ *    the failover as usually, with the difference that the vote request
+ *    will be modified to force masters to vote for a slave that has a
+ *    working master.
+ *
+ * From the point of view of the master things are simpler: when a
+ * PAUSE_CLIENTS packet is received the master sets mf_end as well and
+ * the sender in mf_slave. During the time limit for the manual failover
+ * the master will just send PINGs more often to this slave, flagged with
+ * the PAUSED flag, so that the slave will set mf_master_offset when receiving
+ * a packet from the master with this flag set.
+ *
+ * The gaol of the manual failover is to perform a fast failover without
+ * data loss due to the asynchronous master-slave replication.
+ * -------------------------------------------------------------------------- */
+
+/* Reset the manual failover state. This works for both masters and slavesa
+ * as all the state about manual failover is cleared.
+ *
+ * The function can be used both to initialize the manual failover state at
+ * startup or to abort a manual failover in progress. */
+void resetManualFailover(void) {
+    if (server.cluster->mf_end && clientsArePaused()) {
+        server.clients_pause_end_time = 0;
+        clientsArePaused(); /* Just use the side effect of the function. */
+    }
+    server.cluster->mf_end = 0; /* No manual failover in progress. */
+    server.cluster->mf_can_start = 0;
+    server.cluster->mf_slave = NULL;
+    server.cluster->mf_master_offset = 0;
+}
+
+/* If a manual failover timed out, abort it. */
+void manualFailoverCheckTimeout(void) {
+    if (server.cluster->mf_end < mstime()) {
+        redisLog(REDIS_WARNING,"Manual failover timed out.");
+        resetManualFailover();
+    }
+}
+
+/* This function is called from the cluster cron function in order to go
+ * forward with a manual failover state machine. */
+void clusterHandleManualFailover(void) {
+    /* Return ASAP if no manual failover is in progress. */
+    if (server.cluster->mf_end == 0) return;
+
+    /* If mf_can_start is non-zero, the failover was alrady triggered so the
+     * next steps are performed by clusterHandleSlaveFailover(). */
+    if (server.cluster->mf_can_start) return;
+
+    if (server.cluster->mf_master_offset == 0) return; /* Wait for offset... */
+
+    if (server.cluster->mf_master_offset == replicationGetSlaveOffset()) {
+        /* Our replication offset matches the master replication offset
+         * announced after clients were paused. We can start the failover. */
+        server.cluster->mf_can_start = 1;
+        redisLog(REDIS_WARNING,"All master replication stream processed, manual failover can start.");
+    }
+}
+
+/* -----------------------------------------------------------------------------
  * CLUSTER cron job
  * -------------------------------------------------------------------------- */
 
@@ -2351,6 +2478,17 @@ void clusterCron(void) {
             continue;
         }
 
+        /* If we are a master and one of the slaves requested a manual
+         * failover, ping it continuously. */
+        if (server.cluster->mf_end &&
+            nodeIsMaster(myself) &&
+            server.cluster->mf_slave == node &&
+            node->link)
+        {
+            clusterSendPing(node->link, CLUSTERMSG_TYPE_PING);
+            continue;
+        }
+
         /* Check only if we have an active ping for this instance. */
         if (node->ping_sent == 0) continue;
 
@@ -2383,7 +2521,11 @@ void clusterCron(void) {
         replicationSetMaster(myself->slaveof->ip, myself->slaveof->port);
     }
 
+    /* Abourt a manual failover if the timeout is reached. */
+    manualFailoverCheckTimeout();
+
     if (nodeIsSlave(myself)) {
+        clusterHandleManualFailover();
         clusterHandleSlaveFailover();
         /* If there are orphaned slaves, and we are a slave among the masters
          * with the max number of non-failing slaves, consider migrating to
@@ -2700,6 +2842,7 @@ void clusterSetMaster(clusterNode *n) {
     myself->slaveof = n;
     clusterNodeAddSlave(n,myself);
     replicationSetMaster(n->ip, n->port);
+    resetManualFailover();
 }
 
 /* -----------------------------------------------------------------------------
@@ -3152,6 +3295,20 @@ void clusterCommand(redisClient *c) {
             addReplyBulkCString(c,ni);
             sdsfree(ni);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"failover") && c->argc == 2) {
+        if (nodeIsMaster(myself)) {
+            addReplyError(c,"You should send CLUSTER FAILOVER to a slave");
+            return;
+        } else if (myself->slaveof == NULL || nodeFailed(myself->slaveof) ||
+                   myself->slaveof->link == NULL)
+        {
+            addReplyError(c,"Master is down or failed, "
+                            "please use CLUSTER FAILOVER FORCE");
+            return;
+        }
+        resetManualFailover();
+        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
+        clusterSendMFStart(myself->slaveof);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");
     }