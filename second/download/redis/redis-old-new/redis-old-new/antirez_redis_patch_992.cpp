@@ -224,8 +224,7 @@ int clusterLoadConfig(char *filename) {
 
     /* Config sanity check */
     redisAssert(server.cluster->myself != NULL);
-    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
-        server.cluster->myself->name);
+    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s", myself->name);
     clusterSetStartupEpoch();
     return REDIS_OK;
 
@@ -318,8 +317,8 @@ void clusterInit(void) {
         myself = server.cluster->myself =
             createClusterNode(NULL,REDIS_NODE_MYSELF|REDIS_NODE_MASTER);
         redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
-            server.cluster->myself->name);
-        clusterAddNode(server.cluster->myself);
+            myself->name);
+        clusterAddNode(myself);
         saveconf = 1;
     }
     if (saveconf) clusterSaveConfigOrDie(1);
@@ -771,7 +770,7 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
 
     failures = clusterNodeFailureReportsCount(node);
     /* Also count myself as a voter if I'm a master. */
-    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
+    if (myself->flags & REDIS_NODE_MASTER)
         failures += 1;
     if (failures < needed_quorum) return; /* No weak agreement from masters. */
 
@@ -785,8 +784,7 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
 
     /* Broadcast the failing node name to everybody, forcing all the other
      * reachable nodes to flag the node as FAIL. */
-    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
-        clusterSendFail(node->name);
+    if (myself->flags & REDIS_NODE_MASTER) clusterSendFail(node->name);
     clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
 }
 
@@ -937,9 +935,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         if (node) {
             /* We already know this node.
                Handle failure reports, only when the sender is a master. */
-            if (sender && sender->flags & REDIS_NODE_MASTER &&
-                node != server.cluster->myself)
-            {
+            if (sender && sender->flags & REDIS_NODE_MASTER && node != myself) {
                 if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
                     if (clusterNodeAddFailureReport(node,sender)) {
                         redisLog(REDIS_VERBOSE,
@@ -1037,11 +1033,8 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
 
     /* Check if this is our master and we have to change the
      * replication target as well. */
-    if (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
-        server.cluster->myself->slaveof == node)
-    {
+    if (myself->flags & REDIS_NODE_SLAVE && myself->slaveof == node)
         replicationSetMaster(node->ip, node->port);
-    }
     return 1;
 }
 
@@ -1081,10 +1074,10 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
     /* Here we set curmaster to this node or the node this node
      * replicates to if it's a slave. In the for loop we are
      * interested to check if slots are taken away from curmaster. */
-    if (server.cluster->myself->flags & REDIS_NODE_MASTER)
-        curmaster = server.cluster->myself;
+    if (myself->flags & REDIS_NODE_MASTER)
+        curmaster = myself;
     else
-        curmaster = server.cluster->myself->slaveof;
+        curmaster = myself->slaveof;
 
     for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
         if (bitmapTestBit(slots,j)) {
@@ -1703,7 +1696,7 @@ void clusterSendPing(clusterLink *link, int type) {
          * 3) Nodes with the NOADDR flag set.
          * 4) Disconnected nodes if they don't have configured slots.
          */
-        if (this == server.cluster->myself ||
+        if (this == myself ||
             this->flags & (REDIS_NODE_HANDSHAKE|REDIS_NODE_NOADDR) ||
             (this->link == NULL && this->numslots == 0))
         {
@@ -1904,8 +1897,8 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
      * right to vote, as the cluster size in Redis Cluster is the number
      * of masters serving at least one slot, and quorum is the cluster
      * size + 1 */
-    if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return;
-    if (server.cluster->myself->numslots == 0) return;
+    if (!(myself->flags & REDIS_NODE_MASTER)) return;
+    if (myself->numslots == 0) return;
 
     /* Request epoch must be >= our currentEpoch. */
     if (requestCurrentEpoch < server.cluster->currentEpoch) return;
@@ -1969,10 +1962,10 @@ void clusterHandleSlaveFailover(void) {
      * 1) We are a slave.
      * 2) Our master is flagged as FAIL.
      * 3) It is serving slots. */
-    if (!(server.cluster->myself->flags & REDIS_NODE_SLAVE) ||
-        server.cluster->myself->slaveof == NULL ||
-        !(server.cluster->myself->slaveof->flags & REDIS_NODE_FAIL) ||
-        server.cluster->myself->slaveof->numslots == 0) return;
+    if (!(myself->flags & REDIS_NODE_SLAVE) ||
+        myself->slaveof == NULL ||
+        !(myself->slaveof->flags & REDIS_NODE_FAIL) ||
+        myself->slaveof->numslots == 0) return;
 
     /* Remove the node timeout from the data age as it is fine that we are
      * disconnected from our master at least for the time it was down to be
@@ -2026,32 +2019,30 @@ void clusterHandleSlaveFailover(void) {
 
     /* Check if we reached the quorum. */
     if (server.cluster->failover_auth_count >= needed_quorum) {
-        clusterNode *oldmaster = server.cluster->myself->slaveof;
+        clusterNode *oldmaster = myself->slaveof;
 
         redisLog(REDIS_WARNING,
             "Failover election won: I'm the new master.");
         /* We have the quorum, perform all the steps to correctly promote
          * this slave to a master.
          *
          * 1) Turn this node into a master. */
-        clusterNodeRemoveSlave(server.cluster->myself->slaveof,
-                               server.cluster->myself);
-        server.cluster->myself->flags &= ~REDIS_NODE_SLAVE;
-        server.cluster->myself->flags |= REDIS_NODE_MASTER;
-        server.cluster->myself->slaveof = NULL;
+        clusterNodeRemoveSlave(myself->slaveof, myself);
+        myself->flags &= ~REDIS_NODE_SLAVE;
+        myself->flags |= REDIS_NODE_MASTER;
+        myself->slaveof = NULL;
         replicationUnsetMaster();
 
         /* 2) Claim all the slots assigned to our master. */
         for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
             if (clusterNodeGetSlotBit(oldmaster,j)) {
                 clusterDelSlot(j);
-                clusterAddSlot(server.cluster->myself,j);
+                clusterAddSlot(myself,j);
             }
         }
 
         /* 3) Update my configEpoch to the epoch of the election. */
-        server.cluster->myself->configEpoch =
-            server.cluster->failover_auth_epoch;
+        myself->configEpoch = server.cluster->failover_auth_epoch;
 
         /* 4) Update state and save config. */
         clusterUpdateState();
@@ -2226,13 +2217,12 @@ void clusterCron(void) {
     /* If we are a slave node but the replication is still turned off,
      * enable it if we know the address of our master and it appears to
      * be up. */
-    if (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
+    if (myself->flags & REDIS_NODE_SLAVE &&
         server.masterhost == NULL &&
-        server.cluster->myself->slaveof &&
-        !(server.cluster->myself->slaveof->flags & REDIS_NODE_NOADDR))
+        myself->slaveof &&
+        !(myself->slaveof->flags & REDIS_NODE_NOADDR))
     {
-        replicationSetMaster(server.cluster->myself->slaveof->ip,
-                             server.cluster->myself->slaveof->port);
+        replicationSetMaster(myself->slaveof->ip, myself->slaveof->port);
     }
 
     clusterHandleSlaveFailover();
@@ -2376,7 +2366,7 @@ void clusterUpdateState(void) {
      * the first call to this function and not since the server start, in order
      * to don't count the DB loading time. */
     if (first_call_time == 0) first_call_time = mstime();
-    if (server.cluster->myself->flags & REDIS_NODE_MASTER &&
+    if (myself->flags & REDIS_NODE_MASTER &&
         mstime() - first_call_time < REDIS_CLUSTER_WRITABLE_DELAY) return;
 
     /* Start assuming the state is OK. We'll turn it into FAIL if there
@@ -2442,7 +2432,7 @@ void clusterUpdateState(void) {
             rejoin_delay = REDIS_CLUSTER_MIN_REJOIN_DELAY;
 
         if (new_state == REDIS_CLUSTER_OK &&
-            server.cluster->myself->flags & REDIS_NODE_MASTER &&
+            myself->flags & REDIS_NODE_MASTER &&
             mstime() - among_minority_time < rejoin_delay)
         {
             return;
@@ -2483,7 +2473,7 @@ int verifyClusterConfigWithData(void) {
 
     /* If this node is a slave, don't perform the check at all as we
      * completely depend on the replication stream. */
-    if (server.cluster->myself->flags & REDIS_NODE_SLAVE) return REDIS_OK;
+    if (myself->flags & REDIS_NODE_SLAVE) return REDIS_OK;
 
     /* Make sure we only have keys in DB0. */
     for (j = 1; j < server.dbnum; j++) {
@@ -2497,7 +2487,7 @@ int verifyClusterConfigWithData(void) {
         /* Check if we are assigned to this slot or if we are importing it.
          * In both cases check the next slot as the configuration makes
          * sense. */
-        if (server.cluster->slots[j] == server.cluster->myself ||
+        if (server.cluster->slots[j] == myself ||
             server.cluster->importing_slots_from[j] != NULL) continue;
 
         /* If we are here data and cluster config don't agree, and we have
@@ -2510,7 +2500,7 @@ int verifyClusterConfigWithData(void) {
             redisLog(REDIS_WARNING, "I've keys about slot %d that is "
                                     "unassigned. Taking responsability "
                                     "for it.",j);
-            clusterAddSlot(server.cluster->myself,j);
+            clusterAddSlot(myself,j);
         } else {
             redisLog(REDIS_WARNING, "I've keys about slot %d that is "
                                     "already assigned to a different node. "
@@ -2702,7 +2692,7 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"DB must be empty to perform CLUSTER FLUSHSLOTS.");
             return;
         }
-        clusterDelNodeSlots(server.cluster->myself);
+        clusterDelNodeSlots(myself);
         clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
@@ -2748,7 +2738,7 @@ void clusterCommand(redisClient *c) {
                     server.cluster->importing_slots_from[j] = NULL;
 
                 retval = del ? clusterDelSlot(j) :
-                               clusterAddSlot(server.cluster->myself,j);
+                               clusterAddSlot(myself,j);
                 redisAssertWithInfo(c,NULL,retval == REDIS_OK);
             }
         }
@@ -2766,7 +2756,7 @@ void clusterCommand(redisClient *c) {
         if ((slot = getSlotOrReply(c,c->argv[2])) == -1) return;
 
         if (!strcasecmp(c->argv[3]->ptr,"migrating") && c->argc == 5) {
-            if (server.cluster->slots[slot] != server.cluster->myself) {
+            if (server.cluster->slots[slot] != myself) {
                 addReplyErrorFormat(c,"I'm not the owner of hash slot %u",slot);
                 return;
             }
@@ -2777,7 +2767,7 @@ void clusterCommand(redisClient *c) {
             }
             server.cluster->migrating_slots_to[slot] = n;
         } else if (!strcasecmp(c->argv[3]->ptr,"importing") && c->argc == 5) {
-            if (server.cluster->slots[slot] == server.cluster->myself) {
+            if (server.cluster->slots[slot] == myself) {
                 addReplyErrorFormat(c,
                     "I'm already the owner of hash slot %u",slot);
                 return;
@@ -2803,9 +2793,7 @@ void clusterCommand(redisClient *c) {
             }
             /* If this hash slot was served by 'myself' before to switch
              * make sure there are no longer local keys for this hash slot. */
-            if (server.cluster->slots[slot] == server.cluster->myself &&
-                n != server.cluster->myself)
-            {
+            if (server.cluster->slots[slot] == myself && n != myself) {
                 if (countKeysInSlot(slot) != 0) {
                     addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
                     return;
@@ -2814,13 +2802,13 @@ void clusterCommand(redisClient *c) {
             /* If this node was the slot owner and the slot was marked as
              * migrating, assigning the slot to another node will clear
              * the migratig status. */
-            if (server.cluster->slots[slot] == server.cluster->myself &&
+            if (server.cluster->slots[slot] == myself &&
                 server.cluster->migrating_slots_to[slot])
                 server.cluster->migrating_slots_to[slot] = NULL;
 
             /* If this node was importing this slot, assigning the slot to
              * itself also clears the importing status. */
-            if (n == server.cluster->myself &&
+            if (n == myself &&
                 server.cluster->importing_slots_from[slot])
                 server.cluster->importing_slots_from[slot] = NULL;
             clusterDelSlot(slot);
@@ -2928,11 +2916,10 @@ void clusterCommand(redisClient *c) {
         if (!n) {
             addReplyErrorFormat(c,"Unknown node %s", (char*)c->argv[2]->ptr);
             return;
-        } else if (n == server.cluster->myself) {
+        } else if (n == myself) {
             addReplyError(c,"I tried hard but I can't forget myself...");
             return;
-        } else if (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
-                   server.cluster->myself->slaveof == n) {
+        } else if (myself->flags & REDIS_NODE_SLAVE && myself->slaveof == n) {
             addReplyError(c,"Can't forget my master!");
             return;
         }
@@ -2951,7 +2938,7 @@ void clusterCommand(redisClient *c) {
         }
 
         /* I can't replicate myself. */
-        if (n == server.cluster->myself) {
+        if (n == myself) {
             addReplyError(c,"Can't replicate myself");
             return;
         }
@@ -2965,8 +2952,8 @@ void clusterCommand(redisClient *c) {
         /* If the instance is currently a master, it should have no assigned
          * slots nor keys to accept to replicate some other node.
          * Slaves can switch to another master without issues. */
-        if (server.cluster->myself->flags & REDIS_NODE_MASTER &&
-            (server.cluster->myself->numslots != 0 ||
+        if (myself->flags & REDIS_NODE_MASTER &&
+            (myself->numslots != 0 ||
             dictSize(server.db[0].dict) != 0))
         {
             addReplyError(c,"To set a master the node must be empty and without assigned slots.");
@@ -3459,7 +3446,7 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
     if (cmd->proc == execCommand) {
         /* If REDIS_MULTI flag is not set EXEC is just going to return an
          * error. */
-        if (!(c->flags & REDIS_MULTI)) return server.cluster->myself;
+        if (!(c->flags & REDIS_MULTI)) return myself;
         ms = &c->mstate;
     } else {
         /* In order to have a single codepath create a fake Multi State
@@ -3509,15 +3496,13 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
     if (ask) *ask = 0; /* This is the default. Set to 1 if needed later. */
     /* No key at all in command? then we can serve the request
      * without redirections. */
-    if (n == NULL) return server.cluster->myself;
+    if (n == NULL) return myself;
     if (hashslot) *hashslot = slot;
     /* This request is about a slot we are migrating into another instance?
      * Then we need to check if we have the key. If we have it we can reply.
      * If instead is a new key, we pass the request to the node that is
      * receiving the slot. */
-    if (n == server.cluster->myself &&
-        server.cluster->migrating_slots_to[slot] != NULL)
-    {
+    if (n == myself && server.cluster->migrating_slots_to[slot] != NULL) {
         if (lookupKeyRead(&server.db[0],firstkey) == NULL) {
             if (ask) *ask = 1;
             return server.cluster->migrating_slots_to[slot];
@@ -3529,17 +3514,17 @@ clusterNode *getNodeByQuery(redisClient *c, struct redisCommand *cmd, robj **arg
      * issued an ASKING command before. */
     if (server.cluster->importing_slots_from[slot] != NULL &&
         (c->flags & REDIS_ASKING || cmd->flags & REDIS_CMD_ASKING)) {
-        return server.cluster->myself;
+        return myself;
     }
     /* Handle the read-only client case reading from a slave: if this
      * node is a slave and the request is about an hash slot our master
      * is serving, we can reply without redirection. */
     if (c->flags & REDIS_READONLY &&
         cmd->flags & REDIS_CMD_READONLY &&
-        server.cluster->myself->flags & REDIS_NODE_SLAVE &&
-        server.cluster->myself->slaveof == n)
+        myself->flags & REDIS_NODE_SLAVE &&
+        myself->slaveof == n)
     {
-        return server.cluster->myself;
+        return myself;
     }
     /* It's not a -ASK case. Base case: just return the right node. */
     return n;