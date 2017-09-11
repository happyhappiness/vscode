@@ -493,7 +493,7 @@ int sentinelAddrIsEqual(sentinelAddr *a, sentinelAddr *b) {
 /* =========================== Events notification ========================== */
 
 /* Send an event to log, pub/sub, user notification script.
- * 
+ *
  * 'level' is the log level for logging. Only REDIS_WARNING events will trigger
  * the execution of the user notification script.
  *
@@ -616,7 +616,7 @@ void sentinelScheduleScriptExecution(char *path, ...) {
     }
     va_end(ap);
     argv[0] = sdsnew(path);
-    
+
     sj = zmalloc(sizeof(*sj));
     sj->flags = SENTINEL_SCRIPT_NONE;
     sj->retry_num = 0;
@@ -742,7 +742,7 @@ void sentinelCollectTerminatedScripts(void) {
         if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
         sentinelEvent(REDIS_DEBUG,"-script-child",NULL,"%ld %d %d",
             (long)pid, exitcode, bysignal);
-        
+
         ln = sentinelGetScriptListNodeByPid(pid);
         if (ln == NULL) {
             redisLog(REDIS_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
@@ -1020,7 +1020,7 @@ sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
 {
     sds key;
     sentinelRedisInstance *slave;
-  
+
     redisAssert(ri->flags & SRI_MASTER);
     key = sdscatprintf(sdsempty(),
         strchr(ip,':') ? "[%s]:%d" : "%s:%d",
@@ -1040,7 +1040,7 @@ const char *sentinelRedisInstanceTypeStr(sentinelRedisInstance *ri) {
 
 /* This function removes all the instances found in the dictionary of
  * sentinels in the specified 'master', having either:
- * 
+ *
  * 1) The same ip/port as specified.
  * 2) The same runid.
  *
@@ -1234,7 +1234,7 @@ int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip,
                                                  slave->addr->port);
     }
     dictReleaseIterator(di);
-    
+
     /* If we are switching to a different address, include the old address
      * as a slave as well, so that we'll be able to sense / reconfigure
      * the old master. */
@@ -1847,7 +1847,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
                     ri->slave_conf_change_time = mstime();
                 }
             }
-            
+
             /* master_link_status:<status> */
             if (sdslen(l) >= 19 && !memcmp(l,"master_link_status:",19)) {
                 ri->slave_master_link_status =
@@ -2168,7 +2168,7 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
      * receive our messages as well this timestamp can be used to detect
      * if the link is probably disconnected even if it seems otherwise. */
     ri->pc_last_activity = mstime();
-   
+
     /* Sanity check in the reply we expect, so that the code that follows
      * can avoid to check for details. */
     if (r->type != REDIS_REPLY_ARRAY ||
@@ -3241,7 +3241,7 @@ void sentinelStartFailover(sentinelRedisInstance *master) {
  * 1) Master must be in ODOWN condition.
  * 2) No failover already in progress.
  * 3) No failover already attempted recently.
- * 
+ *
  * We still don't know if we'll win the election so it is possible that we
  * start the failover but that we'll not be able to act.
  *