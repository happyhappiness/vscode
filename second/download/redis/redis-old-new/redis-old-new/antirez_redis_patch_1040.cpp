@@ -1724,8 +1724,11 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
             }
 
             /* Update local current_epoch if received current_epoch is greater. */
-            if (current_epoch > sentinel.current_epoch)
+            if (current_epoch > sentinel.current_epoch) {
                 sentinel.current_epoch = current_epoch;
+                sentinelEvent(REDIS_WARNING,"+new-epoch",ri,"%llu",
+                    (unsigned long long) sentinel.current_epoch);
+            }
 
             /* Update master info if received configuration is newer. */
             if ((msgmaster = sentinelGetMasterByName(token[5])) != NULL) {
@@ -2399,15 +2402,18 @@ int compareRunID(const void *a, const void *b) {
  * If a vote is not available returns NULL, otherwise return the Sentinel
  * runid and populate the leader_epoch with the epoch of the last vote. */
 char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
-    if (req_epoch > sentinel.current_epoch)
+    if (req_epoch > sentinel.current_epoch) {
         sentinel.current_epoch = req_epoch;
+        sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+            (unsigned long long) sentinel.current_epoch);
+    }
 
     if (master->leader_epoch < req_epoch && sentinel.current_epoch <= req_epoch) {
         sdsfree(master->leader);
         master->leader = sdsnew(req_runid);
         master->leader_epoch = sentinel.current_epoch;
-        printf("Selected leader %s for epoch %llu\n", master->leader,
-            (unsigned long long) master->leader_epoch);
+        sentinelEvent(REDIS_WARNING,"+vote-for-leader",master,"%s %llu",
+            master->leader, (unsigned long long) master->leader_epoch);
     }
 
     *leader_epoch = master->leader_epoch;
@@ -2539,7 +2545,9 @@ void sentinelStartFailover(sentinelRedisInstance *master) {
     master->failover_state = SENTINEL_FAILOVER_STATE_WAIT_START;
     master->flags |= SRI_FAILOVER_IN_PROGRESS;
     master->failover_epoch = ++sentinel.current_epoch;
-    sentinelEvent(REDIS_WARNING,"+failover-triggered",master,"%@");
+    sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+        (unsigned long long) sentinel.current_epoch);
+    sentinelEvent(REDIS_WARNING,"+try-failover",master,"%@");
     master->failover_start_time = mstime();
     master->failover_state_change_time = mstime();
 }
@@ -2658,6 +2666,7 @@ void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
 
     /* If I'm not the leader, I can't continue with the failover. */
     if (!isleader) return;
+    sentinelEvent(REDIS_WARNING,"+elected-leader",ri,"%@");
 
     /* Start the failover going to the next state if enough time has
      * elapsed. */