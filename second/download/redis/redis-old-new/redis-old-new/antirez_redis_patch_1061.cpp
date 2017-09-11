@@ -257,6 +257,7 @@ void clusterInit(void) {
     server.cluster->nodes = dictCreate(&clusterNodesDictType,NULL);
     server.cluster->failover_auth_time = 0;
     server.cluster->failover_auth_count = 0;
+    server.cluster->failover_auth_epoch = 0;
     memset(server.cluster->migrating_slots_to,0,
         sizeof(server.cluster->migrating_slots_to));
     memset(server.cluster->importing_slots_from,0,
@@ -1581,36 +1582,60 @@ void clusterSendFailoverAuthIfNeeded(clusterNode *node, clusterMsg *request) {
  *
  * The gaol of this function is:
  * 1) To check if we are able to perform a failover, is our data updated?
- * 2) Ask reachable masters the authorization to perform the failover.
+ * 2) Try to get elected by masters.
  * 3) Check if there is the majority of masters agreeing we should failover.
  * 4) Perform the failover informing all the other nodes.
  */
 void clusterHandleSlaveFailover(void) {
     time_t data_age = server.unixtime - server.repl_down_since;
-    time_t auth_age = server.unixtime - server.cluster->failover_auth_time;
+    mstime_t auth_age = mstime() - server.cluster->failover_auth_time;
     int needed_quorum = (server.cluster->size / 2) + 1;
     int j;
 
+    /* Remove the node timeout from the data age as it is fine that we are
+     * disconnected from our master at least for the time it was down to be
+     * flagged as FAIL, that's the baseline. */
+    if (data_age > server.cluster_node_timeout)
+        data_age -= server.cluster_node_timeout;
+
     /* Check if our data is recent enough. For now we just use a fixed
      * constant of ten times the node timeout since the cluster should
      * react much faster to a master down. */
     if (data_age >
         server.cluster_node_timeout * REDIS_CLUSTER_SLAVE_VALIDITY_MULT)
         return;
 
-    /* TODO: check if we are the first slave as well? Or just rely on the
-     * master authorization? */
-
-    /* Ask masters if we are authorized to perform the failover. If there
-     * is a pending auth request that's too old, reset it. */
+    /* Compute the time at which we can start an election. */
     if (server.cluster->failover_auth_time == 0 ||
         auth_age >
-        server.cluster_node_timeout * REDIS_CLUSTER_FAILOVER_AUTH_RETRY_MULT)
+        server.cluster_node_timeout * 1000 * REDIS_CLUSTER_FAILOVER_AUTH_RETRY_MULT)
     {
-        redisLog(REDIS_WARNING,"Asking masters if I can failover...");
-        server.cluster->failover_auth_time = time(NULL);
+        server.cluster->failover_auth_time = mstime() +
+            500 + /* Fixed delay of 500 milliseconds, let FAIL msg propagate. */
+            data_age * 100 + /* Add 100 milliseconds for every second of age. */
+            random() % 500; /* Random delay between 0 and 500 milliseconds. */
         server.cluster->failover_auth_count = 0;
+        server.cluster->failover_auth_sent = 0;
+        redisLog(REDIS_WARNING,"Start of election delayed for %lld milliseconds.",
+            server.cluster->failover_auth_time - mstime());
+        return;
+    }
+
+    /* Return ASAP if we can't still start the election. */
+    if (mstime() < server.cluster->failover_auth_time) return;
+
+    /* Return ASAP if the election is too old to be valid. */
+    if (mstime() - server.cluster->failover_auth_time > server.cluster_node_timeout)
+        return;
+
+    /* Ask for votes if needed. */
+    if (server.cluster->failover_auth_sent == 0) {
+        server.cluster->currentEpoch++;
+        server.cluster->failover_auth_epoch = server.cluster->currentEpoch;
+        redisLog(REDIS_WARNING,"Starting a failover election for epoch %llu.",
+            server.cluster->currentEpoch);
         clusterRequestFailoverAuth();
+        server.cluster->failover_auth_sent = 1;
         return; /* Wait for replies. */
     }
 
@@ -1619,7 +1644,7 @@ void clusterHandleSlaveFailover(void) {
         clusterNode *oldmaster = server.cluster->myself->slaveof;
 
         redisLog(REDIS_WARNING,
-            "Masters quorum reached: failing over my (failing) master.");
+            "Failover election won: failing over my (failing) master.");
         /* We have the quorum, perform all the steps to correctly promote
          * this slave to a master.
          *
@@ -1644,7 +1669,10 @@ void clusterHandleSlaveFailover(void) {
          *    accordingly and detect that we switched to master role. */
         clusterBroadcastPong();
 
-        /* 4) Update state and save config. */
+        /* 4) Update my configEpoch to the epoch of the election. */
+        server.cluster->myself->configEpoch = server.cluster->failover_auth_epoch;
+
+        /* 5) Update state and save config. */
         clusterUpdateState();
         clusterSaveConfigOrDie();
     }