      * 1) We are a master left without slots. This means that we were
      *    failed over and we should turn into a replica of the new
      *    master.
      * 2) We are a slave and our master is left without slots. We need
      *    to replicate to the new slots owner. */
     if (newmaster && curmaster->numslots == 0) {
-        redisLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Configuration change detected. Reconfiguring myself "
             "as a replica of %.40s", sender->name);
         clusterSetMaster(sender);
         clusterDoBeforeSleep(CLUSTER_TODO_SAVE_CONFIG|
                              CLUSTER_TODO_UPDATE_STATE|
                              CLUSTER_TODO_FSYNC_CONFIG);
