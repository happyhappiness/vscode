@@ -58,25 +58,20 @@ typedef struct sentinelAddr {
 #define SRI_O_DOWN (1<<5)   /* Objectively down (quorum reached). */
 #define SRI_MASTER_DOWN (1<<6) /* A Sentinel with this flag set thinks that
                                    its master is down. */
-/* SRI_CAN_FAILOVER when set in an SRI_MASTER instance means that we are
- * allowed to perform the failover for this master.
- * When set in a SRI_SENTINEL instance means that sentinel is allowed to
- * perform the failover on its master. */
-#define SRI_CAN_FAILOVER (1<<7)
-#define SRI_FAILOVER_IN_PROGRESS (1<<8) /* Failover is in progress for
+#define SRI_FAILOVER_IN_PROGRESS (1<<7) /* Failover is in progress for
                                            this master. */
-#define SRI_PROMOTED (1<<9)            /* Slave selected for promotion. */
-#define SRI_RECONF_SENT (1<<10)     /* SLAVEOF <newmaster> sent. */
-#define SRI_RECONF_INPROG (1<<11)   /* Slave synchronization in progress. */
-#define SRI_RECONF_DONE (1<<12)     /* Slave synchronized with new master. */
-#define SRI_FORCE_FAILOVER (1<<13)  /* Force failover with master up. */
-#define SRI_SCRIPT_KILL_SENT (1<<14) /* SCRIPT KILL already sent on -BUSY */
+#define SRI_PROMOTED (1<<8)            /* Slave selected for promotion. */
+#define SRI_RECONF_SENT (1<<9)     /* SLAVEOF <newmaster> sent. */
+#define SRI_RECONF_INPROG (1<<10)   /* Slave synchronization in progress. */
+#define SRI_RECONF_DONE (1<<11)     /* Slave synchronized with new master. */
+#define SRI_FORCE_FAILOVER (1<<12)  /* Force failover with master up. */
+#define SRI_SCRIPT_KILL_SENT (1<<13) /* SCRIPT KILL already sent on -BUSY */
 
 #define SENTINEL_INFO_PERIOD 10000
 #define SENTINEL_PING_PERIOD 1000
 #define SENTINEL_ASK_PERIOD 1000
 #define SENTINEL_PUBLISH_PERIOD 2000
-#define SENTINEL_DOWN_AFTER_PERIOD 30000
+#define SENTINEL_DEFAULT_DOWN_AFTER 30000
 #define SENTINEL_HELLO_CHANNEL "__sentinel__:hello"
 #define SENTINEL_TILT_TRIGGER 2000
 #define SENTINEL_TILT_PERIOD (SENTINEL_PING_PERIOD*30)
@@ -893,7 +888,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->s_down_since_time = 0;
     ri->o_down_since_time = 0;
     ri->down_after_period = master ? master->down_after_period :
-                            SENTINEL_DOWN_AFTER_PERIOD;
+                            SENTINEL_DEFAULT_DOWN_AFTER;
     ri->master_link_down_time = 0;
     ri->auth_pass = NULL;
     ri->slave_priority = SENTINEL_DEFAULT_SLAVE_PRIORITY;
@@ -1111,7 +1106,7 @@ void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
     }
     if (ri->cc) sentinelKillLink(ri,ri->cc);
     if (ri->pc) sentinelKillLink(ri,ri->pc);
-    ri->flags &= SRI_MASTER|SRI_CAN_FAILOVER|SRI_DISCONNECTED;
+    ri->flags &= SRI_MASTER|SRI_DISCONNECTED;
     if (ri->leader) {
         sdsfree(ri->leader);
         ri->leader = NULL;
@@ -1276,17 +1271,6 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         ri->failover_timeout = atoi(argv[2]);
         if (ri->failover_timeout <= 0)
             return "negative or zero time parameter.";
-    } else if (!strcasecmp(argv[0],"can-failover") && argc == 3) {
-        /* can-failover <name> <yes/no> */
-        int yesno = yesnotoi(argv[2]);
-
-        ri = sentinelGetMasterByName(argv[1]);
-        if (!ri) return "No such master with specified name.";
-        if (yesno == -1) return "Argument must be either yes or no.";
-        if (yesno)
-            ri->flags |= SRI_CAN_FAILOVER;
-        else
-            ri->flags &= ~SRI_CAN_FAILOVER;
    } else if (!strcasecmp(argv[0],"parallel-syncs") && argc == 3) {
         /* parallel-syncs <name> <milliseconds> */
         ri = sentinelGetMasterByName(argv[1]);
@@ -1826,25 +1810,24 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
     if (strstr(r->element[2]->str,server.runid) != NULL) return;
 
     {
-        /* Format is composed of 9 tokens:
-         * 0=ip,1=port,2=runid,3=can_failover,4=current_epoch,
-         * 5=master_name,6=master_ip,7=master_port,8=master_config_epoch. */
-        int numtokens, port, removed, canfailover, master_port;
+        /* Format is composed of 8 tokens:
+         * 0=ip,1=port,2=runid,3=current_epoch,4=master_name,
+         * 5=master_ip,6=master_port,7=master_config_epoch. */
+        int numtokens, port, removed, master_port;
         uint64_t current_epoch, master_config_epoch;
         char **token = sdssplitlen(r->element[2]->str,
                                    r->element[2]->len,
                                    ",",1,&numtokens);
         sentinelRedisInstance *si;
 
-        if (numtokens == 9) {
+        if (numtokens == 8) {
             /* First, try to see if we already have this sentinel. */
             port = atoi(token[1]);
-            master_port = atoi(token[7]);
-            canfailover = atoi(token[3]);
+            master_port = atoi(token[6]);
             si = getSentinelRedisInstanceByAddrAndRunID(
                             master->sentinels,token[0],port,token[2]);
-            current_epoch = strtoull(token[4],NULL,10);
-            master_config_epoch = strtoull(token[8],NULL,10);
+            current_epoch = strtoull(token[3],NULL,10);
+            master_config_epoch = strtoull(token[7],NULL,10);
             sentinelRedisInstance *msgmaster;
 
             if (!si) {
@@ -1871,39 +1854,33 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
                 }
             }
 
-            /* Update local current_epoch if received current_epoch is greater. */
+            /* Update local current_epoch if received current_epoch is greater.*/
             if (current_epoch > sentinel.current_epoch) {
                 sentinel.current_epoch = current_epoch;
                 sentinelEvent(REDIS_WARNING,"+new-epoch",ri,"%llu",
                     (unsigned long long) sentinel.current_epoch);
             }
 
             /* Update master info if received configuration is newer. */
-            if ((msgmaster = sentinelGetMasterByName(token[5])) != NULL) {
+            if ((msgmaster = sentinelGetMasterByName(token[4])) != NULL) {
                 if (msgmaster->config_epoch < master_config_epoch) {
                     msgmaster->config_epoch = master_config_epoch;
                     if (master_port != msgmaster->addr->port ||
-                        !strcmp(msgmaster->addr->ip, token[6]))
+                        !strcmp(msgmaster->addr->ip, token[5]))
                     {
                         sentinelEvent(REDIS_WARNING,"+switch-master",
                             msgmaster,"%s %s %d %s %d",
                             msgmaster->name,
                             msgmaster->addr->ip, msgmaster->addr->port,
-                            token[6], master_port);
+                            token[5], master_port);
                         sentinelResetMasterAndChangeAddress(msgmaster,
-                                                    token[6], master_port);
+                                                    token[5], master_port);
                     }
                 }
             }
 
             /* Update the state of the Sentinel. */
-            if (si) {
-                si->last_hello_time = mstime();
-                if (canfailover)
-                    si->flags |= SRI_CAN_FAILOVER;
-                else
-                    si->flags &= ~SRI_CAN_FAILOVER;
-            }
+            if (si) si->last_hello_time = mstime();
         }
         sdsfreesplitres(token,numtokens);
     }
@@ -1964,10 +1941,9 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
             sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
             snprintf(payload,sizeof(payload),
-                "%s,%d,%s,%d,%llu," /* Info about this sentinel. */
+                "%s,%d,%s,%llu," /* Info about this sentinel. */
                 "%s,%s,%d,%lld",    /* Info about current master. */
                 ip, server.port, server.runid,
-                (master->flags & SRI_CAN_FAILOVER) != 0,
                 (unsigned long long) sentinel.current_epoch,
                 /* --- */
                 master->name,master_addr->ip,master_addr->port,
@@ -2138,10 +2114,6 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
         addReplyBulkLongLong(c,mstime() - ri->last_hello_time);
         fields++;
 
-        addReplyBulkCString(c,"can-failover-its-master");
-        addReplyBulkLongLong(c,(ri->flags & SRI_CAN_FAILOVER) != 0);
-        fields++;
-
         addReplyBulkCString(c,"voted-leader");
         addReplyBulkCString(c,ri->leader ? ri->leader : "?");
         fields++;
@@ -2540,25 +2512,6 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
 
 /* =============================== FAILOVER ================================= */
 
-/* Given a master get the "subjective leader", that is, among all the sentinels
- * with given characteristics, the one with the lexicographically smaller
- * runid. The characteristics required are:
- *
- * 1) Has SRI_CAN_FAILOVER flag.
- * 2) Is not disconnected.
- * 3) Recently answered to our ping (no longer than
- *    SENTINEL_INFO_VALIDITY_TIME milliseconds ago).
- *
- * The function returns a pointer to an sds string representing the runid of the
- * leader sentinel instance (from our point of view). Otherwise NULL is
- * returned if there are no suitable sentinels.
- */
-
-int compareRunID(const void *a, const void *b) {
-    char **aptrptr = (char**)a, **bptrptr = (char**)b;
-    return strcasecmp(*aptrptr, *bptrptr);
-}
-
 /* Vote for the sentinel with 'req_runid' or return the old vote if already
  * voted for the specifed 'req_epoch' or one greater.
  *
@@ -2725,17 +2678,17 @@ void sentinelStartFailover(sentinelRedisInstance *master) {
 /* This function checks if there are the conditions to start the failover,
  * that is:
  *
- * 1) Enough time has passed since O_DOWN.
- * 2) The master is marked as SRI_CAN_FAILOVER, so we can failover it.
+ * 1) Master must be in ODOWN condition.
+ * 2) No failover already in progress.
+ * 3) No failover already attempted recently.
  * 
  * We still don't know if we'll win the election so it is possible that we
  * start the failover but that we'll not be able to act.
  *
  * Return non-zero if a failover was started. */
 int sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
     /* We can't failover if the master is not in O_DOWN state. */
-    if (!(master->flags & SRI_CAN_FAILOVER) ||
-        !(master->flags & SRI_O_DOWN)) return 0;
+    if (!(master->flags & SRI_O_DOWN)) return 0;
 
     /* Failover already in progress? */
     if (master->flags & SRI_FAILOVER_IN_PROGRESS) return 0;