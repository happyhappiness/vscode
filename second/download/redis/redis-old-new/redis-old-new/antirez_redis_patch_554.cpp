@@ -114,6 +114,11 @@ typedef struct sentinelAddr {
 #define SENTINEL_SCRIPT_MAX_RETRY 10
 #define SENTINEL_SCRIPT_RETRY_DELAY 30000 /* 30 seconds between retries. */
 
+/* SENTINEL SIMULATE-FAILURE command flags. */
+#define SENTINEL_SIMFAILURE_NONE 0
+#define SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION (1<<0)
+#define SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION (1<<1)
+
 /* The link to a sentinelRedisInstance. When we have the same set of Sentinels
  * monitoring many masters, we have different instances representing the
  * same Sentinels, one per master, and we need to share the hiredis connections
@@ -235,6 +240,7 @@ struct sentinelState {
                            not NULL. */
     int announce_port;  /* Port that is gossiped to other sentinels if
                            non zero. */
+    unsigned long simfailure_flags; /* Failures simulation. */
 } sentinel;
 
 /* A script execution job. */
@@ -369,6 +375,7 @@ void sentinelGenerateInitialMonitorEvents(void);
 int sentinelSendPing(sentinelRedisInstance *ri);
 int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master);
 sentinelRedisInstance *getSentinelRedisInstanceByAddrAndRunID(dict *instances, char *ip, int port, char *runid);
+void sentinelSimFailureCrash(void);
 
 /* ========================= Dictionary types =============================== */
 
@@ -460,6 +467,7 @@ void initSentinel(void) {
     sentinel.scripts_queue = listCreate();
     sentinel.announce_ip = NULL;
     sentinel.announce_port = 0;
+    sentinel.simfailure_flags = SENTINEL_SIMFAILURE_NONE;
     memset(sentinel.myid,0,sizeof(sentinel.myid));
 }
 
@@ -2140,6 +2148,9 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
             ri->master->failover_state_change_time = mstime();
             sentinelFlushConfig();
             sentinelEvent(REDIS_WARNING,"+promoted-slave",ri,"%@");
+            if (sentinel.simfailure_flags &
+                SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION)
+                sentinelSimFailureCrash();
             sentinelEvent(REDIS_WARNING,"+failover-state-reconf-slaves",
                 ri->master,"%@");
             sentinelCallClientReconfScript(ri->master,SENTINEL_LEADER,
@@ -3049,6 +3060,7 @@ void sentinelCommand(redisClient *c) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);
     } else if (!strcasecmp(c->argv[1]->ptr,"info-cache")) {
+        /* SENTINEL INFO-CACHE <name> */
         if (c->argc < 2) goto numargserr;
         mstime_t now = mstime();
 
@@ -3109,6 +3121,29 @@ void sentinelCommand(redisClient *c) {
         }
         dictReleaseIterator(di);
         if (masters_local != sentinel.masters) dictRelease(masters_local);
+    } else if (!strcasecmp(c->argv[1]->ptr,"simulate-failure")) {
+        /* SENTINEL SIMULATE-FAILURE <flag> <flag> ... <flag> */
+        int j;
+
+        sentinel.simfailure_flags = SENTINEL_SIMFAILURE_NONE;
+        for (j = 2; j < c->argc; j++) {
+            if (!strcasecmp(c->argv[j]->ptr,"crash-after-election")) {
+                sentinel.simfailure_flags |=
+                    SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION;
+                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
+                    "will crash after being successfully elected as failover "
+                    "leader");
+            } else if (!strcasecmp(c->argv[j]->ptr,"crash-after-promotion")) {
+                sentinel.simfailure_flags |=
+                    SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
+                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
+                    "will crash after promoting the selected slave to master");
+            } else {
+                addReplyError(c,"Unknown failure simulation specified");
+                return;
+            }
+        }
+        addReply(c,shared.ok);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);
@@ -3156,11 +3191,13 @@ void sentinelInfoCommand(redisClient *c) {
             "sentinel_masters:%lu\r\n"
             "sentinel_tilt:%d\r\n"
             "sentinel_running_scripts:%d\r\n"
-            "sentinel_scripts_queue_length:%ld\r\n",
+            "sentinel_scripts_queue_length:%ld\r\n"
+            "sentinel_simulate_failure_flags:%lu\r\n",
             dictSize(sentinel.masters),
             sentinel.tilt,
             sentinel.running_scripts,
-            listLength(sentinel.scripts_queue));
+            listLength(sentinel.scripts_queue),
+            sentinel.simfailure_flags);
 
         di = dictGetIterator(sentinel.masters);
         while((de = dictNext(di)) != NULL) {
@@ -3503,6 +3540,13 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
 
 /* =============================== FAILOVER ================================= */
 
+/* Crash because of user request via SENTINEL simulate-failure command. */
+void sentinelSimFailureCrash(void) {
+    redisLog(REDIS_WARNING,
+        "Sentinel CRASH because of SENTINEL simulate-failure");
+    exit(99);
+}
+
 /* Vote for the sentinel with 'req_runid' or return the old vote if already
  * voted for the specifed 'req_epoch' or one greater.
  *
@@ -3881,6 +3925,8 @@ void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
         return;
     }
     sentinelEvent(REDIS_WARNING,"+elected-leader",ri,"%@");
+    if (sentinel.simfailure_flags & SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION)
+        sentinelSimFailureCrash();
     ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
     ri->failover_state_change_time = mstime();
     sentinelEvent(REDIS_WARNING,"+failover-state-select-slave",ri,"%@");