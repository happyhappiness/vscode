@@ -512,6 +512,7 @@ void clusterReset(int hard) {
         server.cluster->currentEpoch = 0;
         server.cluster->lastVoteEpoch = 0;
         myself->configEpoch = 0;
+        redisLog(REDIS_WARNING, "configEpoch set to 0 via CLUSTER RESET HARD");
 
         /* To change the Node ID we need to remove the old name from the
          * nodes table, change the ID, and re-add back with new name. */
@@ -1427,7 +1428,7 @@ void clusterHandleConfigEpochCollision(clusterNode *sender) {
     clusterSaveConfigOrDie(1);
     redisLog(REDIS_VERBOSE,
         "WARNING: configEpoch collision with node %.40s."
-        " Updating my configEpoch to %llu",
+        " configEpoch set to %llu",
         sender->name,
         (unsigned long long) myself->configEpoch);
 }
@@ -2557,8 +2558,12 @@ void clusterHandleSlaveFailover(void) {
         }
 
         /* 3) Update my configEpoch to the epoch of the election. */
-        if (myself->configEpoch < server.cluster->failover_auth_epoch)
+        if (myself->configEpoch < server.cluster->failover_auth_epoch) {
             myself->configEpoch = server.cluster->failover_auth_epoch;
+            redisLog(REDIS_WARNING,
+                "configEpoch set to %llu after successful failover",
+                (unsigned long long) myself->configEpoch);
+        }
 
         /* 4) Update state and save config. */
         clusterUpdateState();
@@ -3838,6 +3843,10 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Node config epoch is already non-zero");
         } else {
             myself->configEpoch = epoch;
+            redisLog(REDIS_WARNING,
+                "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
+                (unsigned long long) myself->configEpoch);
+
             if (server.cluster->currentEpoch < epoch)
                 server.cluster->currentEpoch = epoch;
             /* No need to fsync the config here since in the unlucky event