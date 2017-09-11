@@ -477,11 +477,11 @@ void sentinelIsRunning(void) {
     int j;
 
     if (server.configfile == NULL) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Sentinel started without a config file. Exiting...");
         exit(1);
     } else if (access(server.configfile,W_OK) == -1) {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Sentinel config file %s is not writable: %s. Exiting...",
             server.configfile,strerror(errno));
         exit(1);
@@ -500,7 +500,7 @@ void sentinelIsRunning(void) {
     }
 
     /* Log its ID to make debugging of issues simpler. */
-    redisLog(REDIS_WARNING,"Sentinel ID is %s", sentinel.myid);
+    serverLog(REDIS_WARNING,"Sentinel ID is %s", sentinel.myid);
 
     /* We want to generate a +monitor event for every configured master
      * at startup. */
@@ -614,7 +614,7 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
 
     /* Log the message if the log level allows it to be logged. */
     if (level >= server.verbosity)
-        redisLog(level,"%s %s",type,msg);
+        serverLog(level,"%s %s",type,msg);
 
     /* Publish the message via Pub/Sub if it's not a debugging one. */
     if (level != REDIS_DEBUG) {
@@ -808,7 +808,7 @@ void sentinelCollectTerminatedScripts(void) {
 
         ln = sentinelGetScriptListNodeByPid(pid);
         if (ln == NULL) {
-            redisLog(REDIS_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
+            serverLog(REDIS_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
             continue;
         }
         sj = ln->value;
@@ -1852,7 +1852,7 @@ void sentinelFlushConfig(void) {
 
 werr:
     if (fd != -1) close(fd);
-    redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
+    serverLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
 }
 
 /* ====================== hiredis connection handling ======================= */
@@ -2967,7 +2967,7 @@ void sentinelCommand(redisClient *c) {
             addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
             return;
         }
-        redisLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
+        serverLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
             ri->name);
         sentinelStartFailover(ri);
         ri->flags |= SRI_FORCE_FAILOVER;
@@ -3136,13 +3136,13 @@ void sentinelCommand(redisClient *c) {
             if (!strcasecmp(c->argv[j]->ptr,"crash-after-election")) {
                 sentinel.simfailure_flags |=
                     SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION;
-                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
+                serverLog(REDIS_WARNING,"Failure simulation: this Sentinel "
                     "will crash after being successfully elected as failover "
                     "leader");
             } else if (!strcasecmp(c->argv[j]->ptr,"crash-after-promotion")) {
                 sentinel.simfailure_flags |=
                     SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
-                redisLog(REDIS_WARNING,"Failure simulation: this Sentinel "
+                serverLog(REDIS_WARNING,"Failure simulation: this Sentinel "
                     "will crash after promoting the selected slave to master");
             } else if (!strcasecmp(c->argv[j]->ptr,"help")) {
                 addReplyMultiBulkLen(c,2);
@@ -3490,7 +3490,7 @@ void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *p
              * replied with a vote. */
             sdsfree(ri->leader);
             if ((long long)ri->leader_epoch != r->element[2]->integer)
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "%s voted for %s %llu", ri->name,
                     r->element[1]->str,
                     (unsigned long long) r->element[2]->integer);
@@ -3552,7 +3552,7 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
 
 /* Crash because of user request via SENTINEL simulate-failure command. */
 void sentinelSimFailureCrash(void) {
-    redisLog(REDIS_WARNING,
+    serverLog(REDIS_WARNING,
         "Sentinel CRASH because of SENTINEL simulate-failure");
     exit(99);
 }
@@ -3793,7 +3793,7 @@ int sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
             ctime_r(&clock,ctimebuf);
             ctimebuf[24] = '\0'; /* Remove newline. */
             master->failover_delay_logged = master->failover_start_time;
-            redisLog(REDIS_WARNING,
+            serverLog(REDIS_WARNING,
                 "Next failover delay: I will not start a failover before %s",
                 ctimebuf);
         }