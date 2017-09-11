@@ -3172,8 +3172,10 @@ void clusterCommand(redisClient *c) {
                  * at least to the value of the configEpoch of the old owner
                  * so that its old replicas, or some of its old message pending
                  * on the cluster bus, can't claim our slot. */
-                if (old_owner->configEpoch > myself->configEpoch)
+                if (old_owner->configEpoch > myself->configEpoch) {
                     myself->configEpoch = old_owner->configEpoch;
+                    clusterDoBeforeSleep(CLUSTER_TODO_FSYNC_CONFIG);
+                }
                 server.cluster->importing_slots_from[slot] = NULL;
             }
             clusterDelSlot(slot);
@@ -3182,9 +3184,7 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Invalid CLUSTER SETSLOT action or number of arguments");
             return;
         }
-        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
-                             CLUSTER_TODO_UPDATE_STATE|
-                             CLUSTER_TODO_FSYNC_CONFIG);
+        clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|CLUSTER_TODO_UPDATE_STATE);
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"info") && c->argc == 2) {
         /* CLUSTER INFO */