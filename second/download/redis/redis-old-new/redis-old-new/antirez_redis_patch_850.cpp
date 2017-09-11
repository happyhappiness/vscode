@@ -3790,6 +3790,8 @@ void clusterCommand(redisClient *c) {
             addReplyError(c,"Node config epoch is already non-zero");
         } else {
             myself->configEpoch = epoch;
+            if (server.cluster->currentEpoch < epoch)
+                server.cluster->currentEpoch = epoch;
             /* No need to fsync the config here since in the unlucky event
              * of a failure to persist the config, the conflict resolution code
              * will assign an unique config to this node. */