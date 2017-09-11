@@ -53,12 +53,31 @@ int clusterDelSlot(int slot);
 int clusterDelNodeSlots(clusterNode *node);
 int clusterNodeSetSlotBit(clusterNode *n, int slot);
 void clusterSetMaster(clusterNode *n);
+void clusterHandleSlaveFailover(void);
 int bitmapTestBit(unsigned char *bitmap, int pos);
+void clusterDoBeforeSleep(int flags);
 
 /* -----------------------------------------------------------------------------
  * Initialization
  * -------------------------------------------------------------------------- */
 
+/* This function is called at startup in order to set the currentEpoch
+ * (which is not saved on permanent storage) to the greatest configEpoch found
+ * in the loaded nodes (configEpoch is stored on permanent storage as soon as
+ * it changes for some node). */
+void clusterSetStartupEpoch() {
+    dictIterator *di;
+    dictEntry *de;
+
+    di = dictGetSafeIterator(server.cluster->nodes);
+    while((de = dictNext(di)) != NULL) {
+        clusterNode *node = dictGetVal(de);
+        if (node->configEpoch > server.cluster->currentEpoch)
+            server.cluster->currentEpoch = node->configEpoch;
+    }
+    dictReleaseIterator(di);
+}
+
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
     char *line;
@@ -117,8 +136,6 @@ int clusterLoadConfig(char *filename) {
                 n->flags |= REDIS_NODE_HANDSHAKE;
             } else if (!strcasecmp(s,"noaddr")) {
                 n->flags |= REDIS_NODE_NOADDR;
-            } else if (!strcasecmp(s,"promoted")) {
-                n->flags |= REDIS_NODE_PROMOTED;
             } else if (!strcasecmp(s,"noflags")) {
                 /* nothing to do */
             } else {
@@ -143,8 +160,11 @@ int clusterLoadConfig(char *filename) {
         if (atoi(argv[4])) n->ping_sent = time(NULL);
         if (atoi(argv[5])) n->pong_received = time(NULL);
 
+        /* Set configEpoch for this node. */
+        n->configEpoch = strtoull(argv[6],NULL,10);
+
         /* Populate hash slots served by this instance. */
-        for (j = 7; j < argc; j++) {
+        for (j = 8; j < argc; j++) {
             int start, stop;
 
             if (argv[j][0] == '[') {
@@ -189,6 +209,7 @@ int clusterLoadConfig(char *filename) {
     redisAssert(server.cluster->myself != NULL);
     redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s",
         server.cluster->myself->name);
+    clusterSetStartupEpoch();
     clusterUpdateState();
     return REDIS_OK;
 
@@ -202,13 +223,14 @@ int clusterLoadConfig(char *filename) {
  *
  * This function writes the node config and returns 0, on error -1
  * is returned. */
-int clusterSaveConfig(void) {
+int clusterSaveConfig(int do_fsync) {
     sds ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
     int fd;
     
     if ((fd = open(server.cluster_configfile,O_WRONLY|O_CREAT|O_TRUNC,0644))
         == -1) goto err;
     if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
+    if (do_fsync) fsync(fd);
     close(fd);
     sdsfree(ci);
     return 0;
@@ -218,8 +240,8 @@ int clusterSaveConfig(void) {
     return -1;
 }
 
-void clusterSaveConfigOrDie(void) {
-    if (clusterSaveConfig() == -1) {
+void clusterSaveConfigOrDie(int do_fsync) {
+    if (clusterSaveConfig(do_fsync) == -1) {
         redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
         exit(1);
     }
@@ -230,11 +252,16 @@ void clusterInit(void) {
 
     server.cluster = zmalloc(sizeof(clusterState));
     server.cluster->myself = NULL;
+    server.cluster->currentEpoch = 0;
     server.cluster->state = REDIS_CLUSTER_FAIL;
     server.cluster->size = 1;
     server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
     server.cluster->failover_auth_time = 0;
     server.cluster->failover_auth_count = 0;
+    server.cluster->failover_auth_epoch = 0;
+    server.cluster->last_vote_epoch = 0;
+    server.cluster->stats_bus_messages_sent = 0;
+    server.cluster->stats_bus_messages_received = 0;
     memset(server.cluster->migrating_slots_to,0,
         sizeof(server.cluster->migrating_slots_to));
     memset(server.cluster->importing_slots_from,0,
@@ -251,7 +278,7 @@ void clusterInit(void) {
         clusterAddNode(server.cluster->myself);
         saveconf = 1;
     }
-    if (saveconf) clusterSaveConfigOrDie();
+    if (saveconf) clusterSaveConfigOrDie(1);
 
     /* We need a listening TCP port for our cluster messaging needs. */
     server.cfd_count = 0;
@@ -360,6 +387,7 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     else
         getRandomHexChars(node->name, REDIS_CLUSTER_NAMELEN);
     node->ctime = time(NULL);
+    node->configEpoch = 0;
     node->flags = flags;
     memset(node->slots,0,sizeof(node->slots));
     node->numslots = 0;
@@ -372,6 +400,7 @@ clusterNode *createClusterNode(char *nodename, int flags) {
     memset(node->ip,0,sizeof(node->ip));
     node->port = 0;
     node->fail_reports = listCreate();
+    node->voted_time = 0;
     listSetFreeMethod(node->fail_reports,zfree);
     return node;
 }
@@ -637,15 +666,13 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
      * reachable nodes to flag the node as FAIL. */
     if (server.cluster->myself->flags & REDIS_NODE_MASTER)
         clusterSendFail(node->name);
-    clusterUpdateState();
-    clusterSaveConfigOrDie();
+    clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
 }
 
 /* This function is called only if a node is marked as FAIL, but we are able
  * to reach it again. It checks if there are the conditions to undo the FAIL
  * state. */
 void clearNodeFailureIfNeeded(clusterNode *node) {
-    int changes = 0;
     time_t now = time(NULL);
 
     redisAssert(node->flags & REDIS_NODE_FAIL);
@@ -654,10 +681,10 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
      * node again. */
     if (node->flags & REDIS_NODE_SLAVE) {
         redisLog(REDIS_NOTICE,
-            "Clear FAIL state for node %.40s: slave is already reachable.",
+            "Clear FAIL state for node %.40s: slave is reachable again.",
                 node->name);
         node->flags &= ~REDIS_NODE_FAIL;
-        changes++;
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
     }
 
     /* If it is a master and...
@@ -677,13 +704,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
             "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                 node->name);
         node->flags &= ~REDIS_NODE_FAIL;
-        changes++;
-    }
-
-    /* Update state and save config. */
-    if (changes) {
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
     }
 }
 
@@ -727,7 +748,6 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         if (flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
         if (flags & REDIS_NODE_HANDSHAKE) ci = sdscat(ci,"handshake,");
         if (flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
-        if (flags & REDIS_NODE_PROMOTED) ci = sdscat(ci,"promoted,");
         if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
 
         redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
@@ -850,8 +870,10 @@ int clusterProcessPacket(clusterLink *link) {
     uint32_t totlen = ntohl(hdr->totlen);
     uint16_t type = ntohs(hdr->type);
     uint16_t flags = ntohs(hdr->flags);
+    uint64_t senderCurrentEpoch, senderConfigEpoch;
     clusterNode *sender;
 
+    server.cluster->stats_bus_messages_received++;
     redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
 
@@ -886,11 +908,23 @@ int clusterProcessPacket(clusterLink *link) {
         if (totlen != explen) return 1;
     }
 
-    /* Process packets by type. */
+    /* Check if the sender is a known node. */
     sender = clusterLookupNode(hdr->sender);
+    if (sender && !(sender->flags & REDIS_NODE_HANDSHAKE)) {
+        /* Update our curretEpoch if we see a newer epoch in the cluster. */
+        senderCurrentEpoch = ntohu64(hdr->currentEpoch);
+        senderConfigEpoch = ntohu64(hdr->configEpoch);
+        if (senderCurrentEpoch > server.cluster->currentEpoch)
+            server.cluster->currentEpoch = senderCurrentEpoch;
+        /* Update the sender configEpoch if it is publishing a newer one. */
+        if (senderConfigEpoch > sender->configEpoch) {
+            sender->configEpoch = senderConfigEpoch;
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_FSYNC_CONFIG);
+        }
+    }
 
+    /* Process packets by type. */
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
-        int update_config = 0;
         redisLog(REDIS_DEBUG,"Ping packet received: %p", (void*)link->node);
 
         /* Add this node if it is new for us and the msg type is MEET.
@@ -904,26 +938,20 @@ int clusterProcessPacket(clusterLink *link) {
             nodeIp2String(node->ip,link);
             node->port = ntohs(hdr->port);
             clusterAddNode(node);
-            update_config = 1;
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
         }
 
         /* Get info from the gossip section */
         clusterProcessGossipSection(hdr,link);
 
         /* Anyway reply with a PONG */
         clusterSendPing(link,CLUSTERMSG_TYPE_PONG);
-
-        /* Update config if needed */
-        if (update_config) clusterSaveConfigOrDie();
     }
 
     /* PING or PONG: process config information. */
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
         type == CLUSTERMSG_TYPE_MEET)
     {
-        int update_state = 0;
-        int update_config = 0;
-
         redisLog(REDIS_DEBUG,"%s packet received: %p",
             type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
             (void*)link->node);
@@ -936,8 +964,8 @@ int clusterProcessPacket(clusterLink *link) {
                         "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
                     if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
                     {
-                        clusterUpdateState();
-                        clusterSaveConfigOrDie();
+                        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                             CLUSTER_TODO_UPDATE_STATE);
                     }
                     /* Free this node as we alrady have it. This will
                      * cause the link to be freed as well. */
@@ -952,7 +980,7 @@ int clusterProcessPacket(clusterLink *link) {
                     link->node->name);
                 link->node->flags &= ~REDIS_NODE_HANDSHAKE;
                 link->node->flags |= flags&(REDIS_NODE_MASTER|REDIS_NODE_SLAVE);
-                update_config = 1;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
             } else if (memcmp(link->node->name,hdr->sender,
                         REDIS_CLUSTER_NAMELEN) != 0)
             {
@@ -964,7 +992,7 @@ int clusterProcessPacket(clusterLink *link) {
                 link->node->ip[0] = '\0';
                 link->node->port = 0;
                 freeClusterLink(link);
-                update_config = 1;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                 /* FIXME: remove this node if we already have it.
                  *
                  * If we already have it but the IP is different, use
@@ -979,8 +1007,7 @@ int clusterProcessPacket(clusterLink *link) {
             !(sender->flags & REDIS_NODE_HANDSHAKE) &&
             nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
         {
-            update_state = 1;
-            update_config = 1;
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
         }
 
         /* Update our info about the node */
@@ -996,7 +1023,8 @@ int clusterProcessPacket(clusterLink *link) {
              * conditions detected by clearNodeFailureIfNeeded(). */
             if (link->node->flags & REDIS_NODE_PFAIL) {
                 link->node->flags &= ~REDIS_NODE_PFAIL;
-                update_state = 1;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                     CLUSTER_TODO_UPDATE_STATE);
             } else if (link->node->flags & REDIS_NODE_FAIL) {
                 clearNodeFailureIfNeeded(link->node);
             }
@@ -1009,42 +1037,16 @@ int clusterProcessPacket(clusterLink *link) {
             {
                 /* Node is a master. */
                 if (sender->flags & REDIS_NODE_SLAVE) {
-                    /* Slave turned into master! */
-                    clusterNode *oldmaster = sender->slaveof;
-
                     /* Reconfigure node as master. */
                     if (sender->slaveof)
                         clusterNodeRemoveSlave(sender->slaveof,sender);
                     sender->flags &= ~REDIS_NODE_SLAVE;
                     sender->flags |= REDIS_NODE_MASTER;
                     sender->slaveof = NULL;
 
-                    /* If this node used to be our slave, and now has the
-                     * PROMOTED flag set. We'll turn ourself into a slave
-                     * of the new master. */
-                    if (flags & REDIS_NODE_PROMOTED &&
-                        oldmaster == server.cluster->myself)
-                    {
-                        redisLog(REDIS_WARNING,"One of my slaves took my place. Reconfiguring myself as a replica of %.40s", sender->name);
-                        clusterDelNodeSlots(server.cluster->myself);
-                        clusterSetMaster(sender);
-                    }
-
-                    /* If we are a slave, and this node used to be a slave
-                     * of our master, and now has the PROMOTED flag set, we
-                     * need to switch our replication setup over it. */
-                    if (flags & REDIS_NODE_PROMOTED &&
-                        server.cluster->myself->flags & REDIS_NODE_SLAVE &&
-                        server.cluster->myself->slaveof == oldmaster)
-                    {
-                        redisLog(REDIS_WARNING,"One of the slaves failed over my master. Reconfiguring myself as a replica of %.40s", sender->name);
-                        clusterDelNodeSlots(server.cluster->myself);
-                        clusterSetMaster(sender);
-                    }
-
                     /* Update config and state. */
-                    update_state = 1;
-                    update_config = 1;
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                         CLUSTER_TODO_UPDATE_STATE);
                 }
             } else {
                 /* Node is a slave. */
@@ -1060,8 +1062,8 @@ int clusterProcessPacket(clusterLink *link) {
                     if (sender->numslaves) clusterNodeResetSlaves(sender);
 
                     /* Update config and state. */
-                    update_state = 1;
-                    update_config = 1;
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                         CLUSTER_TODO_UPDATE_STATE);
                 }
 
                 /* Master node changed for this slave? */
@@ -1070,6 +1072,9 @@ int clusterProcessPacket(clusterLink *link) {
                         clusterNodeRemoveSlave(sender->slaveof,sender);
                     clusterNodeAddSlave(master,sender);
                     sender->slaveof = master;
+
+                    /* Update config. */
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                 }
             }
         }
@@ -1083,55 +1088,91 @@ int clusterProcessPacket(clusterLink *link) {
             changes =
                 memcmp(sender->slots,hdr->myslots,sizeof(hdr->myslots)) != 0;
             if (changes) {
+                clusterNode *curmaster, *newmaster = NULL;
+
+                /* Here we set curmaster to this node or the node this node
+                 * replicates to if it's a slave. In the for loop we are
+                 * interested to check if slots are taken away from curmaster. */
+                if (server.cluster->myself->flags & REDIS_NODE_MASTER)
+                    curmaster = server.cluster->myself;
+                else
+                    curmaster = server.cluster->myself->slaveof;
+
                 for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
                     if (bitmapTestBit(hdr->myslots,j)) {
-                        /* If this slot was not served, or served by a node
-                         * in FAIL state, update the table with the new node
-                         * claiming to serve the slot. */
+                        /* We rebind the slot to the new node claiming it if:
+                         * 1) The slot was unassigned.
+                         * 2) The new node claims it with a greater configEpoch. */
                         if (server.cluster->slots[j] == sender) continue;
                         if (server.cluster->slots[j] == NULL ||
-                            server.cluster->slots[j]->flags & REDIS_NODE_FAIL)
+                            server.cluster->slots[j]->configEpoch <
+                            senderConfigEpoch)
                         {
+                            if (server.cluster->slots[j] == curmaster)
+                                newmaster = sender;
                             clusterDelSlot(j);
                             clusterAddSlot(sender,j);
-                            update_state = update_config = 1;
+                            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                                 CLUSTER_TODO_UPDATE_STATE|
+                                                 CLUSTER_TODO_FSYNC_CONFIG);
                         }
                     } else {
                         /* This node claims to no longer handling the slot,
-                         * however we don't change our config as this is likely
-                         * happening because a resharding is in progress, and
-                         * it already knows where to redirect clients. */
+                         * however we don't change our config as this is likely:
+                         * 1) Rehashing in progress.
+                         * 2) Failover.
+                         * In both cases we'll be informed about who is serving
+                         * the slot eventually. In the meantime it's up to the
+                         * original owner to try to redirect our clients to the
+                         * right node. */
                     }
                 }
+
+                /* If at least one slot was reassigned from a node to another node
+                 * with a greater configEpoch, it is possible that:
+                 * 1) We are a master is left without slots. This means that we were
+                 *    failed over and we should turn into a replica of the new
+                 *    master.
+                 * 2) We are a slave and our master is left without slots. We need
+                 *    to replicate to the new slots owner. */
+                if (newmaster && curmaster->numslots == 0) {
+                    redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
+                    clusterSetMaster(sender);
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                         CLUSTER_TODO_UPDATE_STATE|
+                                         CLUSTER_TODO_FSYNC_CONFIG);
+                }
             }
         }
 
         /* Get info from the gossip section */
         clusterProcessGossipSection(hdr,link);
-
-        /* Update the cluster state if needed */
-        if (update_state) clusterUpdateState();
-        if (update_config) clusterSaveConfigOrDie();
-    } else if (type == CLUSTERMSG_TYPE_FAIL && sender) {
+    } else if (type == CLUSTERMSG_TYPE_FAIL) {
         clusterNode *failing;
 
-        failing = clusterLookupNode(hdr->data.fail.about.nodename);
-        if (failing && !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
-        {
+        if (sender) {
+            failing = clusterLookupNode(hdr->data.fail.about.nodename);
+            if (failing && !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
+            {
+                redisLog(REDIS_NOTICE,
+                    "FAIL message received from %.40s about %.40s",
+                    hdr->sender, hdr->data.fail.about.nodename);
+                failing->flags |= REDIS_NODE_FAIL;
+                failing->fail_time = time(NULL);
+                failing->flags &= ~REDIS_NODE_PFAIL;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
+            }
+        } else {
             redisLog(REDIS_NOTICE,
-                "FAIL message received from %.40s about %.40s",
+                "Ignoring FAIL message from unknonw node %.40s about %.40s",
                 hdr->sender, hdr->data.fail.about.nodename);
-            failing->flags |= REDIS_NODE_FAIL;
-            failing->fail_time = time(NULL);
-            failing->flags &= ~REDIS_NODE_PFAIL;
-            clusterUpdateState();
-            clusterSaveConfigOrDie();
         }
     } else if (type == CLUSTERMSG_TYPE_PUBLISH) {
         robj *channel, *message;
         uint32_t channel_len, message_len;
 
-        /* Don't bother creating useless objects if there are no Pub/Sub subscribers. */
+        /* Don't bother creating useless objects if there are no
+         * Pub/Sub subscribers. */
         if (dictSize(server.pubsub_channels) || listLength(server.pubsub_patterns)) {
             channel_len = ntohl(hdr->data.publish.msg.channel_len);
             message_len = ntohl(hdr->data.publish.msg.message_len);
@@ -1145,15 +1186,21 @@ int clusterProcessPacket(clusterLink *link) {
         }
     } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST) {
         if (!sender) return 1;  /* We don't know that node. */
-        /* If we are not a master, ignore that message at all. */
-        if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return 0;
         clusterSendFailoverAuthIfNeeded(sender,hdr);
     } else if (type == CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK) {
         if (!sender) return 1;  /* We don't know that node. */
-        /* If this is a master, increment the number of acknowledges
-         * we received so far. */
-        if (sender->flags & REDIS_NODE_MASTER)
+        /* We consider this vote only if the sender is a master serving
+         * a non zero number of slots, and its currentEpoch is greater or
+         * equal to epoch where this node started the election. */
+        if (sender->flags & REDIS_NODE_MASTER &&
+            sender->numslots > 0 &&
+            senderCurrentEpoch >= server.cluster->failover_auth_epoch)
+        {
             server.cluster->failover_auth_count++;
+            /* Maybe we reached a quorum here, set a flag to make sure
+             * we check ASAP. */
+            clusterDoBeforeSleep(CLUSTER_TODO_HANDLE_FAILOVER);
+        }
     } else {
         redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
     }
@@ -1253,17 +1300,26 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 }
 
-/* Put stuff into the send buffer. */
+/* Put stuff into the send buffer.
+ *
+ * It is guaranteed that this function will never have as a side effect
+ * the link to be invalidated, so it is safe to call this function
+ * from event handlers that will do stuff with the same link later. */
 void clusterSendMessage(clusterLink *link, unsigned char *msg, size_t msglen) {
     if (sdslen(link->sndbuf) == 0 && msglen != 0)
         aeCreateFileEvent(server.el,link->fd,AE_WRITABLE,
                     clusterWriteHandler,link);
 
     link->sndbuf = sdscatlen(link->sndbuf, msg, msglen);
+    server.cluster->stats_bus_messages_sent++;
 }
 
 /* Send a message to all the nodes that are part of the cluster having
- * a connected link. */
+ * a connected link.
+ * 
+ * It is guaranteed that this function will never have as a side effect
+ * some node->link to be invalidated, so it is safe to call this function
+ * from event handlers that will do stuff with node links later. */
 void clusterBroadcastMessage(void *buf, size_t len) {
     dictIterator *di;
     dictEntry *de;
@@ -1283,12 +1339,21 @@ void clusterBroadcastMessage(void *buf, size_t len) {
 /* Build the message header */
 void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     int totlen = 0;
+    clusterNode *master;
+
+    /* If this node is a master, we send its slots bitmap and configEpoch.
+     * If this node is a slave we send the master's information instead (the
+     * node is flagged as slave so the receiver knows that it is NOT really
+     * in charge for this slots. */
+    master = (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
+              server.cluster->myself->slaveof) ?
+              server.cluster->myself->slaveof : server.cluster->myself;
 
     memset(hdr,0,sizeof(*hdr));
     hdr->type = htons(type);
     memcpy(hdr->sender,server.cluster->myself->name,REDIS_CLUSTER_NAMELEN);
-    memcpy(hdr->myslots,server.cluster->myself->slots,
-        sizeof(hdr->myslots));
+
+    memcpy(hdr->myslots,master->slots,sizeof(hdr->myslots));
     memset(hdr->slaveof,0,REDIS_CLUSTER_NAMELEN);
     if (server.cluster->myself->slaveof != NULL) {
         memcpy(hdr->slaveof,server.cluster->myself->slaveof->name,
@@ -1298,12 +1363,16 @@ void clusterBuildMessageHdr(clusterMsg *hdr, int type) {
     hdr->flags = htons(server.cluster->myself->flags);
     hdr->state = server.cluster->state;
 
+    /* Set the currentEpoch and configEpochs. */
+    hdr->currentEpoch = htonu64(server.cluster->currentEpoch);
+    hdr->configEpoch = htonu64(master->configEpoch);
+
     if (type == CLUSTERMSG_TYPE_FAIL) {
         totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
         totlen += sizeof(clusterMsgDataFail);
     }
     hdr->totlen = htonl(totlen);
-    /* For PING, PONG, and MEET, fixing the totlen field is up to the caller */
+    /* For PING, PONG, and MEET, fixing the totlen field is up to the caller. */
 }
 
 /* Send a PING or PONG packet to the specified node, making sure to add enough
@@ -1370,10 +1439,11 @@ void clusterSendPing(clusterLink *link, int type) {
     clusterSendMessage(link,buf,totlen);
 }
 
-/* Send a PONG packet to every connected node that's not in handshake state.
+/* Send a PONG packet to every connected node that's not in handshake state
+ * and for which we have a valid link.
  *
- * In Redis Cluster pings are not just used for failure detection, but also
- * to carry important configuration informations. So broadcasting a pong is
+ * In Redis Cluster pongs are not used just for failure detection, but also
+ * to carry important configuration information. So broadcasting a pong is
  * useful when something changes in the configuration and we want to make
  * the cluster aware ASAP (for instance after a slave promotion). */
 void clusterBroadcastPong(void) {
@@ -1384,6 +1454,7 @@ void clusterBroadcastPong(void) {
     while((de = dictNext(di)) != NULL) {
         clusterNode *node = dictGetVal(de);
 
+        if (!node->link) continue;
         if (node->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE)) continue;
         clusterSendPing(node->link,CLUSTERMSG_TYPE_PONG);
     }
@@ -1477,14 +1548,11 @@ void clusterRequestFailoverAuth(void) {
     clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_FAILOVER_AUTH_REQUEST);
     totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
     hdr->totlen = htonl(totlen);
-    hdr->time = mstime();
     clusterBroadcastMessage(buf,totlen);
 }
 
-/* Send a FAILOVER_AUTH_ACK message to the specified node.
- * Reqtime is the time field from the original failover auth request packet,
- * so that the receiver is able to check the reply age. */
-void clusterSendFailoverAuth(clusterNode *node, uint64_t reqtime) {
+/* Send a FAILOVER_AUTH_ACK message to the specified node. */
+void clusterSendFailoverAuth(clusterNode *node) {
     unsigned char buf[4096];
     clusterMsg *hdr = (clusterMsg*) buf;
     uint32_t totlen;
@@ -1493,84 +1561,136 @@ void clusterSendFailoverAuth(clusterNode *node, uint64_t reqtime) {
     clusterBuildMessageHdr(hdr,CLUSTERMSG_TYPE_FAILOVER_AUTH_ACK);
     totlen = sizeof(clusterMsg)-sizeof(union clusterMsgData);
     hdr->totlen = htonl(totlen);
-    hdr->time = reqtime;
     clusterSendMessage(node->link,buf,totlen);
 }
 
-/* If we believe 'node' is the "first slave" of it's master, reply with
- * a FAILOVER_AUTH_GRANTED packet.
- * The 'request' field points to the authorization request packet header, we
- * need it in order to copy back the 'time' field in our reply.
- *
- * To be a first slave the sender must:
- * 1) Be a slave.
- * 2) Its master should be in FAIL state.
- * 3) Ordering all the slaves IDs for its master by run-id, it should be the
- *    first (the smallest) among the ones not in FAIL / PFAIL state.
- */
+/* Vote for the node asking for our vote if there are the conditions. */
 void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
-    char first[REDIS_CLUSTER_NAMELEN];
     clusterNode *master = node->slaveof;
+    uint64_t requestCurrentEpoch = ntohu64(request->currentEpoch);
+    uint64_t requestConfigEpoch = ntohu64(request->configEpoch);
+    unsigned char *claimed_slots = request->myslots;
     int j;
 
-    /* Node is a slave? Its master is down? */
+    /* IF we are not a master serving at least 1 slot, we don't have the
+     * right to vote, as the cluster size in Redis Cluster is the number
+     * of masters serving at least one slot, and quorum is the cluster size + 1 */
+    if (!(server.cluster->myself->flags & REDIS_NODE_MASTER)) return;
+    if (server.cluster->myself->numslots == 0) return;
+
+    /* Request epoch must be >= our currentEpoch. */
+    if (requestCurrentEpoch < server.cluster->currentEpoch) return;
+
+    /* I already voted for this epoch? Return ASAP. */
+    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) return;
+
+    /* Node must be a slave and its master down. */
     if (!(node->flags & REDIS_NODE_SLAVE) ||
         master == NULL ||
         !(master->flags & REDIS_NODE_FAIL)) return;
 
-    /* Iterate all the master slaves to check what's the first one. */
-    memset(first,0xff,sizeof(first));
-    for (j = 0; j < master->numslaves; j++) {
-        clusterNode *slave = master->slaves[j];
+    /* We did not voted for a slave about this master for two
+     * times the node timeout. This is not strictly needed for correctness
+     * of the algorithm but makes the base case more linear. */
+    if (server.unixtime - node->slaveof->voted_time <
+        server.cluster_node_timeout * 2) return;
 
-        if (slave->flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) continue;
-        if (memcmp(slave->name,first,sizeof(first)) < 0) {
-            memcpy(first,slave->name,sizeof(first));
-        }
+    /* The slave requesting the vote must have a configEpoch for the claimed slots
+     * that is >= the one of the masters currently serving the same slots in the
+     * current configuration. */
+    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        if (bitmapTestBit(claimed_slots, j) == 0) continue;
+        if (server.cluster->slots[j] == NULL ||
+            server.cluster->slots[j]->configEpoch <= requestConfigEpoch) continue;
+        /* If we reached this point we found a slot that in our current slots
+         * is served by a master with a greater configEpoch than the one claimed
+         * by the slave requesting our vote. Refuse to vote for this slave. */
+        return;
     }
 
-    /* Is 'node' the first slave? */
-    if (memcmp(node->name,first,sizeof(first)) != 0) return;
-
-    /* We can send the packet. */
-    clusterSendFailoverAuth(node,request->time);
+    /* We can vote for this slave. */
+    clusterSendFailoverAuth(node);
+    server.cluster->last_vote_epoch = server.cluster->currentEpoch;
+    node->slaveof->voted_time = server.unixtime;
 }
 
 /* This function is called if we are a slave node and our master serving
  * a non-zero amount of hash slots is in FAIL state.
  *
  * The gaol of this function is:
  * 1) To check if we are able to perform a failover, is our data updated?
- * 2) Ask reachable masters the authorization to perform the failover.
- * 3) Check if there is the majority of masters agreeing we should failover.
- * 4) Perform the failover informing all the other nodes.
+ * 2) Try to get elected by masters.
+ * 3) Perform the failover informing all the other nodes.
  */
 void clusterHandleSlaveFailover(void) {
-    time_t data_age = server.unixtime - server.repl_down_since;
-    time_t auth_age = server.unixtime - server.cluster->failover_auth_time;
+    time_t data_age;
+    mstime_t auth_age = mstime() - server.cluster->failover_auth_time;
     int needed_quorum = (server.cluster->size / 2) + 1;
     int j;
 
+    /* Set data_age to the number of seconds we are disconnected from the master. */
+    if (server.repl_state == REDIS_REPL_CONNECTED) {
+        data_age = server.unixtime - server.master->lastinteraction;
+    } else {
+        data_age = server.unixtime - server.repl_down_since;
+    }
+
+    /* Pre conditions to run the function:
+     * 1) We are a slave.
+     * 2) Our master is flagged as FAIL.
+     * 3) It is serving slots. */
+    if (!(server.cluster->myself->flags & REDIS_NODE_SLAVE) ||
+        server.cluster->myself->slaveof == NULL ||
+        !(server.cluster->myself->slaveof->flags & REDIS_NODE_FAIL) ||
+        server.cluster->myself->slaveof->numslots == 0) return;
+
+    /* Remove the node timeout from the data age as it is fine that we are
+     * disconnected from our master at least for the time it was down to be
+     * flagged as FAIL, that's the baseline. */
+    if (data_age > server.cluster_node_timeout)
+        data_age -= server.cluster_node_timeout;
+
     /* Check if our data is recent enough. For now we just use a fixed
      * constant of ten times the node timeout since the cluster should
      * react much faster to a master down. */
     if (data_age >
         server.cluster_node_timeout * REDIS_CLUSTER_SLAVE_VALIDITY_MULT)
         return;
 
-    /* TODO: check if we are the first slave as well? Or just rely on the
-     * master authorization? */
-
-    /* Ask masters if we are authorized to perform the failover. If there
-     * is a pending auth request that's too old, reset it. */
+    /* Compute the time at which we can start an election. */
     if (server.cluster->failover_auth_time == 0 ||
         auth_age >
-        server.cluster_node_timeout * REDIS_CLUSTER_FAILOVER_AUTH_RETRY_MULT)
+        server.cluster_node_timeout * 1000 * REDIS_CLUSTER_FAILOVER_AUTH_RETRY_MULT)
     {
-        redisLog(REDIS_WARNING,"Asking masters if I can failover...");
-        server.cluster->failover_auth_time = time(NULL);
+        server.cluster->failover_auth_time = mstime() +
+            500 + /* Fixed delay of 500 milliseconds, let FAIL msg propagate. */
+            data_age * 100 + /* Add 100 milliseconds for every second of age. */
+            random() % 500; /* Random delay between 0 and 500 milliseconds. */
         server.cluster->failover_auth_count = 0;
+        server.cluster->failover_auth_sent = 0;
+        redisLog(REDIS_WARNING,"Start of election delayed for %lld milliseconds.",
+            server.cluster->failover_auth_time - mstime());
+        return;
+    }
+
+    /* Return ASAP if we can't still start the election. */
+    if (mstime() < server.cluster->failover_auth_time) return;
+
+    /* Return ASAP if the election is too old to be valid. */
+    if (mstime() - server.cluster->failover_auth_time > server.cluster_node_timeout * 1000)
+        return;
+
+    /* Ask for votes if needed. */
+    if (server.cluster->failover_auth_sent == 0) {
+        server.cluster->currentEpoch++;
+        server.cluster->failover_auth_epoch = server.cluster->currentEpoch;
+        redisLog(REDIS_WARNING,"Starting a failover election for epoch %llu.",
+            server.cluster->currentEpoch);
         clusterRequestFailoverAuth();
+        server.cluster->failover_auth_sent = 1;
+        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                             CLUSTER_TODO_UPDATE_STATE|
+                             CLUSTER_TODO_FSYNC_CONFIG);
         return; /* Wait for replies. */
     }
 
@@ -1579,7 +1699,7 @@ void clusterHandleSlaveFailover(void) {
         clusterNode *oldmaster = server.cluster->myself->slaveof;
 
         redisLog(REDIS_WARNING,
-            "Masters quorum reached: failing over my (failing) master.");
+            "Failover election won: I'm the new master.");
         /* We have the quorum, perform all the steps to correctly promote
          * this slave to a master.
          *
@@ -1588,7 +1708,6 @@ void clusterHandleSlaveFailover(void) {
                                server.cluster->myself);
         server.cluster->myself->flags &= ~REDIS_NODE_SLAVE;
         server.cluster->myself->flags |= REDIS_NODE_MASTER;
-        server.cluster->myself->flags |= REDIS_NODE_PROMOTED;
         server.cluster->myself->slaveof = NULL;
         replicationUnsetMaster();
 
@@ -1600,13 +1719,16 @@ void clusterHandleSlaveFailover(void) {
             }
         }
 
-        /* 3) Pong all the other nodes so that they can update the state
-         *    accordingly and detect that we switched to master role. */
-        clusterBroadcastPong();
+        /* 3) Update my configEpoch to the epoch of the election. */
+        server.cluster->myself->configEpoch = server.cluster->failover_auth_epoch;
 
         /* 4) Update state and save config. */
         clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterSaveConfigOrDie(1);
+
+        /* 5) Pong all the other nodes so that they can update the state
+         *    accordingly and detect that we switched to master role. */
+        clusterBroadcastPong();
     }
 }
 
@@ -1767,30 +1889,44 @@ void clusterCron(void) {
                              server.cluster->myself->slaveof->port);
     }
 
-    /* If we are a slave and our master is down, but is serving slots,
-     * call the function that handles the failover.
-     * This function is called with a small delay in order to let the
-     * FAIL message to propagate after failure detection, this is not
-     * strictly required but makes 99.99% of failovers mechanically
-     * simpler. */
-    if (server.cluster->myself->flags & REDIS_NODE_SLAVE &&
-        server.cluster->myself->slaveof &&
-        server.cluster->myself->slaveof->flags & REDIS_NODE_FAIL &&
-        (server.unixtime - server.cluster->myself->slaveof->fail_time) >
-         REDIS_CLUSTER_FAILOVER_DELAY &&
-        server.cluster->myself->slaveof->numslots != 0)
-    {
+    clusterHandleSlaveFailover();
+    if (update_state) clusterUpdateState();
+}
+
+/* This function is called before the event handler returns to sleep for
+ * events. It is useful to perform operations that must be done ASAP in
+ * reaction to events fired but that are not safe to perform inside event
+ * handlers, or to perform potentially expansive tasks that we need to do
+ * a single time before replying to clients. */
+void clusterBeforeSleep(void) {
+    /* Handle failover, this is needed when it is likely that there is already
+     * the quorum from masters in order to react fast. */
+    if (server.cluster->todo_before_sleep & CLUSTER_TODO_HANDLE_FAILOVER)
         clusterHandleSlaveFailover();
+
+    /* Update the cluster state. */
+    if (server.cluster->todo_before_sleep & CLUSTER_TODO_UPDATE_STATE)
+        clusterUpdateState();
+
+    /* Save the config, possibly using fsync. */
+    if (server.cluster->todo_before_sleep & CLUSTER_TODO_SAVE_CONFIG) {
+        int fsync = server.cluster->todo_before_sleep & CLUSTER_TODO_FSYNC_CONFIG;
+        clusterSaveConfigOrDie(fsync);
     }
 
-    if (update_state) clusterUpdateState();
+    /* Reset our flags. */
+    server.cluster->todo_before_sleep = 0;
+}
+
+void clusterDoBeforeSleep(int flags) {
+    server.cluster->todo_before_sleep |= flags;
 }
 
 /* -----------------------------------------------------------------------------
  * Slots management
  * -------------------------------------------------------------------------- */
 
-/* Test bit 'pos' in a generic bitmap. Return 1 if the bit is zet,
+/* Test bit 'pos' in a generic bitmap. Return 1 if the bit is set,
  * otherwise 0. */
 int bitmapTestBit(unsigned char *bitmap, int pos) {
     off_t byte = pos/8;
@@ -1913,8 +2049,14 @@ void clusterUpdateState(void) {
     }
 
     /* If we can't reach at least half the masters, change the cluster state
-     * as FAIL, as we are not even able to mark nodes as FAIL in this side
-     * of the netsplit because of lack of majority. */
+     * to FAIL, as we are not even able to mark nodes as FAIL in this side
+     * of the netsplit because of lack of majority.
+     *
+     * TODO: when this condition is entered, we should not undo it for some
+     * (small) time after the majority is reachable again, to make sure that
+     * other nodes have enough time to inform this node of a configuration change.
+     * Otherwise a client with an old routing table may write to this node
+     * and later it may turn into a slave losing the write. */
     {
         int needed_quorum = (server.cluster->size / 2) + 1;
         
@@ -1991,7 +2133,7 @@ int verifyClusterConfigWithData(void) {
             server.cluster->importing_slots_from[j] = server.cluster->slots[j];
         }
     }
-    if (update_config) clusterSaveConfigOrDie();
+    if (update_config) clusterSaveConfigOrDie(1);
     return REDIS_OK;
 }
 
@@ -2011,9 +2153,6 @@ void clusterSetMaster(clusterNode *n) {
         myself->flags &= ~REDIS_NODE_MASTER;
         myself->flags |= REDIS_NODE_SLAVE;
     }
-    /* Clear the promoted flag anyway if we are a slave, to ensure it will
-     * be set only when the node turns into a master because of fail over. */
-    myself->flags &= ~REDIS_NODE_PROMOTED;
     myself->slaveof = n;
     replicationSetMaster(n->ip, n->port);
 }
@@ -2061,7 +2200,6 @@ sds clusterGenNodesDescription(int filter) {
         if (node->flags & REDIS_NODE_FAIL) ci = sdscat(ci,"fail,");
         if (node->flags & REDIS_NODE_HANDSHAKE) ci =sdscat(ci,"handshake,");
         if (node->flags & REDIS_NODE_NOADDR) ci = sdscat(ci,"noaddr,");
-        if (node->flags & REDIS_NODE_PROMOTED) ci = sdscat(ci,"promoted,");
         if (ci[sdslen(ci)-1] == ',') ci[sdslen(ci)-1] = ' ';
 
         /* Slave of... or just "-" */
@@ -2071,9 +2209,10 @@ sds clusterGenNodesDescription(int filter) {
             ci = sdscatprintf(ci,"- ");
 
         /* Latency from the POV of this node, link status */
-        ci = sdscatprintf(ci,"%ld %ld %s",
+        ci = sdscatprintf(ci,"%ld %ld %llu %s",
             (long) node->ping_sent,
             (long) node->pong_received,
+            (unsigned long long) node->configEpoch,
             (node->link || node->flags & REDIS_NODE_MYSELF) ?
                         "connected" : "disconnected");
 
@@ -2193,8 +2332,7 @@ void clusterCommand(redisClient *c) {
             return;
         }
         clusterDelNodeSlots(server.cluster->myself);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
                !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3)
@@ -2244,8 +2382,7 @@ void clusterCommand(redisClient *c) {
             }
         }
         zfree(slots);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"setslot") && c->argc >= 4) {
         /* SETSLOT 10 MIGRATING <node ID> */
@@ -2321,8 +2458,7 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;
         }
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         /* CLUSTER INFO */
@@ -2352,20 +2488,26 @@ void clusterCommand(redisClient *c) {
             "cluster_slots_fail:%d\r\n"
             "cluster_known_nodes:%lu\r\n"
             "cluster_size:%d\r\n"
+            "cluster_current_epoch:%llu\r\n"
+            "cluster_stats_messages_sent:%lld\r\n"
+            "cluster_stats_messages_received:%lld\r\n"
             , statestr[server.cluster->state],
             slots_assigned,
             slots_ok,
             slots_pfail,
             slots_fail,
             dictSize(server.cluster->nodes),
-            server.cluster->size
+            server.cluster->size,
+            (unsigned long long) server.cluster->currentEpoch,
+            server.cluster->stats_bus_messages_sent,
+            server.cluster->stats_bus_messages_received
         );
         addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
             (unsigned long)sdslen(info)));
         addReplySds(c,info);
         addReply(c,shared.crlf);
     } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
-        int retval = clusterSaveConfig();
+        int retval = clusterSaveConfig(1);
 
         if (retval == 0)
             addReply(c,shared.ok);
@@ -2417,8 +2559,7 @@ void clusterCommand(redisClient *c) {
             return;
         }
         clusterDelNode(n);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"replicate") && c->argc == 3) {
         /* CLUSTER REPLICATE <NODE ID> */
@@ -2453,8 +2594,7 @@ void clusterCommand(redisClient *c) {
 
         /* Set the master. */
         clusterSetMaster(n);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");