@@ -1389,6 +1389,7 @@ void clusterHandleSlaveFailover(void) {
     time_t data_age = server.unixtime - server.repl_down_since;
     time_t auth_age = server.unixtime - server.cluster->failover_auth_time;
     int needed_quorum = (server.cluster->size / 2) + 1;
+    int j;
 
     /* Check if our data is recent enough. For now we just use a fixed
      * constant of ten times the node timeout since the cluster should
@@ -1411,6 +1412,8 @@ void clusterHandleSlaveFailover(void) {
 
     /* Check if we reached the quorum. */
     if (server.cluster->failover_auth_count >= needed_quorum) {
+        clusterNode *oldmaster = server.cluster->myself->slaveof;
+
         redisLog(REDIS_WARNING,
             "Masters quorum reached: failing over my (failing) master.");
         /* We have the quorum, perform all the steps to correctly promote
@@ -1424,9 +1427,21 @@ void clusterHandleSlaveFailover(void) {
         server.cluster->myself->slaveof = NULL;
         replicationUnsetMaster();
 
-        /* 2) Ping all the other nodes so that they can update the state
+        /* 2) Claim all the slots assigned to our master. */
+        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+            if (clusterNodeGetSlotBit(oldmaster,j)) {
+                clusterDelSlot(j);
+                clusterAddSlot(server.cluster->myself,j);
+            }
+        }
+
+        /* 3) Ping all the other nodes so that they can update the state
          *    accordingly and detect that we switched to master role. */
         clusterBroadcastPing();
+
+        /* 4) Update state and save config. */
+        clusterUpdateState();
+        clusterSaveConfigOrDie();
     }
 }
 