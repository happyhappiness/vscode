@@ -1235,11 +1235,12 @@ void clusterHandleConfigEpochCollision(clusterNode *sender) {
     /* Don't act if the colliding node has a smaller Node ID. */
     if (memcmp(sender->name,myself->name,REDIS_CLUSTER_NAMELEN) <= 0) return;
     /* Get the next ID available at the best of this node knowledge. */
-    myself->configEpoch = clusterGetMaxEpoch()+1;
+    server.cluster->currentEpoch++;
+    myself->configEpoch = server.cluster->currentEpoch;
     clusterSaveConfigOrDie(1);
     redisLog(REDIS_VERBOSE,
         "WARNING: configEpoch collision with node %.40s."
-        "Updating my configEpoch to %llu",
+        " Updating my configEpoch to %llu",
         sender->name,
         (unsigned long long) myself->configEpoch);
 }
@@ -3343,6 +3344,9 @@ void clusterCommand(redisClient *c) {
                     server.cluster->currentEpoch++;
                     myself->configEpoch = server.cluster->currentEpoch;
                     clusterDoBeforeSleep(CLUSTER_TODO_FSYNC_CONFIG);
+                    redisLog(REDIS_WARNING,
+                        "configEpoch set to %llu after importing slot %d",
+                        (unsigned long long) myself->configEpoch, slot);
                 }
                 server.cluster->importing_slots_from[slot] = NULL;
             }