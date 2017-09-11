@@ -1115,8 +1115,7 @@ void clusterUpdateSlotsConfigWith(clusterNode *sender, uint64_t senderConfigEpoc
              * 2) The new node claims it with a greater configEpoch. */
             if (server.cluster->slots[j] == sender) continue;
             if (server.cluster->slots[j] == NULL ||
-                server.cluster->slots[j]->configEpoch <
-                senderConfigEpoch)
+                server.cluster->slots[j]->configEpoch < senderConfigEpoch)
             {
                 if (server.cluster->slots[j] == curmaster)
                     newmaster = sender;
@@ -3164,14 +3163,26 @@ void clusterCommand(redisClient *c) {
              * itself also clears the importing status. */
             if (n == myself &&
                 server.cluster->importing_slots_from[slot])
+            {
+                clusterNode *old_owner =
+                    server.cluster->importing_slots_from[slot];
+                /* This slot was manually migrated, set this node configEpoch
+                 * at least to the value of the configEpoch of the old owner
+                 * so that its old replicas, or some of its old message pending
+                 * on the cluster bus, can't claim our slot. */
+                if (old_owner->configEpoch > myself->configEpoch)
+                    myself->configEpoch = old_owner->configEpoch;
                 server.cluster->importing_slots_from[slot] = NULL;
+            }
             clusterDelSlot(slot);
             clusterAddSlot(n,slot);
         } else {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;
         }
-        clusterDoBeforeSleep(CLUSTER_TODO_UPDATE_STATE|CLUSTER_TODO_SAVE_CONFIG);
+        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
+                             CLUSTER_TODO_UPDATE_STATE|
+                             CLUSTER_TODO_FSYNC_CONFIG);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         /* CLUSTER INFO */