@@ -73,6 +73,7 @@ typedef struct sentinelAddr {
 #define SRI_RECONF_SENT (1<<11)     /* SLAVEOF <newmaster> sent. */
 #define SRI_RECONF_INPROG (1<<12)   /* Slave synchronization in progress. */
 #define SRI_RECONF_DONE (1<<13)     /* Slave synchronized with new master. */
+#define SRI_FORCE_FAILOVER (1<<14)  /* Force failover with master up. */
 
 #define SENTINEL_INFO_PERIOD 10000
 #define SENTINEL_PING_PERIOD 1000
@@ -323,6 +324,7 @@ void sentinelAbortFailover(sentinelRedisInstance *ri);
 void sentinelEvent(int level, char *type, sentinelRedisInstance *ri, const char *fmt, ...);
 sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master);
 void sentinelScheduleScriptExecution(char *path, ...);
+void sentinelStartFailover(sentinelRedisInstance *master, int state);
 
 /* ========================= Dictionary types =============================== */
 
@@ -1990,6 +1992,24 @@ void sentinelCommand(redisClient *c) {
             addReplyBulkCString(c,addr->ip);
             addReplyBulkLongLong(c,addr->port);
         }
+    } else if (!strcasecmp(c->argv[1]->ptr,"failover")) {
+        /* SENTINEL FAILOVER <master-name> */
+        sentinelRedisInstance *ri;
+
+        if (c->argc != 3) goto numargserr;
+        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2])) == NULL)
+            return;
+        if (ri->flags & SRI_FAILOVER_IN_PROGRESS) {
+            addReplySds(c,sdsnew("-INPROG Failover already in progress\r\n"));
+            return;
+        }
+        if (sentinelSelectSlave(ri) == NULL) {
+            addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
+            return;
+        }
+        sentinelStartFailover(ri,SENTINEL_FAILOVER_STATE_WAIT_START);
+        ri->flags |= SRI_FORCE_FAILOVER;
+        addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
         /* SENTINEL PENDING-SCRIPTS */
 
@@ -2303,6 +2323,35 @@ char *sentinelGetObjectiveLeader(sentinelRedisInstance *master) {
     return winner;
 }
 
+/* Setup the master state to start a failover as a leader.
+ *
+ * State can be either:
+ *
+ * SENTINEL_FAILOVER_STATE_WAIT_START: starts a failover from scratch.
+ * SENTINEL_FAILOVER_STATE_RECONF_SLAVES: takedown a failed failover.
+ */
+void sentinelStartFailover(sentinelRedisInstance *master, int state) {
+    redisAssert(master->flags & SRI_MASTER);
+    redisAssert(state == SENTINEL_FAILOVER_STATE_WAIT_START ||
+                state == SENTINEL_FAILOVER_STATE_RECONF_SLAVES);
+
+    master->failover_state = state;
+    master->flags |= SRI_FAILOVER_IN_PROGRESS|SRI_I_AM_THE_LEADER;
+    sentinelEvent(REDIS_WARNING,"+failover-triggered",master,"%@");
+
+    /* Pick a random delay if it's a fresh failover (WAIT_START), and not
+     * a recovery of a failover started by another sentinel. */
+    if (master->failover_state == SENTINEL_FAILOVER_STATE_WAIT_START) {
+        master->failover_start_time = mstime() +
+            SENTINEL_FAILOVER_FIXED_DELAY +
+            (rand() % SENTINEL_FAILOVER_MAX_RANDOM_DELAY);
+        sentinelEvent(REDIS_WARNING,"+failover-state-wait-start",master,
+            "%@ #starting in %lld milliseconds",
+            master->failover_start_time-mstime());
+    }
+    master->failover_state_change_time = mstime();
+}
+
 /* This function checks if there are the conditions to start the failover,
  * that is:
  *
@@ -2313,7 +2362,7 @@ char *sentinelGetObjectiveLeader(sentinelRedisInstance *master) {
  * If the conditions are met we flag the master as SRI_FAILOVER_IN_PROGRESS
  * and SRI_I_AM_THE_LEADER.
  */
-void sentinelStartFailover(sentinelRedisInstance *master) {
+void sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
     char *leader;
     int isleader;
 
@@ -2353,7 +2402,7 @@ void sentinelStartFailover(sentinelRedisInstance *master) {
             /* We have already an elected slave if we are in
              * FAILOVER_IN_PROGRESS state, that is, the slave that we
              * observed turning into a master. */
-            master->failover_state = SENTINEL_FAILOVER_STATE_RECONF_SLAVES;
+            sentinelStartFailover(master,SENTINEL_FAILOVER_STATE_RECONF_SLAVES);
             /* As an observer we flagged all the slaves as RECONF_SENT but
              * now we are in charge of actually sending the reconfiguration
              * command so let's clear this flag for all the instances. */
@@ -2366,23 +2415,8 @@ void sentinelStartFailover(sentinelRedisInstance *master) {
          * Do we have a slave to promote? Otherwise don't start a failover
          * at all. */
         if (sentinelSelectSlave(master) == NULL) return;
-        master->failover_state = SENTINEL_FAILOVER_STATE_WAIT_START;
-    }
-
-    master->flags |= SRI_FAILOVER_IN_PROGRESS|SRI_I_AM_THE_LEADER;
-    sentinelEvent(REDIS_WARNING,"+failover-triggered",master,"%@");
-
-    /* Pick a random delay if it's a fresh failover (WAIT_START), and not
-     * a recovery of a failover started by another sentinel. */
-    if (master->failover_state == SENTINEL_FAILOVER_STATE_WAIT_START) {
-        master->failover_start_time = mstime() +
-            SENTINEL_FAILOVER_FIXED_DELAY +
-            (rand() % SENTINEL_FAILOVER_MAX_RANDOM_DELAY);
-        sentinelEvent(REDIS_WARNING,"+failover-state-wait-start",master,
-            "%@ #starting in %lld milliseconds",
-            master->failover_start_time-mstime());
+        sentinelStartFailover(master,SENTINEL_FAILOVER_STATE_WAIT_START);
     }
-    master->failover_state_change_time = mstime();
 }
 
 /* Select a suitable slave to promote. The current algorithm only uses
@@ -2417,10 +2451,11 @@ sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master) {
     int instances = 0;
     dictIterator *di;
     dictEntry *de;
-    mstime_t max_master_down_time;
+    mstime_t max_master_down_time = 0;
 
-    max_master_down_time = (mstime() - master->s_down_since_time) +
-                           (master->down_after_period * 10);
+    if (master->flags & SRI_S_DOWN)
+        max_master_down_time += mstime() - master->s_down_since_time;
+    max_master_down_time += master->down_after_period * 10;
 
     di = dictGetIterator(master->slaves);
     while((de = dictNext(di)) != NULL) {
@@ -2429,6 +2464,12 @@ sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master) {
 
         if (slave->flags & (SRI_S_DOWN|SRI_O_DOWN|SRI_DISCONNECTED)) continue;
         if (slave->last_avail_time < info_validity_time) continue;
+
+        /* If the master is in SDOWN state we get INFO for slaves every second.
+         * Otherwise we get it with the usual period so we need to account for
+         * a larger delay. */
+        if ((master->flags & SRI_S_DOWN) == 0)
+            info_validity_time -= SENTINEL_INFO_PERIOD;
         if (slave->info_refresh < info_validity_time) continue;
         if (slave->master_link_down_time > max_master_down_time) continue;
         instance[instances++] = slave;
@@ -2454,7 +2495,7 @@ void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
      * can go to waitstart if the slave is back rechable a few milliseconds
      * before the master is. In that case when the master is back online
      * we cancel the failover. */
-    if ((ri->flags & (SRI_S_DOWN|SRI_O_DOWN)) == 0) {
+    if ((ri->flags & (SRI_S_DOWN|SRI_O_DOWN|SRI_FORCE_FAILOVER)) == 0) {
         sentinelEvent(REDIS_WARNING,"-failover-abort-master-is-back",
             ri,"%@");
         sentinelAbortFailover(ri);
@@ -2747,7 +2788,7 @@ void sentinelAbortFailover(sentinelRedisInstance *ri) {
 
     sentinel_role = (ri->flags & SRI_I_AM_THE_LEADER) ? SENTINEL_LEADER :
                                                         SENTINEL_OBSERVER;
-    ri->flags &= ~(SRI_FAILOVER_IN_PROGRESS|SRI_I_AM_THE_LEADER);
+    ri->flags &= ~(SRI_FAILOVER_IN_PROGRESS|SRI_I_AM_THE_LEADER|SRI_FORCE_FAILOVER);
     ri->failover_state = SENTINEL_FAILOVER_STATE_NONE;
     ri->failover_state_change_time = mstime();
     if (ri->promoted_slave) {
@@ -2821,7 +2862,7 @@ void sentinelHandleRedisInstance(sentinelRedisInstance *ri) {
     /* Only masters */
     if (ri->flags & SRI_MASTER) {
         sentinelCheckObjectivelyDown(ri);
-        sentinelStartFailover(ri);
+        sentinelStartFailoverIfNeeded(ri);
         sentinelFailoverStateMachine(ri);
         sentinelAbortFailoverIfNeeded(ri);
     }