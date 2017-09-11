@@ -331,7 +331,7 @@ static int redisAeAttach(aeEventLoop *loop, redisAsyncContext *ac) {
 
     /* Nothing should be attached when something is already attached */
     if (ac->ev.data != NULL)
-        return REDIS_ERR;
+        return C_ERR;
 
     /* Create container for context and r/w events */
     e = (redisAeEvents*)zmalloc(sizeof(*e));
@@ -348,7 +348,7 @@ static int redisAeAttach(aeEventLoop *loop, redisAsyncContext *ac) {
     ac->ev.cleanup = redisAeCleanup;
     ac->ev.data = e;
 
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* ============================= Prototypes ================================= */
@@ -1012,16 +1012,16 @@ instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
  * a single connection, will send a single PING per second for failure
  * detection and so forth.
  *
- * Return REDIS_OK if a matching Sentinel was found in the context of a
- * different master and sharing was performed. Otherwise REDIS_ERR
+ * Return C_OK if a matching Sentinel was found in the context of a
+ * different master and sharing was performed. Otherwise C_ERR
  * is returned. */
 int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
     serverAssert(ri->flags & SRI_SENTINEL);
     dictIterator *di;
     dictEntry *de;
 
-    if (ri->runid == NULL) return REDIS_ERR; /* No way to identify it. */
-    if (ri->link->refcount > 1) return REDIS_ERR; /* Already shared. */
+    if (ri->runid == NULL) return C_ERR; /* No way to identify it. */
+    if (ri->link->refcount > 1) return C_ERR; /* Already shared. */
 
     di = dictGetIterator(sentinel.masters);
     while((de = dictNext(di)) != NULL) {
@@ -1039,10 +1039,10 @@ int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
         releaseInstanceLink(ri->link,NULL);
         ri->link = match->link;
         match->link->refcount++;
-        return REDIS_OK;
+        return C_OK;
     }
     dictReleaseIterator(di);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* When we detect a Sentinel to switch address (reporting a different IP/port
@@ -1103,7 +1103,7 @@ void instanceLinkConnectionError(const redisAsyncContext *c) {
 /* Hiredis connection established / disconnected callbacks. We need them
  * just to cleanup our link state. */
 void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
-    if (status != REDIS_OK) instanceLinkConnectionError(c);
+    if (status != C_OK) instanceLinkConnectionError(c);
 }
 
 void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
@@ -1447,8 +1447,8 @@ int sentinelResetMastersByPattern(char *pattern, int flags) {
  *
  * This is used to handle the +switch-master event.
  *
- * The function returns REDIS_ERR if the address can't be resolved for some
- * reason. Otherwise REDIS_OK is returned.  */
+ * The function returns C_ERR if the address can't be resolved for some
+ * reason. Otherwise C_OK is returned.  */
 int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip, int port) {
     sentinelAddr *oldaddr, *newaddr;
     sentinelAddr **slaves = NULL;
@@ -1457,7 +1457,7 @@ int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip,
     dictEntry *de;
 
     newaddr = createSentinelAddr(ip,port);
-    if (newaddr == NULL) return REDIS_ERR;
+    if (newaddr == NULL) return C_ERR;
 
     /* Make a list of slaves to add back after the reset.
      * Don't include the one having the address we are switching to. */
@@ -1503,7 +1503,7 @@ int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip,
      * gets the master->addr->ip and master->addr->port as arguments. */
     releaseSentinelAddr(oldaddr);
     sentinelFlushConfig();
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Return non-zero if there was no SDOWN or ODOWN error associated to this
@@ -1869,7 +1869,7 @@ void sentinelSendAuthIfNeeded(sentinelRedisInstance *ri, redisAsyncContext *c) {
 
     if (auth_pass) {
         if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri, "AUTH %s",
-            auth_pass) == REDIS_OK) ri->link->pending_commands++;
+            auth_pass) == C_OK) ri->link->pending_commands++;
     }
 }
 
@@ -1884,7 +1884,7 @@ void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char
 
     snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
     if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri,
-        "CLIENT SETNAME %s", name) == REDIS_OK)
+        "CLIENT SETNAME %s", name) == C_OK)
     {
         ri->link->pending_commands++;
     }
@@ -1946,7 +1946,7 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
             retval = redisAsyncCommand(link->pc,
                 sentinelReceiveHelloMessages, ri, "SUBSCRIBE %s",
                     SENTINEL_HELLO_CHANNEL);
-            if (retval != REDIS_OK) {
+            if (retval != C_OK) {
                 /* If we can't subscribe, the Pub/Sub connection is useless
                  * and we can simply disconnect it and try again. */
                 instanceLinkCloseConnection(link,link->pc);
@@ -2172,7 +2172,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
                 int retval = sentinelSendSlaveOf(ri,
                         ri->master->addr->ip,
                         ri->master->addr->port);
-                if (retval == REDIS_OK)
+                if (retval == C_OK)
                     sentinelEvent(REDIS_NOTICE,"+convert-to-slave",ri,"%@");
             }
         }
@@ -2195,7 +2195,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
             int retval = sentinelSendSlaveOf(ri,
                     ri->master->addr->ip,
                     ri->master->addr->port);
-            if (retval == REDIS_OK)
+            if (retval == C_OK)
                 sentinelEvent(REDIS_NOTICE,"+fix-slave-config",ri,"%@");
         }
     }
@@ -2279,7 +2279,7 @@ void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata
             {
                 if (redisAsyncCommand(ri->link->cc,
                         sentinelDiscardReplyCallback, ri,
-                        "SCRIPT KILL") == REDIS_OK)
+                        "SCRIPT KILL") == C_OK)
                     ri->link->pending_commands++;
                 ri->flags |= SRI_SCRIPT_KILL_SENT;
             }
@@ -2437,8 +2437,8 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
  * sentinel_ip,sentinel_port,sentinel_runid,current_epoch,
  * master_name,master_ip,master_port,master_config_epoch.
  *
- * Returns REDIS_OK if the PUBLISH was queued correctly, otherwise
- * REDIS_ERR is returned. */
+ * Returns C_OK if the PUBLISH was queued correctly, otherwise
+ * C_ERR is returned. */
 int sentinelSendHello(sentinelRedisInstance *ri) {
     char ip[REDIS_IP_STR_LEN];
     char payload[REDIS_IP_STR_LEN+1024];
@@ -2448,15 +2448,15 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
     sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
-    if (ri->link->disconnected) return REDIS_ERR;
+    if (ri->link->disconnected) return C_ERR;
 
     /* Use the specified announce address if specified, otherwise try to
      * obtain our own IP address. */
     if (sentinel.announce_ip) {
         announce_ip = sentinel.announce_ip;
     } else {
         if (anetSockName(ri->link->cc->c.fd,ip,sizeof(ip),NULL) == -1)
-            return REDIS_ERR;
+            return C_ERR;
         announce_ip = ip;
     }
     announce_port = sentinel.announce_port ?
@@ -2474,9 +2474,9 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     retval = redisAsyncCommand(ri->link->cc,
         sentinelPublishReplyCallback, ri, "PUBLISH %s %s",
             SENTINEL_HELLO_CHANNEL,payload);
-    if (retval != REDIS_OK) return REDIS_ERR;
+    if (retval != C_OK) return C_ERR;
     ri->link->pending_commands++;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Reset last_pub_time in all the instances in the specified dictionary
@@ -2503,12 +2503,12 @@ void sentinelForceHelloUpdateDictOfRedisInstances(dict *instances) {
  * Sentinel upgrades a configuration it is a good idea to deliever an update
  * to the other Sentinels ASAP. */
 int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master) {
-    if (!(master->flags & SRI_MASTER)) return REDIS_ERR;
+    if (!(master->flags & SRI_MASTER)) return C_ERR;
     if (master->last_pub_time >= (SENTINEL_PUBLISH_PERIOD+1))
         master->last_pub_time -= (SENTINEL_PUBLISH_PERIOD+1);
     sentinelForceHelloUpdateDictOfRedisInstances(master->sentinels);
     sentinelForceHelloUpdateDictOfRedisInstances(master->slaves);
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Send a PING to the specified instance and refresh the act_ping_time
@@ -2519,7 +2519,7 @@ int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master) {
 int sentinelSendPing(sentinelRedisInstance *ri) {
     int retval = redisAsyncCommand(ri->link->cc,
         sentinelPingReplyCallback, ri, "PING");
-    if (retval == REDIS_OK) {
+    if (retval == C_OK) {
         ri->link->pending_commands++;
         ri->link->last_ping_time = mstime();
         /* We update the active ping time only if we received the pong for
@@ -2577,7 +2577,7 @@ void sentinelSendPeriodicCommands(sentinelRedisInstance *ri) {
         /* Send INFO to masters and slaves, not sentinels. */
         retval = redisAsyncCommand(ri->link->cc,
             sentinelInfoReplyCallback, ri, "INFO");
-        if (retval == REDIS_OK) ri->link->pending_commands++;
+        if (retval == C_OK) ri->link->pending_commands++;
     } else if ((now - ri->link->last_pong_time) > ping_period &&
                (now - ri->link->last_ping_time) > ping_period/2) {
         /* Send PING to all the three kinds of instances. */
@@ -2905,9 +2905,9 @@ void sentinelCommand(client *c) {
         int isdown = 0;
 
         if (c->argc != 6) goto numargserr;
-        if (getLongFromObjectOrReply(c,c->argv[3],&port,NULL) != REDIS_OK ||
+        if (getLongFromObjectOrReply(c,c->argv[3],&port,NULL) != C_OK ||
             getLongLongFromObjectOrReply(c,c->argv[4],&req_epoch,NULL)
-                                                              != REDIS_OK)
+                                                              != C_OK)
             return;
         ri = getSentinelRedisInstanceByAddrAndRunID(sentinel.masters,
             c->argv[2]->ptr,port,NULL);
@@ -2985,9 +2985,9 @@ void sentinelCommand(client *c) {
 
         if (c->argc != 6) goto numargserr;
         if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
-            != REDIS_OK) return;
+            != C_OK) return;
         if (getLongFromObjectOrReply(c,c->argv[4],&port,"Invalid port")
-            != REDIS_OK) return;
+            != C_OK) return;
 
         if (quorum <= 0) {
             addReplyError(c, "Quorum must be 1 or greater.");
@@ -3267,20 +3267,20 @@ void sentinelSetCommand(client *c) {
 
         if (!strcasecmp(option,"down-after-milliseconds")) {
             /* down-after-millisecodns <milliseconds> */
-            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
+            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0)
                 goto badfmt;
             ri->down_after_period = ll;
             sentinelPropagateDownAfterPeriod(ri);
             changes++;
         } else if (!strcasecmp(option,"failover-timeout")) {
             /* failover-timeout <milliseconds> */
-            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
+            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0)
                 goto badfmt;
             ri->failover_timeout = ll;
             changes++;
        } else if (!strcasecmp(option,"parallel-syncs")) {
             /* parallel-syncs <milliseconds> */
-            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
+            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0)
                 goto badfmt;
             ri->parallel_syncs = ll;
             changes++;
@@ -3314,7 +3314,7 @@ void sentinelSetCommand(client *c) {
             changes++;
        } else if (!strcasecmp(option,"quorum")) {
             /* quorum <count> */
-            if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll <= 0)
+            if (getLongLongFromObject(o,&ll) == C_ERR || ll <= 0)
                 goto badfmt;
             ri->quorum = ll;
             changes++;
@@ -3543,7 +3543,7 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
                     sentinel.current_epoch,
                     (master->failover_state > SENTINEL_FAILOVER_STATE_NONE) ?
                     sentinel.myid : "*");
-        if (retval == REDIS_OK) ri->link->pending_commands++;
+        if (retval == C_OK) ri->link->pending_commands++;
     }
     dictReleaseIterator(di);
 }
@@ -3690,8 +3690,8 @@ char *sentinelGetLeader(sentinelRedisInstance *master, uint64_t epoch) {
  *
  * If Host is NULL the function sends "SLAVEOF NO ONE".
  *
- * The command returns REDIS_OK if the SLAVEOF command was accepted for
- * (later) delivery otherwise REDIS_ERR. The command replies are just
+ * The command returns C_OK if the SLAVEOF command was accepted for
+ * (later) delivery otherwise C_ERR. The command replies are just
  * discarded. */
 int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port) {
     char portstr[32];
@@ -3718,17 +3718,17 @@ int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port) {
      * will observe instead the effects in the next INFO output. */
     retval = redisAsyncCommand(ri->link->cc,
         sentinelDiscardReplyCallback, ri, "MULTI");
-    if (retval == REDIS_ERR) return retval;
+    if (retval == C_ERR) return retval;
     ri->link->pending_commands++;
 
     retval = redisAsyncCommand(ri->link->cc,
         sentinelDiscardReplyCallback, ri, "SLAVEOF %s %s", host, portstr);
-    if (retval == REDIS_ERR) return retval;
+    if (retval == C_ERR) return retval;
     ri->link->pending_commands++;
 
     retval = redisAsyncCommand(ri->link->cc,
         sentinelDiscardReplyCallback, ri, "CONFIG REWRITE");
-    if (retval == REDIS_ERR) return retval;
+    if (retval == C_ERR) return retval;
     ri->link->pending_commands++;
 
     /* CLIENT KILL TYPE <type> is only supported starting from Redis 2.8.12,
@@ -3738,15 +3738,15 @@ int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port) {
      * only the unsupported command will fail). */
     retval = redisAsyncCommand(ri->link->cc,
         sentinelDiscardReplyCallback, ri, "CLIENT KILL TYPE normal");
-    if (retval == REDIS_ERR) return retval;
+    if (retval == C_ERR) return retval;
     ri->link->pending_commands++;
 
     retval = redisAsyncCommand(ri->link->cc,
         sentinelDiscardReplyCallback, ri, "EXEC");
-    if (retval == REDIS_ERR) return retval;
+    if (retval == C_ERR) return retval;
     ri->link->pending_commands++;
 
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Setup the master state to start a failover. */
@@ -3980,7 +3980,7 @@ void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
      * really care about the reply. We check if it worked indirectly observing
      * if INFO returns a different role (master instead of slave). */
     retval = sentinelSendSlaveOf(ri->promoted_slave,NULL,0);
-    if (retval != REDIS_OK) return;
+    if (retval != C_OK) return;
     sentinelEvent(REDIS_NOTICE, "+failover-state-wait-promotion",
         ri->promoted_slave,"%@");
     ri->failover_state = SENTINEL_FAILOVER_STATE_WAIT_PROMOTION;
@@ -4052,7 +4052,7 @@ void sentinelFailoverDetectEnd(sentinelRedisInstance *master) {
             retval = sentinelSendSlaveOf(slave,
                     master->promoted_slave->addr->ip,
                     master->promoted_slave->addr->port);
-            if (retval == REDIS_OK) {
+            if (retval == C_OK) {
                 sentinelEvent(REDIS_NOTICE,"+slave-reconf-sent-be",slave,"%@");
                 slave->flags |= SRI_RECONF_SENT;
             }
@@ -4109,7 +4109,7 @@ void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
         retval = sentinelSendSlaveOf(slave,
                 master->promoted_slave->addr->ip,
                 master->promoted_slave->addr->port);
-        if (retval == REDIS_OK) {
+        if (retval == C_OK) {
             slave->flags |= SRI_RECONF_SENT;
             slave->slave_reconf_sent_time = mstime();
             sentinelEvent(REDIS_NOTICE,"+slave-reconf-sent",slave,"%@");