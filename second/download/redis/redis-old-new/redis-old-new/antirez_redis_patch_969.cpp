@@ -327,6 +327,7 @@ void sentinelDiscardReplyCallback(redisAsyncContext *c, void *reply, void *privd
 int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port);
 char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch);
 void sentinelFlushConfig(void);
+void sentinelGenerateInitialMonitorEvents(void);
 
 /* ========================= Dictionary types =============================== */
 
@@ -427,6 +428,10 @@ void sentinelIsRunning(void) {
             server.configfile,strerror(errno));
         exit(1);
     }
+
+    /* We want to generate a +monitor event for every configured master
+     * at startup. */
+    sentinelGenerateInitialMonitorEvents();
 }
 
 /* ============================== sentinelAddr ============================== */
@@ -558,6 +563,22 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
     }
 }
 
+/* This function is called only at startup and is used to generate a
+ * +monitor event for every configured master. The same events are also
+ * generated when a master to monitor is added at runtime via the
+ * SENTINEL MONITOR command. */
+void sentinelGenerateInitialMonitorEvents(void) {
+    dictIterator *di;
+    dictEntry *de;
+
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *ri = dictGetVal(de);
+        sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@");
+    }
+    dictReleaseIterator(di);
+}
+
 /* ============================ script execution ============================ */
 
 /* Release a script job structure and all the associated data. */