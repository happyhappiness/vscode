@@ -1693,16 +1693,16 @@ void clusterHandleSlaveFailover(void) {
             }
         }
 
-        /* 3) Pong all the other nodes so that they can update the state
-         *    accordingly and detect that we switched to master role. */
-        clusterBroadcastPong();
-
-        /* 4) Update my configEpoch to the epoch of the election. */
+        /* 3) Update my configEpoch to the epoch of the election. */
         server.cluster->myself->configEpoch = server.cluster->failover_auth_epoch;
 
-        /* 5) Update state and save config. */
+        /* 4) Update state and save config. */
         clusterUpdateState();
         clusterSaveConfigOrDie();
+
+        /* 5) Pong all the other nodes so that they can update the state
+         *    accordingly and detect that we switched to master role. */
+        clusterBroadcastPong();
     }
 }
 