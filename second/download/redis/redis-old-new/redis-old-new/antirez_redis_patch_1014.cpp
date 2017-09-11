@@ -1293,44 +1293,46 @@ int clusterProcessPacket(clusterLink *link) {
          * so that REDIS_NODE_MASTER flag will be set. */
 
         /* Many checks are only needed if the set of served slots this
-         * instance claims is different compared to the set of slots we have for
-         * it. Check this ASAP to avoid other computational expansive checks later. */
-        clusterNode *sender_master = NULL; /* Sender or its master if it is a slave. */
+         * instance claims is different compared to the set of slots we have
+         * for it. Check this ASAP to avoid other computational expansive
+         * checks later. */
+        clusterNode *sender_master = NULL; /* Sender or its master if slave. */
         int dirty_slots = 0; /* Sender claimed slots don't match my view? */
 
         if (sender) {
-            sender_master = (sender->flags & REDIS_NODE_MASTER) ? sender :
-                                                                  sender->slaveof;
+            sender_master = (sender->flags & REDIS_NODE_MASTER) ?
+                sender : sender->slaveof;
             if (sender_master) {
                 dirty_slots = memcmp(sender_master->slots,
                         hdr->myslots,sizeof(hdr->myslots)) != 0;
             }
         }
 
-        /* 1) If the sender of the message is a master, and we detected that the
-         *    set of slots it claims changed, scan the slots to see if we need
-         *    to update our configuration. */
+        /* 1) If the sender of the message is a master, and we detected that
+         *    the set of slots it claims changed, scan the slots to see if we
+         *    need to update our configuration. */
         if (sender && sender->flags & REDIS_NODE_MASTER && dirty_slots) {
             clusterUpdateSlotsConfigWith(sender,senderConfigEpoch,hdr->myslots);
         }
 
-        /* 2) We also check for the reverse condition, that is, the sender claims
-         *    to serve slots we know are served by a master with a greater
-         *    configEpoch. If this happens we inform the sender.
+        /* 2) We also check for the reverse condition, that is, the sender
+         *    claims to serve slots we know are served by a master with a
+         *    greater configEpoch. If this happens we inform the sender.
          *
-         * This is useful because sometimes after a partition heals, a reappearing
-         * master may be the last one to claim a given set of hash slots, but with
-         * a configuration that other instances know to be deprecated. Example:
+         * This is useful because sometimes after a partition heals, a
+         * reappearing master may be the last one to claim a given set of
+         * hash slots, but with a configuration that other instances know to
+         * be deprecated. Example:
          *
          * A and B are master and slave for slots 1,2,3.
          * A is partitioned away, B gets promoted.
          * B is partitioned away, and A returns available.
          *
          * Usually B would PING A publishing its set of served slots and its
-         * configEpoch, but because of the partition B can't inform A of the new
-         * configuration, so other nodes that have an updated table must do it.
-         * In this way A will stop to act as a master (or can try to failover if
-         * there are the conditions to win the election). */
+         * configEpoch, but because of the partition B can't inform A of the
+         * new configuration, so other nodes that have an updated table must
+         * do it. In this way A will stop to act as a master (or can try to
+         * failover if there are the conditions to win the election). */
         if (sender && dirty_slots) {
             int j;
 
@@ -1363,7 +1365,8 @@ int clusterProcessPacket(clusterLink *link) {
 
         if (sender) {
             failing = clusterLookupNode(hdr->data.fail.about.nodename);
-            if (failing && !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
+            if (failing &&
+                !(failing->flags & (REDIS_NODE_FAIL|REDIS_NODE_MYSELF)))
             {
                 redisLog(REDIS_NOTICE,
                     "FAIL message received from %.40s about %.40s",
@@ -1384,13 +1387,16 @@ int clusterProcessPacket(clusterLink *link) {
 
         /* Don't bother creating useless objects if there are no
          * Pub/Sub subscribers. */
-        if (dictSize(server.pubsub_channels) || listLength(server.pubsub_patterns)) {
+        if (dictSize(server.pubsub_channels) ||
+           listLength(server.pubsub_patterns))
+        {
             channel_len = ntohl(hdr->data.publish.msg.channel_len);
             message_len = ntohl(hdr->data.publish.msg.message_len);
             channel = createStringObject(
                         (char*)hdr->data.publish.msg.bulk_data,channel_len);
             message = createStringObject(
-                        (char*)hdr->data.publish.msg.bulk_data+channel_len, message_len);
+                        (char*)hdr->data.publish.msg.bulk_data+channel_len,
+                        message_len);
             pubsubPublishMessage(channel,message);
             decrRefCount(channel);
             decrRefCount(message);
@@ -1424,7 +1430,8 @@ int clusterProcessPacket(clusterLink *link) {
         /* If in our current config the node is a slave, set it as a master. */
         if (n->flags & REDIS_NODE_SLAVE) clusterSetNodeAsMaster(n);
 
-        /* Check the bitmap of served slots and udpate our config accordingly. */
+        /* Check the bitmap of served slots and udpate our
+         * config accordingly. */
         clusterUpdateSlotsConfigWith(n,reportedConfigEpoch,
             hdr->data.update.nodecfg.slots);
     } else {
@@ -1824,21 +1831,34 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
     if (server.cluster->myself->numslots == 0) return;
 
     /* Request epoch must be >= our currentEpoch. */
-    if (requestCurrentEpoch < server.cluster->currentEpoch) return;
+    if (requestCurrentEpoch < server.cluster->currentEpoch) {
+        printf("REFUSED BECAUSE OF EPOCH\n");
+        return;
+    }
 
     /* I already voted for this epoch? Return ASAP. */
-    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) return;
+    if (server.cluster->last_vote_epoch == server.cluster->currentEpoch) {
+        printf("REFUSED BECAUSE ALREADY VOTED FOR EPOCH\n");
+        return;
+    }
 
     /* Node must be a slave and its master down. */
     if (!(node->flags & REDIS_NODE_SLAVE) ||
         master == NULL ||
-        !(master->flags & REDIS_NODE_FAIL)) return;
+        !(master->flags & REDIS_NODE_FAIL))
+    {
+        printf("REFUSED BECAUSE NOT A SLAVE OR MASTER NOT FAIL.\n");
+        return;
+    }
 
     /* We did not voted for a slave about this master for two
      * times the node timeout. This is not strictly needed for correctness
      * of the algorithm but makes the base case more linear. */
     if (mstime() - node->slaveof->voted_time < server.cluster_node_timeout * 2)
+    {
+        printf("REFUSED BECAUSE ALREADY VOTED WITHIN NODE_TIMEOUT*2.\n");
         return;
+    }
 
     /* The slave requesting the vote must have a configEpoch for the claimed
      * slots that is >= the one of the masters currently serving the same
@@ -1850,10 +1870,12 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
         /* If we reached this point we found a slot that in our current slots
          * is served by a master with a greater configEpoch than the one claimed
          * by the slave requesting our vote. Refuse to vote for this slave. */
+        printf("REFUSED BECAUSE SLAVE CONFIG EPOCH FOR SLOTS IS STALE.\n");
         return;
     }
 
     /* We can vote for this slave. */
+    printf("I VOTED.\n");
     clusterSendFailoverAuth(node);
     server.cluster->last_vote_epoch = server.cluster->currentEpoch;
     node->slaveof->voted_time = mstime();