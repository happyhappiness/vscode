@@ -334,6 +334,7 @@ void sentinelStartFailover(sentinelRedisInstance *master);
 void sentinelDiscardReplyCallback(redisAsyncContext *c, void *reply, void *privdata);
 int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port);
 char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch);
+void sentinelFlushConfig(void);
 
 /* ========================= Dictionary types =============================== */
 
@@ -1201,13 +1202,17 @@ int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip,
         slave = createSentinelRedisInstance(NULL,SRI_SLAVE,slaves[j]->ip,
                     slaves[j]->port, master->quorum, master);
         releaseSentinelAddr(slaves[j]);
-        if (slave) sentinelEvent(REDIS_NOTICE,"+slave",slave,"%@");
+        if (slave) {
+            sentinelEvent(REDIS_NOTICE,"+slave",slave,"%@");
+            sentinelFlushConfig();
+        }
     }
     zfree(slaves);
 
     /* Release the old address at the end so we are safe even if the function
      * gets the master->addr->ip and master->addr->port as arguments. */
     releaseSentinelAddr(oldaddr);
+    sentinelFlushConfig();
     return REDIS_OK;
 }
 
@@ -1345,12 +1350,14 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
     di = dictGetIterator(sentinel.masters);
     while((de = dictNext(di)) != NULL) {
         sentinelRedisInstance *master, *ri;
+        sentinelAddr *master_addr;
         sds line;
 
         /* sentinel monitor */
         master = dictGetVal(de);
+        master_addr = sentinelGetCurrentMasterAddress(master);
         line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
-            master->name, master->addr->ip, master->addr->port,
+            master->name, master_addr->ip, master_addr->port,
             master->quorum);
         rewriteConfigRewriteLine(state,"sentinel",line,1);
 
@@ -1411,7 +1418,18 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
         /* sentinel known-slave */
         di2 = dictGetIterator(master->slaves);
         while((de = dictNext(di)) != NULL) {
+            sentinelAddr *slave_addr;
+
             ri = dictGetVal(de);
+            slave_addr = ri->addr;
+
+            /* If master_addr (obtained using sentinelGetCurrentMasterAddress()
+             * so it may be the address of the promoted slave) is equal to this
+             * slave's address, a failover is in progress and the slave was
+             * already successfully promoted. So as the address of this slave
+             * we use the old master address instead. */
+            if (sentinelAddrIsEqual(slave_addr,master_addr))
+                slave_addr = master->addr;
             line = sdscatprintf(sdsempty(),
                 "sentinel known-slave %s %s %d",
                 master->name, ri->addr->ip, ri->addr->port);
@@ -1754,6 +1772,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
             ri->master->config_epoch = ri->master->failover_epoch;
             ri->master->failover_state = SENTINEL_FAILOVER_STATE_RECONF_SLAVES;
             ri->master->failover_state_change_time = mstime();
+            sentinelFlushConfig();
             sentinelEvent(REDIS_WARNING,"+promoted-slave",ri,"%@");
             sentinelEvent(REDIS_WARNING,"+failover-state-reconf-slaves",
                 ri->master,"%@");
@@ -1974,6 +1993,7 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
                      * for Sentinels we don't have a later chance to fill it,
                      * so do it now. */
                     si->runid = sdsnew(token[2]);
+                    sentinelFlushConfig();
                 }
             }
 