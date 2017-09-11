@@ -110,6 +110,10 @@ typedef struct sentinelAddr {
 #define SENTINEL_MASTER_LINK_STATUS_UP 0
 #define SENTINEL_MASTER_LINK_STATUS_DOWN 1
 
+/* Generic flags that can be used with different functions. */
+#define SENTINEL_NO_FLAGS 0
+#define SENTINEL_GENERATE_EVENT 1
+
 typedef struct sentinelRedisInstance {
     int flags;      /* See SRI_... defines */
     char *name;     /* Master name from the point of view of this sentinel. */
@@ -284,6 +288,7 @@ char *sentinelGetSubjectiveLeader(sentinelRedisInstance *master);
 char *sentinelGetObjectiveLeader(sentinelRedisInstance *master);
 int yesnotoi(char *s);
 void sentinelDisconnectInstanceFromContext(const redisAsyncContext *c);
+void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c);
 const char *sentinelRedisInstanceTypeStr(sentinelRedisInstance *ri);
 
 /* ========================= Dictionary types =============================== */
@@ -595,18 +600,9 @@ void releaseSentinelRedisInstance(sentinelRedisInstance *ri) {
     dictRelease(ri->sentinels);
     dictRelease(ri->slaves);
 
-    /* Release hiredis connections. Note that redisAsyncFree() will call
-     * the disconnection callback. */
-    if (ri->cc) {
-        ri->cc->data = NULL;
-        redisAsyncFree(ri->cc);
-        ri->cc = NULL;
-    }
-    if (ri->pc) {
-        ri->pc->data = NULL;
-        redisAsyncFree(ri->pc);
-        ri->pc = NULL;
-    }
+    /* Release hiredis connections. */
+    if (ri->cc) sentinelKillLink(ri,ri->cc);
+    if (ri->pc) sentinelKillLink(ri,ri->pc);
 
     /* Free other resources. */
     sdsfree(ri->name);
@@ -761,14 +757,14 @@ void sentinelDelFlagsToDictOfRedisInstances(dict *instances, int flags) {
  * 5) In the process of doing this undo the failover if in progress.
  * 6) Disconnect the connections with the master (will reconnect automatically).
  */
-void sentinelResetMaster(sentinelRedisInstance *ri) {
+void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
     redisAssert(ri->flags & SRI_MASTER);
     dictRelease(ri->slaves);
     dictRelease(ri->sentinels);
     ri->slaves = dictCreate(&instancesDictType,NULL);
     ri->sentinels = dictCreate(&instancesDictType,NULL);
-    if (ri->cc) redisAsyncFree(ri->cc);
-    if (ri->pc) redisAsyncFree(ri->pc);
+    if (ri->cc) sentinelKillLink(ri,ri->cc);
+    if (ri->pc) sentinelKillLink(ri,ri->pc);
     ri->flags &= SRI_MASTER|SRI_CAN_FAILOVER|SRI_DISCONNECTED;
     if (ri->leader) {
         sdsfree(ri->leader);
@@ -778,12 +774,17 @@ void sentinelResetMaster(sentinelRedisInstance *ri) {
     ri->failover_state_change_time = 0;
     ri->failover_start_time = 0;
     ri->promoted_slave = NULL;
-    sentinelEvent(REDIS_WARNING,"+reset-master",ri,"%@");
+    sdsfree(ri->runid);
+    sdsfree(ri->slave_master_host);
+    ri->runid = NULL;
+    ri->slave_master_host = NULL;
+    if (flags & SENTINEL_GENERATE_EVENT)
+        sentinelEvent(REDIS_WARNING,"+reset-master",ri,"%@");
 }
 
 /* Call sentinelResetMaster() on every master with a name matching the specified
  * pattern. */
-int sentinelResetMastersByPattern(char *pattern) {
+int sentinelResetMastersByPattern(char *pattern, int flags) {
     dictIterator *di;
     dictEntry *de;
     int reset = 0;
@@ -794,7 +795,7 @@ int sentinelResetMastersByPattern(char *pattern) {
 
         if (ri->name) {
             if (stringmatch(pattern,ri->name,0)) {
-                sentinelResetMaster(ri);
+                sentinelResetMaster(ri,flags);
                 reset++;
             }
         }
@@ -803,6 +804,32 @@ int sentinelResetMastersByPattern(char *pattern) {
     return reset;
 }
 
+/* Reset the specified master with sentinelResetMaster(), and also change
+ * the ip:port address, but take the name of the instance unmodified.
+ *
+ * This is used to handle the +switch-master and +redirect-to-master events.
+ *
+ * The function returns REDIS_ERR if the address can't be resolved for some
+ * reason. Otherwise REDIS_OK is returned.
+ *
+ * TODO: make this reset so that original sentinels are re-added with
+ * same ip / port / runid.
+ */
+
+int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip, int port) {
+    sentinelAddr *oldaddr, *newaddr;
+
+    newaddr = createSentinelAddr(ip,port);
+    if (newaddr == NULL) return REDIS_ERR;
+    sentinelResetMaster(master,SENTINEL_NO_FLAGS);
+    oldaddr = master->addr;
+    master->addr = newaddr;
+    /* Release the old address at the end so we are safe even if the function
+     * gets the master->addr->ip and master->addr->port as arguments. */
+    releaseSentinelAddr(oldaddr);
+    return REDIS_OK;
+}
+
 /* ============================ Config handling ============================= */
 char *sentinelHandleConfiguration(char **argv, int argc) {
     sentinelRedisInstance *ri;
@@ -859,6 +886,15 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
 
 /* ====================== hiredis connection handling ======================= */
 
+/* Completely disconnect an hiredis link from an instance. */
+void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c) {
+    if (ri->cc == c) ri->cc = NULL;
+    if (ri->pc == c) ri->pc = NULL;
+    c->data = NULL;
+    ri->flags |= SRI_DISCONNECTED;
+    redisAsyncFree(c);
+}
+
 /* This function takes an hiredis context that is in an error condition
  * and make sure to mark the instance as disconnected performing the
  * cleanup needed.
@@ -894,6 +930,7 @@ void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
 }
 
 void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
+    printf("DISCONNECT CALLBACK CALLED: %p (%p)\n", (void*)c, (void*)c->data);
     sentinelDisconnectInstanceFromContext(c);
 }
 
@@ -909,8 +946,7 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
         if (ri->cc->err) {
             sentinelEvent(REDIS_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
                 ri->cc->errstr);
-            redisAsyncFree(ri->cc);
-            ri->cc = NULL;
+            sentinelKillLink(ri,ri->cc);
         } else {
             ri->cc_conn_time = mstime();
             ri->cc->data = ri;
@@ -927,8 +963,7 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
         if (ri->pc->err) {
             sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
                 ri->pc->errstr);
-            redisAsyncFree(ri->pc);
-            ri->pc = NULL;
+            sentinelKillLink(ri,ri->pc);
         } else {
             int retval;
 
@@ -946,8 +981,7 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
             if (retval != REDIS_OK) {
                 /* If we can't subscribe, the Pub/Sub connection is useless
                  * and we can simply disconnect it and try again. */
-                redisAsyncFree(ri->pc);
-                ri->pc = NULL;
+                sentinelKillLink(ri,ri->pc);
                 return;
             }
         }
@@ -1056,19 +1090,35 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
 
     if (sentinel.tilt) return;
 
+    /* Act if a master turned into a slave. */
+    if ((ri->flags & SRI_MASTER) && role == SRI_SLAVE) {
+        if (first_runid && ri->slave_master_host) {
+            /* If it is the first time we receive INFO from it, but it's
+             * a slave while it was configured as a master, we want to monitor
+             * its master instead. */
+            sentinelEvent(REDIS_WARNING,"+redirect-to-master",ri,
+                "%s %s %d %s %d",
+                ri->name, ri->addr->ip, ri->addr->port,
+                ri->slave_master_host, ri->slave_master_port);
+            sentinelResetMasterAndChangeAddress(ri,ri->slave_master_host,
+                                                   ri->slave_master_port);
+            return;
+        }
+    }
+
     /* Act if a slave turned into a master. */
     if ((ri->flags & SRI_SLAVE) && role == SRI_MASTER) {
         if (!(ri->master->flags & SRI_FAILOVER_IN_PROGRESS) &&
             (runid_changed || first_runid))
         {
-            int retval;
-
             /* If a slave turned into a master, but at the same time the
              * runid has changed, or it is simply the first time we see and
              * INFO output from this instance, this is a reboot with a wrong
              * configuration.
              *
              * Log the event and remove the slave. */
+            int retval;
+
             sentinelEvent(REDIS_WARNING,"-slave-restart-as-master",ri,"%@ #removing it from the attached slaves");
             retval = dictDelete(ri->master->slaves,ri->name);
             redisAssert(retval == REDIS_OK);
@@ -1581,7 +1631,7 @@ void sentinelCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"reset")) {
         /* SENTINEL RESET <pattern> */
         if (c->argc != 3) goto numargserr;
-        addReplyLongLong(c,sentinelResetMastersByPattern(c->argv[2]->ptr));
+        addReplyLongLong(c,sentinelResetMastersByPattern(c->argv[2]->ptr,SENTINEL_GENERATE_EVENT));
     } else if (!strcasecmp(c->argv[1]->ptr,"get-master-addr-by-name")) {
         /* SENTINEL GET-MASTER-ADDR-BY-NAME <master-name> */
         sentinelRedisInstance *ri;
@@ -1626,7 +1676,7 @@ void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
         (mstime() - ri->cc_conn_time) > SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
         (mstime() - ri->last_pong_time) > (ri->down_after_period/2))
     {
-        redisAsyncFree(ri->cc); /* will call the disconnection callback */
+        sentinelKillLink(ri,ri->cc);
     }
 
     /* 2) Check if the pubsub link seems connected, was connected not less
@@ -1638,7 +1688,7 @@ void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
         (mstime() - ri->pc_conn_time) > SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
         (mstime() - ri->pc_last_activity) > (SENTINEL_PUBLISH_PERIOD*3))
     {
-        redisAsyncFree(ri->pc); /* will call the disconnection callback */
+        sentinelKillLink(ri,ri->pc);
     }
 
     /* Update the subjectively down flag. */
@@ -2246,30 +2296,14 @@ void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
  * and re-add it with the same address to trigger a complete state
  * refresh. */
 void sentinelFailoverSwitchToPromotedSlave(sentinelRedisInstance *master) {
-    sentinelRedisInstance *new, *ref = master->promoted_slave ?
-                                       master->promoted_slave : master;
-    int quorum = ref->quorum, parallel_syncs = ref->parallel_syncs;
-    char *name = sdsnew(master->name);
-    char *ip = sdsnew(ref->addr->ip), *oldip = sdsnew(master->addr->ip);
-    int port = ref->addr->port, oldport = master->addr->port;
-    int retval, oldflags = master->flags;
-    mstime_t old_down_after_period = master->down_after_period;
-    mstime_t old_failover_timeout = master->failover_timeout;
-
-    retval = dictDelete(sentinel.masters,master->name);
-    redisAssert(retval == DICT_OK);
-    new = createSentinelRedisInstance(name,SRI_MASTER,ip,port,quorum,NULL);
-    redisAssert(new != NULL);
-    new->parallel_syncs = parallel_syncs;
-    new->flags |= (oldflags & SRI_CAN_FAILOVER);
-    new->down_after_period = old_down_after_period;
-    new->failover_timeout = old_failover_timeout;
-    /* TODO: ... set the scripts as well. */
-    sentinelEvent(REDIS_WARNING,"+switch-master",new,"%s %s %d %s %d",
-        name, oldip, oldport, ip, port);
-    sdsfree(name);
-    sdsfree(ip);
-    sdsfree(oldip);
+    sentinelRedisInstance *ref = master->promoted_slave ?
+                                 master->promoted_slave : master;
+
+    sentinelEvent(REDIS_WARNING,"+switch-master",master,"%s %s %d %s %d",
+        master->name, master->addr->ip, master->addr->port,
+        ref->addr->ip, ref->addr->port);
+
+    sentinelResetMasterAndChangeAddress(master,ref->addr->ip,ref->addr->port);
 }
 
 void sentinelFailoverStateMachine(sentinelRedisInstance *ri) {