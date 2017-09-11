@@ -226,7 +226,7 @@ typedef struct sentinelRedisInstance {
 
 /* Main state. */
 struct sentinelState {
-    char myid[REDIS_RUN_ID_SIZE+1]; /* This sentinel ID. */
+    char myid[CONFIG_RUN_ID_SIZE+1]; /* This sentinel ID. */
     uint64_t current_epoch;         /* Current epoch. */
     dict *masters;      /* Dictionary of master sentinelRedisInstances.
                            Key is the instance name, value is the
@@ -384,7 +384,7 @@ int dictSdsKeyCompare(void *privdata, const void *key1, const void *key2);
 void releaseSentinelRedisInstance(sentinelRedisInstance *ri);
 
 void dictInstancesValDestructor (void *privdata, void *obj) {
-    REDIS_NOTUSED(privdata);
+    UNUSED(privdata);
     releaseSentinelRedisInstance(obj);
 }
 
@@ -477,11 +477,11 @@ void sentinelIsRunning(void) {
     int j;
 
     if (server.configfile == NULL) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Sentinel started without a config file. Exiting...");
         exit(1);
     } else if (access(server.configfile,W_OK) == -1) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Sentinel config file %s is not writable: %s. Exiting...",
             server.configfile,strerror(errno));
         exit(1);
@@ -490,17 +490,17 @@ void sentinelIsRunning(void) {
     /* If this Sentinel has yet no ID set in the configuration file, we
      * pick a random one and persist the config on disk. From now on this
      * will be this Sentinel ID across restarts. */
-    for (j = 0; j < REDIS_RUN_ID_SIZE; j++)
+    for (j = 0; j < CONFIG_RUN_ID_SIZE; j++)
         if (sentinel.myid[j] != 0) break;
 
-    if (j == REDIS_RUN_ID_SIZE) {
+    if (j == CONFIG_RUN_ID_SIZE) {
         /* Pick ID and presist the config. */
-        getRandomHexChars(sentinel.myid,REDIS_RUN_ID_SIZE);
+        getRandomHexChars(sentinel.myid,CONFIG_RUN_ID_SIZE);
         sentinelFlushConfig();
     }
 
     /* Log its ID to make debugging of issues simpler. */
-    serverLog(REDIS_WARNING,"Sentinel ID is %s", sentinel.myid);
+    serverLog(LL_WARNING,"Sentinel ID is %s", sentinel.myid);
 
     /* We want to generate a +monitor event for every configured master
      * at startup. */
@@ -515,7 +515,7 @@ void sentinelIsRunning(void) {
  *  EINVAL: Invalid port number.
  */
 sentinelAddr *createSentinelAddr(char *hostname, int port) {
-    char ip[REDIS_IP_STR_LEN];
+    char ip[NET_IP_STR_LEN];
     sentinelAddr *sa;
 
     if (port <= 0 || port > 65535) {
@@ -557,7 +557,7 @@ int sentinelAddrIsEqual(sentinelAddr *a, sentinelAddr *b) {
 
 /* Send an event to log, pub/sub, user notification script.
  *
- * 'level' is the log level for logging. Only REDIS_WARNING events will trigger
+ * 'level' is the log level for logging. Only LL_WARNING events will trigger
  * the execution of the user notification script.
  *
  * 'type' is the message type, also used as a pub/sub channel name.
@@ -582,7 +582,7 @@ int sentinelAddrIsEqual(sentinelAddr *a, sentinelAddr *b) {
 void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
                    const char *fmt, ...) {
     va_list ap;
-    char msg[REDIS_MAX_LOGMSG_LEN];
+    char msg[LOG_MAX_LEN];
     robj *channel, *payload;
 
     /* Handle %@ */
@@ -617,7 +617,7 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
         serverLog(level,"%s %s",type,msg);
 
     /* Publish the message via Pub/Sub if it's not a debugging one. */
-    if (level != REDIS_DEBUG) {
+    if (level != LL_DEBUG) {
         channel = createStringObject(type,strlen(type));
         payload = createStringObject(msg,strlen(msg));
         pubsubPublishMessage(channel,payload);
@@ -626,7 +626,7 @@ void sentinelEvent(int level, char *type, sentinelRedisInstance *ri,
     }
 
     /* Call the notification script if applicable. */
-    if (level == REDIS_WARNING && ri != NULL) {
+    if (level == LL_WARNING && ri != NULL) {
         sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ?
                                          ri : ri->master;
         if (master && master->notification_script) {
@@ -647,7 +647,7 @@ void sentinelGenerateInitialMonitorEvents(void) {
     di = dictGetIterator(sentinel.masters);
     while((de = dictNext(di)) != NULL) {
         sentinelRedisInstance *ri = dictGetVal(de);
-        sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
+        sentinelEvent(LL_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
     }
     dictReleaseIterator(di);
 }
@@ -757,7 +757,7 @@ void sentinelRunPendingScripts(void) {
             /* Parent (fork error).
              * We report fork errors as signal 99, in order to unify the
              * reporting with other kind of errors. */
-            sentinelEvent(REDIS_WARNING,"-script-error",NULL,
+            sentinelEvent(LL_WARNING,"-script-error",NULL,
                           "%s %d %d", sj->argv[0], 99, 0);
             sj->flags &= ~SENTINEL_SCRIPT_RUNNING;
             sj->pid = 0;
@@ -769,7 +769,7 @@ void sentinelRunPendingScripts(void) {
         } else {
             sentinel.running_scripts++;
             sj->pid = pid;
-            sentinelEvent(REDIS_DEBUG,"+script-child",NULL,"%ld",(long)pid);
+            sentinelEvent(LL_DEBUG,"+script-child",NULL,"%ld",(long)pid);
         }
     }
 }
@@ -803,12 +803,12 @@ void sentinelCollectTerminatedScripts(void) {
         sentinelScriptJob *sj;
 
         if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
-        sentinelEvent(REDIS_DEBUG,"-script-child",NULL,"%ld %d %d",
+        sentinelEvent(LL_DEBUG,"-script-child",NULL,"%ld %d %d",
             (long)pid, exitcode, bysignal);
 
         ln = sentinelGetScriptListNodeByPid(pid);
         if (ln == NULL) {
-            serverLog(REDIS_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
+            serverLog(LL_WARNING,"wait3() returned a pid (%ld) we can't find in our scripts execution queue!", (long)pid);
             continue;
         }
         sj = ln->value;
@@ -827,7 +827,7 @@ void sentinelCollectTerminatedScripts(void) {
             /* Otherwise let's remove the script, but log the event if the
              * execution did not terminated in the best of the ways. */
             if (bysignal || exitcode != 0) {
-                sentinelEvent(REDIS_WARNING,"-script-error",NULL,
+                sentinelEvent(LL_WARNING,"-script-error",NULL,
                               "%s %d %d", sj->argv[0], bysignal, exitcode);
             }
             listDelNode(sentinel.scripts_queue,ln);
@@ -851,7 +851,7 @@ void sentinelKillTimedoutScripts(void) {
         if (sj->flags & SENTINEL_SCRIPT_RUNNING &&
             (now - sj->start_time) > SENTINEL_SCRIPT_MAX_RUNTIME)
         {
-            sentinelEvent(REDIS_WARNING,"-script-timeout",NULL,"%s %ld",
+            sentinelEvent(LL_WARNING,"-script-timeout",NULL,"%s %ld",
                 sj->argv[0], (long)sj->pid);
             kill(sj->pid,SIGKILL);
         }
@@ -1075,7 +1075,7 @@ int sentinelUpdateSentinelAddressInAllMasters(sentinelRedisInstance *ri) {
     }
     dictReleaseIterator(di);
     if (reconfigured)
-        sentinelEvent(REDIS_NOTICE,"+sentinel-address-update", ri,
+        sentinelEvent(LL_NOTICE,"+sentinel-address-update", ri,
                     "%@ %d additional matching instances", reconfigured);
     return reconfigured;
 }
@@ -1107,7 +1107,7 @@ void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
 }
 
 void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
-    REDIS_NOTUSED(status);
+    UNUSED(status);
     instanceLinkConnectionError(c);
 }
 
@@ -1138,7 +1138,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     sentinelRedisInstance *ri;
     sentinelAddr *addr;
     dict *table = NULL;
-    char slavename[REDIS_PEER_ID_LEN], *sdsname;
+    char slavename[NET_PEER_ID_LEN], *sdsname;
 
     serverAssert(flags & (SRI_MASTER|SRI_SLAVE|SRI_SENTINEL));
     serverAssert((flags & SRI_MASTER) || master != NULL);
@@ -1260,7 +1260,7 @@ sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
 {
     sds key;
     sentinelRedisInstance *slave;
-    char buf[REDIS_PEER_ID_LEN];
+    char buf[NET_PEER_ID_LEN];
 
     serverAssert(ri->flags & SRI_MASTER);
     anetFormatAddr(buf,sizeof(buf),ip,port);
@@ -1417,7 +1417,7 @@ void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
     ri->role_reported_time = mstime();
     ri->role_reported = SRI_MASTER;
     if (flags & SENTINEL_GENERATE_EVENT)
-        sentinelEvent(REDIS_WARNING,"+reset-master",ri,"%@");
+        sentinelEvent(LL_WARNING,"+reset-master",ri,"%@");
 }
 
 /* Call sentinelResetMaster() on every master with a name matching the specified
@@ -1495,7 +1495,7 @@ int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip,
         slave = createSentinelRedisInstance(NULL,SRI_SLAVE,slaves[j]->ip,
                     slaves[j]->port, master->quorum, master);
         releaseSentinelAddr(slaves[j]);
-        if (slave) sentinelEvent(REDIS_NOTICE,"+slave",slave,"%@");
+        if (slave) sentinelEvent(LL_NOTICE,"+slave",slave,"%@");
     }
     zfree(slaves);
 
@@ -1624,9 +1624,9 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         if (current_epoch > sentinel.current_epoch)
             sentinel.current_epoch = current_epoch;
     } else if (!strcasecmp(argv[0],"myid") && argc == 2) {
-        if (strlen(argv[1]) != REDIS_RUN_ID_SIZE)
+        if (strlen(argv[1]) != CONFIG_RUN_ID_SIZE)
             return "Malformed Sentinel id in myid option.";
-        memcpy(sentinel.myid,argv[1],REDIS_RUN_ID_SIZE);
+        memcpy(sentinel.myid,argv[1],CONFIG_RUN_ID_SIZE);
     } else if (!strcasecmp(argv[0],"config-epoch") && argc == 3) {
         /* config-epoch <name> <epoch> */
         ri = sentinelGetMasterByName(argv[1]);
@@ -1852,7 +1852,7 @@ void sentinelFlushConfig(void) {
 
 werr:
     if (fd != -1) close(fd);
-    serverLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
+    serverLog(LL_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
 }
 
 /* ====================== hiredis connection handling ======================= */
@@ -1903,9 +1903,9 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
 
     /* Commands connection. */
     if (link->cc == NULL) {
-        link->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
+        link->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,NET_FIRST_BIND_ADDR);
         if (link->cc->err) {
-            sentinelEvent(REDIS_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
+            sentinelEvent(LL_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
                 link->cc->errstr);
             instanceLinkCloseConnection(link,link->cc);
         } else {
@@ -1925,9 +1925,9 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
     }
     /* Pub / Sub */
     if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && link->pc == NULL) {
-        link->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
+        link->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,NET_FIRST_BIND_ADDR);
         if (link->pc->err) {
-            sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
+            sentinelEvent(LL_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
                 link->pc->errstr);
             instanceLinkCloseConnection(link,link->pc);
         } else {
@@ -2001,7 +2001,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
                 ri->runid = sdsnewlen(l+7,40);
             } else {
                 if (strncmp(ri->runid,l+7,40) != 0) {
-                    sentinelEvent(REDIS_NOTICE,"+reboot",ri,"%@");
+                    sentinelEvent(LL_NOTICE,"+reboot",ri,"%@");
                     sdsfree(ri->runid);
                     ri->runid = sdsnewlen(l+7,40);
                 }
@@ -2042,7 +2042,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
                 if ((slave = createSentinelRedisInstance(NULL,SRI_SLAVE,ip,
                             atoi(port), ri->quorum, ri)) != NULL)
                 {
-                    sentinelEvent(REDIS_NOTICE,"+slave",slave,"%@");
+                    sentinelEvent(LL_NOTICE,"+slave",slave,"%@");
                     sentinelFlushConfig();
                 }
             }
@@ -2112,7 +2112,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
         if (role == SRI_SLAVE) ri->slave_conf_change_time = mstime();
         /* Log the event with +role-change if the new role is coherent or
          * with -role-change if there is a mismatch with the current config. */
-        sentinelEvent(REDIS_VERBOSE,
+        sentinelEvent(LL_VERBOSE,
             ((ri->flags & (SRI_MASTER|SRI_SLAVE)) == role) ?
             "+role-change" : "-role-change",
             ri, "%@ new reported role is %s",
@@ -2149,11 +2149,11 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
             ri->master->failover_state = SENTINEL_FAILOVER_STATE_RECONF_SLAVES;
             ri->master->failover_state_change_time = mstime();
             sentinelFlushConfig();
-            sentinelEvent(REDIS_WARNING,"+promoted-slave",ri,"%@");
+            sentinelEvent(LL_WARNING,"+promoted-slave",ri,"%@");
             if (sentinel.simfailure_flags &
                 SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION)
                 sentinelSimFailureCrash();
-            sentinelEvent(REDIS_WARNING,"+failover-state-reconf-slaves",
+            sentinelEvent(LL_WARNING,"+failover-state-reconf-slaves",
                 ri->master,"%@");
             sentinelCallClientReconfScript(ri->master,SENTINEL_LEADER,
                 "start",ri->master->addr,ri->addr);
@@ -2173,7 +2173,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
                         ri->master->addr->ip,
                         ri->master->addr->port);
                 if (retval == C_OK)
-                    sentinelEvent(REDIS_NOTICE,"+convert-to-slave",ri,"%@");
+                    sentinelEvent(LL_NOTICE,"+convert-to-slave",ri,"%@");
             }
         }
     }
@@ -2196,7 +2196,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
                     ri->master->addr->ip,
                     ri->master->addr->port);
             if (retval == C_OK)
-                sentinelEvent(REDIS_NOTICE,"+fix-slave-config",ri,"%@");
+                sentinelEvent(LL_NOTICE,"+fix-slave-config",ri,"%@");
         }
     }
 
@@ -2214,7 +2214,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
         {
             ri->flags &= ~SRI_RECONF_SENT;
             ri->flags |= SRI_RECONF_INPROG;
-            sentinelEvent(REDIS_NOTICE,"+slave-reconf-inprog",ri,"%@");
+            sentinelEvent(LL_NOTICE,"+slave-reconf-inprog",ri,"%@");
         }
 
         /* SRI_RECONF_INPROG -> SRI_RECONF_DONE */
@@ -2223,7 +2223,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
         {
             ri->flags &= ~SRI_RECONF_INPROG;
             ri->flags |= SRI_RECONF_DONE;
-            sentinelEvent(REDIS_NOTICE,"+slave-reconf-done",ri,"%@");
+            sentinelEvent(LL_NOTICE,"+slave-reconf-done",ri,"%@");
         }
     }
 }
@@ -2245,8 +2245,8 @@ void sentinelInfoReplyCallback(redisAsyncContext *c, void *reply, void *privdata
  * value of the command but its effects directly. */
 void sentinelDiscardReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
     instanceLink *link = c->data;
-    REDIS_NOTUSED(reply);
-    REDIS_NOTUSED(privdata);
+    UNUSED(reply);
+    UNUSED(privdata);
 
     if (link) link->pending_commands--;
 }
@@ -2338,15 +2338,15 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
              * with the new address back. */
             removed = removeMatchingSentinelFromMaster(master,token[2]);
             if (removed) {
-                sentinelEvent(REDIS_NOTICE,"+sentinel-address-switch",master,
+                sentinelEvent(LL_NOTICE,"+sentinel-address-switch",master,
                     "%@ ip %s port %d for %s", token[0],port,token[2]);
             }
 
             /* Add the new sentinel. */
             si = createSentinelRedisInstance(NULL,SRI_SENTINEL,
                             token[0],port,master->quorum,master);
             if (si) {
-                if (!removed) sentinelEvent(REDIS_NOTICE,"+sentinel",si,"%@");
+                if (!removed) sentinelEvent(LL_NOTICE,"+sentinel",si,"%@");
                 /* The runid is NULL after a new instance creation and
                  * for Sentinels we don't have a later chance to fill it,
                  * so do it now. */
@@ -2361,7 +2361,7 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
         if (current_epoch > sentinel.current_epoch) {
             sentinel.current_epoch = current_epoch;
             sentinelFlushConfig();
-            sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+            sentinelEvent(LL_WARNING,"+new-epoch",master,"%llu",
                 (unsigned long long) sentinel.current_epoch);
         }
 
@@ -2373,8 +2373,8 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
             {
                 sentinelAddr *old_addr;
 
-                sentinelEvent(REDIS_WARNING,"+config-update-from",si,"%@");
-                sentinelEvent(REDIS_WARNING,"+switch-master",
+                sentinelEvent(LL_WARNING,"+config-update-from",si,"%@");
+                sentinelEvent(LL_WARNING,"+switch-master",
                     master,"%s %s %d %s %d",
                     master->name,
                     master->addr->ip, master->addr->port,
@@ -2403,7 +2403,7 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
 void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = privdata;
     redisReply *r;
-    REDIS_NOTUSED(c);
+    UNUSED(c);
 
     if (!reply || !ri) return;
     r = reply;
@@ -2440,8 +2440,8 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
  * Returns C_OK if the PUBLISH was queued correctly, otherwise
  * C_ERR is returned. */
 int sentinelSendHello(sentinelRedisInstance *ri) {
-    char ip[REDIS_IP_STR_LEN];
-    char payload[REDIS_IP_STR_LEN+1024];
+    char ip[NET_IP_STR_LEN];
+    char payload[NET_IP_STR_LEN+1024];
     int retval;
     char *announce_ip;
     int announce_port;
@@ -2967,7 +2967,7 @@ void sentinelCommand(client *c) {
             addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
             return;
         }
-        serverLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
+        serverLog(LL_WARNING,"Executing user requested FAILOVER of '%s'",
             ri->name);
         sentinelStartFailover(ri);
         ri->flags |= SRI_FORCE_FAILOVER;
@@ -2981,7 +2981,7 @@ void sentinelCommand(client *c) {
         /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
         sentinelRedisInstance *ri;
         long quorum, port;
-        char ip[REDIS_IP_STR_LEN];
+        char ip[NET_IP_STR_LEN];
 
         if (c->argc != 6) goto numargserr;
         if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
@@ -3019,7 +3019,7 @@ void sentinelCommand(client *c) {
             }
         } else {
             sentinelFlushConfig();
-            sentinelEvent(REDIS_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
+            sentinelEvent(LL_WARNING,"+monitor",ri,"%@ quorum %d",ri->quorum);
             addReply(c,shared.ok);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"flushconfig")) {
@@ -3032,7 +3032,7 @@ void sentinelCommand(client *c) {
 
         if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
             == NULL) return;
-        sentinelEvent(REDIS_WARNING,"-monitor",ri,"%@");
+        sentinelEvent(LL_WARNING,"-monitor",ri,"%@");
         dictDelete(sentinel.masters,c->argv[2]->ptr);
         sentinelFlushConfig();
         addReply(c,shared.ok);
@@ -3136,13 +3136,13 @@ void sentinelCommand(client *c) {
             if (!strcasecmp(c->argv[j]->ptr,"crash-after-election")) {
                 sentinel.simfailure_flags |=
                     SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION;
-                serverLog(REDIS_WARNING,"Failure simulation: this Sentinel "
+                serverLog(LL_WARNING,"Failure simulation: this Sentinel "
                     "will crash after being successfully elected as failover "
                     "leader");
             } else if (!strcasecmp(c->argv[j]->ptr,"crash-after-promotion")) {
                 sentinel.simfailure_flags |=
                     SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
-                serverLog(REDIS_WARNING,"Failure simulation: this Sentinel "
+                serverLog(LL_WARNING,"Failure simulation: this Sentinel "
                     "will crash after promoting the selected slave to master");
             } else if (!strcasecmp(c->argv[j]->ptr,"help")) {
                 addReplyMultiBulkLen(c,2);
@@ -3324,7 +3324,7 @@ void sentinelSetCommand(client *c) {
             if (changes) sentinelFlushConfig();
             return;
         }
-        sentinelEvent(REDIS_WARNING,"+set",ri,"%@ %s %s",option,value);
+        sentinelEvent(LL_WARNING,"+set",ri,"%@ %s %s",option,value);
     }
 
     if (changes) sentinelFlushConfig();
@@ -3406,14 +3406,14 @@ void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
     {
         /* Is subjectively down */
         if ((ri->flags & SRI_S_DOWN) == 0) {
-            sentinelEvent(REDIS_WARNING,"+sdown",ri,"%@");
+            sentinelEvent(LL_WARNING,"+sdown",ri,"%@");
             ri->s_down_since_time = mstime();
             ri->flags |= SRI_S_DOWN;
         }
     } else {
         /* Is subjectively up */
         if (ri->flags & SRI_S_DOWN) {
-            sentinelEvent(REDIS_WARNING,"-sdown",ri,"%@");
+            sentinelEvent(LL_WARNING,"-sdown",ri,"%@");
             ri->flags &= ~(SRI_S_DOWN|SRI_SCRIPT_KILL_SENT);
         }
     }
@@ -3447,14 +3447,14 @@ void sentinelCheckObjectivelyDown(sentinelRedisInstance *master) {
     /* Set the flag accordingly to the outcome. */
     if (odown) {
         if ((master->flags & SRI_O_DOWN) == 0) {
-            sentinelEvent(REDIS_WARNING,"+odown",master,"%@ #quorum %d/%d",
+            sentinelEvent(LL_WARNING,"+odown",master,"%@ #quorum %d/%d",
                 quorum, master->quorum);
             master->flags |= SRI_O_DOWN;
             master->o_down_since_time = mstime();
         }
     } else {
         if (master->flags & SRI_O_DOWN) {
-            sentinelEvent(REDIS_WARNING,"-odown",master,"%@");
+            sentinelEvent(LL_WARNING,"-odown",master,"%@");
             master->flags &= ~SRI_O_DOWN;
         }
     }
@@ -3490,7 +3490,7 @@ void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *p
              * replied with a vote. */
             sdsfree(ri->leader);
             if ((long long)ri->leader_epoch != r->element[2]->integer)
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "%s voted for %s %llu", ri->name,
                     r->element[1]->str,
                     (unsigned long long) r->element[2]->integer);
@@ -3552,7 +3552,7 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
 
 /* Crash because of user request via SENTINEL simulate-failure command. */
 void sentinelSimFailureCrash(void) {
-    serverLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
         "Sentinel CRASH because of SENTINEL simulate-failure");
     exit(99);
 }
@@ -3566,7 +3566,7 @@ char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char
     if (req_epoch > sentinel.current_epoch) {
         sentinel.current_epoch = req_epoch;
         sentinelFlushConfig();
-        sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+        sentinelEvent(LL_WARNING,"+new-epoch",master,"%llu",
             (unsigned long long) sentinel.current_epoch);
     }
 
@@ -3576,7 +3576,7 @@ char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char
         master->leader = sdsnew(req_runid);
         master->leader_epoch = sentinel.current_epoch;
         sentinelFlushConfig();
-        sentinelEvent(REDIS_WARNING,"+vote-for-leader",master,"%s %llu",
+        sentinelEvent(LL_WARNING,"+vote-for-leader",master,"%s %llu",
             master->leader, (unsigned long long) master->leader_epoch);
         /* If we did not voted for ourselves, set the master failover start
          * time to now, in order to force a delay before we can start a
@@ -3756,9 +3756,9 @@ void sentinelStartFailover(sentinelRedisInstance *master) {
     master->failover_state = SENTINEL_FAILOVER_STATE_WAIT_START;
     master->flags |= SRI_FAILOVER_IN_PROGRESS;
     master->failover_epoch = ++sentinel.current_epoch;
-    sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+    sentinelEvent(LL_WARNING,"+new-epoch",master,"%llu",
         (unsigned long long) sentinel.current_epoch);
-    sentinelEvent(REDIS_WARNING,"+try-failover",master,"%@");
+    sentinelEvent(LL_WARNING,"+try-failover",master,"%@");
     master->failover_start_time = mstime()+rand()%SENTINEL_MAX_DESYNC;
     master->failover_state_change_time = mstime();
 }
@@ -3793,7 +3793,7 @@ int sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
             ctime_r(&clock,ctimebuf);
             ctimebuf[24] = '\0'; /* Remove newline. */
             master->failover_delay_logged = master->failover_start_time;
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Next failover delay: I will not start a failover before %s",
                 ctimebuf);
         }
@@ -3929,17 +3929,17 @@ void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
             election_timeout = ri->failover_timeout;
         /* Abort the failover if I'm not the leader after some time. */
         if (mstime() - ri->failover_start_time > election_timeout) {
-            sentinelEvent(REDIS_WARNING,"-failover-abort-not-elected",ri,"%@");
+            sentinelEvent(LL_WARNING,"-failover-abort-not-elected",ri,"%@");
             sentinelAbortFailover(ri);
         }
         return;
     }
-    sentinelEvent(REDIS_WARNING,"+elected-leader",ri,"%@");
+    sentinelEvent(LL_WARNING,"+elected-leader",ri,"%@");
     if (sentinel.simfailure_flags & SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION)
         sentinelSimFailureCrash();
     ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
     ri->failover_state_change_time = mstime();
-    sentinelEvent(REDIS_WARNING,"+failover-state-select-slave",ri,"%@");
+    sentinelEvent(LL_WARNING,"+failover-state-select-slave",ri,"%@");
 }
 
 void sentinelFailoverSelectSlave(sentinelRedisInstance *ri) {
@@ -3948,15 +3948,15 @@ void sentinelFailoverSelectSlave(sentinelRedisInstance *ri) {
     /* We don't handle the timeout in this state as the function aborts
      * the failover or go forward in the next state. */
     if (slave == NULL) {
-        sentinelEvent(REDIS_WARNING,"-failover-abort-no-good-slave",ri,"%@");
+        sentinelEvent(LL_WARNING,"-failover-abort-no-good-slave",ri,"%@");
         sentinelAbortFailover(ri);
     } else {
-        sentinelEvent(REDIS_WARNING,"+selected-slave",slave,"%@");
+        sentinelEvent(LL_WARNING,"+selected-slave",slave,"%@");
         slave->flags |= SRI_PROMOTED;
         ri->promoted_slave = slave;
         ri->failover_state = SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE;
         ri->failover_state_change_time = mstime();
-        sentinelEvent(REDIS_NOTICE,"+failover-state-send-slaveof-noone",
+        sentinelEvent(LL_NOTICE,"+failover-state-send-slaveof-noone",
             slave, "%@");
     }
 }
@@ -3969,7 +3969,7 @@ void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
      * is reached, then abort the failover. */
     if (ri->link->disconnected) {
         if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
-            sentinelEvent(REDIS_WARNING,"-failover-abort-slave-timeout",ri,"%@");
+            sentinelEvent(LL_WARNING,"-failover-abort-slave-timeout",ri,"%@");
             sentinelAbortFailover(ri);
         }
         return;
@@ -3981,7 +3981,7 @@ void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
      * if INFO returns a different role (master instead of slave). */
     retval = sentinelSendSlaveOf(ri->promoted_slave,NULL,0);
     if (retval != C_OK) return;
-    sentinelEvent(REDIS_NOTICE, "+failover-state-wait-promotion",
+    sentinelEvent(LL_NOTICE, "+failover-state-wait-promotion",
         ri->promoted_slave,"%@");
     ri->failover_state = SENTINEL_FAILOVER_STATE_WAIT_PROMOTION;
     ri->failover_state_change_time = mstime();
@@ -3993,7 +3993,7 @@ void sentinelFailoverWaitPromotion(sentinelRedisInstance *ri) {
     /* Just handle the timeout. Switching to the next state is handled
      * by the function parsing the INFO command of the promoted slave. */
     if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
-        sentinelEvent(REDIS_WARNING,"-failover-abort-slave-timeout",ri,"%@");
+        sentinelEvent(LL_WARNING,"-failover-abort-slave-timeout",ri,"%@");
         sentinelAbortFailover(ri);
     }
 }
@@ -4025,11 +4025,11 @@ void sentinelFailoverDetectEnd(sentinelRedisInstance *master) {
     if (elapsed > master->failover_timeout) {
         not_reconfigured = 0;
         timeout = 1;
-        sentinelEvent(REDIS_WARNING,"+failover-end-for-timeout",master,"%@");
+        sentinelEvent(LL_WARNING,"+failover-end-for-timeout",master,"%@");
     }
 
     if (not_reconfigured == 0) {
-        sentinelEvent(REDIS_WARNING,"+failover-end",master,"%@");
+        sentinelEvent(LL_WARNING,"+failover-end",master,"%@");
         master->failover_state = SENTINEL_FAILOVER_STATE_UPDATE_CONFIG;
         master->failover_state_change_time = mstime();
     }
@@ -4053,7 +4053,7 @@ void sentinelFailoverDetectEnd(sentinelRedisInstance *master) {
                     master->promoted_slave->addr->ip,
                     master->promoted_slave->addr->port);
             if (retval == C_OK) {
-                sentinelEvent(REDIS_NOTICE,"+slave-reconf-sent-be",slave,"%@");
+                sentinelEvent(LL_NOTICE,"+slave-reconf-sent-be",slave,"%@");
                 slave->flags |= SRI_RECONF_SENT;
             }
         }
@@ -4095,7 +4095,7 @@ void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
             (mstime() - slave->slave_reconf_sent_time) >
             SENTINEL_SLAVE_RECONF_TIMEOUT)
         {
-            sentinelEvent(REDIS_NOTICE,"-slave-reconf-sent-timeout",slave,"%@");
+            sentinelEvent(LL_NOTICE,"-slave-reconf-sent-timeout",slave,"%@");
             slave->flags &= ~SRI_RECONF_SENT;
             slave->flags |= SRI_RECONF_DONE;
         }
@@ -4112,7 +4112,7 @@ void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
         if (retval == C_OK) {
             slave->flags |= SRI_RECONF_SENT;
             slave->slave_reconf_sent_time = mstime();
-            sentinelEvent(REDIS_NOTICE,"+slave-reconf-sent",slave,"%@");
+            sentinelEvent(LL_NOTICE,"+slave-reconf-sent",slave,"%@");
             in_progress++;
         }
     }
@@ -4129,7 +4129,7 @@ void sentinelFailoverSwitchToPromotedSlave(sentinelRedisInstance *master) {
     sentinelRedisInstance *ref = master->promoted_slave ?
                                  master->promoted_slave : master;
 
-    sentinelEvent(REDIS_WARNING,"+switch-master",master,"%s %s %d %s %d",
+    sentinelEvent(LL_WARNING,"+switch-master",master,"%s %s %d %s %d",
         master->name, master->addr->ip, master->addr->port,
         ref->addr->ip, ref->addr->port);
 
@@ -4197,7 +4197,7 @@ void sentinelHandleRedisInstance(sentinelRedisInstance *ri) {
     if (sentinel.tilt) {
         if (mstime()-sentinel.tilt_start_time < SENTINEL_TILT_PERIOD) return;
         sentinel.tilt = 0;
-        sentinelEvent(REDIS_WARNING,"-tilt",NULL,"#tilt mode exited");
+        sentinelEvent(LL_WARNING,"-tilt",NULL,"#tilt mode exited");
     }
 
     /* Every kind of instance */
@@ -4270,7 +4270,7 @@ void sentinelCheckTiltCondition(void) {
     if (delta < 0 || delta > SENTINEL_TILT_TRIGGER) {
         sentinel.tilt = 1;
         sentinel.tilt_start_time = mstime();
-        sentinelEvent(REDIS_WARNING,"+tilt",NULL,"#tilt mode entered");
+        sentinelEvent(LL_WARNING,"+tilt",NULL,"#tilt mode entered");
     }
     sentinel.previous_time = mstime();
 }