          * new configuration, so other nodes that have an updated table must
          * do it. In this way A will stop to act as a master (or can try to
          * failover if there are the conditions to win the election). */
         if (sender && dirty_slots) {
             int j;
 
-            for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+            for (j = 0; j < CLUSTER_SLOTS; j++) {
                 if (bitmapTestBit(hdr->myslots,j)) {
                     if (server.cluster->slots[j] == sender ||
                         server.cluster->slots[j] == NULL) continue;
                     if (server.cluster->slots[j]->configEpoch >
                         senderConfigEpoch)
                     {
-                        redisLog(REDIS_VERBOSE,
+                        serverLog(LL_VERBOSE,
                             "Node %.40s has old slots configuration, sending "
                             "an UPDATE message about %.40s",
                                 sender->name, server.cluster->slots[j]->name);
                         clusterSendUpdate(sender->link,
                             server.cluster->slots[j]);
 
