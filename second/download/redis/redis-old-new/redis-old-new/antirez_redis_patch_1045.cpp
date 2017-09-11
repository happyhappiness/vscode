@@ -1029,7 +1029,7 @@ int clusterProcessPacket(clusterLink *link) {
             }
         }
 
-        /* Update master/slave state */
+        /* Check for role switch: slave -> master or master -> slave. */
         if (sender) {
             if (!memcmp(hdr->slaveof,REDIS_NODE_NULL_NAME,
                 sizeof(hdr->slaveof)))
@@ -1079,67 +1079,111 @@ int clusterProcessPacket(clusterLink *link) {
         }
 
         /* Update our info about served slots.
+         *
          * Note: this MUST happen after we update the master/slave state
          * so that REDIS_NODE_MASTER flag will be set. */
-        if (sender && sender->flags & REDIS_NODE_MASTER) {
-            int changes, j;
-
-            changes =
-                memcmp(sender->slots,hdr->myslots,sizeof(hdr->myslots)) != 0;
-            if (changes) {
-                clusterNode *curmaster, *newmaster = NULL;
-
-                /* Here we set curmaster to this node or the node this node
-                 * replicates to if it's a slave. In the for loop we are
-                 * interested to check if slots are taken away from curmaster. */
-                if (server.cluster->myself->flags & REDIS_NODE_MASTER)
-                    curmaster = server.cluster->myself;
-                else
-                    curmaster = server.cluster->myself->slaveof;
-
-                for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-                    if (bitmapTestBit(hdr->myslots,j)) {
-                        /* We rebind the slot to the new node claiming it if:
-                         * 1) The slot was unassigned.
-                         * 2) The new node claims it with a greater configEpoch. */
-                        if (server.cluster->slots[j] == sender) continue;
-                        if (server.cluster->slots[j] == NULL ||
-                            server.cluster->slots[j]->configEpoch <
-                            senderConfigEpoch)
-                        {
-                            if (server.cluster->slots[j] == curmaster)
-                                newmaster = sender;
-                            clusterDelSlot(j);
-                            clusterAddSlot(sender,j);
-                            clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
-                                                 CLUSTER_TODO_UPDATE_STATE|
-                                                 CLUSTER_TODO_FSYNC_CONFIG);
-                        }
-                    } else {
-                        /* This node claims to no longer handling the slot,
-                         * however we don't change our config as this is likely:
-                         * 1) Rehashing in progress.
-                         * 2) Failover.
-                         * In both cases we'll be informed about who is serving
-                         * the slot eventually. In the meantime it's up to the
-                         * original owner to try to redirect our clients to the
-                         * right node. */
+
+        /* Many checks are only needed if the set of served slots this
+         * instance claims is different compared to the set of slots we have for
+         * it. Check this ASAP to avoid other computational expansive checks later. */
+        clusterNode *sender_master = NULL; /* Sender or its master if it is a slave. */
+        int dirty_slots = 0; /* Sender claimed slots don't match my view? */
+
+        if (sender) {
+            sender_master = (sender->flags & REDIS_NODE_MASTER) ? sender :
+                                                                  sender->slaveof;
+            if (sender_master) {
+                dirty_slots = memcmp(sender_master->slots,
+                        hdr->myslots,sizeof(hdr->myslots)) != 0;
+            }
+        }
+
+        /* 1) We check if the sender (master) is claiming slots that we belive to
+         *    serve as a master, or replicate as a slave, but with a configEpoch
+         *    that is newer: in that case we rebind the slots to the claiming node
+         *    in our routing table.
+         *
+         *    Moreover if we are left with 0 slots to serve, we reconfigure as
+         *    a replica of the sender. */
+        if (sender && sender->flags & REDIS_NODE_MASTER && dirty_slots) {
+            int j;
+            clusterNode *curmaster, *newmaster = NULL;
+
+            /* Here we set curmaster to this node or the node this node
+             * replicates to if it's a slave. In the for loop we are
+             * interested to check if slots are taken away from curmaster. */
+            if (server.cluster->myself->flags & REDIS_NODE_MASTER)
+                curmaster = server.cluster->myself;
+            else
+                curmaster = server.cluster->myself->slaveof;
+
+            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+                if (bitmapTestBit(hdr->myslots,j)) {
+                    /* We rebind the slot to the new node claiming it if:
+                     * 1) The slot was unassigned.
+                     * 2) The new node claims it with a greater configEpoch. */
+                    if (server.cluster->slots[j] == sender) continue;
+                    if (server.cluster->slots[j] == NULL ||
+                        server.cluster->slots[j]->configEpoch <
+                        senderConfigEpoch)
+                    {
+                        if (server.cluster->slots[j] == curmaster)
+                            newmaster = sender;
+                        clusterDelSlot(j);
+                        clusterAddSlot(sender,j);
+                        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                             CLUSTER_TODO_UPDATE_STATE|
+                                             CLUSTER_TODO_FSYNC_CONFIG);
                     }
                 }
+            }
 
-                /* If at least one slot was reassigned from a node to another node
-                 * with a greater configEpoch, it is possible that:
-                 * 1) We are a master is left without slots. This means that we were
-                 *    failed over and we should turn into a replica of the new
-                 *    master.
-                 * 2) We are a slave and our master is left without slots. We need
-                 *    to replicate to the new slots owner. */
-                if (newmaster && curmaster->numslots == 0) {
-                    redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
-                    clusterSetMaster(sender);
-                    clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
-                                         CLUSTER_TODO_UPDATE_STATE|
-                                         CLUSTER_TODO_FSYNC_CONFIG);
+            /* If at least one slot was reassigned from a node to another node
+             * with a greater configEpoch, it is possible that:
+             * 1) We are a master is left without slots. This means that we were
+             *    failed over and we should turn into a replica of the new
+             *    master.
+             * 2) We are a slave and our master is left without slots. We need
+             *    to replicate to the new slots owner. */
+            if (newmaster && curmaster->numslots == 0) {
+                redisLog(REDIS_WARNING,"Configuration change detected. Reconfiguring myself as a replica of %.40s", sender->name);
+                clusterSetMaster(sender);
+                clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                                     CLUSTER_TODO_UPDATE_STATE|
+                                     CLUSTER_TODO_FSYNC_CONFIG);
+            }
+        }
+
+        /* 2) We also check for the reverse condition, that is, the sender claims
+         *    to serve slots we know are served by a master with a greater
+         *    configEpoch. If this happens we inform the sender.
+         *
+         * This is useful because sometimes after a partition heals, a reappearing
+         * master may be the last one to claim a given set of hash slots, but with
+         * a configuration that other instances know to be deprecated. Example:
+         *
+         * A and B are master and slave for slots 1,2,3.
+         * A is partitioned away, B gets promoted.
+         * B is partitioned away, and A returns available.
+         *
+         * Usually B would PING A publishing its set of served slots and its
+         * configEpoch, but because of the partition B can't inform A of the new
+         * configuration, so other nodes that have an updated table must do it.
+         * In this way A will stop to act as a master (or can try to failover if
+         * there are the conditions to win the election). */
+        if (sender && dirty_slots) {
+            int j;
+
+            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+                if (bitmapTestBit(hdr->myslots,j)) {
+                    if (server.cluster->slots[j] == sender ||
+                        server.cluster->slots[j] == NULL) continue;
+                    if (server.cluster->slots[j]->configEpoch >
+                        senderConfigEpoch)
+                    {
+                        printf("MASTER or SLAVE have old config\n");
+                        break;
+                    }
                 }
             }
         }