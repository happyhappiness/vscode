@@ -2636,6 +2636,42 @@ void clusterLogCantFailover(int reason) {
     redisLog(REDIS_WARNING,"Currently unable to failover: %s", msg);
 }
 
+/* This function implements the final part of automatic and manual failovers,
+ * where the slave grabs its master's hash slots, and propagates the new
+ * configuration.
+ *
+ * Note that it's up to the caller to be sure that the node got a new
+ * configuration epoch already. */
+void clusterFailoverReplaceYourMaster(void) {
+    int j;
+    clusterNode *oldmaster = myself->slaveof;
+
+    if (nodeIsMaster(myself) || oldmaster == NULL) return;
+
+    /* 1) Turn this node into a master. */
+    clusterSetNodeAsMaster(myself);
+    replicationUnsetMaster();
+
+    /* 2) Claim all the slots assigned to our master. */
+    for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
+        if (clusterNodeGetSlotBit(oldmaster,j)) {
+            clusterDelSlot(j);
+            clusterAddSlot(myself,j);
+        }
+    }
+
+    /* 3) Update state and save config. */
+    clusterUpdateState();
+    clusterSaveConfigOrDie(1);
+
+    /* 4) Pong all the other nodes so that they can update the state
+     *    accordingly and detect that we switched to master role. */
+    clusterBroadcastPong(CLUSTER_BROADCAST_ALL);
+
+    /* 5) If there was a manual failover in progress, clear the state. */
+    resetManualFailover();
+}
+
 /* This function is called if we are a slave node and our master serving
  * a non-zero amount of hash slots is in FAIL state.
  *
@@ -2650,7 +2686,6 @@ void clusterHandleSlaveFailover(void) {
     int needed_quorum = (server.cluster->size / 2) + 1;
     int manual_failover = server.cluster->mf_end != 0 &&
                           server.cluster->mf_can_start;
-    int j;
     mstime_t auth_timeout, auth_retry_time;
 
     server.cluster->todo_before_sleep &= ~CLUSTER_TODO_HANDLE_FAILOVER;
@@ -2792,43 +2827,21 @@ void clusterHandleSlaveFailover(void) {
 
     /* Check if we reached the quorum. */
     if (server.cluster->failover_auth_count >= needed_quorum) {
-        clusterNode *oldmaster = myself->slaveof;
+        /* We have the quorum, we can finally failover the master. */
 
         redisLog(REDIS_WARNING,
             "Failover election won: I'm the new master.");
-        /* We have the quorum, perform all the steps to correctly promote
-         * this slave to a master.
-         *
-         * 1) Turn this node into a master. */
-        clusterSetNodeAsMaster(myself);
-        replicationUnsetMaster();
 
-        /* 2) Claim all the slots assigned to our master. */
-        for (j = 0; j < REDIS_CLUSTER_SLOTS; j++) {
-            if (clusterNodeGetSlotBit(oldmaster,j)) {
-                clusterDelSlot(j);
-                clusterAddSlot(myself,j);
-            }
-        }
-
-        /* 3) Update my configEpoch to the epoch of the election. */
+        /* Update my configEpoch to the epoch of the election. */
         if (myself->configEpoch < server.cluster->failover_auth_epoch) {
             myself->configEpoch = server.cluster->failover_auth_epoch;
             redisLog(REDIS_WARNING,
                 "configEpoch set to %llu after successful failover",
                 (unsigned long long) myself->configEpoch);
         }
 
-        /* 4) Update state and save config. */
-        clusterUpdateState();
-        clusterSaveConfigOrDie(1);
-
-        /* 5) Pong all the other nodes so that they can update the state
-         *    accordingly and detect that we switched to master role. */
-        clusterBroadcastPong(CLUSTER_BROADCAST_ALL);
-
-        /* 6) If there was a manual failover in progress, clear the state. */
-        resetManualFailover();
+        /* Take responsability for the cluster slots. */
+        clusterFailoverReplaceYourMaster();
     } else {
         clusterLogCantFailover(REDIS_CLUSTER_CANT_FAILOVER_WAITING_VOTES);
     }