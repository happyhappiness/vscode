@@ -117,8 +117,8 @@ int clusterLoadConfig(char *filename) {
      * present in a single line, possibly in importing or migrating state, so
      * together with the node ID of the sender/receiver.
      *
-     * To simplify we allocate 1024+REDIS_CLUSTER_SLOTS*128 bytes per line. */
-    maxline = 1024+REDIS_CLUSTER_SLOTS*128;
+     * To simplify we allocate 1024+CLUSTER_SLOTS*128 bytes per line. */
+    maxline = 1024+CLUSTER_SLOTS*128;
     line = zmalloc(maxline);
     while(fgets(line,maxline,fp) != NULL) {
         int argc;
@@ -178,20 +178,20 @@ int clusterLoadConfig(char *filename) {
             if (!strcasecmp(s,"myself")) {
                 serverAssert(server.cluster->myself == NULL);
                 myself = server.cluster->myself = n;
-                n->flags |= REDIS_NODE_MYSELF;
+                n->flags |= CLUSTER_NODE_MYSELF;
             } else if (!strcasecmp(s,"master")) {
-                n->flags |= REDIS_NODE_MASTER;
+                n->flags |= CLUSTER_NODE_MASTER;
             } else if (!strcasecmp(s,"slave")) {
-                n->flags |= REDIS_NODE_SLAVE;
+                n->flags |= CLUSTER_NODE_SLAVE;
             } else if (!strcasecmp(s,"fail?")) {
-                n->flags |= REDIS_NODE_PFAIL;
+                n->flags |= CLUSTER_NODE_PFAIL;
             } else if (!strcasecmp(s,"fail")) {
-                n->flags |= REDIS_NODE_FAIL;
+                n->flags |= CLUSTER_NODE_FAIL;
                 n->fail_time = mstime();
             } else if (!strcasecmp(s,"handshake")) {
-                n->flags |= REDIS_NODE_HANDSHAKE;
+                n->flags |= CLUSTER_NODE_HANDSHAKE;
             } else if (!strcasecmp(s,"noaddr")) {
-                n->flags |= REDIS_NODE_NOADDR;
+                n->flags |= CLUSTER_NODE_NOADDR;
             } else if (!strcasecmp(s,"noflags")) {
                 /* nothing to do */
             } else {
@@ -304,7 +304,7 @@ int clusterSaveConfig(int do_fsync) {
 
     /* Get the nodes description and concatenate our "vars" directive to
      * save currentEpoch and lastVoteEpoch. */
-    ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
+    ci = clusterGenNodesDescription(CLUSTER_NODE_HANDSHAKE);
     ci = sdscatprintf(ci,"vars currentEpoch %llu lastVoteEpoch %llu\n",
         (unsigned long long) server.cluster->currentEpoch,
         (unsigned long long) server.cluster->lastVoteEpoch);
@@ -401,7 +401,7 @@ void clusterInit(void) {
     server.cluster = zmalloc(sizeof(clusterState));
     server.cluster->myself = NULL;
     server.cluster->currentEpoch = 0;
-    server.cluster->state = REDIS_CLUSTER_FAIL;
+    server.cluster->state = CLUSTER_FAIL;
     server.cluster->size = 1;
     server.cluster->todo_before_sleep = 0;
     server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
@@ -411,7 +411,7 @@ void clusterInit(void) {
     server.cluster->failover_auth_count = 0;
     server.cluster->failover_auth_rank = 0;
     server.cluster->failover_auth_epoch = 0;
-    server.cluster->cant_failover_reason = REDIS_CLUSTER_CANT_FAILOVER_NONE;
+    server.cluster->cant_failover_reason = CLUSTER_CANT_FAILOVER_NONE;
     server.cluster->lastVoteEpoch = 0;
     server.cluster->stats_bus_messages_sent = 0;
     server.cluster->stats_bus_messages_received = 0;
@@ -428,7 +428,7 @@ void clusterInit(void) {
         /* No configuration found. We will just use the random name provided
          * by the createClusterNode() function. */
         myself = server.cluster->myself =
-            createClusterNode(NULL,REDIS_NODE_MYSELF|REDIS_NODE_MASTER);
+            createClusterNode(NULL,CLUSTER_NODE_MYSELF|CLUSTER_NODE_MASTER);
         serverLog(LL_NOTICE,"No cluster configuration found, I'm %.40s",
             myself->name);
         clusterAddNode(myself);
@@ -442,7 +442,7 @@ void clusterInit(void) {
     /* Port sanity check II
      * The other handshake port check is triggered too late to stop
      * us from trying to use a too-high cluster port number. */
-    if (server.port > (65535-REDIS_CLUSTER_PORT_INCR)) {
+    if (server.port > (65535-CLUSTER_PORT_INCR)) {
         serverLog(LL_WARNING, "Redis port number too high. "
                    "Cluster communication port is 10,000 port "
                    "numbers higher than your Redis port. "
@@ -451,7 +451,7 @@ void clusterInit(void) {
         exit(1);
     }
 
-    if (listenToPort(server.port+REDIS_CLUSTER_PORT_INCR,
+    if (listenToPort(server.port+CLUSTER_PORT_INCR,
         server.cfd,&server.cfd_count) == C_ERR)
     {
         exit(1);
@@ -503,7 +503,7 @@ void clusterReset(int hard) {
     resetManualFailover();
 
     /* Unassign all the slots. */
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) clusterDelSlot(j);
+    for (j = 0; j < CLUSTER_SLOTS; j++) clusterDelSlot(j);
 
     /* Forget all the nodes, but myself. */
     di = dictGetSafeIterator(server.cluster->nodes);
@@ -526,10 +526,10 @@ void clusterReset(int hard) {
 
         /* To change the Node ID we need to remove the old name from the
          * nodes table, change the ID, and re-add back with new name. */
-        oldname = sdsnewlen(myself->name, REDIS_CLUSTER_NAMELEN);
+        oldname = sdsnewlen(myself->name, CLUSTER_NAMELEN);
         dictDelete(server.cluster->nodes,oldname);
         sdsfree(oldname);
-        getRandomHexChars(myself->name, REDIS_CLUSTER_NAMELEN);
+        getRandomHexChars(myself->name, CLUSTER_NAMELEN);
         clusterAddNode(myself);
     }
 
@@ -653,9 +653,9 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     clusterNode *node = zmalloc(sizeof(*node));
 
     if (nodename)
-        memcpy(node->name, nodename, REDIS_CLUSTER_NAMELEN);
+        memcpy(node->name, nodename, CLUSTER_NAMELEN);
     else
-        getRandomHexChars(node->name, REDIS_CLUSTER_NAMELEN);
+        getRandomHexChars(node->name, CLUSTER_NAMELEN);
     node->ctime = mstime();
     node->configEpoch = 0;
     node->flags = flags;
@@ -723,7 +723,7 @@ void clusterNodeCleanupFailureReports(clusterNode *node) {
     listIter li;
     clusterNodeFailReport *fr;
     mstime_t maxtime = server.cluster_node_timeout *
-                     REDIS_CLUSTER_FAIL_REPORT_VALIDITY_MULT;
+                     CLUSTER_FAIL_REPORT_VALIDITY_MULT;
     mstime_t now = mstime();
 
     listRewind(l,&li);
@@ -832,7 +832,7 @@ void freeClusterNode(clusterNode *n) {
     if (nodeIsSlave(n) && n->slaveof) clusterNodeRemoveSlave(n->slaveof,n);
 
     /* Unlink from the set of nodes. */
-    nodename = sdsnewlen(n->name, REDIS_CLUSTER_NAMELEN);
+    nodename = sdsnewlen(n->name, CLUSTER_NAMELEN);
     serverAssert(dictDelete(server.cluster->nodes,nodename) == DICT_OK);
     sdsfree(nodename);
 
@@ -848,7 +848,7 @@ int clusterAddNode(clusterNode *node) {
     int retval;
 
     retval = dictAdd(server.cluster->nodes,
-            sdsnewlen(node->name,REDIS_CLUSTER_NAMELEN), node);
+            sdsnewlen(node->name,CLUSTER_NAMELEN), node);
     return (retval == DICT_OK) ? C_OK : C_ERR;
 }
 
@@ -869,7 +869,7 @@ void clusterDelNode(clusterNode *delnode) {
     dictEntry *de;
 
     /* 1) Mark slots as unassigned. */
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         if (server.cluster->importing_slots_from[j] == delnode)
             server.cluster->importing_slots_from[j] = NULL;
         if (server.cluster->migrating_slots_to[j] == delnode)
@@ -894,7 +894,7 @@ void clusterDelNode(clusterNode *delnode) {
 
 /* Node lookup by name */
 clusterNode *clusterLookupNode(char *name) {
-    sds s = sdsnewlen(name, REDIS_CLUSTER_NAMELEN);
+    sds s = sdsnewlen(name, CLUSTER_NAMELEN);
     dictEntry *de;
 
     de = dictFind(server.cluster->nodes,s);
@@ -909,14 +909,14 @@ clusterNode *clusterLookupNode(char *name) {
  * this function. */
 void clusterRenameNode(clusterNode *node, char *newname) {
     int retval;
-    sds s = sdsnewlen(node->name, REDIS_CLUSTER_NAMELEN);
+    sds s = sdsnewlen(node->name, CLUSTER_NAMELEN);
 
     serverLog(LL_DEBUG,"Renaming node %.40s into %.40s",
         node->name, newname);
     retval = dictDelete(server.cluster->nodes, s);
     sdsfree(s);
     serverAssert(retval == DICT_OK);
-    memcpy(node->name, newname, REDIS_CLUSTER_NAMELEN);
+    memcpy(node->name, newname, CLUSTER_NAMELEN);
     clusterAddNode(node);
 }
 
@@ -1040,7 +1040,7 @@ void clusterHandleConfigEpochCollision(clusterNode *sender) {
     if (sender->configEpoch != myself->configEpoch ||
         !nodeIsMaster(sender) || !nodeIsMaster(myself)) return;
     /* Don't act if the colliding node has a smaller Node ID. */
-    if (memcmp(sender->name,myself->name,REDIS_CLUSTER_NAMELEN) <= 0) return;
+    if (memcmp(sender->name,myself->name,CLUSTER_NAMELEN) <= 0) return;
     /* Get the next ID available at the best of this node knowledge. */
     server.cluster->currentEpoch++;
     myself->configEpoch = server.cluster->currentEpoch;
@@ -1057,14 +1057,14 @@ void clusterHandleConfigEpochCollision(clusterNode *sender) {
  *
  * The nodes blacklist is just a way to ensure that a given node with a given
  * Node ID is not readded before some time elapsed (this time is specified
- * in seconds in REDIS_CLUSTER_BLACKLIST_TTL).
+ * in seconds in CLUSTER_BLACKLIST_TTL).
  *
  * This is useful when we want to remove a node from the cluster completely:
  * when CLUSTER FORGET is called, it also puts the node into the blacklist so
  * that even if we receive gossip messages from other nodes that still remember
  * about the node we want to remove, we don't re-add it before some time.
  *
- * Currently the REDIS_CLUSTER_BLACKLIST_TTL is set to 1 minute, this means
+ * Currently the CLUSTER_BLACKLIST_TTL is set to 1 minute, this means
  * that redis-trib has 60 seconds to send CLUSTER FORGET messages to nodes
  * in the cluster without dealing with the problem of other nodes re-adding
  * back the node to nodes we already sent the FORGET command to.
@@ -1074,7 +1074,7 @@ void clusterHandleConfigEpochCollision(clusterNode *sender) {
  * value.
  * -------------------------------------------------------------------------- */
 
-#define REDIS_CLUSTER_BLACKLIST_TTL 60      /* 1 minute. */
+#define CLUSTER_BLACKLIST_TTL 60      /* 1 minute. */
 
 
 /* Before of the addNode() or Exists() operations we always remove expired
@@ -1100,7 +1100,7 @@ void clusterBlacklistCleanup(void) {
 /* Cleanup the blacklist and add a new node ID to the black list. */
 void clusterBlacklistAddNode(clusterNode *node) {
     dictEntry *de;
-    sds id = sdsnewlen(node->name,REDIS_CLUSTER_NAMELEN);
+    sds id = sdsnewlen(node->name,CLUSTER_NAMELEN);
 
     clusterBlacklistCleanup();
     if (dictAdd(server.cluster->nodes_black_list,id,NULL) == DICT_OK) {
@@ -1109,15 +1109,15 @@ void clusterBlacklistAddNode(clusterNode *node) {
         id = sdsdup(id);
     }
     de = dictFind(server.cluster->nodes_black_list,id);
-    dictSetUnsignedIntegerVal(de,time(NULL)+REDIS_CLUSTER_BLACKLIST_TTL);
+    dictSetUnsignedIntegerVal(de,time(NULL)+CLUSTER_BLACKLIST_TTL);
     sdsfree(id);
 }
 
 /* Return non-zero if the specified node ID exists in the blacklist.
  * You don't need to pass an sds string here, any pointer to 40 bytes
  * will work. */
 int clusterBlacklistExists(char *nodeid) {
-    sds id = sdsnewlen(nodeid,REDIS_CLUSTER_NAMELEN);
+    sds id = sdsnewlen(nodeid,CLUSTER_NAMELEN);
     int retval;
 
     clusterBlacklistCleanup();
@@ -1167,8 +1167,8 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
         "Marking node %.40s as failing (quorum reached).", node->name);
 
     /* Mark the node as failing. */
-    node->flags &= ~REDIS_NODE_PFAIL;
-    node->flags |= REDIS_NODE_FAIL;
+    node->flags &= ~CLUSTER_NODE_PFAIL;
+    node->flags |= CLUSTER_NODE_FAIL;
     node->fail_time = mstime();
 
     /* Broadcast the failing node name to everybody, forcing all the other
@@ -1192,7 +1192,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
             "Clear FAIL state for node %.40s: %s is reachable again.",
                 node->name,
                 nodeIsSlave(node) ? "slave" : "master without slots");
-        node->flags &= ~REDIS_NODE_FAIL;
+        node->flags &= ~CLUSTER_NODE_FAIL;
         clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
     }
 
@@ -1202,12 +1202,12 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
      * Apparently no one is going to fix these slots, clear the FAIL flag. */
     if (nodeIsMaster(node) && node->numslots > 0 &&
         (now - node->fail_time) >
-        (server.cluster_node_timeout * REDIS_CLUSTER_FAIL_UNDO_TIME_MULT))
+        (server.cluster_node_timeout * CLUSTER_FAIL_UNDO_TIME_MULT))
     {
         serverLog(LL_NOTICE,
             "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                 node->name);
-        node->flags &= ~REDIS_NODE_FAIL;
+        node->flags &= ~CLUSTER_NODE_FAIL;
         clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
     }
 }
@@ -1257,7 +1257,7 @@ int clusterStartHandshake(char *ip, int port) {
     }
 
     /* Port sanity check */
-    if (port <= 0 || port > (65535-REDIS_CLUSTER_PORT_INCR)) {
+    if (port <= 0 || port > (65535-CLUSTER_PORT_INCR)) {
         errno = EINVAL;
         return 0;
     }
@@ -1282,7 +1282,7 @@ int clusterStartHandshake(char *ip, int port) {
     /* Add the node with a random address (NULL as first argument to
      * createClusterNode()). Everything will be fixed during the
      * handshake. */
-    n = createClusterNode(NULL,REDIS_NODE_HANDSHAKE|REDIS_NODE_MEET);
+    n = createClusterNode(NULL,CLUSTER_NODE_HANDSHAKE|CLUSTER_NODE_MEET);
     memcpy(n->ip,norm_ip,sizeof(n->ip));
     n->port = port;
     clusterAddNode(n);
@@ -1317,7 +1317,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
             /* We already know this node.
                Handle failure reports, only when the sender is a master. */
             if (sender && nodeIsMaster(sender) && node != myself) {
-                if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
+                if (flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL)) {
                     if (clusterNodeAddFailureReport(node,sender)) {
                         serverLog(LL_VERBOSE,
                             "Node %.40s reported node %.40s as not reachable.",
@@ -1338,7 +1338,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
              * handshake with the (possibly) new address: this will result
              * into a node address update if the handshake will be
              * successful. */
-            if (node->flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL) &&
+            if (node->flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL) &&
                 (strcasecmp(node->ip,g->ip) || node->port != ntohs(g->port)))
             {
                 clusterStartHandshake(g->ip,ntohs(g->port));
@@ -1351,7 +1351,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
              * is a well known node in our cluster, otherwise we risk
              * joining another cluster. */
             if (sender &&
-                !(flags & REDIS_NODE_NOADDR) &&
+                !(flags & CLUSTER_NODE_NOADDR) &&
                 !clusterBlacklistExists(g->nodename))
             {
                 clusterStartHandshake(g->ip,ntohs(g->port));
@@ -1396,7 +1396,7 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
     memcpy(node->ip,ip,sizeof(ip));
     node->port = port;
     if (node->link) freeClusterLink(node->link);
-    node->flags &= ~REDIS_NODE_NOADDR;
+    node->flags &= ~CLUSTER_NODE_NOADDR;
     serverLog(LL_WARNING,"Address updated for node %.40s, now %s:%d",
         node->name, node->ip, node->port);
 
@@ -1414,8 +1414,8 @@ void clusterSetNodeAsMaster(clusterNode *n) {
     if (nodeIsMaster(n)) return;
 
     if (n->slaveof) clusterNodeRemoveSlave(n->slaveof,n);
-    n->flags &= ~REDIS_NODE_SLAVE;
-    n->flags |= REDIS_NODE_MASTER;
+    n->flags &= ~CLUSTER_NODE_SLAVE;
+    n->flags |= CLUSTER_NODE_MASTER;
     n->slaveof = NULL;
 
     /* Update config and state. */
@@ -1444,7 +1444,7 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
      * If the update message is not able to demote a master to slave (in this
      * case we'll resync with the master updating the whole key space), we
      * need to delete all the keys in the slots we lost ownership. */
-    uint16_t dirty_slots[REDIS_CLUSTER_SLOTS];
+    uint16_t dirty_slots[CLUSTER_SLOTS];
     int dirty_slots_count = 0;
 
     /* Here we set curmaster to this node or the node this node
@@ -1457,7 +1457,7 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
         return;
     }
 
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         if (bitmapTestBit(slots,j)) {
             /* The slot is already bound to the sender of this message. */
             if (server.cluster->slots[j] == sender) continue;
@@ -1654,7 +1654,7 @@ int clusterProcessPacket(clusterLink *link) {
         if (!sender && type == CLUSTERMSG_TYPE_MEET) {
             clusterNode *node;
 
-            node = createClusterNode(NULL,REDIS_NODE_HANDSHAKE);
+            node = createClusterNode(NULL,CLUSTER_NODE_HANDSHAKE);
             nodeIp2String(node->ip,link);
             node->port = ntohs(hdr->port);
             clusterAddNode(node);
@@ -1702,17 +1702,17 @@ int clusterProcessPacket(clusterLink *link) {
                 clusterRenameNode(link->node, hdr->sender);
                 serverLog(LL_DEBUG,"Handshake with node %.40s completed.",
                     link->node->name);
-                link->node->flags &= ~REDIS_NODE_HANDSHAKE;
-                link->node->flags |= flags&(REDIS_NODE_MASTER|REDIS_NODE_SLAVE);
+                link->node->flags &= ~CLUSTER_NODE_HANDSHAKE;
+                link->node->flags |= flags&(CLUSTER_NODE_MASTER|CLUSTER_NODE_SLAVE);
                 clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
             } else if (memcmp(link->node->name,hdr->sender,
-                        REDIS_CLUSTER_NAMELEN) != 0)
+                        CLUSTER_NAMELEN) != 0)
             {
                 /* If the reply has a non matching node ID we
                  * disconnect this node and set it as not having an associated
                  * address. */
                 serverLog(LL_DEBUG,"PONG contains mismatching sender ID");
-                link->node->flags |= REDIS_NODE_NOADDR;
+                link->node->flags |= CLUSTER_NODE_NOADDR;
                 link->node->ip[0] = '\0';
                 link->node->port = 0;
                 freeClusterLink(link);
@@ -1742,7 +1742,7 @@ int clusterProcessPacket(clusterLink *link) {
              * The FAIL condition is also reversible under specific
              * conditions detected by clearNodeFailureIfNeeded(). */
             if (nodeTimedOut(link->node)) {
-                link->node->flags &= ~REDIS_NODE_PFAIL;
+                link->node->flags &= ~CLUSTER_NODE_PFAIL;
                 clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                      CLUSTER_TODO_UPDATE_STATE);
             } else if (nodeFailed(link->node)) {
@@ -1752,7 +1752,7 @@ int clusterProcessPacket(clusterLink *link) {
 
         /* Check for role switch: slave -> master or master -> slave. */
         if (sender) {
-            if (!memcmp(hdr->slaveof,REDIS_NODE_NULL_NAME,
+            if (!memcmp(hdr->slaveof,CLUSTER_NODE_NULL_NAME,
                 sizeof(hdr->slaveof)))
             {
                 /* Node is a master. */
@@ -1764,8 +1764,8 @@ int clusterProcessPacket(clusterLink *link) {
                 if (nodeIsMaster(sender)) {
                     /* Master turned into a slave! Reconfigure the node. */
                     clusterDelNodeSlots(sender);
-                    sender->flags &= ~REDIS_NODE_MASTER;
-                    sender->flags |= REDIS_NODE_SLAVE;
+                    sender->flags &= ~CLUSTER_NODE_MASTER;
+                    sender->flags |= CLUSTER_NODE_SLAVE;
 
                     /* Remove the list of slaves from the node. */
                     if (sender->numslaves) clusterNodeResetSlaves(sender);
@@ -1791,7 +1791,7 @@ int clusterProcessPacket(clusterLink *link) {
         /* Update our info about served slots.
          *
          * Note: this MUST happen after we update the master/slave state
-         * so that REDIS_NODE_MASTER flag will be set. */
+         * so that CLUSTER_NODE_MASTER flag will be set. */
 
         /* Many checks are only needed if the set of served slots this
          * instance claims is different compared to the set of slots we have
@@ -1835,7 +1835,7 @@ int clusterProcessPacket(clusterLink *link) {
         if (sender && dirty_slots) {
             int j;
 
-            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+            for (j = 0; j < CLUSTER_SLOTS; j++) {
                 if (bitmapTestBit(hdr->myslots,j)) {
                     if (server.cluster->slots[j] == sender ||
                         server.cluster->slots[j] == NULL) continue;
@@ -1875,14 +1875,14 @@ int clusterProcessPacket(clusterLink *link) {
         if (sender) {
             failing = clusterLookupNode(hdr->data.fail.about.nodename);
             if (failing &&
-                !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
+                !(failing->flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_MYSELF)))
             {
                 serverLog(LL_NOTICE,
                     "FAIL message received from %.40s about %.40s",
                     hdr->sender, hdr->data.fail.about.nodename);
-                failing->flags |= REDIS_NODE_FAIL;
+                failing->flags |= CLUSTER_NODE_FAIL;
                 failing->fail_time = mstime();
-                failing->flags &= ~REDIS_NODE_PFAIL;
+                failing->flags &= ~CLUSTER_NODE_PFAIL;
                 clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                                      CLUSTER_TODO_UPDATE_STATE);
             }
@@ -1934,9 +1934,9 @@ int clusterProcessPacket(clusterLink *link) {
         /* Manual failover requested from slaves. Initialize the state
          * accordingly. */
         resetManualFailover();
-        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
+        server.cluster->mf_end = mstime() + CLUSTER_MF_TIMEOUT;
         server.cluster->mf_slave = sender;
-        pauseClients(mstime()+(REDIS_CLUSTER_MF_TIMEOUT*2));
+        pauseClients(mstime()+(CLUSTER_MF_TIMEOUT*2));
         serverLog(LL_WARNING,"Manual failover requested by slave %.40s.",
             sender->name);
     } else if (type == CLUSTERMSG_TYPE_UPDATE) {
@@ -2093,7 +2093,7 @@ void clusterBroadcastMessage(void *buf, size_t len) {
         clusterNode *node = dictGetVal(de);
 
         if (!node->link) continue;
-        if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE))
+        if (node->flags & (CLUSTER_NODE_MYSELF|CLUSTER_NODE_HANDSHAKE))
             continue;
         clusterSendMessage(node->link,buf,len);
     }
@@ -2121,12 +2121,12 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     hdr->sig[2] = 'm';
     hdr->sig[3] = 'b';
     hdr->type = htons(type);
-    memcpy(hdr->sender,myself->name,REDIS_CLUSTER_NAMELEN);
+    memcpy(hdr->sender,myself->name,CLUSTER_NAMELEN);
 
     memcpy(hdr->myslots,master->slots,sizeof(hdr->myslots));
-    memset(hdr->slaveof,0,REDIS_CLUSTER_NAMELEN);
+    memset(hdr->slaveof,0,CLUSTER_NAMELEN);
     if (myself->slaveof != NULL)
-        memcpy(hdr->slaveof,myself->slaveof->name, REDIS_CLUSTER_NAMELEN);
+        memcpy(hdr->slaveof,myself->slaveof->name, CLUSTER_NAMELEN);
     hdr->port = htons(server.port);
     hdr->flags = htons(myself->flags);
     hdr->state = server.cluster->state;
@@ -2233,15 +2233,15 @@ void clusterSendPing(clusterLink *link, int type) {
 
         /* Give a bias to FAIL/PFAIL nodes. */
         if (maxiterations > wanted*2 &&
-            !(this->flags & (REDIS_NODE_PFAIL|REDIS_NODE_FAIL)))
+            !(this->flags & (CLUSTER_NODE_PFAIL|CLUSTER_NODE_FAIL)))
             continue;
 
         /* In the gossip section don't include:
          * 1) Nodes in HANDSHAKE state.
          * 3) Nodes with the NOADDR flag set.
          * 4) Disconnected nodes if they don't have configured slots.
          */
-        if (this->flags & (REDIS_NODE_HANDSHAKE|REDIS_NODE_NOADDR) ||
+        if (this->flags & (CLUSTER_NODE_HANDSHAKE|CLUSTER_NODE_NOADDR) ||
             (this->link == NULL && this->numslots == 0))
         {
             freshnodes--; /* Tecnically not correct, but saves CPU. */
@@ -2251,14 +2251,14 @@ void clusterSendPing(clusterLink *link, int type) {
         /* Check if we already added this node */
         for (j = 0; j < gossipcount; j++) {
             if (memcmp(hdr->data.ping.gossip[j].nodename,this->name,
-                    REDIS_CLUSTER_NAMELEN) == 0) break;
+                    CLUSTER_NAMELEN) == 0) break;
         }
         if (j != gossipcount) continue;
 
         /* Add it */
         freshnodes--;
         gossip = &(hdr->data.ping.gossip[gossipcount]);
-        memcpy(gossip->nodename,this->name,REDIS_CLUSTER_NAMELEN);
+        memcpy(gossip->nodename,this->name,CLUSTER_NAMELEN);
         gossip->ping_sent = htonl(this->ping_sent);
         gossip->pong_received = htonl(this->pong_received);
         memcpy(gossip->ip,this->ip,sizeof(this->ip));
@@ -2362,15 +2362,15 @@ void clusterSendPublish(clusterLink *link, robj *channel, robj *message) {
 
 /* Send a FAIL message to all the nodes we are able to contact.
  * The FAIL message is sent when we detect that a node is failing
- * (REDIS_NODE_PFAIL) and we also receive a gossip confirmation of this:
- * we switch the node state to REDIS_NODE_FAIL and ask all the other
+ * (CLUSTER_NODE_PFAIL) and we also receive a gossip confirmation of this:
+ * we switch the node state to CLUSTER_NODE_FAIL and ask all the other
  * nodes to do the same ASAP. */
 void clusterSendFail(char *nodename) {
     unsigned char buf[sizeof(clusterMsg)];
     clusterMsg *hdr = (clusterMsg*) buf;
 
     clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_FAIL);
-    memcpy(hdr->data.fail.about.nodename,nodename,REDIS_CLUSTER_NAMELEN);
+    memcpy(hdr->data.fail.about.nodename,nodename,CLUSTER_NAMELEN);
     clusterBroadcastMessage(buf,ntohl(hdr->totlen));
 }
 
@@ -2383,7 +2383,7 @@ void clusterSendUpdate(clusterLink *link, clusterNode *node) {
 
     if (link == NULL) return;
     clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_UPDATE);
-    memcpy(hdr->data.update.nodecfg.nodename,node->name,REDIS_CLUSTER_NAMELEN);
+    memcpy(hdr->data.update.nodecfg.nodename,node->name,CLUSTER_NAMELEN);
     hdr->data.update.nodecfg.configEpoch = htonu64(node->configEpoch);
     memcpy(hdr->data.update.nodecfg.slots,node->slots,sizeof(node->slots));
     clusterSendMessage(link,buf,ntohl(hdr->totlen));
@@ -2527,7 +2527,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     /* The slave requesting the vote must have a configEpoch for the claimed
      * slots that is >= the one of the masters currently serving the same
      * slots in the current configuration. */
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         if (bitmapTestBit(claimed_slots, j) == 0) continue;
         if (server.cluster->slots[j] == NULL ||
             server.cluster->slots[j]->configEpoch <= requestConfigEpoch)
@@ -2595,13 +2595,13 @@ int clusterGetSlaveRank(void) {
  *    when the slave finds that its master is fine (no FAIL flag).
  * 2) Also, the log is emitted again if the master is still down and
  *    the reason for not failing over is still the same, but more than
- *    REDIS_CLUSTER_CANT_FAILOVER_RELOG_PERIOD seconds elapsed.
+ *    CLUSTER_CANT_FAILOVER_RELOG_PERIOD seconds elapsed.
  * 3) Finally, the function only logs if the slave is down for more than
  *    five seconds + NODE_TIMEOUT. This way nothing is logged when a
  *    failover starts in a reasonable time.
  *
  * The function is called with the reason why the slave can't failover
- * which is one of the integer macros REDIS_CLUSTER_CANT_FAILOVER_*.
+ * which is one of the integer macros CLUSTER_CANT_FAILOVER_*.
  *
  * The function is guaranteed to be called only if 'myself' is a slave. */
 void clusterLogCantFailover(int reason) {
@@ -2611,7 +2611,7 @@ void clusterLogCantFailover(int reason) {
 
     /* Don't log if we have the same reason for some time. */
     if (reason == server.cluster->cant_failover_reason &&
-        time(NULL)-lastlog_time < REDIS_CLUSTER_CANT_FAILOVER_RELOG_PERIOD)
+        time(NULL)-lastlog_time < CLUSTER_CANT_FAILOVER_RELOG_PERIOD)
         return;
 
     server.cluster->cant_failover_reason = reason;
@@ -2624,16 +2624,16 @@ void clusterLogCantFailover(int reason) {
         (mstime() - myself->slaveof->fail_time) < nolog_fail_time) return;
 
     switch(reason) {
-    case REDIS_CLUSTER_CANT_FAILOVER_DATA_AGE:
+    case CLUSTER_CANT_FAILOVER_DATA_AGE:
         msg = "Disconnected from master for longer than allowed.";
         break;
-    case REDIS_CLUSTER_CANT_FAILOVER_WAITING_DELAY:
+    case CLUSTER_CANT_FAILOVER_WAITING_DELAY:
         msg = "Waiting the delay before I can start a new failover.";
         break;
-    case REDIS_CLUSTER_CANT_FAILOVER_EXPIRED:
+    case CLUSTER_CANT_FAILOVER_EXPIRED:
         msg = "Failover attempt expired.";
         break;
-    case REDIS_CLUSTER_CANT_FAILOVER_WAITING_VOTES:
+    case CLUSTER_CANT_FAILOVER_WAITING_VOTES:
         msg = "Waiting for votes, but majority still not reached.";
         break;
     default:
@@ -2661,7 +2661,7 @@ void clusterFailoverReplaceYourMaster(void) {
     replicationUnsetMaster();
 
     /* 2) Claim all the slots assigned to our master. */
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         if (clusterNodeGetSlotBit(oldmaster,j)) {
             clusterDelSlot(j);
             clusterAddSlot(myself,j);
@@ -2721,7 +2721,7 @@ void clusterHandleSlaveFailover(void) {
     {
         /* There are no reasons to failover, so we set the reason why we
          * are returning without failing over to NONE. */
-        server.cluster->cant_failover_reason = REDIS_CLUSTER_CANT_FAILOVER_NONE;
+        server.cluster->cant_failover_reason = CLUSTER_CANT_FAILOVER_NONE;
         return;
     }
 
@@ -2750,7 +2750,7 @@ void clusterHandleSlaveFailover(void) {
          (server.cluster_node_timeout * server.cluster_slave_validity_factor)))
     {
         if (!manual_failover) {
-            clusterLogCantFailover(REDIS_CLUSTER_CANT_FAILOVER_DATA_AGE);
+            clusterLogCantFailover(CLUSTER_CANT_FAILOVER_DATA_AGE);
             return;
         }
     }
@@ -2809,13 +2809,13 @@ void clusterHandleSlaveFailover(void) {
 
     /* Return ASAP if we can't still start the election. */
     if (mstime() < server.cluster->failover_auth_time) {
-        clusterLogCantFailover(REDIS_CLUSTER_CANT_FAILOVER_WAITING_DELAY);
+        clusterLogCantFailover(CLUSTER_CANT_FAILOVER_WAITING_DELAY);
         return;
     }
 
     /* Return ASAP if the election is too old to be valid. */
     if (auth_age > auth_timeout) {
-        clusterLogCantFailover(REDIS_CLUSTER_CANT_FAILOVER_EXPIRED);
+        clusterLogCantFailover(CLUSTER_CANT_FAILOVER_EXPIRED);
         return;
     }
 
@@ -2851,7 +2851,7 @@ void clusterHandleSlaveFailover(void) {
         /* Take responsability for the cluster slots. */
         clusterFailoverReplaceYourMaster();
     } else {
-        clusterLogCantFailover(REDIS_CLUSTER_CANT_FAILOVER_WAITING_VOTES);
+        clusterLogCantFailover(CLUSTER_CANT_FAILOVER_WAITING_VOTES);
     }
 }
 
@@ -2889,7 +2889,7 @@ void clusterHandleSlaveMigration(int max_slaves) {
     dictEntry *de;
 
     /* Step 1: Don't migrate if the cluster state is not ok. */
-    if (server.cluster->state != REDIS_CLUSTER_OK) return;
+    if (server.cluster->state != CLUSTER_OK) return;
 
     /* Step 2: Don't migrate if my master will not be left with at least
      *         'migration-barrier' slaves after my migration. */
@@ -2929,7 +2929,7 @@ void clusterHandleSlaveMigration(int max_slaves) {
             for (j = 0; j < node->numslaves; j++) {
                 if (memcmp(node->slaves[j]->name,
                            candidate->name,
-                           REDIS_CLUSTER_NAMELEN) < 0)
+                           CLUSTER_NAMELEN) < 0)
                 {
                     candidate = node->slaves[j];
                 }
@@ -2955,7 +2955,7 @@ void clusterHandleSlaveMigration(int max_slaves) {
  *    setting mf_end to the millisecond unix time at which we'll abort the
  *    attempt.
  * 2) Slave sends a MFSTART message to the master requesting to pause clients
- *    for two times the manual failover timeout REDIS_CLUSTER_MF_TIMEOUT.
+ *    for two times the manual failover timeout CLUSTER_MF_TIMEOUT.
  *    When master is paused for manual failover, it also starts to flag
  *    packets with CLUSTERMSG_FLAG0_PAUSED.
  * 3) Slave waits for master to send its replication offset flagged as PAUSED.
@@ -3053,7 +3053,7 @@ void clusterCron(void) {
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
-        if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR)) continue;
+        if (node->flags & (CLUSTER_NODE_MYSELF|CLUSTER_NODE_NOADDR)) continue;
 
         /* A Node in HANDSHAKE state has a limited lifespan equal to the
          * configured node timeout. */
@@ -3068,7 +3068,7 @@ void clusterCron(void) {
             clusterLink *link;
 
             fd = anetTcpNonBlockBindConnect(server.neterr, node->ip,
-                node->port+REDIS_CLUSTER_PORT_INCR, NET_FIRST_BIND_ADDR);
+                node->port+CLUSTER_PORT_INCR, NET_FIRST_BIND_ADDR);
             if (fd == -1) {
                 /* We got a synchronous error from connect before
                  * clusterSendPing() had a chance to be called.
@@ -3078,7 +3078,7 @@ void clusterCron(void) {
                 if (node->ping_sent == 0) node->ping_sent = mstime();
                 serverLog(LL_DEBUG, "Unable to connect to "
                     "Cluster Node [%s]:%d -> %s", node->ip,
-                    node->port+REDIS_CLUSTER_PORT_INCR,
+                    node->port+CLUSTER_PORT_INCR,
                     server.neterr);
                 continue;
             }
@@ -3094,7 +3094,7 @@ void clusterCron(void) {
              * of a PING one, to force the receiver to add us in its node
              * table. */
             old_ping_sent = node->ping_sent;
-            clusterSendPing(link, node->flags & REDIS_NODE_MEET ?
+            clusterSendPing(link, node->flags & CLUSTER_NODE_MEET ?
                     CLUSTERMSG_TYPE_MEET : CLUSTERMSG_TYPE_PING);
             if (old_ping_sent) {
                 /* If there was an active ping before the link was
@@ -3107,10 +3107,10 @@ void clusterCron(void) {
              * to this node. Instead after the PONG is received and we
              * are no longer in meet/handshake status, we want to send
              * normal PING packets. */
-            node->flags &= ~REDIS_NODE_MEET;
+            node->flags &= ~CLUSTER_NODE_MEET;
 
             serverLog(LL_DEBUG,"Connecting with Node %.40s at %s:%d",
-                    node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
+                    node->name, node->ip, node->port+CLUSTER_PORT_INCR);
         }
     }
     dictReleaseIterator(di);
@@ -3128,7 +3128,7 @@ void clusterCron(void) {
 
             /* Don't ping nodes disconnected or with a ping currently active. */
             if (this->link == NULL || this->ping_sent != 0) continue;
-            if (this->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE))
+            if (this->flags & (CLUSTER_NODE_MYSELF|CLUSTER_NODE_HANDSHAKE))
                 continue;
             if (min_pong_node == NULL || min_pong > this->pong_received) {
                 min_pong_node = this;
@@ -3157,7 +3157,7 @@ void clusterCron(void) {
         mstime_t delay;
 
         if (node->flags &
-            (REDIS_NODE_MYSELF|REDIS_NODE_NOADDR|REDIS_NODE_HANDSHAKE))
+            (CLUSTER_NODE_MYSELF|CLUSTER_NODE_NOADDR|CLUSTER_NODE_HANDSHAKE))
                 continue;
 
         /* Orphaned master check, useful only if the current instance
@@ -3224,10 +3224,10 @@ void clusterCron(void) {
         if (delay > server.cluster_node_timeout) {
             /* Timeout reached. Set the node as possibly failing if it is
              * not already in this state. */
-            if (!(node->flags & (REDIS_NODE_PFAIL|REDIS_NODE_FAIL))) {
+            if (!(node->flags & (CLUSTER_NODE_PFAIL|CLUSTER_NODE_FAIL))) {
                 serverLog(LL_DEBUG,"*** NODE %.40s possibly failing",
                     node->name);
-                node->flags |= REDIS_NODE_PFAIL;
+                node->flags |= CLUSTER_NODE_PFAIL;
                 update_state = 1;
             }
         }
@@ -3260,7 +3260,7 @@ void clusterCron(void) {
             clusterHandleSlaveMigration(max_slaves);
     }
 
-    if (update_state || server.cluster->state == REDIS_CLUSTER_FAIL)
+    if (update_state || server.cluster->state == CLUSTER_FAIL)
         clusterUpdateState();
 }
 
@@ -3370,7 +3370,7 @@ int clusterDelSlot(int slot) {
 int clusterDelNodeSlots(clusterNode *node) {
     int deleted = 0, j;
 
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         if (clusterNodeGetSlotBit(node,j)) clusterDelSlot(j);
         deleted++;
     }
@@ -3394,9 +3394,9 @@ void clusterCloseAllSlots(void) {
  * and are based on heuristics. Actaully the main point about the rejoin and
  * writable delay is that they should be a few orders of magnitude larger
  * than the network latency. */
-#define REDIS_CLUSTER_MAX_REJOIN_DELAY 5000
-#define REDIS_CLUSTER_MIN_REJOIN_DELAY 500
-#define REDIS_CLUSTER_WRITABLE_DELAY 2000
+#define CLUSTER_MAX_REJOIN_DELAY 5000
+#define CLUSTER_MIN_REJOIN_DELAY 500
+#define CLUSTER_WRITABLE_DELAY 2000
 
 void clusterUpdateState(void) {
     int j, new_state;
@@ -3414,20 +3414,20 @@ void clusterUpdateState(void) {
      * to don't count the DB loading time. */
     if (first_call_time == 0) first_call_time = mstime();
     if (nodeIsMaster(myself) &&
-        server.cluster->state == REDIS_CLUSTER_FAIL &&
-        mstime() - first_call_time < REDIS_CLUSTER_WRITABLE_DELAY) return;
+        server.cluster->state == CLUSTER_FAIL &&
+        mstime() - first_call_time < CLUSTER_WRITABLE_DELAY) return;
 
     /* Start assuming the state is OK. We'll turn it into FAIL if there
      * are the right conditions. */
-    new_state = REDIS_CLUSTER_OK;
+    new_state = CLUSTER_OK;
 
     /* Check if all the slots are covered. */
     if (server.cluster_require_full_coverage) {
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        for (j = 0; j < CLUSTER_SLOTS; j++) {
             if (server.cluster->slots[j] == NULL ||
-                server.cluster->slots[j]->flags & (REDIS_NODE_FAIL))
+                server.cluster->slots[j]->flags & (CLUSTER_NODE_FAIL))
             {
-                new_state = REDIS_CLUSTER_FAIL;
+                new_state = CLUSTER_FAIL;
                 break;
             }
         }
@@ -3449,7 +3449,7 @@ void clusterUpdateState(void) {
 
             if (nodeIsMaster(node) && node->numslots) {
                 server.cluster->size++;
-                if ((node->flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) == 0)
+                if ((node->flags & (CLUSTER_NODE_FAIL|CLUSTER_NODE_PFAIL)) == 0)
                     reachable_masters++;
             }
         }
@@ -3462,7 +3462,7 @@ void clusterUpdateState(void) {
         int needed_quorum = (server.cluster->size / 2) + 1;
 
         if (reachable_masters < needed_quorum) {
-            new_state = REDIS_CLUSTER_FAIL;
+            new_state = CLUSTER_FAIL;
             among_minority_time = mstime();
         }
     }
@@ -3475,12 +3475,12 @@ void clusterUpdateState(void) {
          * minority, don't let it accept queries for some time after the
          * partition heals, to make sure there is enough time to receive
          * a configuration update. */
-        if (rejoin_delay > REDIS_CLUSTER_MAX_REJOIN_DELAY)
-            rejoin_delay = REDIS_CLUSTER_MAX_REJOIN_DELAY;
-        if (rejoin_delay < REDIS_CLUSTER_MIN_REJOIN_DELAY)
-            rejoin_delay = REDIS_CLUSTER_MIN_REJOIN_DELAY;
+        if (rejoin_delay > CLUSTER_MAX_REJOIN_DELAY)
+            rejoin_delay = CLUSTER_MAX_REJOIN_DELAY;
+        if (rejoin_delay < CLUSTER_MIN_REJOIN_DELAY)
+            rejoin_delay = CLUSTER_MIN_REJOIN_DELAY;
 
-        if (new_state == REDIS_CLUSTER_OK &&
+        if (new_state == CLUSTER_OK &&
             nodeIsMaster(myself) &&
             mstime() - among_minority_time < rejoin_delay)
         {
@@ -3489,7 +3489,7 @@ void clusterUpdateState(void) {
 
         /* Change the state and log the event. */
         serverLog(LL_WARNING,"Cluster state changed: %s",
-            new_state == REDIS_CLUSTER_OK ? "ok" : "fail");
+            new_state == CLUSTER_OK ? "ok" : "fail");
         server.cluster->state = new_state;
     }
 }
@@ -3531,7 +3531,7 @@ int verifyClusterConfigWithData(void) {
 
     /* Check that all the slots we see populated memory have a corresponding
      * entry in the cluster table. Otherwise fix the table. */
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         if (!countKeysInSlot(j)) continue; /* No keys in this slot. */
         /* Check if we are assigned to this slot or if we are importing it.
          * In both cases check the next slot as the configuration makes
@@ -3571,8 +3571,8 @@ void clusterSetMaster(clusterNode *n) {
     serverAssert(myself->numslots == 0);
 
     if (nodeIsMaster(myself)) {
-        myself->flags &= ~REDIS_NODE_MASTER;
-        myself->flags |= REDIS_NODE_SLAVE;
+        myself->flags &= ~CLUSTER_NODE_MASTER;
+        myself->flags |= CLUSTER_NODE_SLAVE;
         clusterCloseAllSlots();
     } else {
         if (myself->slaveof)
@@ -3594,13 +3594,13 @@ struct redisNodeFlags {
 };
 
 static struct redisNodeFlags redisNodeFlagsTable[] = {
-    {REDIS_NODE_MYSELF,    "myself,"},
-    {REDIS_NODE_MASTER,    "master,"},
-    {REDIS_NODE_SLAVE,     "slave,"},
-    {REDIS_NODE_PFAIL,     "fail?,"},
-    {REDIS_NODE_FAIL,      "fail,"},
-    {REDIS_NODE_HANDSHAKE, "handshake,"},
-    {REDIS_NODE_NOADDR,    "noaddr,"}
+    {CLUSTER_NODE_MYSELF,    "myself,"},
+    {CLUSTER_NODE_MASTER,    "master,"},
+    {CLUSTER_NODE_SLAVE,     "slave,"},
+    {CLUSTER_NODE_PFAIL,     "fail?,"},
+    {CLUSTER_NODE_FAIL,      "fail,"},
+    {CLUSTER_NODE_HANDSHAKE, "handshake,"},
+    {CLUSTER_NODE_NOADDR,    "noaddr,"}
 };
 
 /* Concatenate the comma separated list of node flags to the given SDS
@@ -3647,19 +3647,19 @@ sds clusterGenNodeDescription(clusterNode *node) {
         (long long) node->ping_sent,
         (long long) node->pong_received,
         (unsigned long long) node->configEpoch,
-        (node->link || node->flags & REDIS_NODE_MYSELF) ?
+        (node->link || node->flags & CLUSTER_NODE_MYSELF) ?
                     "connected" : "disconnected");
 
     /* Slots served by this instance */
     start = -1;
-    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    for (j = 0; j < CLUSTER_SLOTS; j++) {
         int bit;
 
         if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
             if (start == -1) start = j;
         }
-        if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
-            if (bit && j == REDIS_CLUSTER_SLOTS-1) j++;
+        if (start != -1 && (!bit || j == CLUSTER_SLOTS-1)) {
+            if (bit && j == CLUSTER_SLOTS-1) j++;
 
             if (start == j-1) {
                 ci = sdscatprintf(ci," %d",start);
@@ -3673,8 +3673,8 @@ sds clusterGenNodeDescription(clusterNode *node) {
     /* Just for MYSELF node we also dump info about slots that
      * we are migrating to other instances or importing from other
      * instances. */
-    if (node->flags & REDIS_NODE_MYSELF) {
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+    if (node->flags & CLUSTER_NODE_MYSELF) {
+        for (j = 0; j < CLUSTER_SLOTS; j++) {
             if (server.cluster->migrating_slots_to[j]) {
                 ci = sdscatprintf(ci," [%d->-%.40s]",j,
                     server.cluster->migrating_slots_to[j]->name);
@@ -3726,7 +3726,7 @@ int getSlotOrReply(client *c, robj *o) {
     long long slot;
 
     if (getLongLongFromObject(o,&slot) != C_OK ||
-        slot < 0 || slot >= REDIS_CLUSTER_SLOTS)
+        slot < 0 || slot >= CLUSTER_SLOTS)
     {
         addReplyError(c,"Invalid or out of range slot");
         return -1;
@@ -3757,17 +3757,17 @@ void clusterReplyMultiBulkSlots(client *c) {
          * master) and  masters not serving any slot. */
         if (!nodeIsMaster(node) || node->numslots == 0) continue;
 
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        for (j = 0; j < CLUSTER_SLOTS; j++) {
             int bit, i;
 
             if ((bit = clusterNodeGetSlotBit(node,j)) != 0) {
                 if (start == -1) start = j;
             }
-            if (start != -1 && (!bit || j == REDIS_CLUSTER_SLOTS-1)) {
+            if (start != -1 && (!bit || j == CLUSTER_SLOTS-1)) {
                 int nested_elements = 3; /* slots (2) + master addr (1). */
                 void *nested_replylen = addDeferredMultiBulkLength(c);
 
-                if (bit && j == REDIS_CLUSTER_SLOTS-1) j++;
+                if (bit && j == CLUSTER_SLOTS-1) j++;
 
                 /* If slot exists in output map, add to it's list.
                  * else, create a new output map for this slot */
@@ -3837,7 +3837,7 @@ void clusterCommand(client *c) {
         decrRefCount(o);
     } else if (!strcasecmp(c->argv[1]->ptr,"myid") && c->argc == 2) {
         /* CLUSTER MYID */
-        addReplyBulkCBuffer(c,myself->name, REDIS_CLUSTER_NAMELEN);
+        addReplyBulkCBuffer(c,myself->name, CLUSTER_NAMELEN);
     } else if (!strcasecmp(c->argv[1]->ptr,"slots") && c->argc == 2) {
         /* CLUSTER SLOTS */
         clusterReplyMultiBulkSlots(c);
@@ -3856,10 +3856,10 @@ void clusterCommand(client *c) {
         /* CLUSTER ADDSLOTS <slot> [slot] ... */
         /* CLUSTER DELSLOTS <slot> [slot] ... */
         int j, slot;
-        unsigned char *slots = zmalloc(REDIS_CLUSTER_SLOTS);
+        unsigned char *slots = zmalloc(CLUSTER_SLOTS);
         int del = !strcasecmp(c->argv[1]->ptr,"delslots");
 
-        memset(slots,0,REDIS_CLUSTER_SLOTS);
+        memset(slots,0,CLUSTER_SLOTS);
         /* Check that all the arguments are parseable and that all the
          * slots are not already busy. */
         for (j = 2; j < c->argc; j++) {
@@ -3883,7 +3883,7 @@ void clusterCommand(client *c) {
                 return;
             }
         }
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        for (j = 0; j < CLUSTER_SLOTS; j++) {
             if (slots[j]) {
                 int retval;
 
@@ -3999,7 +3999,7 @@ void clusterCommand(client *c) {
         uint64_t myepoch;
         int j;
 
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        for (j = 0; j < CLUSTER_SLOTS; j++) {
             clusterNode *n = server.cluster->slots[j];
 
             if (n == NULL) continue;
@@ -4063,7 +4063,7 @@ void clusterCommand(client *c) {
 
         if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
             return;
-        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS) {
+        if (slot < 0 || slot >= CLUSTER_SLOTS) {
             addReplyError(c,"Invalid slot");
             return;
         }
@@ -4079,7 +4079,7 @@ void clusterCommand(client *c) {
         if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL)
             != C_OK)
             return;
-        if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0) {
+        if (slot < 0 || slot >= CLUSTER_SLOTS || maxkeys < 0) {
             addReplyError(c,"Invalid slot or number of keys");
             return;
         }
@@ -4213,7 +4213,7 @@ void clusterCommand(client *c) {
             return;
         }
         resetManualFailover();
-        server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
+        server.cluster->mf_end = mstime() + CLUSTER_MF_TIMEOUT;
 
         if (takeover) {
             /* A takeover does not perform any initial check. It just
@@ -4760,22 +4760,22 @@ void readwriteCommand(client *c) {
  * On success the function returns the node that is able to serve the request.
  * If the node is not 'myself' a redirection must be perfomed. The kind of
  * redirection is specified setting the integer passed by reference
- * 'error_code', which will be set to REDIS_CLUSTER_REDIR_ASK or
- * REDIS_CLUSTER_REDIR_MOVED.
+ * 'error_code', which will be set to CLUSTER_REDIR_ASK or
+ * CLUSTER_REDIR_MOVED.
  *
- * When the node is 'myself' 'error_code' is set to REDIS_CLUSTER_REDIR_NONE.
+ * When the node is 'myself' 'error_code' is set to CLUSTER_REDIR_NONE.
  *
  * If the command fails NULL is returned, and the reason of the failure is
  * provided via 'error_code', which will be set to:
  *
- * REDIS_CLUSTER_REDIR_CROSS_SLOT if the request contains multiple keys that
+ * CLUSTER_REDIR_CROSS_SLOT if the request contains multiple keys that
  * don't belong to the same hash slot.
  *
- * REDIS_CLUSTER_REDIR_UNSTABLE if the request contains mutliple keys
+ * CLUSTER_REDIR_UNSTABLE if the request contains mutliple keys
  * belonging to the same slot, but the slot is not stable (in migration or
  * importing state, likely because a resharding is in progress).
  *
- * REDIS_CLUSTER_REDIR_DOWN_UNBOUND if the request addresses a slot which is
+ * CLUSTER_REDIR_DOWN_UNBOUND if the request addresses a slot which is
  * not bound to any node. In this case the cluster global state should be
  * already "down" but it is fragile to rely on the update of the global state,
  * so we also handle it here. */
@@ -4788,7 +4788,7 @@ clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, in
     int i, slot = 0, migrating_slot = 0, importing_slot = 0, missing_keys = 0;
 
     /* Set error code optimistically for the base case. */
-    if (error_code) *error_code = REDIS_CLUSTER_REDIR_NONE;
+    if (error_code) *error_code = CLUSTER_REDIR_NONE;
 
     /* We handle all the cases as if they were EXEC commands, so we have
      * a common code path for everything */
@@ -4840,7 +4840,7 @@ clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, in
                 if (n == NULL) {
                     getKeysFreeResult(keyindex);
                     if (error_code)
-                        *error_code = REDIS_CLUSTER_REDIR_DOWN_UNBOUND;
+                        *error_code = CLUSTER_REDIR_DOWN_UNBOUND;
                     return NULL;
                 }
 
@@ -4864,7 +4864,7 @@ clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, in
                         /* Error: multiple keys from different slots. */
                         getKeysFreeResult(keyindex);
                         if (error_code)
-                            *error_code = REDIS_CLUSTER_REDIR_CROSS_SLOT;
+                            *error_code = CLUSTER_REDIR_CROSS_SLOT;
                         return NULL;
                     } else {
                         /* Flag this request as one with multiple different
@@ -4897,7 +4897,7 @@ clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, in
     /* If we don't have all the keys and we are migrating the slot, send
      * an ASK redirection. */
     if (migrating_slot && missing_keys) {
-        if (error_code) *error_code = REDIS_CLUSTER_REDIR_ASK;
+        if (error_code) *error_code = CLUSTER_REDIR_ASK;
         return server.cluster->migrating_slots_to[slot];
     }
 
@@ -4909,7 +4909,7 @@ clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, in
         (c->flags & CLIENT_ASKING || cmd->flags & CMD_ASKING))
     {
         if (multiple_keys && missing_keys) {
-            if (error_code) *error_code = REDIS_CLUSTER_REDIR_UNSTABLE;
+            if (error_code) *error_code = CLUSTER_REDIR_UNSTABLE;
             return NULL;
         } else {
             return myself;
@@ -4929,35 +4929,35 @@ clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, in
 
     /* Base case: just return the right node. However if this node is not
      * myself, set error_code to MOVED since we need to issue a rediretion. */
-    if (n != myself && error_code) *error_code = REDIS_CLUSTER_REDIR_MOVED;
+    if (n != myself && error_code) *error_code = CLUSTER_REDIR_MOVED;
     return n;
 }
 
 /* Send the client the right redirection code, according to error_code
- * that should be set to one of REDIS_CLUSTER_REDIR_* macros.
+ * that should be set to one of CLUSTER_REDIR_* macros.
  *
- * If REDIS_CLUSTER_REDIR_ASK or REDIS_CLUSTER_REDIR_MOVED error codes
+ * If CLUSTER_REDIR_ASK or CLUSTER_REDIR_MOVED error codes
  * are used, then the node 'n' should not be NULL, but should be the
  * node we want to mention in the redirection. Moreover hashslot should
  * be set to the hash slot that caused the redirection. */
 void clusterRedirectClient(client *c, clusterNode *n, int hashslot, int error_code) {
-    if (error_code == REDIS_CLUSTER_REDIR_CROSS_SLOT) {
+    if (error_code == CLUSTER_REDIR_CROSS_SLOT) {
         addReplySds(c,sdsnew("-CROSSSLOT Keys in request don't hash to the same slot\r\n"));
-    } else if (error_code == REDIS_CLUSTER_REDIR_UNSTABLE) {
+    } else if (error_code == CLUSTER_REDIR_UNSTABLE) {
         /* The request spawns mutliple keys in the same slot,
          * but the slot is not "stable" currently as there is
          * a migration or import in progress. */
         addReplySds(c,sdsnew("-TRYAGAIN Multiple keys request during rehashing of slot\r\n"));
-    } else if (error_code == REDIS_CLUSTER_REDIR_DOWN_STATE) {
+    } else if (error_code == CLUSTER_REDIR_DOWN_STATE) {
         addReplySds(c,sdsnew("-CLUSTERDOWN The cluster is down\r\n"));
-    } else if (error_code == REDIS_CLUSTER_REDIR_DOWN_UNBOUND) {
+    } else if (error_code == CLUSTER_REDIR_DOWN_UNBOUND) {
         addReplySds(c,sdsnew("-CLUSTERDOWN Hash slot not served\r\n"));
-    } else if (error_code == REDIS_CLUSTER_REDIR_MOVED ||
-               error_code == REDIS_CLUSTER_REDIR_ASK)
+    } else if (error_code == CLUSTER_REDIR_MOVED ||
+               error_code == CLUSTER_REDIR_ASK)
     {
         addReplySds(c,sdscatprintf(sdsempty(),
             "-%s %d %s:%d\r\n",
-            (error_code == REDIS_CLUSTER_REDIR_ASK) ? "ASK" : "MOVED",
+            (error_code == CLUSTER_REDIR_ASK) ? "ASK" : "MOVED",
             hashslot,n->ip,n->port));
     } else {
         serverPanic("getNodeByQuery() unknown error.");
@@ -4981,8 +4981,8 @@ int clusterRedirectBlockedClientIfNeeded(client *c) {
         dictIterator *di;
 
         /* If the cluster is down, unblock the client with the right error. */
-        if (server.cluster->state == REDIS_CLUSTER_FAIL) {
-            clusterRedirectClient(c,NULL,0,REDIS_CLUSTER_REDIR_DOWN_STATE);
+        if (server.cluster->state == CLUSTER_FAIL) {
+            clusterRedirectClient(c,NULL,0,CLUSTER_REDIR_DOWN_STATE);
             return 1;
         }
 
@@ -5000,10 +5000,10 @@ int clusterRedirectBlockedClientIfNeeded(client *c) {
             {
                 if (node == NULL) {
                     clusterRedirectClient(c,NULL,0,
-                        REDIS_CLUSTER_REDIR_DOWN_UNBOUND);
+                        CLUSTER_REDIR_DOWN_UNBOUND);
                 } else {
                     clusterRedirectClient(c,node,slot,
-                        REDIS_CLUSTER_REDIR_MOVED);
+                        CLUSTER_REDIR_MOVED);
                 }
                 return 1;
             }