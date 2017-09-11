@@ -765,13 +765,12 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
     int failures;
     int needed_quorum = (server.cluster->size / 2) + 1;
 
-    if (!(node->flags & REDIS_NODE_PFAIL)) return; /* We can reach it. */
-    if (node->flags & REDIS_NODE_FAIL) return; /* Already FAILing. */
+    if (!nodeTimedOut(node)) return; /* We can reach it. */
+    if (nodeFailed(node)) return; /* Already FAILing. */
 
     failures = clusterNodeFailureReportsCount(node);
     /* Also count myself as a voter if I'm a master. */
-    if (myself->flags & REDIS_NODE_MASTER)
-        failures += 1;
+    if (nodeIsMaster(myself)) failures++;
     if (failures < needed_quorum) return; /* No weak agreement from masters. */
 
     redisLog(REDIS_NOTICE,
@@ -784,7 +783,7 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
 
     /* Broadcast the failing node name to everybody, forcing all the other
      * reachable nodes to flag the node as FAIL. */
-    if (myself->flags & REDIS_NODE_MASTER) clusterSendFail(node->name);
+    if (nodeIsMaster(myself)) clusterSendFail(node->name);
     clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
 }
 
@@ -794,11 +793,11 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
 void clearNodeFailureIfNeeded(clusterNode *node) {
     mstime_t now = mstime();
 
-    redisAssert(node->flags & REDIS_NODE_FAIL);
+    redisAssert(nodeFailed(node));
 
     /* For slaves we always clear the FAIL flag if we can contact the
      * node again. */
-    if (node->flags & REDIS_NODE_SLAVE) {
+    if (nodeIsSlave(node)) {
         redisLog(REDIS_NOTICE,
             "Clear FAIL state for node %.40s: slave is reachable again.",
                 node->name);
@@ -810,8 +809,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
      * 1) The FAIL state is old enough.
      * 2) It is yet serving slots from our point of view (not failed over).
      * Apparently no one is going to fix these slots, clear the FAIL flag. */
-    if (node->flags & REDIS_NODE_MASTER &&
-        node->numslots > 0 &&
+    if (nodeIsMaster(node) && node->numslots > 0 &&
         (now - node->fail_time) >
         (server.cluster_node_timeout * REDIS_CLUSTER_FAIL_UNDO_TIME_MULT))
     {
@@ -834,7 +832,7 @@ int clusterHandshakeInProgress(char *ip, int port) {
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
-        if (!(node->flags & REDIS_NODE_HANDSHAKE)) continue;
+        if (!nodeInHandshake(node)) continue;
         if (!strcasecmp(node->ip,ip) && node->port == port) break;
     }
     dictReleaseIterator(di);
@@ -935,7 +933,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         if (node) {
             /* We already know this node.
                Handle failure reports, only when the sender is a master. */
-            if (sender && sender->flags & REDIS_NODE_MASTER && node != myself) {
+            if (sender && nodeIsMaster(sender) && node != myself) {
                 if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
                     if (clusterNodeAddFailureReport(node,sender)) {
                         redisLog(REDIS_VERBOSE,
@@ -1033,7 +1031,7 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
 
     /* Check if this is our master and we have to change the
      * replication target as well. */
-    if (myself->flags & REDIS_NODE_SLAVE && myself->slaveof == node)
+    if (nodeIsSlave(myself) && myself->slaveof == node)
         replicationSetMaster(node->ip, node->port);
     return 1;
 }
@@ -1042,7 +1040,7 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
  * a node that we believed to be a slave is now acting as master in order to
  * update the state of the node. */
 void clusterSetNodeAsMaster(clusterNode *n) {
-    if (n->flags & REDIS_NODE_MASTER) return;
+    if (nodeIsMaster(n)) return;
 
     if (n->slaveof) clusterNodeRemoveSlave(n->slaveof,n);
     n->flags &= ~REDIS_NODE_SLAVE;
@@ -1074,10 +1072,7 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
     /* Here we set curmaster to this node or the node this node
      * replicates to if it's a slave. In the for loop we are
      * interested to check if slots are taken away from curmaster. */
-    if (myself->flags & REDIS_NODE_MASTER)
-        curmaster = myself;
-    else
-        curmaster = myself->slaveof;
+    curmaster = nodeIsMaster(myself) ? myself : myself->slaveof;
 
     for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
         if (bitmapTestBit(slots,j)) {
@@ -1175,7 +1170,7 @@ int clusterProcessPacket(clusterLink *link) {
 
     /* Check if the sender is a known node. */
     sender = clusterLookupNode(hdr->sender);
-    if (sender && !(sender->flags & REDIS_NODE_HANDSHAKE)) {
+    if (sender && !nodeInHandshake(sender)) {
         /* Update our curretEpoch if we see a newer epoch in the cluster. */
         senderCurrentEpoch = ntohu64(hdr->currentEpoch);
         senderConfigEpoch = ntohu64(hdr->configEpoch);
@@ -1221,7 +1216,7 @@ int clusterProcessPacket(clusterLink *link) {
             type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
             (void*)link->node);
         if (link->node) {
-            if (link->node->flags & REDIS_NODE_HANDSHAKE) {
+            if (nodeInHandshake(link->node)) {
                 /* If we already have this node, try to change the
                  * IP/port of the node with the new one. */
                 if (sender) {
@@ -1264,7 +1259,7 @@ int clusterProcessPacket(clusterLink *link) {
 
         /* Update the node address if it changed. */
         if (sender && type == CLUSTERMSG_TYPE_PING &&
-            !(sender->flags & REDIS_NODE_HANDSHAKE) &&
+            !nodeInHandshake(sender) &&
             nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
         {
             clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
@@ -1281,11 +1276,11 @@ int clusterProcessPacket(clusterLink *link) {
              *
              * The FAIL condition is also reversible under specific
              * conditions detected by clearNodeFailureIfNeeded(). */
-            if (link->node->flags & REDIS_NODE_PFAIL) {
+            if (nodeTimedOut(link->node)) {
                 link->node->flags &= ~REDIS_NODE_PFAIL;
                 clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                      CLUSTER_TODO_UPDATE_STATE);
-            } else if (link->node->flags & REDIS_NODE_FAIL) {
+            } else if (nodeFailed(link->node)) {
                 clearNodeFailureIfNeeded(link->node);
             }
         }
@@ -1301,7 +1296,7 @@ int clusterProcessPacket(clusterLink *link) {
                 /* Node is a slave. */
                 clusterNode *master = clusterLookupNode(hdr->slaveof);
 
-                if (sender->flags & REDIS_NODE_MASTER) {
+                if (nodeIsMaster(sender)) {
                     /* Master turned into a slave! Reconfigure the node. */
                     clusterDelNodeSlots(sender);
                     sender->flags &= ~REDIS_NODE_MASTER;
@@ -1341,8 +1336,7 @@ int clusterProcessPacket(clusterLink *link) {
         int dirty_slots = 0; /* Sender claimed slots don't match my view? */
 
         if (sender) {
-            sender_master = (sender->flags & REDIS_NODE_MASTER) ?
-                sender : sender->slaveof;
+            sender_master = nodeIsMaster(sender) ? sender : sender->slaveof;
             if (sender_master) {
                 dirty_slots = memcmp(sender_master->slots,
                         hdr->myslots,sizeof(hdr->myslots)) != 0;
@@ -1352,9 +1346,8 @@ int clusterProcessPacket(clusterLink *link) {
         /* 1) If the sender of the message is a master, and we detected that
          *    the set of slots it claims changed, scan the slots to see if we
          *    need to update our configuration. */
-        if (sender && sender->flags & REDIS_NODE_MASTER && dirty_slots) {
+        if (sender && nodeIsMaster(sender) && dirty_slots)
             clusterUpdateSlotsConfigWith(sender,senderConfigEpoch,hdr->myslots);
-        }
 
         /* 2) We also check for the reverse condition, that is, the sender
          *    claims to serve slots we know are served by a master with a
@@ -1450,8 +1443,7 @@ int clusterProcessPacket(clusterLink *link) {
         /* We consider this vote only if the sender is a master serving
          * a non zero number of slots, and its currentEpoch is greater or
          * equal to epoch where this node started the election. */
-        if (sender->flags & REDIS_NODE_MASTER &&
-            sender->numslots > 0 &&
+        if (nodeIsMaster(sender) && sender->numslots > 0 &&
             senderCurrentEpoch >= server.cluster->failover_auth_epoch)
         {
             server.cluster->failover_auth_count++;
@@ -1469,7 +1461,7 @@ int clusterProcessPacket(clusterLink *link) {
         if (n->configEpoch >= reportedConfigEpoch) return 1; /* Nothing new. */
 
         /* If in our current config the node is a slave, set it as a master. */
-        if (n->flags & REDIS_NODE_SLAVE) clusterSetNodeAsMaster(n);
+        if (nodeIsSlave(n)) clusterSetNodeAsMaster(n);
 
         /* Check the bitmap of served slots and udpate our
          * config accordingly. */
@@ -1620,7 +1612,7 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
      * If this node is a slave we send the master's information instead (the
      * node is flagged as slave so the receiver knows that it is NOT really
      * in charge for this slots. */
-    master = (myself->flags & REDIS_NODE_SLAVE && myself->slaveof) ?
+    master = (nodeIsSlave(myself) && myself->slaveof) ?
               myself->slaveof : myself;
 
     memset(hdr,0,sizeof(*hdr));
@@ -1640,7 +1632,7 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     hdr->configEpoch = htonu64(master->configEpoch);
 
     /* Set the replication offset. */
-    if (myself->flags & REDIS_NODE_SLAVE) {
+    if (nodeIsSlave(myself)) {
         if (server.master)
             offset = server.master->reploff;
         else if (server.cached_master)
@@ -1754,11 +1746,10 @@ void clusterBroadcastPong(int target) {
         clusterNode *node = dictGetVal(de);
 
         if (!node->link) continue;
-        if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE)) continue;
+        if (node == myself || nodeInHandshake(node)) continue;
         if (target == CLUSTER_BROADCAST_LOCAL_SLAVES) {
             int local_slave =
-                node->flags & REDIS_NODE_SLAVE &&
-                node->slaveof &&
+                nodeIsSlave(node) && node->slaveof &&
                 (node->slaveof == myself || node->slaveof == myself->slaveof);
             if (!local_slave) continue;
         }
@@ -1897,8 +1888,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
      * right to vote, as the cluster size in Redis Cluster is the number
      * of masters serving at least one slot, and quorum is the cluster
      * size + 1 */
-    if (!(myself->flags & REDIS_NODE_MASTER)) return;
-    if (myself->numslots == 0) return;
+    if (nodeIsSlave(myself) || myself->numslots == 0) return;
 
     /* Request epoch must be >= our currentEpoch. */
     if (requestCurrentEpoch < server.cluster->currentEpoch) return;
@@ -1907,9 +1897,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) return;
 
     /* Node must be a slave and its master down. */
-    if (!(node->flags & REDIS_NODE_SLAVE) ||
-        master == NULL ||
-        !(master->flags & REDIS_NODE_FAIL)) return;
+    if (nodeIsMaster(node) || master == NULL || !nodeFailed(master)) return;
 
     /* We did not voted for a slave about this master for two
      * times the node timeout. This is not strictly needed for correctness
@@ -1962,9 +1950,9 @@ void clusterHandleSlaveFailover(void) {
      * 1) We are a slave.
      * 2) Our master is flagged as FAIL.
      * 3) It is serving slots. */
-    if (!(myself->flags & REDIS_NODE_SLAVE) ||
+    if (nodeIsMaster(myself) ||
         myself->slaveof == NULL ||
-        !(myself->slaveof->flags & REDIS_NODE_FAIL) ||
+        !nodeFailed(myself->slaveof) ||
         myself->slaveof->numslots == 0) return;
 
     /* Remove the node timeout from the data age as it is fine that we are
@@ -2086,9 +2074,7 @@ void clusterCron(void) {
 
         /* A Node in HANDSHAKE state has a limited lifespan equal to the
          * configured node timeout. */
-        if (node->flags & REDIS_NODE_HANDSHAKE &&
-            now - node->ctime > handshake_timeout)
-        {
+        if (nodeInHandshake(node) && now - node->ctime > handshake_timeout) {
             freeClusterNode(node);
             continue;
         }
@@ -2217,10 +2203,10 @@ void clusterCron(void) {
     /* If we are a slave node but the replication is still turned off,
      * enable it if we know the address of our master and it appears to
      * be up. */
-    if (myself->flags & REDIS_NODE_SLAVE &&
+    if (nodeIsSlave(myself) &&
         server.masterhost == NULL &&
         myself->slaveof &&
-        !(myself->slaveof->flags & REDIS_NODE_NOADDR))
+        nodeHasAddr(myself->slaveof))
     {
         replicationSetMaster(myself->slaveof->ip, myself->slaveof->port);
     }
@@ -2366,7 +2352,7 @@ void clusterUpdateState(void) {
      * the first call to this function and not since the server start, in order
      * to don't count the DB loading time. */
     if (first_call_time == 0) first_call_time = mstime();
-    if (myself->flags & REDIS_NODE_MASTER &&
+    if (nodeIsMaster(myself) &&
         mstime() - first_call_time < REDIS_CLUSTER_WRITABLE_DELAY) return;
 
     /* Start assuming the state is OK. We'll turn it into FAIL if there
@@ -2397,7 +2383,7 @@ void clusterUpdateState(void) {
         while((de = dictNext(di)) != NULL) {
             clusterNode *node = dictGetVal(de);
 
-            if (node->flags & REDIS_NODE_MASTER && node->numslots) {
+            if (nodeIsMaster(node) && node->numslots) {
                 server.cluster->size++;
                 if (node->flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL))
                     unreachable_masters++;
@@ -2432,7 +2418,7 @@ void clusterUpdateState(void) {
             rejoin_delay = REDIS_CLUSTER_MIN_REJOIN_DELAY;
 
         if (new_state == REDIS_CLUSTER_OK &&
-            myself->flags & REDIS_NODE_MASTER &&
+            nodeIsMaster(myself) &&
             mstime() - among_minority_time < rejoin_delay)
         {
             return;
@@ -2473,7 +2459,7 @@ int verifyClusterConfigWithData(void) {
 
     /* If this node is a slave, don't perform the check at all as we
      * completely depend on the replication stream. */
-    if (myself->flags & REDIS_NODE_SLAVE) return REDIS_OK;
+    if (nodeIsSlave(myself)) return REDIS_OK;
 
     /* Make sure we only have keys in DB0. */
     for (j = 1; j < server.dbnum; j++) {
@@ -2522,7 +2508,7 @@ void clusterSetMaster(clusterNode *n) {
     redisAssert(n != myself);
     redisAssert(myself->numslots == 0);
 
-    if (myself->flags & REDIS_NODE_MASTER) {
+    if (nodeIsMaster(myself)) {
         myself->flags &= ~REDIS_NODE_MASTER;
         myself->flags |= REDIS_NODE_SLAVE;
     } else {
@@ -2830,9 +2816,9 @@ void clusterCommand(redisClient *c) {
 
             if (n == NULL) continue;
             slots_assigned++;
-            if (n->flags & REDIS_NODE_FAIL) {
+            if (nodeFailed(n)) {
                 slots_fail++;
-            } else if (n->flags & REDIS_NODE_PFAIL) {
+            } else if (nodeTimedOut(n)) {
                 slots_pfail++;
             } else {
                 slots_ok++;
@@ -2919,7 +2905,7 @@ void clusterCommand(redisClient *c) {
         } else if (n == myself) {
             addReplyError(c,"I tried hard but I can't forget myself...");
             return;
-        } else if (myself->flags & REDIS_NODE_SLAVE && myself->slaveof == n) {
+        } else if (nodeIsSlave(myself) && myself->slaveof == n) {
             addReplyError(c,"Can't forget my master!");
             return;
         }
@@ -2952,10 +2938,8 @@ void clusterCommand(redisClient *c) {
         /* If the instance is currently a master, it should have no assigned
          * slots nor keys to accept to replicate some other node.
          * Slaves can switch to another master without issues. */
-        if (myself->flags & REDIS_NODE_MASTER &&
-            (myself->numslots != 0 ||
-            dictSize(server.db[0].dict) != 0))
-        {
+        if (nodeIsMaster(myself) &&
+            (myself->numslots != 0 || dictSize(server.db[0].dict) != 0)) {
             addReplyError(c,"To set a master the node must be empty and without assigned slots.");
             return;
         }
@@ -2975,7 +2959,7 @@ void clusterCommand(redisClient *c) {
             return;
         }
 
-        if (n->flags & REDIS_NODE_SLAVE) {
+        if (nodeIsSlave(n)) {
             addReplyError(c,"The specified node is not a master");
             return;
         }
@@ -3521,7 +3505,7 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
      * is serving, we can reply without redirection. */
     if (c->flags & REDIS_READONLY &&
         cmd->flags & REDIS_CMD_READONLY &&
-        myself->flags & REDIS_NODE_SLAVE &&
+        nodeIsSlave(myself) &&
         myself->slaveof == n)
     {
         return myself;