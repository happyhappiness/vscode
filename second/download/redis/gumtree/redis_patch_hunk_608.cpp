         /* Only ask if master is down to other sentinels if:
          *
          * 1) We believe it is down, or there is a failover in progress.
          * 2) Sentinel is connected.
          * 3) We did not received the info within SENTINEL_ASK_PERIOD ms. */
         if ((master->flags & SRI_S_DOWN) == 0) continue;
-        if (ri->flags & SRI_DISCONNECTED) continue;
+        if (ri->link->disconnected) continue;
         if (!(flags & SENTINEL_ASK_FORCED) &&
             mstime() - ri->last_master_down_reply_time < SENTINEL_ASK_PERIOD)
             continue;
 
         /* Ask */
         ll2string(port,sizeof(port),master->addr->port);
-        retval = redisAsyncCommand(ri->cc,
-                    sentinelReceiveIsMasterDownReply, NULL,
+        retval = redisAsyncCommand(ri->link->cc,
+                    sentinelReceiveIsMasterDownReply, ri,
                     "SENTINEL is-master-down-by-addr %s %s %llu %s",
                     master->addr->ip, port,
                     sentinel.current_epoch,
                     (master->failover_state > SENTINEL_FAILOVER_STATE_NONE) ?
-                    server.runid : "*");
-        if (retval == REDIS_OK) ri->pending_commands++;
+                    sentinel.myid : "*");
+        if (retval == C_OK) ri->link->pending_commands++;
     }
     dictReleaseIterator(di);
 }
 
 /* =============================== FAILOVER ================================= */
 
+/* Crash because of user request via SENTINEL simulate-failure command. */
+void sentinelSimFailureCrash(void) {
+    serverLog(LL_WARNING,
+        "Sentinel CRASH because of SENTINEL simulate-failure");
+    exit(99);
+}
+
 /* Vote for the sentinel with 'req_runid' or return the old vote if already
  * voted for the specifed 'req_epoch' or one greater.
  *
  * If a vote is not available returns NULL, otherwise return the Sentinel
  * runid and populate the leader_epoch with the epoch of the vote. */
 char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
     if (req_epoch > sentinel.current_epoch) {
         sentinel.current_epoch = req_epoch;
         sentinelFlushConfig();
-        sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+        sentinelEvent(LL_WARNING,"+new-epoch",master,"%llu",
             (unsigned long long) sentinel.current_epoch);
     }
 
     if (master->leader_epoch < req_epoch && sentinel.current_epoch <= req_epoch)
     {
         sdsfree(master->leader);
         master->leader = sdsnew(req_runid);
         master->leader_epoch = sentinel.current_epoch;
         sentinelFlushConfig();
-        sentinelEvent(REDIS_WARNING,"+vote-for-leader",master,"%s %llu",
+        sentinelEvent(LL_WARNING,"+vote-for-leader",master,"%s %llu",
             master->leader, (unsigned long long) master->leader_epoch);
         /* If we did not voted for ourselves, set the master failover start
          * time to now, in order to force a delay before we can start a
          * failover for the same master. */
-        if (strcasecmp(master->leader,server.runid))
+        if (strcasecmp(master->leader,sentinel.myid))
             master->failover_start_time = mstime()+rand()%SENTINEL_MAX_DESYNC;
     }
 
     *leader_epoch = master->leader_epoch;
     return master->leader ? sdsnew(master->leader) : NULL;
 }
