@@ -233,7 +233,8 @@ int clusterLoadConfig(char *filename) {
     return REDIS_OK;
 
 fmterr:
-    redisLog(REDIS_WARNING,"Unrecoverable error: corrupted cluster config file.");
+    redisLog(REDIS_WARNING,
+        "Unrecoverable error: corrupted cluster config file.");
     fclose(fp);
     exit(1);
 }
@@ -1134,7 +1135,10 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
                     countKeysInSlot(j) &&
                     sender != myself)
                 {
-                    redisLog(REDIS_WARNING,"Slot update for a slot I still have keys received. Putting the slot in IMPORTING state. Please run the 'redis-trib fix' command.");
+                    redisLog(REDIS_WARNING,
+                        "I received a slot update for a slot I've still "
+                        "keys into. Putting the slot in IMPORTING state. "
+                        "Please run the 'redis-trib fix' command.");
                     server.cluster->importing_slots_from[j] = sender;
                 }
 
@@ -1157,7 +1161,9 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
      * 2) We are a slave and our master is left without slots. We need
      *    to replicate to the new slots owner. */
     if (newmaster && curmaster->numslots == 0) {
-        redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
+        redisLog(REDIS_WARNING,
+            "Configuration change detected. Reconfiguring myself "
+            "as a replica of %.40s", sender->name);
         clusterSetMaster(sender);
         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                              CLUSTER_TODO_UPDATE_STATE|
@@ -1188,7 +1194,7 @@ int clusterProcessPacket(clusterLink *link) {
 
     /* Perform sanity checks */
     if (totlen < 16) return 1; /* At least signature, version, totlen, count. */
-    if (ntohs(hdr->ver) != 0) return 1; /* Can't handle versions other than 0. */
+    if (ntohs(hdr->ver) != 0) return 1; /* Can't handle versions other than 0.*/
     if (totlen > sdslen(link->rcvbuf)) return 1;
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
         type == CLUSTERMSG_TYPE_MEET)
@@ -1236,7 +1242,8 @@ int clusterProcessPacket(clusterLink *link) {
         /* Update the sender configEpoch if it is publishing a newer one. */
         if (senderConfigEpoch > sender->configEpoch) {
             sender->configEpoch = senderConfigEpoch;
-            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_FSYNC_CONFIG);
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                 CLUSTER_TODO_FSYNC_CONFIG);
         }
         /* Update the replication offset info for this node. */
         sender->repl_offset = ntohu64(hdr->offset);
@@ -1250,7 +1257,10 @@ int clusterProcessPacket(clusterLink *link) {
             server.cluster->mf_master_offset == 0)
         {
             server.cluster->mf_master_offset = sender->repl_offset;
-            redisLog(REDIS_WARNING,"Received replication offset for paused master manual failover: %lld", server.cluster->mf_master_offset);
+            redisLog(REDIS_WARNING,
+                "Received replication offset for paused "
+                "master manual failover: %lld",
+                server.cluster->mf_master_offset);
         }
     }
 
@@ -1292,7 +1302,8 @@ int clusterProcessPacket(clusterLink *link) {
                  * IP/port of the node with the new one. */
                 if (sender) {
                     redisLog(REDIS_WARNING,
-                        "Handshake error: we already know node %.40s, updating the address if needed.", sender->name);
+                        "Handshake: we already know node %.40s, "
+                        "updating the address if needed.", sender->name);
                     if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
                     {
                         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
@@ -1333,7 +1344,8 @@ int clusterProcessPacket(clusterLink *link) {
             !nodeInHandshake(sender) &&
             nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
         {
-            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
+            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                 CLUSTER_TODO_UPDATE_STATE);
         }
 
         /* Update our info about the node */
@@ -1452,7 +1464,8 @@ int clusterProcessPacket(clusterLink *link) {
                             "Node %.40s has old slots configuration, sending "
                             "an UPDATE message about %.40s",
                                 sender->name, server.cluster->slots[j]->name);
-                        clusterSendUpdate(sender->link,server.cluster->slots[j]);
+                        clusterSendUpdate(sender->link,
+                            server.cluster->slots[j]);
 
                         /* TODO: instead of exiting the loop send every other
                          * UPDATE packet for other nodes that are the new owner
@@ -1479,7 +1492,8 @@ int clusterProcessPacket(clusterLink *link) {
                 failing->flags |= REDIS_NODE_FAIL;
                 failing->fail_time = mstime();
                 failing->flags &= ~REDIS_NODE_PFAIL;
-                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                     CLUSTER_TODO_UPDATE_STATE);
             }
         } else {
             redisLog(REDIS_NOTICE,
@@ -1536,7 +1550,8 @@ int clusterProcessPacket(clusterLink *link) {
             sender->name);
     } else if (type == CLUSTERMSG_TYPE_UPDATE) {
         clusterNode *n; /* The node the update is about. */
-        uint64_t reportedConfigEpoch = ntohu64(hdr->data.update.nodecfg.configEpoch);
+        uint64_t reportedConfigEpoch =
+                    ntohu64(hdr->data.update.nodecfg.configEpoch);
 
         if (!sender) return 1;  /* We don't know the sender. */
         n = clusterLookupNode(hdr->data.update.nodecfg.nodename);
@@ -1548,7 +1563,8 @@ int clusterProcessPacket(clusterLink *link) {
 
         /* Update the node's configEpoch. */
         n->configEpoch = reportedConfigEpoch;
-        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_FSYNC_CONFIG);
+        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                             CLUSTER_TODO_FSYNC_CONFIG);
 
         /* Check the bitmap of served slots and udpate our
          * config accordingly. */
@@ -2025,7 +2041,10 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
         if (bitmapTestBit(claimed_slots, j) == 0) continue;
         if (server.cluster->slots[j] == NULL ||
-            server.cluster->slots[j]->configEpoch <= requestConfigEpoch) continue;
+            server.cluster->slots[j]->configEpoch <= requestConfigEpoch)
+        {
+            continue;
+        }
         /* If we reached this point we found a slot that in our current slots
          * is served by a master with a greater configEpoch than the one claimed
          * by the slave requesting our vote. Refuse to vote for this slave. */
@@ -2298,7 +2317,9 @@ void clusterHandleSlaveMigration(int max_slaves) {
         if (nodeIsSlave(node) || nodeFailed(node)) continue;
         okslaves = clusterCountNonFailingSlaves(node);
 
-        if (okslaves == 0 && target == NULL && node->numslots > 0) target = node;
+        if (okslaves == 0 && target == NULL && node->numslots > 0)
+            target = node;
+
         if (okslaves == max_slaves) {
             for (j = 0; j < node->numslaves; j++) {
                 if (memcmp(node->slaves[j]->name,
@@ -2389,7 +2410,9 @@ void clusterHandleManualFailover(void) {
         /* Our replication offset matches the master replication offset
          * announced after clients were paused. We can start the failover. */
         server.cluster->mf_can_start = 1;
-        redisLog(REDIS_WARNING,"All master replication stream processed, manual failover can start.");
+        redisLog(REDIS_WARNING,
+            "All master replication stream processed, "
+            "manual failover can start.");
     }
 }
 
@@ -2451,7 +2474,8 @@ void clusterCron(void) {
             link = createClusterLink(node);
             link->fd = fd;
             node->link = link;
-            aeCreateFileEvent(server.el,link->fd,AE_READABLE,clusterReadHandler,link);
+            aeCreateFileEvent(server.el,link->fd,AE_READABLE,
+                    clusterReadHandler,link);
             /* Queue a PING in the new connection ASAP: this is crucial
              * to avoid false positives in failure detection.
              *
@@ -2474,7 +2498,8 @@ void clusterCron(void) {
              * normal PING packets. */
             node->flags &= ~REDIS_NODE_MEET;
 
-            redisLog(REDIS_DEBUG,"Connecting with Node %.40s at %s:%d", node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
+            redisLog(REDIS_DEBUG,"Connecting with Node %.40s at %s:%d",
+                    node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
         }
     }
     dictReleaseIterator(di);
@@ -2492,7 +2517,8 @@ void clusterCron(void) {
 
             /* Don't ping nodes disconnected or with a ping currently active. */
             if (this->link == NULL || this->ping_sent != 0) continue;
-            if (this->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE)) continue;
+            if (this->flags & (REDIS_NODE_MYSELF|REDIS_NODE_HANDSHAKE))
+                continue;
             if (min_pong_node == NULL || min_pong > this->pong_received) {
                 min_pong_node = this;
                 min_pong = this->pong_received;
@@ -2640,7 +2666,8 @@ void clusterBeforeSleep(void) {
 
     /* Save the config, possibly using fsync. */
     if (server.cluster->todo_before_sleep & CLUSTER_TODO_SAVE_CONFIG) {
-        int fsync = server.cluster->todo_before_sleep & CLUSTER_TODO_FSYNC_CONFIG;
+        int fsync = server.cluster->todo_before_sleep &
+                    CLUSTER_TODO_FSYNC_CONFIG;
         clusterSaveConfigOrDie(fsync);
     }
 
@@ -3199,7 +3226,9 @@ void clusterCommand(redisClient *c) {
              * make sure there are no longer local keys for this hash slot. */
             if (server.cluster->slots[slot] == myself && n != myself) {
                 if (countKeysInSlot(slot) != 0) {
-                    addReplyErrorFormat(c, "Can't assign hashslot %d to a different node while I still hold keys for this hash slot.", slot);
+                    addReplyErrorFormat(c,
+                        "Can't assign hashslot %d to a different node "
+                        "while I still hold keys for this hash slot.", slot);
                     return;
                 }
             }
@@ -3236,7 +3265,8 @@ void clusterCommand(redisClient *c) {
             clusterDelSlot(slot);
             clusterAddSlot(n,slot);
         } else {
-            addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
+            addReplyError(c,
+                "Invalid CLUSTER SETSLOT action or number of arguments");
             return;
         }
         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
@@ -3319,7 +3349,8 @@ void clusterCommand(redisClient *c) {
 
         if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != REDIS_OK)
             return;
-        if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL)
+            != REDIS_OK)
             return;
         if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0) {
             addReplyError(c,"Invalid slot or number of keys");
@@ -3347,7 +3378,8 @@ void clusterCommand(redisClient *c) {
         }
         clusterBlacklistAddNode(n);
         clusterDelNode(n);
-        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
+        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|
+                             CLUSTER_TODO_SAVE_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"replicate") && c->argc == 3) {
         /* CLUSTER REPLICATE <NODE ID> */
@@ -3376,7 +3408,9 @@ void clusterCommand(redisClient *c) {
          * Slaves can switch to another master without issues. */
         if (nodeIsMaster(myself) &&
             (myself->numslots != 0 || dictSize(server.db[0].dict) != 0)) {
-            addReplyError(c,"To set a master the node must be empty and without assigned slots.");
+            addReplyError(c,
+                "To set a master the node must be empty and "
+                "without assigned slots.");
             return;
         }
 
@@ -3630,7 +3664,8 @@ int migrateGetSocket(redisClient *c, robj *host, robj *port, long timeout) {
     /* Check if it connects within the specified timeout. */
     if ((aeWait(fd,AE_WRITABLE,timeout) & AE_WRITABLE) == 0) {
         sdsfree(name);
-        addReplySds(c,sdsnew("-IOERR error or timeout connecting to the client\r\n"));
+        addReplySds(c,
+            sdsnew("-IOERR error or timeout connecting to the client\r\n"));
         close(fd);
         return -1;
     }
@@ -3744,7 +3779,8 @@ void migrateCommand(redisClient *c) {
     else
         redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,"RESTORE",7));
     redisAssertWithInfo(c,NULL,sdsEncodedObject(c->argv[3]));
-    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,c->argv[3]->ptr,sdslen(c->argv[3]->ptr)));
+    redisAssertWithInfo(c,NULL,rioWriteBulkString(&cmd,c->argv[3]->ptr,
+            sdslen(c->argv[3]->ptr)));
     redisAssertWithInfo(c,NULL,rioWriteBulkLongLong(&cmd,ttl));
 
     /* Emit the payload argument, that is the serialized object using