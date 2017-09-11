@@ -55,6 +55,7 @@ int clusterNodeSetSlotBit(clusterNode *n, int slot);
 void clusterSetMaster(clusterNode *n);
 void clusterHandleSlaveFailover(void);
 int bitmapTestBit(unsigned char *bitmap, int pos);
+void clusterDoBeforeSleep(int flags);
 
 /* -----------------------------------------------------------------------------
  * Initialization
@@ -222,14 +223,14 @@ int clusterLoadConfig(char *filename) {
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
-    fsync(fd);
+    if (do_fsync) fsync(fd);
     close(fd);
     sdsfree(ci);
     return 0;
@@ -239,8 +240,8 @@ int clusterSaveConfig(void) {
     return -1;
 }
 
-void clusterSaveConfigOrDie(void) {
-    if (clusterSaveConfig() == -1) {
+void clusterSaveConfigOrDie(int do_fsync) {
+    if (clusterSaveConfig(do_fsync) == -1) {
         redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
         exit(1);
     }
@@ -277,7 +278,7 @@ void clusterInit(void) {
         clusterAddNode(server.cluster->myself);
         saveconf = 1;
     }
-    if (saveconf) clusterSaveConfigOrDie();
+    if (saveconf) clusterSaveConfigOrDie(1);
 
     /* We need a listening TCP port for our cluster messaging needs. */
     server.cfd_count = 0;
@@ -665,15 +666,13 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
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
@@ -685,7 +684,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
             "Clear FAIL state for node %.40s: slave is already reachable.",
                 node->name);
         node->flags &= ~REDIS_NODE_FAIL;
-        changes++;
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
     }
 
     /* If it is a master and...
@@ -705,13 +704,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
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
 
@@ -926,13 +919,12 @@ int clusterProcessPacket(clusterLink *link) {
         /* Update the sender configEpoch if it is publishing a newer one. */
         if (senderConfigEpoch > sender->configEpoch) {
             sender->configEpoch = senderConfigEpoch;
-            clusterSaveConfigOrDie();
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_FSYNC_CONFIG);
         }
     }
 
     /* Process packets by type. */
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
-        int update_config = 0;
         redisLog(REDIS_DEBUG,"Ping packet received: %p", (void*)link->node);
 
         /* Add this node if it is new for us and the msg type is MEET.
@@ -946,26 +938,20 @@ int clusterProcessPacket(clusterLink *link) {
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
@@ -978,8 +964,8 @@ int clusterProcessPacket(clusterLink *link) {
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
@@ -994,7 +980,7 @@ int clusterProcessPacket(clusterLink *link) {
                     link->node->name);
                 link->node->flags &= ~REDIS_NODE_HANDSHAKE;
                 link->node->flags |= flags&(REDIS_NODE_MASTER|REDIS_NODE_SLAVE);
-                update_config = 1;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
             } else if (memcmp(link->node->name,hdr->sender,
                         REDIS_CLUSTER_NAMELEN) != 0)
             {
@@ -1006,7 +992,7 @@ int clusterProcessPacket(clusterLink *link) {
                 link->node->ip[0] = '\0';
                 link->node->port = 0;
                 freeClusterLink(link);
-                update_config = 1;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                 /* FIXME: remove this node if we already have it.
                  *
                  * If we already have it but the IP is different, use
@@ -1021,8 +1007,7 @@ int clusterProcessPacket(clusterLink *link) {
             !(sender->flags & REDIS_NODE_HANDSHAKE) &&
             nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
         {
-            update_state = 1;
-            update_config = 1;
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
         }
 
         /* Update our info about the node */
@@ -1038,7 +1023,8 @@ int clusterProcessPacket(clusterLink *link) {
              * conditions detected by clearNodeFailureIfNeeded(). */
             if (link->node->flags & REDIS_NODE_PFAIL) {
                 link->node->flags &= ~REDIS_NODE_PFAIL;
-                update_state = 1;
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                     CLUSTER_TODO_UPDATE_STATE);
             } else if (link->node->flags & REDIS_NODE_FAIL) {
                 clearNodeFailureIfNeeded(link->node);
             }
@@ -1059,8 +1045,8 @@ int clusterProcessPacket(clusterLink *link) {
                     sender->slaveof = NULL;
 
                     /* Update config and state. */
-                    update_state = 1;
-                    update_config = 1;
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                         CLUSTER_TODO_UPDATE_STATE);
                 }
             } else {
                 /* Node is a slave. */
@@ -1076,8 +1062,8 @@ int clusterProcessPacket(clusterLink *link) {
                     if (sender->numslaves) clusterNodeResetSlaves(sender);
 
                     /* Update config and state. */
-                    update_state = 1;
-                    update_config = 1;
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                         CLUSTER_TODO_UPDATE_STATE);
                 }
 
                 /* Master node changed for this slave? */
@@ -1088,7 +1074,7 @@ int clusterProcessPacket(clusterLink *link) {
                     sender->slaveof = master;
 
                     /* Update config. */
-                    update_config = 1;
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
                 }
             }
         }
@@ -1126,7 +1112,9 @@ int clusterProcessPacket(clusterLink *link) {
                                 newmaster = sender;
                             clusterDelSlot(j);
                             clusterAddSlot(sender,j);
-                            update_state = update_config = 1;
+                            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                                 CLUSTER_TODO_UPDATE_STATE|
+                                                 CLUSTER_TODO_FSYNC_CONFIG);
                         }
                     } else {
                         /* This node claims to no longer handling the slot,
@@ -1150,16 +1138,15 @@ int clusterProcessPacket(clusterLink *link) {
                 if (newmaster && curmaster->numslots == 0) {
                     redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
                     clusterSetMaster(sender);
+                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                         CLUSTER_TODO_UPDATE_STATE|
+                                         CLUSTER_TODO_FSYNC_CONFIG);
                 }
             }
         }
 
         /* Get info from the gossip section */
         clusterProcessGossipSection(hdr,link);
-
-        /* Update the cluster state if needed */
-        if (update_state) clusterUpdateState();
-        if (update_config) clusterSaveConfigOrDie();
     } else if (type == CLUSTERMSG_TYPE_FAIL) {
         clusterNode *failing;
 
@@ -1173,8 +1160,7 @@ int clusterProcessPacket(clusterLink *link) {
                 failing->flags |= REDIS_NODE_FAIL;
                 failing->fail_time = time(NULL);
                 failing->flags &= ~REDIS_NODE_PFAIL;
-                clusterUpdateState();
-                clusterSaveConfigOrDie();
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
             }
         } else {
             redisLog(REDIS_NOTICE,
@@ -1185,7 +1171,8 @@ int clusterProcessPacket(clusterLink *link) {
         robj *channel, *message;
         uint32_t channel_len, message_len;
 
-        /* Don't bother creating useless objects if there are no Pub/Sub subscribers. */
+        /* Don't bother creating useless objects if there are no
+         * Pub/Sub subscribers. */
         if (dictSize(server.pubsub_channels) || listLength(server.pubsub_patterns)) {
             channel_len = ntohl(hdr->data.publish.msg.channel_len);
             message_len = ntohl(hdr->data.publish.msg.message_len);
@@ -1212,7 +1199,7 @@ int clusterProcessPacket(clusterLink *link) {
             server.cluster->failover_auth_count++;
             /* Maybe we reached a quorum here, set a flag to make sure
              * we check ASAP. */
-            server.cluster->handle_slave_failover_asap++;
+            clusterDoBeforeSleep(CLUSTER_TODO_HANDLE_FAILOVER);
         }
     } else {
         redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
@@ -1673,6 +1660,9 @@ void clusterHandleSlaveFailover(void) {
             server.cluster->currentEpoch);
         clusterRequestFailoverAuth();
         server.cluster->failover_auth_sent = 1;
+        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                             CLUSTER_TODO_UPDATE_STATE|
+                             CLUSTER_TODO_FSYNC_CONFIG);
         return; /* Wait for replies. */
     }
 
@@ -1706,7 +1696,7 @@ void clusterHandleSlaveFailover(void) {
 
         /* 4) Update state and save config. */
         clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterSaveConfigOrDie(1);
 
         /* 5) Pong all the other nodes so that they can update the state
          *    accordingly and detect that we switched to master role. */
@@ -1878,12 +1868,30 @@ void clusterCron(void) {
 /* This function is called before the event handler returns to sleep for
  * events. It is useful to perform operations that must be done ASAP in
  * reaction to events fired but that are not safe to perform inside event
- * handlers. */
+ * handlers, or to perform potentially expansive tasks that we need to do
+ * a single time before replying to clients. */
 void clusterBeforeSleep(void) {
-    if (server.cluster->handle_slave_failover_asap) {
+    /* Handle failover, this is needed when it is likely that there is already
+     * the quorum from masters in order to react fast. */
+    if (server.cluster->todo_before_sleep & CLUSTER_TODO_HANDLE_FAILOVER)
         clusterHandleSlaveFailover();
-        server.cluster->handle_slave_failover_asap = 0;
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
+
+    /* Reset our flags. */
+    server.cluster->todo_before_sleep = 0;
+}
+
+void clusterDoBeforeSleep(int flags) {
+    server.cluster->todo_before_sleep |= flags;
 }
 
 /* -----------------------------------------------------------------------------
@@ -2097,7 +2105,7 @@ int verifyClusterConfigWithData(void) {
             server.cluster->importing_slots_from[j] = server.cluster->slots[j];
         }
     }
-    if (update_config) clusterSaveConfigOrDie();
+    if (update_config) clusterSaveConfigOrDie(1);
     return REDIS_OK;
 }
 
@@ -2296,8 +2304,7 @@ void clusterCommand(redisClient *c) {
             return;
         }
         clusterDelNodeSlots(server.cluster->myself);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if ((!strcasecmp(c->argv[1]->ptr,"addslots") ||
                !strcasecmp(c->argv[1]->ptr,"delslots")) && c->argc >= 3)
@@ -2347,8 +2354,7 @@ void clusterCommand(redisClient *c) {
             }
         }
         zfree(slots);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"setslot") && c->argc >= 4) {
         /* SETSLOT 10 MIGRATING <node ID> */
@@ -2424,8 +2430,7 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;
         }
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         /* CLUSTER INFO */
@@ -2474,7 +2479,7 @@ void clusterCommand(redisClient *c) {
         addReplySds(c,info);
         addReply(c,shared.crlf);
     } else if (!strcasecmp(c->argv[1]->ptr,"saveconfig") && c->argc == 2) {
-        int retval = clusterSaveConfig();
+        int retval = clusterSaveConfig(1);
 
         if (retval == 0)
             addReply(c,shared.ok);
@@ -2526,8 +2531,7 @@ void clusterCommand(redisClient *c) {
             return;
         }
         clusterDelNode(n);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"replicate") && c->argc == 3) {
         /* CLUSTER REPLICATE <NODE ID> */
@@ -2562,8 +2566,7 @@ void clusterCommand(redisClient *c) {
 
         /* Set the master. */
         clusterSetMaster(n);
-        clusterUpdateState();
-        clusterSaveConfigOrDie();
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else {
         addReplyError(c,"Wrong CLUSTER subcommand or number of arguments");