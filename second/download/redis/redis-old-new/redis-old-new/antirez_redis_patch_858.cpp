@@ -306,6 +306,8 @@ int clusterSaveConfig(int do_fsync) {
     struct stat sb;
     int fd;
 
+    server.cluster->todo_before_sleep &= ~CLUSTER_TODO_SAVE_CONFIG;
+
     /* Get the nodes description and concatenate our "vars" directive to
      * save currentEpoch and lastVoteEpoch. */
     ci = clusterGenNodesDescription(REDIS_NODE_HANDSHAKE);
@@ -325,7 +327,10 @@ int clusterSaveConfig(int do_fsync) {
         }
     }
     if (write(fd,ci,sdslen(ci)) != (ssize_t)sdslen(ci)) goto err;
-    if (do_fsync) fsync(fd);
+    if (do_fsync) {
+        server.cluster->todo_before_sleep &= ~CLUSTER_TODO_FSYNC_CONFIG;
+        fsync(fd);
+    }
 
     /* Truncate the file if needed to remove the final \n padding that
      * is just garbage. */
@@ -2367,6 +2372,8 @@ void clusterHandleSlaveFailover(void) {
     int j;
     mstime_t auth_timeout, auth_retry_time;
 
+    server.cluster->todo_before_sleep &= ~CLUSTER_TODO_HANDLE_FAILOVER;
+
     /* Compute the failover timeout (the max time we have to send votes
      * and wait for replies), and the failover retry time (the time to wait
      * before waiting again.
@@ -2944,7 +2951,8 @@ void clusterBeforeSleep(void) {
         clusterSaveConfigOrDie(fsync);
     }
 
-    /* Reset our flags. */
+    /* Reset our flags (not strictly needed since every single function
+     * called for flags set should be able to clear its flag). */
     server.cluster->todo_before_sleep = 0;
 }
 
@@ -3061,6 +3069,8 @@ void clusterUpdateState(void) {
     static mstime_t among_minority_time;
     static mstime_t first_call_time = 0;
 
+    server.cluster->todo_before_sleep &= ~CLUSTER_TODO_UPDATE_STATE;
+
     /* If this is a master node, wait some time before turning the state
      * into OK, since it is not a good idea to rejoin the cluster as a writable
      * master, after a reboot, without giving the cluster a chance to