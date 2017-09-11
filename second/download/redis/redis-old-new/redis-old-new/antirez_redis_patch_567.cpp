@@ -118,7 +118,7 @@ typedef struct sentinelAddr {
 typedef struct sentinelRedisInstance {
     int flags;      /* See SRI_... defines */
     char *name;     /* Master name from the point of view of this sentinel. */
-    char *runid;    /* run ID of this instance. */
+    char *runid;    /* Run ID of this instance, or unique ID if is a Sentinel.*/
     uint64_t config_epoch;  /* Configuration epoch. */
     sentinelAddr *addr; /* Master host. */
     redisAsyncContext *cc; /* Hiredis context for commands. */
@@ -195,19 +195,20 @@ typedef struct sentinelRedisInstance {
 
 /* Main state. */
 struct sentinelState {
-    uint64_t current_epoch;     /* Current epoch. */
+    char myid[REDIS_RUN_ID_SIZE+1]; /* This sentinel ID. */
+    uint64_t current_epoch;         /* Current epoch. */
     dict *masters;      /* Dictionary of master sentinelRedisInstances.
                            Key is the instance name, value is the
                            sentinelRedisInstance structure pointer. */
     int tilt;           /* Are we in TILT mode? */
     int running_scripts;    /* Number of scripts in execution right now. */
-    mstime_t tilt_start_time;   /* When TITL started. */
-    mstime_t previous_time;     /* Last time we ran the time handler. */
-    list *scripts_queue;    /* Queue of user scripts to execute. */
-    char *announce_ip;      /* IP addr that is gossiped to other sentinels if
-                               not NULL. */
-    int announce_port;      /* Port that is gossiped to other sentinels if
-                               non zero. */
+    mstime_t tilt_start_time;       /* When TITL started. */
+    mstime_t previous_time;         /* Last time we ran the time handler. */
+    list *scripts_queue;            /* Queue of user scripts to execute. */
+    char *announce_ip;  /* IP addr that is gossiped to other sentinels if
+                           not NULL. */
+    int announce_port;  /* Port that is gossiped to other sentinels if
+                           non zero. */
 } sentinel;
 
 /* A script execution job. */
@@ -433,12 +434,13 @@ void initSentinel(void) {
     sentinel.scripts_queue = listCreate();
     sentinel.announce_ip = NULL;
     sentinel.announce_port = 0;
+    memset(sentinel.myid,0,sizeof(sentinel.myid));
 }
 
 /* This function gets called when the server is in Sentinel mode, started,
  * loaded the configuration, and is ready for normal operations. */
 void sentinelIsRunning(void) {
-    redisLog(REDIS_WARNING,"Sentinel runid is %s", server.runid);
+    int j;
 
     if (server.configfile == NULL) {
         redisLog(REDIS_WARNING,
@@ -451,6 +453,21 @@ void sentinelIsRunning(void) {
         exit(1);
     }
 
+    /* If this Sentinel has yet no ID set in the configuration file, we
+     * pick a random one and persist the config on disk. From now on this
+     * will be this Sentinel ID across restarts. */
+    for (j = 0; j < REDIS_RUN_ID_SIZE; j++)
+        if (sentinel.myid[j] != 0) break;
+
+    if (j == REDIS_RUN_ID_SIZE) {
+        /* Pick ID and presist the config. */
+        getRandomHexChars(sentinel.myid,REDIS_RUN_ID_SIZE);
+        sentinelFlushConfig();
+    }
+
+    /* Log its ID to make debugging of issues simpler. */
+    redisLog(REDIS_WARNING,"Sentinel ID is %s", sentinel.myid);
+
     /* We want to generate a +monitor event for every configured master
      * at startup. */
     sentinelGenerateInitialMonitorEvents();
@@ -1392,6 +1409,10 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         unsigned long long current_epoch = strtoull(argv[1],NULL,10);
         if (current_epoch > sentinel.current_epoch)
             sentinel.current_epoch = current_epoch;
+    } else if (!strcasecmp(argv[0],"myid") && argc == 2) {
+        if (strlen(argv[1]) != REDIS_RUN_ID_SIZE)
+            return "Malformed Sentinel id in myid option.";
+        memcpy(sentinel.myid,argv[1],REDIS_RUN_ID_SIZE);
     } else if (!strcasecmp(argv[0],"config-epoch") && argc == 3) {
         /* config-epoch <name> <epoch> */
         ri = sentinelGetMasterByName(argv[1]);
@@ -1460,6 +1481,10 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
         sentinelRedisInstance *master, *ri;
         sentinelAddr *master_addr;
 
+        /* sentinel unique ID. */
+        line = sdscatprintf(sdsempty(), "sentinel myid %s", sentinel.myid);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+
         /* sentinel monitor */
         master = dictGetVal(de);
         master_addr = sentinelGetCurrentMasterAddress(master);
@@ -1691,7 +1716,7 @@ void sentinelSendAuthIfNeeded(sentinelRedisInstance *ri, redisAsyncContext *c) {
 void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
     char name[64];
 
-    snprintf(name,sizeof(name),"sentinel-%.8s-%s",server.runid,type);
+    snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
     if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL,
         "CLIENT SETNAME %s", name) == REDIS_OK)
     {
@@ -2225,7 +2250,7 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
         strcmp(r->element[0]->str,"message") != 0) return;
 
     /* We are not interested in meeting ourselves */
-    if (strstr(r->element[2]->str,server.runid) != NULL) return;
+    if (strstr(r->element[2]->str,sentinel.myid) != NULL) return;
 
     sentinelProcessHelloMessage(r->element[2]->str, r->element[2]->len);
 }
@@ -2268,7 +2293,7 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     snprintf(payload,sizeof(payload),
         "%s,%d,%s,%llu," /* Info about this sentinel. */
         "%s,%s,%d,%llu", /* Info about current master. */
-        announce_ip, announce_port, server.runid,
+        announce_ip, announce_port, sentinel.myid,
         (unsigned long long) sentinel.current_epoch,
         /* --- */
         master->name,master_addr->ip,master_addr->port,
@@ -3233,7 +3258,7 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
                     master->addr->ip, port,
                     sentinel.current_epoch,
                     (master->failover_state > SENTINEL_FAILOVER_STATE_NONE) ?
-                    server.runid : "*");
+                    sentinel.myid : "*");
         if (retval == REDIS_OK) ri->pending_commands++;
     }
     dictReleaseIterator(di);
@@ -3265,7 +3290,7 @@ char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char
         /* If we did not voted for ourselves, set the master failover start
          * time to now, in order to force a delay before we can start a
          * failover for the same master. */
-        if (strcasecmp(master->leader,server.runid))
+        if (strcasecmp(master->leader,sentinel.myid))
             master->failover_start_time = mstime()+rand()%SENTINEL_MAX_DESYNC;
     }
 
@@ -3346,7 +3371,7 @@ char *sentinelGetLeader(sentinelRedisInstance *master, uint64_t epoch) {
     if (winner)
         myvote = sentinelVoteLeader(master,epoch,winner,&leader_epoch);
     else
-        myvote = sentinelVoteLeader(master,epoch,server.runid,&leader_epoch);
+        myvote = sentinelVoteLeader(master,epoch,sentinel.myid,&leader_epoch);
 
     if (myvote && leader_epoch == epoch) {
         uint64_t votes = sentinelLeaderIncr(counters,myvote);
@@ -3598,7 +3623,7 @@ void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
 
     /* Check if we are the leader for the failover epoch. */
     leader = sentinelGetLeader(ri, ri->failover_epoch);
-    isleader = leader && strcasecmp(leader,server.runid) == 0;
+    isleader = leader && strcasecmp(leader,sentinel.myid) == 0;
     sdsfree(leader);
 
     /* If I'm not the leader, and it is not a forced failover via