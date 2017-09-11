@@ -97,7 +97,7 @@ int clusterLoadConfig(char *filename) {
         if (errno == ENOENT) {
             return REDIS_ERR;
         } else {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Loading the cluster node config from %s: %s",
                 filename, strerror(errno));
             exit(1);
@@ -146,7 +146,7 @@ int clusterLoadConfig(char *filename) {
                     server.cluster->lastVoteEpoch =
                             strtoull(argv[j+1],NULL,10);
                 } else {
-                    redisLog(REDIS_WARNING,
+                    serverLog(REDIS_WARNING,
                         "Skipping unknown cluster config variable '%s'",
                         argv[j]);
                 }
@@ -264,7 +264,7 @@ int clusterLoadConfig(char *filename) {
     zfree(line);
     fclose(fp);
 
-    redisLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s", myself->name);
+    serverLog(REDIS_NOTICE,"Node configuration loaded, I'm %.40s", myself->name);
 
     /* Something that should never happen: currentEpoch smaller than
      * the max epoch found in the nodes configuration. However we handle this
@@ -275,7 +275,7 @@ int clusterLoadConfig(char *filename) {
     return REDIS_OK;
 
 fmterr:
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
         "Unrecoverable error: corrupted cluster config file.");
     zfree(line);
     if (fp) fclose(fp);
@@ -343,7 +343,7 @@ int clusterSaveConfig(int do_fsync) {
 
 void clusterSaveConfigOrDie(int do_fsync) {
     if (clusterSaveConfig(do_fsync) == -1) {
-        redisLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
+        serverLog(REDIS_WARNING,"Fatal: can't update cluster config file.");
         exit(1);
     }
 }
@@ -368,21 +368,21 @@ int clusterLockConfig(char *filename) {
      * processes. */
     int fd = open(filename,O_WRONLY|O_CREAT,0644);
     if (fd == -1) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Can't open %s in order to acquire a lock: %s",
             filename, strerror(errno));
         return REDIS_ERR;
     }
 
     if (flock(fd,LOCK_EX|LOCK_NB) == -1) {
         if (errno == EWOULDBLOCK) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                  "Sorry, the cluster configuration file %s is already used "
                  "by a different Redis Cluster node. Please make sure that "
                  "different nodes use different cluster configuration "
                  "files.", filename);
         } else {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Impossible to lock %s: %s", filename, strerror(errno));
         }
         close(fd);
@@ -429,7 +429,7 @@ void clusterInit(void) {
          * by the createClusterNode() function. */
         myself = server.cluster->myself =
             createClusterNode(NULL,REDIS_NODE_MYSELF|REDIS_NODE_MASTER);
-        redisLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
+        serverLog(REDIS_NOTICE,"No cluster configuration found, I'm %.40s",
             myself->name);
         clusterAddNode(myself);
         saveconf = 1;
@@ -443,7 +443,7 @@ void clusterInit(void) {
      * The other handshake port check is triggered too late to stop
      * us from trying to use a too-high cluster port number. */
     if (server.port > (65535-REDIS_CLUSTER_PORT_INCR)) {
-        redisLog(REDIS_WARNING, "Redis port number too high. "
+        serverLog(REDIS_WARNING, "Redis port number too high. "
                    "Cluster communication port is 10,000 port "
                    "numbers higher than your Redis port. "
                    "Your Redis port number must be "
@@ -522,7 +522,7 @@ void clusterReset(int hard) {
         server.cluster->currentEpoch = 0;
         server.cluster->lastVoteEpoch = 0;
         myself->configEpoch = 0;
-        redisLog(REDIS_WARNING, "configEpoch set to 0 via CLUSTER RESET HARD");
+        serverLog(REDIS_WARNING, "configEpoch set to 0 via CLUSTER RESET HARD");
 
         /* To change the Node ID we need to remove the old name from the
          * nodes table, change the ID, and re-add back with new name. */
@@ -587,15 +587,15 @@ void clusterAcceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
         if (cfd == ANET_ERR) {
             if (errno != EWOULDBLOCK)
-                redisLog(REDIS_VERBOSE,
+                serverLog(REDIS_VERBOSE,
                     "Error accepting cluster node: %s", server.neterr);
             return;
         }
         anetNonBlock(NULL,cfd);
         anetEnableTcpNoDelay(NULL,cfd);
 
         /* Use non-blocking I/O for cluster messages. */
-        redisLog(REDIS_VERBOSE,"Accepted cluster node %s:%d", cip, cport);
+        serverLog(REDIS_VERBOSE,"Accepted cluster node %s:%d", cip, cport);
         /* Create a link object we use to handle the connection.
          * It gets passed to the readable handler when data is available.
          * Initiallly the link->node pointer is set to NULL as we don't know
@@ -911,7 +911,7 @@ void clusterRenameNode(clusterNode *node, char *newname) {
     int retval;
     sds s = sdsnewlen(node->name, REDIS_CLUSTER_NAMELEN);
 
-    redisLog(REDIS_DEBUG,"Renaming node %.40s into %.40s",
+    serverLog(REDIS_DEBUG,"Renaming node %.40s into %.40s",
         node->name, newname);
     retval = dictDelete(server.cluster->nodes, s);
     sdsfree(s);
@@ -980,7 +980,7 @@ int clusterBumpConfigEpochWithoutConsensus(void) {
         myself->configEpoch = server.cluster->currentEpoch;
         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                              CLUSTER_TODO_FSYNC_CONFIG);
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "New configEpoch set to %llu",
             (unsigned long long) myself->configEpoch);
         return REDIS_OK;
@@ -1045,7 +1045,7 @@ void clusterHandleConfigEpochCollision(clusterNode *sender) {
     server.cluster->currentEpoch++;
     myself->configEpoch = server.cluster->currentEpoch;
     clusterSaveConfigOrDie(1);
-    redisLog(REDIS_VERBOSE,
+    serverLog(REDIS_VERBOSE,
         "WARNING: configEpoch collision with node %.40s."
         " configEpoch set to %llu",
         sender->name,
@@ -1163,7 +1163,7 @@ void markNodeAsFailingIfNeeded(clusterNode *node) {
     if (nodeIsMaster(myself)) failures++;
     if (failures < needed_quorum) return; /* No weak agreement from masters. */
 
-    redisLog(REDIS_NOTICE,
+    serverLog(REDIS_NOTICE,
         "Marking node %.40s as failing (quorum reached).", node->name);
 
     /* Mark the node as failing. */
@@ -1188,7 +1188,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
     /* For slaves we always clear the FAIL flag if we can contact the
      * node again. */
     if (nodeIsSlave(node) || node->numslots == 0) {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Clear FAIL state for node %.40s: %s is reachable again.",
                 node->name,
                 nodeIsSlave(node) ? "slave" : "master without slots");
@@ -1204,7 +1204,7 @@ void clearNodeFailureIfNeeded(clusterNode *node) {
         (now - node->fail_time) >
         (server.cluster_node_timeout * REDIS_CLUSTER_FAIL_UNDO_TIME_MULT))
     {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Clear FAIL state for node %.40s: is reachable again and nobody is serving its slots after some time.",
                 node->name);
         node->flags &= ~REDIS_NODE_FAIL;
@@ -1304,7 +1304,7 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
         sds ci;
 
         ci = representRedisNodeFlags(sdsempty(), flags);
-        redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
+        serverLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
             g->nodename,
             g->ip,
             ntohs(g->port),
@@ -1319,14 +1319,14 @@ void clusterProcessGossipSection(clusterMsg *hdr, clusterLink *link) {
             if (sender && nodeIsMaster(sender) && node != myself) {
                 if (flags & (REDIS_NODE_FAIL|REDIS_NODE_PFAIL)) {
                     if (clusterNodeAddFailureReport(node,sender)) {
-                        redisLog(REDIS_VERBOSE,
+                        serverLog(REDIS_VERBOSE,
                             "Node %.40s reported node %.40s as not reachable.",
                             sender->name, node->name);
                     }
                     markNodeAsFailingIfNeeded(node);
                 } else {
                     if (clusterNodeDelFailureReport(node,sender)) {
-                        redisLog(REDIS_VERBOSE,
+                        serverLog(REDIS_VERBOSE,
                             "Node %.40s reported node %.40s is back online.",
                             sender->name, node->name);
                     }
@@ -1397,7 +1397,7 @@ int nodeUpdateAddressIfNeeded(clusterNode *node, clusterLink *link, int port) {
     node->port = port;
     if (node->link) freeClusterLink(node->link);
     node->flags &= ~REDIS_NODE_NOADDR;
-    redisLog(REDIS_WARNING,"Address updated for node %.40s, now %s:%d",
+    serverLog(REDIS_WARNING,"Address updated for node %.40s, now %s:%d",
         node->name, node->ip, node->port);
 
     /* Check if this is our master and we have to change the
@@ -1453,7 +1453,7 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
     curmaster = nodeIsMaster(myself) ? myself : myself->slaveof;
 
     if (sender == myself) {
-        redisLog(REDIS_WARNING,"Discarding UPDATE message about myself.");
+        serverLog(REDIS_WARNING,"Discarding UPDATE message about myself.");
         return;
     }
 
@@ -1504,7 +1504,7 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
      * 2) We are a slave and our master is left without slots. We need
      *    to replicate to the new slots owner. */
     if (newmaster && curmaster->numslots == 0) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Configuration change detected. Reconfiguring myself "
             "as a replica of %.40s", sender->name);
         clusterSetMaster(sender);
@@ -1542,7 +1542,7 @@ int clusterProcessPacket(clusterLink *link) {
     clusterNode *sender;
 
     server.cluster->stats_bus_messages_received++;
-    redisLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
+    serverLog(REDIS_DEBUG,"--- Processing packet of type %d, %lu bytes",
         type, (unsigned long) totlen);
 
     /* Perform sanity checks */
@@ -1612,7 +1612,7 @@ int clusterProcessPacket(clusterLink *link) {
             server.cluster->mf_master_offset == 0)
         {
             server.cluster->mf_master_offset = sender->repl_offset;
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Received replication offset for paused "
                 "master manual failover: %lld",
                 server.cluster->mf_master_offset);
@@ -1621,7 +1621,7 @@ int clusterProcessPacket(clusterLink *link) {
 
     /* Initial processing of PING and MEET requests replying with a PONG. */
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_MEET) {
-        redisLog(REDIS_DEBUG,"Ping packet received: %p", (void*)link->node);
+        serverLog(REDIS_DEBUG,"Ping packet received: %p", (void*)link->node);
 
         /* We use incoming MEET messages in order to set the address
          * for 'myself', since only other cluster nodes will send us
@@ -1641,7 +1641,7 @@ int clusterProcessPacket(clusterLink *link) {
                 strcmp(ip,myself->ip))
             {
                 memcpy(myself->ip,ip,REDIS_IP_STR_LEN);
-                redisLog(REDIS_WARNING,"IP address for this node updated to %s",
+                serverLog(REDIS_WARNING,"IP address for this node updated to %s",
                     myself->ip);
                 clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG);
             }
@@ -1675,15 +1675,15 @@ int clusterProcessPacket(clusterLink *link) {
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
         type == CLUSTERMSG_TYPE_MEET)
     {
-        redisLog(REDIS_DEBUG,"%s packet received: %p",
+        serverLog(REDIS_DEBUG,"%s packet received: %p",
             type == CLUSTERMSG_TYPE_PING ? "ping" : "pong",
             (void*)link->node);
         if (link->node) {
             if (nodeInHandshake(link->node)) {
                 /* If we already have this node, try to change the
                  * IP/port of the node with the new one. */
                 if (sender) {
-                    redisLog(REDIS_VERBOSE,
+                    serverLog(REDIS_VERBOSE,
                         "Handshake: we already know node %.40s, "
                         "updating the address if needed.", sender->name);
                     if (nodeUpdateAddressIfNeeded(sender,link,ntohs(hdr->port)))
@@ -1700,7 +1700,7 @@ int clusterProcessPacket(clusterLink *link) {
                 /* First thing to do is replacing the random name with the
                  * right node name if this was a handshake stage. */
                 clusterRenameNode(link->node, hdr->sender);
-                redisLog(REDIS_DEBUG,"Handshake with node %.40s completed.",
+                serverLog(REDIS_DEBUG,"Handshake with node %.40s completed.",
                     link->node->name);
                 link->node->flags &= ~REDIS_NODE_HANDSHAKE;
                 link->node->flags |= flags&(REDIS_NODE_MASTER|REDIS_NODE_SLAVE);
@@ -1711,7 +1711,7 @@ int clusterProcessPacket(clusterLink *link) {
                 /* If the reply has a non matching node ID we
                  * disconnect this node and set it as not having an associated
                  * address. */
-                redisLog(REDIS_DEBUG,"PONG contains mismatching sender ID");
+                serverLog(REDIS_DEBUG,"PONG contains mismatching sender ID");
                 link->node->flags |= REDIS_NODE_NOADDR;
                 link->node->ip[0] = '\0';
                 link->node->port = 0;
@@ -1842,7 +1842,7 @@ int clusterProcessPacket(clusterLink *link) {
                     if (server.cluster->slots[j]->configEpoch >
                         senderConfigEpoch)
                     {
-                        redisLog(REDIS_VERBOSE,
+                        serverLog(REDIS_VERBOSE,
                             "Node %.40s has old slots configuration, sending "
                             "an UPDATE message about %.40s",
                                 sender->name, server.cluster->slots[j]->name);
@@ -1877,7 +1877,7 @@ int clusterProcessPacket(clusterLink *link) {
             if (failing &&
                 !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
             {
-                redisLog(REDIS_NOTICE,
+                serverLog(REDIS_NOTICE,
                     "FAIL message received from %.40s about %.40s",
                     hdr->sender, hdr->data.fail.about.nodename);
                 failing->flags |= REDIS_NODE_FAIL;
@@ -1887,7 +1887,7 @@ int clusterProcessPacket(clusterLink *link) {
                                      CLUSTER_TODO_UPDATE_STATE);
             }
         } else {
-            redisLog(REDIS_NOTICE,
+            serverLog(REDIS_NOTICE,
                 "Ignoring FAIL message from unknown node %.40s about %.40s",
                 hdr->sender, hdr->data.fail.about.nodename);
         }
@@ -1937,7 +1937,7 @@ int clusterProcessPacket(clusterLink *link) {
         server.cluster->mf_end = mstime() + REDIS_CLUSTER_MF_TIMEOUT;
         server.cluster->mf_slave = sender;
         pauseClients(mstime()+(REDIS_CLUSTER_MF_TIMEOUT*2));
-        redisLog(REDIS_WARNING,"Manual failover requested by slave %.40s.",
+        serverLog(REDIS_WARNING,"Manual failover requested by slave %.40s.",
             sender->name);
     } else if (type == CLUSTERMSG_TYPE_UPDATE) {
         clusterNode *n; /* The node the update is about. */
@@ -1962,7 +1962,7 @@ int clusterProcessPacket(clusterLink *link) {
         clusterUpdateSlotsConfigWith(n,reportedConfigEpoch,
             hdr->data.update.nodecfg.slots);
     } else {
-        redisLog(REDIS_WARNING,"Received unknown packet type: %d", type);
+        serverLog(REDIS_WARNING,"Received unknown packet type: %d", type);
     }
     return 1;
 }
@@ -1988,7 +1988,7 @@ void clusterWriteHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     nwritten = write(fd, link->sndbuf, sdslen(link->sndbuf));
     if (nwritten <= 0) {
-        redisLog(REDIS_DEBUG,"I/O error writing to node link: %s",
+        serverLog(REDIS_DEBUG,"I/O error writing to node link: %s",
             strerror(errno));
         handleLinkIOError(link);
         return;
@@ -2025,7 +2025,7 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
                 if (memcmp(hdr->sig,"RCmb",4) != 0 ||
                     ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN)
                 {
-                    redisLog(REDIS_WARNING,
+                    serverLog(REDIS_WARNING,
                         "Bad message length or signature received "
                         "from Cluster bus.");
                     handleLinkIOError(link);
@@ -2041,7 +2041,7 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
         if (nread <= 0) {
             /* I/O error... */
-            redisLog(REDIS_DEBUG,"I/O error reading from node link: %s",
+            serverLog(REDIS_DEBUG,"I/O error reading from node link: %s",
                 (nread == 0) ? "connection closed" : strerror(errno));
             handleLinkIOError(link);
             return;
@@ -2471,7 +2471,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
      * our currentEpoch was updated as a side effect of receiving this
      * request, if the request epoch was greater. */
     if (requestCurrentEpoch < server.cluster->currentEpoch) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Failover auth denied to %.40s: reqEpoch (%llu) < curEpoch(%llu)",
             node->name,
             (unsigned long long) requestCurrentEpoch,
@@ -2481,7 +2481,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
 
     /* I already voted for this epoch? Return ASAP. */
     if (server.cluster->lastVoteEpoch == server.cluster->currentEpoch) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
                 "Failover auth denied to %.40s: already voted for epoch %llu",
                 node->name,
                 (unsigned long long) server.cluster->currentEpoch);
@@ -2495,15 +2495,15 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
         (!nodeFailed(master) && !force_ack))
     {
         if (nodeIsMaster(node)) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                     "Failover auth denied to %.40s: it is a master node",
                     node->name);
         } else if (master == NULL) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                     "Failover auth denied to %.40s: I don't know its master",
                     node->name);
         } else if (!nodeFailed(master)) {
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                     "Failover auth denied to %.40s: its master is up",
                     node->name);
         }
@@ -2515,7 +2515,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
      * of the algorithm but makes the base case more linear. */
     if (mstime() - node->slaveof->voted_time < server.cluster_node_timeout * 2)
     {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
                 "Failover auth denied to %.40s: "
                 "can't vote about this master before %lld milliseconds",
                 node->name,
@@ -2537,7 +2537,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
         /* If we reached this point we found a slot that in our current slots
          * is served by a master with a greater configEpoch than the one claimed
          * by the slave requesting our vote. Refuse to vote for this slave. */
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
                 "Failover auth denied to %.40s: "
                 "slot %d epoch (%llu) > reqEpoch (%llu)",
                 node->name, j,
@@ -2550,7 +2550,7 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     clusterSendFailoverAuth(node);
     server.cluster->lastVoteEpoch = server.cluster->currentEpoch;
     node->slaveof->voted_time = mstime();
-    redisLog(REDIS_WARNING, "Failover auth granted to %.40s for epoch %llu",
+    serverLog(REDIS_WARNING, "Failover auth granted to %.40s for epoch %llu",
         node->name, (unsigned long long) server.cluster->currentEpoch);
 }
 
@@ -2641,7 +2641,7 @@ void clusterLogCantFailover(int reason) {
         break;
     }
     lastlog_time = time(NULL);
-    redisLog(REDIS_WARNING,"Currently unable to failover: %s", msg);
+    serverLog(REDIS_WARNING,"Currently unable to failover: %s", msg);
 }
 
 /* This function implements the final part of automatic and manual failovers,
@@ -2774,7 +2774,7 @@ void clusterHandleSlaveFailover(void) {
             server.cluster->failover_auth_time = mstime();
             server.cluster->failover_auth_rank = 0;
         }
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Start of election delayed for %lld milliseconds "
             "(rank #%d, offset %lld).",
             server.cluster->failover_auth_time - mstime(),
@@ -2801,7 +2801,7 @@ void clusterHandleSlaveFailover(void) {
                 (newrank - server.cluster->failover_auth_rank) * 1000;
             server.cluster->failover_auth_time += added_delay;
             server.cluster->failover_auth_rank = newrank;
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Slave rank updated to #%d, added %lld milliseconds of delay.",
                 newrank, added_delay);
         }
@@ -2823,7 +2823,7 @@ void clusterHandleSlaveFailover(void) {
     if (server.cluster->failover_auth_sent == 0) {
         server.cluster->currentEpoch++;
         server.cluster->failover_auth_epoch = server.cluster->currentEpoch;
-        redisLog(REDIS_WARNING,"Starting a failover election for epoch %llu.",
+        serverLog(REDIS_WARNING,"Starting a failover election for epoch %llu.",
             (unsigned long long) server.cluster->currentEpoch);
         clusterRequestFailoverAuth();
         server.cluster->failover_auth_sent = 1;
@@ -2837,13 +2837,13 @@ void clusterHandleSlaveFailover(void) {
     if (server.cluster->failover_auth_count >= needed_quorum) {
         /* We have the quorum, we can finally failover the master. */
 
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Failover election won: I'm the new master.");
 
         /* Update my configEpoch to the epoch of the election. */
         if (myself->configEpoch < server.cluster->failover_auth_epoch) {
             myself->configEpoch = server.cluster->failover_auth_epoch;
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "configEpoch set to %llu after successful failover",
                 (unsigned long long) myself->configEpoch);
         }
@@ -2941,7 +2941,7 @@ void clusterHandleSlaveMigration(int max_slaves) {
     /* Step 4: perform the migration if there is a target, and if I'm the
      * candidate. */
     if (target && candidate == myself) {
-        redisLog(REDIS_WARNING,"Migrating to orphaned master %.40s",
+        serverLog(REDIS_WARNING,"Migrating to orphaned master %.40s",
             target->name);
         clusterSetMaster(target);
     }
@@ -2995,7 +2995,7 @@ void resetManualFailover(void) {
 /* If a manual failover timed out, abort it. */
 void manualFailoverCheckTimeout(void) {
     if (server.cluster->mf_end && server.cluster->mf_end < mstime()) {
-        redisLog(REDIS_WARNING,"Manual failover timed out.");
+        serverLog(REDIS_WARNING,"Manual failover timed out.");
         resetManualFailover();
     }
 }
@@ -3016,7 +3016,7 @@ void clusterHandleManualFailover(void) {
         /* Our replication offset matches the master replication offset
          * announced after clients were paused. We can start the failover. */
         server.cluster->mf_can_start = 1;
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "All master replication stream processed, "
             "manual failover can start.");
     }
@@ -3076,7 +3076,7 @@ void clusterCron(void) {
                  * so we claim we actually sent a ping now (that will
                  * be really sent as soon as the link is obtained). */
                 if (node->ping_sent == 0) node->ping_sent = mstime();
-                redisLog(REDIS_DEBUG, "Unable to connect to "
+                serverLog(REDIS_DEBUG, "Unable to connect to "
                     "Cluster Node [%s]:%d -> %s", node->ip,
                     node->port+REDIS_CLUSTER_PORT_INCR,
                     server.neterr);
@@ -3109,7 +3109,7 @@ void clusterCron(void) {
              * normal PING packets. */
             node->flags &= ~REDIS_NODE_MEET;
 
-            redisLog(REDIS_DEBUG,"Connecting with Node %.40s at %s:%d",
+            serverLog(REDIS_DEBUG,"Connecting with Node %.40s at %s:%d",
                     node->name, node->ip, node->port+REDIS_CLUSTER_PORT_INCR);
         }
     }
@@ -3136,7 +3136,7 @@ void clusterCron(void) {
             }
         }
         if (min_pong_node) {
-            redisLog(REDIS_DEBUG,"Pinging node %.40s", min_pong_node->name);
+            serverLog(REDIS_DEBUG,"Pinging node %.40s", min_pong_node->name);
             clusterSendPing(min_pong_node->link, CLUSTERMSG_TYPE_PING);
         }
     }
@@ -3225,7 +3225,7 @@ void clusterCron(void) {
             /* Timeout reached. Set the node as possibly failing if it is
              * not already in this state. */
             if (!(node->flags & (REDIS_NODE_PFAIL|REDIS_NODE_FAIL))) {
-                redisLog(REDIS_DEBUG,"*** NODE %.40s possibly failing",
+                serverLog(REDIS_DEBUG,"*** NODE %.40s possibly failing",
                     node->name);
                 node->flags |= REDIS_NODE_PFAIL;
                 update_state = 1;
@@ -3488,7 +3488,7 @@ void clusterUpdateState(void) {
         }
 
         /* Change the state and log the event. */
-        redisLog(REDIS_WARNING,"Cluster state changed: %s",
+        serverLog(REDIS_WARNING,"Cluster state changed: %s",
             new_state == REDIS_CLUSTER_OK ? "ok" : "fail");
         server.cluster->state = new_state;
     }
@@ -3546,11 +3546,11 @@ int verifyClusterConfigWithData(void) {
         update_config++;
         /* Case A: slot is unassigned. Take responsibility for it. */
         if (server.cluster->slots[j] == NULL) {
-            redisLog(REDIS_WARNING, "I have keys for unassigned slot %d. "
+            serverLog(REDIS_WARNING, "I have keys for unassigned slot %d. "
                                     "Taking responsibility for it.",j);
             clusterAddSlot(myself,j);
         } else {
-            redisLog(REDIS_WARNING, "I have keys for slot %d, but the slot is "
+            serverLog(REDIS_WARNING, "I have keys for slot %d, but the slot is "
                                     "assigned to another node. "
                                     "Setting it to importing state.",j);
             server.cluster->importing_slots_from[j] = server.cluster->slots[j];
@@ -3978,7 +3978,7 @@ void clusterCommand(redisClient *c) {
                  * configEpoch collision resolution will fix it assigning
                  * a different epoch to each node. */
                 if (clusterBumpConfigEpochWithoutConsensus() == REDIS_OK) {
-                    redisLog(REDIS_WARNING,
+                    serverLog(REDIS_WARNING,
                         "configEpoch updated after importing slot %d", slot);
                 }
                 server.cluster->importing_slots_from[slot] = NULL;
@@ -4220,17 +4220,17 @@ void clusterCommand(redisClient *c) {
              * generates a new configuration epoch for this node without
              * consensus, claims the master's slots, and broadcast the new
              * configuration. */
-            redisLog(REDIS_WARNING,"Taking over the master (user request).");
+            serverLog(REDIS_WARNING,"Taking over the master (user request).");
             clusterBumpConfigEpochWithoutConsensus();
             clusterFailoverReplaceYourMaster();
         } else if (force) {
             /* If this is a forced failover, we don't need to talk with our
              * master to agree about the offset. We just failover taking over
              * it without coordination. */
-            redisLog(REDIS_WARNING,"Forced failover user request accepted.");
+            serverLog(REDIS_WARNING,"Forced failover user request accepted.");
             server.cluster->mf_can_start = 1;
         } else {
-            redisLog(REDIS_WARNING,"Manual failover user request accepted.");
+            serverLog(REDIS_WARNING,"Manual failover user request accepted.");
             clusterSendMFStart(myself->slaveof);
         }
         addReply(c,shared.ok);
@@ -4257,7 +4257,7 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Node config epoch is already non-zero");
         } else {
             myself->configEpoch = epoch;
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
                 (unsigned long long) myself->configEpoch);
 