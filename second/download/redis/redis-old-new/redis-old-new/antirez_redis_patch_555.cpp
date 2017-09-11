@@ -54,19 +54,18 @@ typedef struct sentinelAddr {
 #define SRI_MASTER  (1<<0)
 #define SRI_SLAVE   (1<<1)
 #define SRI_SENTINEL (1<<2)
-#define SRI_DISCONNECTED (1<<3)
-#define SRI_S_DOWN (1<<4)   /* Subjectively down (no quorum). */
-#define SRI_O_DOWN (1<<5)   /* Objectively down (confirmed by others). */
-#define SRI_MASTER_DOWN (1<<6) /* A Sentinel with this flag set thinks that
+#define SRI_S_DOWN (1<<3)   /* Subjectively down (no quorum). */
+#define SRI_O_DOWN (1<<4)   /* Objectively down (confirmed by others). */
+#define SRI_MASTER_DOWN (1<<5) /* A Sentinel with this flag set thinks that
                                    its master is down. */
-#define SRI_FAILOVER_IN_PROGRESS (1<<7) /* Failover is in progress for
+#define SRI_FAILOVER_IN_PROGRESS (1<<6) /* Failover is in progress for
                                            this master. */
-#define SRI_PROMOTED (1<<8)            /* Slave selected for promotion. */
-#define SRI_RECONF_SENT (1<<9)     /* SLAVEOF <newmaster> sent. */
-#define SRI_RECONF_INPROG (1<<10)   /* Slave synchronization in progress. */
-#define SRI_RECONF_DONE (1<<11)     /* Slave synchronized with new master. */
-#define SRI_FORCE_FAILOVER (1<<12)  /* Force failover with master up. */
-#define SRI_SCRIPT_KILL_SENT (1<<13) /* SCRIPT KILL already sent on -BUSY */
+#define SRI_PROMOTED (1<<7)            /* Slave selected for promotion. */
+#define SRI_RECONF_SENT (1<<8)     /* SLAVEOF <newmaster> sent. */
+#define SRI_RECONF_INPROG (1<<9)   /* Slave synchronization in progress. */
+#define SRI_RECONF_DONE (1<<10)     /* Slave synchronized with new master. */
+#define SRI_FORCE_FAILOVER (1<<11)  /* Force failover with master up. */
+#define SRI_SCRIPT_KILL_SENT (1<<12) /* SCRIPT KILL already sent on -BUSY */
 
 /* Note: times are in milliseconds. */
 #define SENTINEL_INFO_PERIOD 10000
@@ -115,27 +114,54 @@ typedef struct sentinelAddr {
 #define SENTINEL_SCRIPT_MAX_RETRY 10
 #define SENTINEL_SCRIPT_RETRY_DELAY 30000 /* 30 seconds between retries. */
 
-typedef struct sentinelRedisInstance {
-    int flags;      /* See SRI_... defines */
-    char *name;     /* Master name from the point of view of this sentinel. */
-    char *runid;    /* run ID of this instance. */
-    uint64_t config_epoch;  /* Configuration epoch. */
-    sentinelAddr *addr; /* Master host. */
+/* The link to a sentinelRedisInstance. When we have the same set of Sentinels
+ * monitoring many masters, we have different instances representing the
+ * same Sentinels, one per master, and we need to share the hiredis connections
+ * among them. Oherwise if 5 Sentinels are monitoring 100 masters we create
+ * 500 outgoing connections instead of 5.
+ *
+ * So this structure represents a reference counted link in terms of the two
+ * hiredis connections for commands and Pub/Sub, and the fields needed for
+ * failure detection, since the ping/pong time are now local to the link: if
+ * the link is available, the instance is avaialbe. This way we don't just
+ * have 5 connections instead of 500, we also send 5 pings instead of 500.
+ *
+ * Links are shared only for Sentinels: master and slave instances have
+ * a link with refcount = 1, always. */
+typedef struct instanceLink {
+    int refcount;          /* Number of sentinelRedisInstance owners. */
+    int disconnected;      /* Non-zero if we need to reconnect cc or pc. */
+    int pending_commands;  /* Number of commands sent waiting for a reply. */
     redisAsyncContext *cc; /* Hiredis context for commands. */
     redisAsyncContext *pc; /* Hiredis context for Pub / Sub. */
-    int pending_commands;   /* Number of commands sent waiting for a reply. */
     mstime_t cc_conn_time; /* cc connection time. */
     mstime_t pc_conn_time; /* pc connection time. */
     mstime_t pc_last_activity; /* Last time we received any message. */
     mstime_t last_avail_time; /* Last time the instance replied to ping with
                                  a reply we consider valid. */
-    mstime_t last_ping_time;  /* Last time a pending ping was sent in the
-                                 context of the current command connection
-                                 with the instance. 0 if still not sent or
-                                 if pong already received. */
+    mstime_t act_ping_time;   /* Time at which the last pending ping (no pong
+                                 received after it) was sent. This field is
+                                 set to 0 when a pong is received, and set again
+                                 to the current time if the value is 0 and a new
+                                 ping is sent. */
+    mstime_t last_ping_time;  /* Time at which we sent the last ping. This is
+                                 only used to avoid sending too many pings
+                                 during failure. Idle time is computed using
+                                 the act_ping_time field. */
     mstime_t last_pong_time;  /* Last time the instance replied to ping,
                                  whatever the reply was. That's used to check
                                  if the link is idle and must be reconnected. */
+    mstime_t last_reconn_time;  /* Last reconnection attempt performed when
+                                   the link was down. */
+} instanceLink;
+
+typedef struct sentinelRedisInstance {
+    int flags;      /* See SRI_... defines */
+    char *name;     /* Master name from the point of view of this sentinel. */
+    char *runid;    /* Run ID of this instance, or unique ID if is a Sentinel.*/
+    uint64_t config_epoch;  /* Configuration epoch. */
+    sentinelAddr *addr; /* Master host. */
+    instanceLink *link; /* Link to the instance, may be shared for Sentinels. */
     mstime_t last_pub_time;   /* Last time we sent hello via Pub/Sub. */
     mstime_t last_hello_time; /* Only used if SRI_SENTINEL is set. Last time
                                  we received a hello from this Sentinel
@@ -195,19 +221,20 @@ typedef struct sentinelRedisInstance {
 
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
@@ -327,8 +354,7 @@ sentinelRedisInstance *sentinelGetMasterByName(char *name);
 char *sentinelGetSubjectiveLeader(sentinelRedisInstance *master);
 char *sentinelGetObjectiveLeader(sentinelRedisInstance *master);
 int yesnotoi(char *s);
-void sentinelDisconnectInstanceFromContext(const redisAsyncContext *c);
-void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c);
+void instanceLinkConnectionError(const redisAsyncContext *c);
 const char *sentinelRedisInstanceTypeStr(sentinelRedisInstance *ri);
 void sentinelAbortFailover(sentinelRedisInstance *ri);
 void sentinelEvent(int level, char *type, sentinelRedisInstance *ri, const char *fmt, ...);
@@ -342,6 +368,7 @@ void sentinelFlushConfig(void);
 void sentinelGenerateInitialMonitorEvents(void);
 int sentinelSendPing(sentinelRedisInstance *ri);
 int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master);
+sentinelRedisInstance *getSentinelRedisInstanceByAddrAndRunID(dict *instances, char *ip, int port, char *runid);
 
 /* ========================= Dictionary types =============================== */
 
@@ -433,12 +460,13 @@ void initSentinel(void) {
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
@@ -451,6 +479,21 @@ void sentinelIsRunning(void) {
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
@@ -872,6 +915,193 @@ void sentinelCallClientReconfScript(sentinelRedisInstance *master, int role, cha
         state, from->ip, fromport, to->ip, toport, NULL);
 }
 
+/* =============================== instanceLink ============================= */
+
+/* Create a not yet connected link object. */
+instanceLink *createInstanceLink(void) {
+    instanceLink *link = zmalloc(sizeof(*link));
+
+    link->refcount = 1;
+    link->disconnected = 1;
+    link->pending_commands = 0;
+    link->cc = NULL;
+    link->pc = NULL;
+    link->cc_conn_time = 0;
+    link->pc_conn_time = 0;
+    link->last_reconn_time = 0;
+    link->pc_last_activity = 0;
+    /* We set the act_ping_time to "now" even if we actually don't have yet
+     * a connection with the node, nor we sent a ping.
+     * This is useful to detect a timeout in case we'll not be able to connect
+     * with the node at all. */
+    link->act_ping_time = mstime();
+    link->last_ping_time = 0;
+    link->last_avail_time = mstime();
+    link->last_pong_time = mstime();
+    return link;
+}
+
+/* Disconnect an hiredis connection in the context of an instance link. */
+void instanceLinkCloseConnection(instanceLink *link, redisAsyncContext *c) {
+    if (c == NULL) return;
+
+    if (link->cc == c) {
+        link->cc = NULL;
+        link->pending_commands = 0;
+    }
+    if (link->pc == c) link->pc = NULL;
+    c->data = NULL;
+    link->disconnected = 1;
+    redisAsyncFree(c);
+}
+
+/* Decrement the refcount of a link object, if it drops to zero, actually
+ * free it and return NULL. Otherwise don't do anything and return the pointer
+ * to the object.
+ *
+ * If we are not going to free the link and ri is not NULL, we rebind all the
+ * pending requests in link->cc (hiredis connection for commands) to a
+ * callback that will just ignore them. This is useful to avoid processing
+ * replies for an instance that no longer exists. */
+instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
+{
+    redisAssert(link->refcount > 0);
+    link->refcount--;
+    if (link->refcount != 0) {
+        if (ri && ri->link->cc) {
+            /* This instance may have pending callbacks in the hiredis async
+             * context, having as 'privdata' the instance that we are going to
+             * free. Let's rewrite the callback list, directly exploiting
+             * hiredis internal data structures, in order to bind them with
+             * a callback that will ignore the reply at all. */
+            redisCallback *cb;
+            redisCallbackList *callbacks = &link->cc->replies;
+
+            cb = callbacks->head;
+            while(cb) {
+                if (cb->privdata == ri) {
+                    cb->fn = sentinelDiscardReplyCallback;
+                    cb->privdata = NULL; /* Not strictly needed. */
+                }
+                cb = cb->next;
+            }
+        }
+        return link; /* Other active users. */
+    }
+
+    instanceLinkCloseConnection(link,link->cc);
+    instanceLinkCloseConnection(link,link->pc);
+    zfree(link);
+    return NULL;
+}
+
+/* This function will attempt to share the instance link we already have
+ * for the same Sentinel in the context of a different master, with the
+ * instance we are passing as argument.
+ *
+ * This way multiple Sentinel objects that refer all to the same physical
+ * Sentinel instance but in the context of different masters will use
+ * a single connection, will send a single PING per second for failure
+ * detection and so forth.
+ *
+ * Return REDIS_OK if a matching Sentinel was found in the context of a
+ * different master and sharing was performed. Otherwise REDIS_ERR
+ * is returned. */
+int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
+    redisAssert(ri->flags & SRI_SENTINEL);
+    dictIterator *di;
+    dictEntry *de;
+
+    if (ri->runid == NULL) return REDIS_ERR; /* No way to identify it. */
+    if (ri->link->refcount > 1) return REDIS_ERR; /* Already shared. */
+
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *master = dictGetVal(de), *match;
+        /* We want to share with the same physical Sentinel referenced
+         * in other masters, so skip our master. */
+        if (master == ri->master) continue;
+        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
+                                                       NULL,0,ri->runid);
+        if (match == ri) continue; /* Should never happen but... safer. */
+
+        /* We identified a matching Sentinel, great! Let's free our link
+         * and use the one of the matching Sentinel. */
+        releaseInstanceLink(ri->link,NULL);
+        ri->link = match->link;
+        match->link->refcount++;
+        return REDIS_OK;
+    }
+    dictReleaseIterator(di);
+    return REDIS_ERR;
+}
+
+/* When we detect a Sentinel to switch address (reporting a different IP/port
+ * pair in Hello messages), let's update all the matching Sentinels in the
+ * context of other masters as well and disconnect the links, so that everybody
+ * will be updated.
+ *
+ * Return the number of updated Sentinel addresses. */
+int sentinelUpdateSentinelAddressInAllMasters(sentinelRedisInstance *ri) {
+    redisAssert(ri->flags & SRI_SENTINEL);
+    dictIterator *di;
+    dictEntry *de;
+    int reconfigured = 0;
+
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *master = dictGetVal(de), *match;
+        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
+                                                       NULL,0,ri->runid);
+        if (match->link->disconnected == 0) {
+            instanceLinkCloseConnection(match->link,match->link->cc);
+            instanceLinkCloseConnection(match->link,match->link->pc);
+        }
+        if (match == ri) continue; /* Address already updated for it. */
+        /* Update the address of the matching Sentinel by copying the address
+         * of the Sentinel object that received the address update. */
+        releaseSentinelAddr(match->addr);
+        match->addr = dupSentinelAddr(ri->addr);
+        reconfigured++;
+    }
+    dictReleaseIterator(di);
+    if (reconfigured)
+        sentinelEvent(REDIS_NOTICE,"+sentinel-address-update", ri,
+                    "%@ %d additional matching instances", reconfigured);
+    return reconfigured;
+}
+
+/* This function is called when an hiredis connection reported an error.
+ * We set it to NULL and mark the link as disconnected so that it will be
+ * reconnected again.
+ *
+ * Note: we don't free the hiredis context as hiredis will do it for us
+ * for async connections. */
+void instanceLinkConnectionError(const redisAsyncContext *c) {
+    instanceLink *link = c->data;
+    int pubsub;
+
+    if (!link) return;
+
+    pubsub = (link->pc == c);
+    if (pubsub)
+        link->pc = NULL;
+    else
+        link->cc = NULL;
+    link->disconnected = 1;
+}
+
+/* Hiredis connection established / disconnected callbacks. We need them
+ * just to cleanup our link state. */
+void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
+    if (status != REDIS_OK) instanceLinkConnectionError(c);
+}
+
+void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
+    REDIS_NOTUSED(status);
+    instanceLinkConnectionError(c);
+}
+
 /* ========================== sentinelRedisInstance ========================= */
 
 /* Create a redis instance, the following fields must be populated by the
@@ -894,6 +1124,7 @@ void sentinelCallClientReconfScript(sentinelRedisInstance *master, int role, cha
  *
  * The function may also fail and return NULL with errno set to EBUSY if
  * a master or slave with the same name already exists. */
+
 sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *hostname, int port, int quorum, sentinelRedisInstance *master) {
     sentinelRedisInstance *ri;
     sentinelAddr *addr;
@@ -932,24 +1163,12 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri = zmalloc(sizeof(*ri));
     /* Note that all the instances are started in the disconnected state,
      * the event loop will take care of connecting them. */
-    ri->flags = flags | SRI_DISCONNECTED;
+    ri->flags = flags;
     ri->name = sdsname;
     ri->runid = NULL;
     ri->config_epoch = 0;
     ri->addr = addr;
-    ri->cc = NULL;
-    ri->pc = NULL;
-    ri->pending_commands = 0;
-    ri->cc_conn_time = 0;
-    ri->pc_conn_time = 0;
-    ri->pc_last_activity = 0;
-    /* We set the last_ping_time to "now" even if we actually don't have yet
-     * a connection with the node, nor we sent a ping.
-     * This is useful to detect a timeout in case we'll not be able to connect
-     * with the node at all. */
-    ri->last_ping_time = mstime();
-    ri->last_avail_time = mstime();
-    ri->last_pong_time = mstime();
+    ri->link = createInstanceLink();
     ri->last_pub_time = mstime();
     ri->last_hello_time = mstime();
     ri->last_master_down_reply_time = mstime();
@@ -1005,9 +1224,8 @@ void releaseSentinelRedisInstance(sentinelRedisInstance *ri) {
     dictRelease(ri->sentinels);
     dictRelease(ri->slaves);
 
-    /* Release hiredis connections. */
-    if (ri->cc) sentinelKillLink(ri,ri->cc);
-    if (ri->pc) sentinelKillLink(ri,ri->pc);
+    /* Disconnect the instance. */
+    releaseInstanceLink(ri->link,ri);
 
     /* Free other resources. */
     sdsfree(ri->name);
@@ -1051,35 +1269,29 @@ const char *sentinelRedisInstanceTypeStr(sentinelRedisInstance *ri) {
     else return "unknown";
 }
 
-/* This function removes all the instances found in the dictionary of
- * sentinels in the specified 'master', having either:
- *
- * 1) The same ip/port as specified.
- * 2) The same runid.
+/* This function remove the Sentinel with the specified ID from the
+ * specified master.
  *
- * "1" and "2" don't need to verify at the same time, just one is enough.
- * If "runid" is NULL it is not checked.
- * Similarly if "ip" is NULL it is not checked.
+ * If "runid" is NULL the function returns ASAP.
  *
- * This function is useful because every time we add a new Sentinel into
- * a master's Sentinels dictionary, we want to be very sure about not
- * having duplicated instances for any reason. This is important because
- * other sentinels are needed to reach ODOWN quorum, and later to get
- * voted for a given configuration epoch in order to perform the failover.
+ * This function is useful because on Sentinels address switch, we want to
+ * remove our old entry and add a new one for the same ID but with the new
+ * address.
  *
- * The function returns the number of Sentinels removed. */
-int removeMatchingSentinelsFromMaster(sentinelRedisInstance *master, char *ip, int port, char *runid) {
+ * The function returns 1 if the matching Sentinel was removed, otherwise
+ * 0 if there was no Sentinel with this ID. */
+int removeMatchingSentinelFromMaster(sentinelRedisInstance *master, char *runid) {
     dictIterator *di;
     dictEntry *de;
     int removed = 0;
 
+    if (runid == NULL) return 0;
+
     di = dictGetSafeIterator(master->sentinels);
     while((de = dictNext(di)) != NULL) {
         sentinelRedisInstance *ri = dictGetVal(de);
 
-        if ((ri->runid && runid && strcmp(ri->runid,runid) == 0) ||
-            (ip && strcmp(ri->addr->ip,ip) == 0 && port == ri->addr->port))
-        {
+        if (ri->runid && strcmp(ri->runid,runid) == 0) {
             dictDelete(master->sentinels,ri->name);
             removed++;
         }
@@ -1172,9 +1384,9 @@ void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
         dictRelease(ri->sentinels);
         ri->sentinels = dictCreate(&instancesDictType,NULL);
     }
-    if (ri->cc) sentinelKillLink(ri,ri->cc);
-    if (ri->pc) sentinelKillLink(ri,ri->pc);
-    ri->flags &= SRI_MASTER|SRI_DISCONNECTED;
+    instanceLinkCloseConnection(ri->link,ri->link->cc);
+    instanceLinkCloseConnection(ri->link,ri->link->pc);
+    ri->flags &= SRI_MASTER;
     if (ri->leader) {
         sdsfree(ri->leader);
         ri->leader = NULL;
@@ -1187,9 +1399,10 @@ void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
     sdsfree(ri->slave_master_host);
     ri->runid = NULL;
     ri->slave_master_host = NULL;
-    ri->last_ping_time = mstime();
-    ri->last_avail_time = mstime();
-    ri->last_pong_time = mstime();
+    ri->link->act_ping_time = mstime();
+    ri->link->last_ping_time = 0;
+    ri->link->last_avail_time = mstime();
+    ri->link->last_pong_time = mstime();
     ri->role_reported_time = mstime();
     ri->role_reported = SRI_MASTER;
     if (flags & SENTINEL_GENERATE_EVENT)
@@ -1329,6 +1542,13 @@ void sentinelPropagateDownAfterPeriod(sentinelRedisInstance *master) {
     }
 }
 
+char *sentinelGetInstanceTypeString(sentinelRedisInstance *ri) {
+    if (ri->flags & SRI_MASTER) return "master";
+    else if (ri->flags & SRI_SLAVE) return "slave";
+    else if (ri->flags & SRI_SENTINEL) return "sentinel";
+    else return "unknown";
+}
+
 /* ============================ Config handling ============================= */
 char *sentinelHandleConfiguration(char **argv, int argc) {
     sentinelRedisInstance *ri;
@@ -1392,6 +1612,10 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
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
@@ -1430,7 +1654,10 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         {
             return "Wrong hostname or port for sentinel.";
         }
-        if (argc == 5) si->runid = sdsnew(argv[4]);
+        if (argc == 5) {
+            si->runid = sdsnew(argv[4]);
+            sentinelTryConnectionSharing(si);
+        }
     } else if (!strcasecmp(argv[0],"announce-ip") && argc == 2) {
         /* announce-ip <ip-address> */
         if (strlen(argv[1]))
@@ -1454,6 +1681,10 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
     dictEntry *de;
     sds line;
 
+    /* sentinel unique ID. */
+    line = sdscatprintf(sdsempty(), "sentinel myid %s", sentinel.myid);
+    rewriteConfigRewriteLine(state,"sentinel",line,1);
+
     /* For every master emit a "sentinel monitor" config entry. */
     di = dictGetIterator(sentinel.masters);
     while((de = dictNext(di)) != NULL) {
@@ -1615,57 +1846,6 @@ void sentinelFlushConfig(void) {
 
 /* ====================== hiredis connection handling ======================= */
 
-/* Completely disconnect a hiredis link from an instance. */
-void sentinelKillLink(sentinelRedisInstance *ri, redisAsyncContext *c) {
-    if (ri->cc == c) {
-        ri->cc = NULL;
-        ri->pending_commands = 0;
-    }
-    if (ri->pc == c) ri->pc = NULL;
-    c->data = NULL;
-    ri->flags |= SRI_DISCONNECTED;
-    redisAsyncFree(c);
-}
-
-/* This function takes a hiredis context that is in an error condition
- * and make sure to mark the instance as disconnected performing the
- * cleanup needed.
- *
- * Note: we don't free the hiredis context as hiredis will do it for us
- * for async connections. */
-void sentinelDisconnectInstanceFromContext(const redisAsyncContext *c) {
-    sentinelRedisInstance *ri = c->data;
-    int pubsub;
-
-    if (ri == NULL) return; /* The instance no longer exists. */
-
-    pubsub = (ri->pc == c);
-    sentinelEvent(REDIS_DEBUG, pubsub ? "-pubsub-link" : "-cmd-link", ri,
-        "%@ #%s", c->errstr);
-    if (pubsub)
-        ri->pc = NULL;
-    else
-        ri->cc = NULL;
-    ri->flags |= SRI_DISCONNECTED;
-}
-
-void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
-    if (status != REDIS_OK) {
-        sentinelDisconnectInstanceFromContext(c);
-    } else {
-        sentinelRedisInstance *ri = c->data;
-        int pubsub = (ri->pc == c);
-
-        sentinelEvent(REDIS_DEBUG, pubsub ? "+pubsub-link" : "+cmd-link", ri,
-            "%@");
-    }
-}
-
-void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
-    REDIS_NOTUSED(status);
-    sentinelDisconnectInstanceFromContext(c);
-}
-
 /* Send the AUTH command with the specified master password if needed.
  * Note that for slaves the password set for the master is used.
  *
@@ -1677,8 +1857,8 @@ void sentinelSendAuthIfNeeded(sentinelRedisInstance *ri, redisAsyncContext *c) {
                                                  ri->master->auth_pass;
 
     if (auth_pass) {
-        if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL, "AUTH %s",
-            auth_pass) == REDIS_OK) ri->pending_commands++;
+        if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri, "AUTH %s",
+            auth_pass) == REDIS_OK) ri->link->pending_commands++;
     }
 }
 
@@ -1691,77 +1871,82 @@ void sentinelSendAuthIfNeeded(sentinelRedisInstance *ri, redisAsyncContext *c) {
 void sentinelSetClientName(sentinelRedisInstance *ri, redisAsyncContext *c, char *type) {
     char name[64];
 
-    snprintf(name,sizeof(name),"sentinel-%.8s-%s",server.runid,type);
-    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, NULL,
+    snprintf(name,sizeof(name),"sentinel-%.8s-%s",sentinel.myid,type);
+    if (redisAsyncCommand(c, sentinelDiscardReplyCallback, ri,
         "CLIENT SETNAME %s", name) == REDIS_OK)
     {
-        ri->pending_commands++;
+        ri->link->pending_commands++;
     }
 }
 
-/* Create the async connections for the specified instance if the instance
- * is disconnected. Note that the SRI_DISCONNECTED flag is set even if just
+/* Create the async connections for the instance link if the link
+ * is disconnected. Note that link->disconnected is true even if just
  * one of the two links (commands and pub/sub) is missing. */
 void sentinelReconnectInstance(sentinelRedisInstance *ri) {
-    if (!(ri->flags & SRI_DISCONNECTED)) return;
+    if (ri->link->disconnected == 0) return;
+    instanceLink *link = ri->link;
+    mstime_t now = mstime();
+
+    if (now - ri->link->last_reconn_time < SENTINEL_PING_PERIOD) return;
+    ri->link->last_reconn_time = now;
 
     /* Commands connection. */
-    if (ri->cc == NULL) {
-        ri->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
-        if (ri->cc->err) {
+    if (link->cc == NULL) {
+        link->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
+        if (link->cc->err) {
             sentinelEvent(REDIS_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
-                ri->cc->errstr);
-            sentinelKillLink(ri,ri->cc);
+                link->cc->errstr);
+            instanceLinkCloseConnection(link,link->cc);
         } else {
-            ri->cc_conn_time = mstime();
-            ri->cc->data = ri;
-            redisAeAttach(server.el,ri->cc);
-            redisAsyncSetConnectCallback(ri->cc,
-                                            sentinelLinkEstablishedCallback);
-            redisAsyncSetDisconnectCallback(ri->cc,
-                                            sentinelDisconnectCallback);
-            sentinelSendAuthIfNeeded(ri,ri->cc);
-            sentinelSetClientName(ri,ri->cc,"cmd");
+            link->cc_conn_time = mstime();
+            link->cc->data = link;
+            redisAeAttach(server.el,link->cc);
+            redisAsyncSetConnectCallback(link->cc,
+                    sentinelLinkEstablishedCallback);
+            redisAsyncSetDisconnectCallback(link->cc,
+                    sentinelDisconnectCallback);
+            sentinelSendAuthIfNeeded(ri,link->cc);
+            sentinelSetClientName(ri,link->cc,"cmd");
 
             /* Send a PING ASAP when reconnecting. */
             sentinelSendPing(ri);
         }
     }
     /* Pub / Sub */
-    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && ri->pc == NULL) {
-        ri->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
-        if (ri->pc->err) {
+    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && link->pc == NULL) {
+        link->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,REDIS_BIND_ADDR);
+        if (link->pc->err) {
             sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
-                ri->pc->errstr);
-            sentinelKillLink(ri,ri->pc);
+                link->pc->errstr);
+            instanceLinkCloseConnection(link,link->pc);
         } else {
             int retval;
 
-            ri->pc_conn_time = mstime();
-            ri->pc->data = ri;
-            redisAeAttach(server.el,ri->pc);
-            redisAsyncSetConnectCallback(ri->pc,
-                                            sentinelLinkEstablishedCallback);
-            redisAsyncSetDisconnectCallback(ri->pc,
-                                            sentinelDisconnectCallback);
-            sentinelSendAuthIfNeeded(ri,ri->pc);
-            sentinelSetClientName(ri,ri->pc,"pubsub");
+            link->pc_conn_time = mstime();
+            link->pc->data = link;
+            redisAeAttach(server.el,link->pc);
+            redisAsyncSetConnectCallback(link->pc,
+                    sentinelLinkEstablishedCallback);
+            redisAsyncSetDisconnectCallback(link->pc,
+                    sentinelDisconnectCallback);
+            sentinelSendAuthIfNeeded(ri,link->pc);
+            sentinelSetClientName(ri,link->pc,"pubsub");
             /* Now we subscribe to the Sentinels "Hello" channel. */
-            retval = redisAsyncCommand(ri->pc,
-                sentinelReceiveHelloMessages, NULL, "SUBSCRIBE %s",
+            retval = redisAsyncCommand(link->pc,
+                sentinelReceiveHelloMessages, ri, "SUBSCRIBE %s",
                     SENTINEL_HELLO_CHANNEL);
             if (retval != REDIS_OK) {
                 /* If we can't subscribe, the Pub/Sub connection is useless
                  * and we can simply disconnect it and try again. */
-                sentinelKillLink(ri,ri->pc);
+                instanceLinkCloseConnection(link,link->pc);
                 return;
             }
         }
     }
-    /* Clear the DISCONNECTED flags only if we have both the connections
+    /* Clear the disconnected status only if we have both the connections
      * (or just the commands connection if this is a sentinel instance). */
-    if (ri->cc && (ri->flags & SRI_SENTINEL || ri->pc))
-        ri->flags &= ~SRI_DISCONNECTED;
+    if (link->cc && (ri->flags & SRI_SENTINEL || link->pc))
+        link->disconnected = 0;
 }
 
 /* ======================== Redis instances pinging  ======================== */
@@ -2030,36 +2215,35 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
 }
 
 void sentinelInfoReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    sentinelRedisInstance *ri = privdata;
+    instanceLink *link = c->data;
     redisReply *r;
-    REDIS_NOTUSED(privdata);
 
-    if (ri) ri->pending_commands--;
-    if (!reply || !ri) return;
+    if (!reply || !link) return;
+    link->pending_commands--;
     r = reply;
 
-    if (r->type == REDIS_REPLY_STRING) {
+    if (r->type == REDIS_REPLY_STRING)
         sentinelRefreshInstanceInfo(ri,r->str);
-    }
 }
 
 /* Just discard the reply. We use this when we are not monitoring the return
  * value of the command but its effects directly. */
 void sentinelDiscardReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    instanceLink *link = c->data;
     REDIS_NOTUSED(reply);
     REDIS_NOTUSED(privdata);
 
-    if (ri) ri->pending_commands--;
+    if (link) link->pending_commands--;
 }
 
 void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    sentinelRedisInstance *ri = privdata;
+    instanceLink *link = c->data;
     redisReply *r;
-    REDIS_NOTUSED(privdata);
 
-    if (ri) ri->pending_commands--;
-    if (!reply || !ri) return;
+    if (!reply || !link) return;
+    link->pending_commands--;
     r = reply;
 
     if (r->type == REDIS_REPLY_STATUS ||
@@ -2070,35 +2254,35 @@ void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata
             strncmp(r->str,"LOADING",7) == 0 ||
             strncmp(r->str,"MASTERDOWN",10) == 0)
         {
-            ri->last_avail_time = mstime();
-            ri->last_ping_time = 0; /* Flag the pong as received. */
+            link->last_avail_time = mstime();
+            link->act_ping_time = 0; /* Flag the pong as received. */
         } else {
             /* Send a SCRIPT KILL command if the instance appears to be
              * down because of a busy script. */
             if (strncmp(r->str,"BUSY",4) == 0 &&
                 (ri->flags & SRI_S_DOWN) &&
                 !(ri->flags & SRI_SCRIPT_KILL_SENT))
             {
-                if (redisAsyncCommand(ri->cc,
-                        sentinelDiscardReplyCallback, NULL,
+                if (redisAsyncCommand(ri->link->cc,
+                        sentinelDiscardReplyCallback, ri,
                         "SCRIPT KILL") == REDIS_OK)
-                    ri->pending_commands++;
+                    ri->link->pending_commands++;
                 ri->flags |= SRI_SCRIPT_KILL_SENT;
             }
         }
     }
-    ri->last_pong_time = mstime();
+    link->last_pong_time = mstime();
 }
 
 /* This is called when we get the reply about the PUBLISH command we send
  * to the master to advertise this sentinel. */
 void sentinelPublishReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    sentinelRedisInstance *ri = privdata;
+    instanceLink *link = c->data;
     redisReply *r;
-    REDIS_NOTUSED(privdata);
 
-    if (ri) ri->pending_commands--;
-    if (!reply || !ri) return;
+    if (!reply || !link) return;
+    link->pending_commands--;
     r = reply;
 
     /* Only update pub_time if we actually published our message. Otherwise
@@ -2136,25 +2320,25 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
 
         if (!si) {
             /* If not, remove all the sentinels that have the same runid
-             * OR the same ip/port, because it's either a restart or a
-             * network topology change. */
-            removed = removeMatchingSentinelsFromMaster(master,token[0],port,
-                            token[2]);
+             * because there was an address change, and add the same Sentinel
+             * with the new address back. */
+            removed = removeMatchingSentinelFromMaster(master,token[2]);
             if (removed) {
-                sentinelEvent(REDIS_NOTICE,"-dup-sentinel",master,
-                    "%@ #duplicate of %s:%d or %s",
-                    token[0],port,token[2]);
+                sentinelEvent(REDIS_NOTICE,"+sentinel-address-switch",master,
+                    "%@ ip %s port %d for %s", token[0],port,token[2]);
             }
 
             /* Add the new sentinel. */
             si = createSentinelRedisInstance(NULL,SRI_SENTINEL,
                             token[0],port,master->quorum,master);
             if (si) {
-                sentinelEvent(REDIS_NOTICE,"+sentinel",si,"%@");
+                if (!removed) sentinelEvent(REDIS_NOTICE,"+sentinel",si,"%@");
                 /* The runid is NULL after a new instance creation and
                  * for Sentinels we don't have a later chance to fill it,
                  * so do it now. */
                 si->runid = sdsnew(token[2]);
+                sentinelTryConnectionSharing(si);
+                if (removed) sentinelUpdateSentinelAddressInAllMasters(si);
                 sentinelFlushConfig();
             }
         }
@@ -2203,17 +2387,17 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
 /* This is our Pub/Sub callback for the Hello channel. It's useful in order
  * to discover other sentinels attached at the same master. */
 void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    sentinelRedisInstance *ri = privdata;
     redisReply *r;
-    REDIS_NOTUSED(privdata);
+    REDIS_NOTUSED(c);
 
     if (!reply || !ri) return;
     r = reply;
 
     /* Update the last activity in the pubsub channel. Note that since we
      * receive our messages as well this timestamp can be used to detect
      * if the link is probably disconnected even if it seems otherwise. */
-    ri->pc_last_activity = mstime();
+    ri->link->pc_last_activity = mstime();
 
     /* Sanity check in the reply we expect, so that the code that follows
      * can avoid to check for details. */
@@ -2225,7 +2409,7 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
         strcmp(r->element[0]->str,"message") != 0) return;
 
     /* We are not interested in meeting ourselves */
-    if (strstr(r->element[2]->str,server.runid) != NULL) return;
+    if (strstr(r->element[2]->str,sentinel.myid) != NULL) return;
 
     sentinelProcessHelloMessage(r->element[2]->str, r->element[2]->len);
 }
@@ -2250,14 +2434,14 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
     sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
 
-    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
+    if (ri->link->disconnected) return REDIS_ERR;
 
     /* Use the specified announce address if specified, otherwise try to
      * obtain our own IP address. */
     if (sentinel.announce_ip) {
         announce_ip = sentinel.announce_ip;
     } else {
-        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1)
+        if (anetSockName(ri->link->cc->c.fd,ip,sizeof(ip),NULL) == -1)
             return REDIS_ERR;
         announce_ip = ip;
     }
@@ -2268,16 +2452,16 @@ int sentinelSendHello(sentinelRedisInstance *ri) {
     snprintf(payload,sizeof(payload),
         "%s,%d,%s,%llu," /* Info about this sentinel. */
         "%s,%s,%d,%llu", /* Info about current master. */
-        announce_ip, announce_port, server.runid,
+        announce_ip, announce_port, sentinel.myid,
         (unsigned long long) sentinel.current_epoch,
         /* --- */
         master->name,master_addr->ip,master_addr->port,
         (unsigned long long) master->config_epoch);
-    retval = redisAsyncCommand(ri->cc,
-        sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
+    retval = redisAsyncCommand(ri->link->cc,
+        sentinelPublishReplyCallback, ri, "PUBLISH %s %s",
             SENTINEL_HELLO_CHANNEL,payload);
     if (retval != REDIS_OK) return REDIS_ERR;
-    ri->pending_commands++;
+    ri->link->pending_commands++;
     return REDIS_OK;
 }
 
@@ -2313,20 +2497,22 @@ int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master) {
     return REDIS_OK;
 }
 
-/* Send a PING to the specified instance and refresh the last_ping_time
+/* Send a PING to the specified instance and refresh the act_ping_time
  * if it is zero (that is, if we received a pong for the previous ping).
  *
  * On error zero is returned, and we can't consider the PING command
  * queued in the connection. */
 int sentinelSendPing(sentinelRedisInstance *ri) {
-    int retval = redisAsyncCommand(ri->cc,
-        sentinelPingReplyCallback, NULL, "PING");
+    int retval = redisAsyncCommand(ri->link->cc,
+        sentinelPingReplyCallback, ri, "PING");
     if (retval == REDIS_OK) {
-        ri->pending_commands++;
-        /* We update the ping time only if we received the pong for
-         * the previous ping, otherwise we are technically waiting
-         * since the first ping that did not received a reply. */
-        if (ri->last_ping_time == 0) ri->last_ping_time = mstime();
+        ri->link->pending_commands++;
+        ri->link->last_ping_time = mstime();
+        /* We update the active ping time only if we received the pong for
+         * the previous ping, otherwise we are technically waiting since the
+         * first ping that did not received a reply. */
+        if (ri->link->act_ping_time == 0)
+            ri->link->act_ping_time = ri->link->last_ping_time;
         return 1;
     } else {
         return 0;
@@ -2342,15 +2528,16 @@ void sentinelSendPeriodicCommands(sentinelRedisInstance *ri) {
 
     /* Return ASAP if we have already a PING or INFO already pending, or
      * in the case the instance is not properly connected. */
-    if (ri->flags & SRI_DISCONNECTED) return;
+    if (ri->link->disconnected) return;
 
     /* For INFO, PING, PUBLISH that are not critical commands to send we
      * also have a limit of SENTINEL_MAX_PENDING_COMMANDS. We don't
      * want to use a lot of memory just because a link is not working
      * properly (note that anyway there is a redundant protection about this,
      * that is, the link will be disconnected and reconnected if a long
      * timeout condition is detected. */
-    if (ri->pending_commands >= SENTINEL_MAX_PENDING_COMMANDS) return;
+    if (ri->link->pending_commands >=
+        SENTINEL_MAX_PENDING_COMMANDS * ri->link->refcount) return;
 
     /* If this is a slave of a master in O_DOWN condition we start sending
      * it INFO every second, instead of the usual SENTINEL_INFO_PERIOD
@@ -2374,10 +2561,11 @@ void sentinelSendPeriodicCommands(sentinelRedisInstance *ri) {
         (now - ri->info_refresh) > info_period))
     {
         /* Send INFO to masters and slaves, not sentinels. */
-        retval = redisAsyncCommand(ri->cc,
-            sentinelInfoReplyCallback, NULL, "INFO");
-        if (retval == REDIS_OK) ri->pending_commands++;
-    } else if ((now - ri->last_pong_time) > ping_period) {
+        retval = redisAsyncCommand(ri->link->cc,
+            sentinelInfoReplyCallback, ri, "INFO");
+        if (retval == REDIS_OK) ri->link->pending_commands++;
+    } else if ((now - ri->link->last_pong_time) > ping_period &&
+               (now - ri->link->last_ping_time) > ping_period/2) {
         /* Send PING to all the three kinds of instances. */
         sentinelSendPing(ri);
     } else if ((now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD) {
@@ -2431,7 +2619,7 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
     if (ri->flags & SRI_MASTER) flags = sdscat(flags,"master,");
     if (ri->flags & SRI_SLAVE) flags = sdscat(flags,"slave,");
     if (ri->flags & SRI_SENTINEL) flags = sdscat(flags,"sentinel,");
-    if (ri->flags & SRI_DISCONNECTED) flags = sdscat(flags,"disconnected,");
+    if (ri->link->disconnected) flags = sdscat(flags,"disconnected,");
     if (ri->flags & SRI_MASTER_DOWN) flags = sdscat(flags,"master_down,");
     if (ri->flags & SRI_FAILOVER_IN_PROGRESS)
         flags = sdscat(flags,"failover_in_progress,");
@@ -2445,8 +2633,12 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
     sdsfree(flags);
     fields++;
 
-    addReplyBulkCString(c,"pending-commands");
-    addReplyBulkLongLong(c,ri->pending_commands);
+    addReplyBulkCString(c,"link-pending-commands");
+    addReplyBulkLongLong(c,ri->link->pending_commands);
+    fields++;
+
+    addReplyBulkCString(c,"link-refcount");
+    addReplyBulkLongLong(c,ri->link->refcount);
     fields++;
 
     if (ri->flags & SRI_FAILOVER_IN_PROGRESS) {
@@ -2457,15 +2649,15 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
 
     addReplyBulkCString(c,"last-ping-sent");
     addReplyBulkLongLong(c,
-        ri->last_ping_time ? (mstime() - ri->last_ping_time) : 0);
+        ri->link->act_ping_time ? (mstime() - ri->link->act_ping_time) : 0);
     fields++;
 
     addReplyBulkCString(c,"last-ok-ping-reply");
-    addReplyBulkLongLong(c,mstime() - ri->last_avail_time);
+    addReplyBulkLongLong(c,mstime() - ri->link->last_avail_time);
     fields++;
 
     addReplyBulkCString(c,"last-ping-reply");
-    addReplyBulkLongLong(c,mstime() - ri->last_pong_time);
+    addReplyBulkLongLong(c,mstime() - ri->link->last_pong_time);
     fields++;
 
     if (ri->flags & SRI_S_DOWN) {
@@ -2619,6 +2811,31 @@ sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(redisClient *c,
     return ri;
 }
 
+#define SENTINEL_ISQR_OK 0
+#define SENTINEL_ISQR_NOQUORUM (1<<0)
+#define SENTINEL_ISQR_NOAUTH (1<<1)
+int sentinelIsQuorumReachable(sentinelRedisInstance *master, int *usableptr) {
+    dictIterator *di;
+    dictEntry *de;
+    int usable = 1; /* Number of usable Sentinels. Init to 1 to count myself. */
+    int result = SENTINEL_ISQR_OK;
+    int voters = dictSize(master->sentinels)+1; /* Known Sentinels + myself. */
+
+    di = dictGetIterator(master->sentinels);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *ri = dictGetVal(de);
+
+        if (ri->flags & (SRI_S_DOWN|SRI_O_DOWN)) continue;
+        usable++;
+    }
+    dictReleaseIterator(di);
+
+    if (usable < (int)master->quorum) result |= SENTINEL_ISQR_NOQUORUM;
+    if (usable < voters/2+1) result |= SENTINEL_ISQR_NOAUTH;
+    if (usableptr) *usableptr = usable;
+    return result;
+}
+
 void sentinelCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"masters")) {
         /* SENTINEL MASTERS */
@@ -2649,7 +2866,23 @@ void sentinelCommand(redisClient *c) {
             return;
         addReplyDictOfRedisInstances(c,ri->sentinels);
     } else if (!strcasecmp(c->argv[1]->ptr,"is-master-down-by-addr")) {
-        /* SENTINEL IS-MASTER-DOWN-BY-ADDR <ip> <port> <current-epoch> <runid>*/
+        /* SENTINEL IS-MASTER-DOWN-BY-ADDR <ip> <port> <current-epoch> <runid>
+         *
+         * Arguments:
+         *
+         * ip and port are the ip and port of the master we want to be
+         * checked by Sentinel. Note that the command will not check by
+         * name but just by master, in theory different Sentinels may monitor
+         * differnet masters with the same name.
+         *
+         * current-epoch is needed in order to understand if we are allowed
+         * to vote for a failover leader or not. Each Sentinel can vote just
+         * one time per epoch.
+         *
+         * runid is "*" if we are not seeking for a vote from the Sentinel
+         * in order to elect the failover leader. Otherwise it is set to the
+         * runid we want the Sentinel to vote if it did not already voted.
+         */
         sentinelRedisInstance *ri;
         long long req_epoch;
         uint64_t leader_epoch = 0;
@@ -2785,6 +3018,32 @@ void sentinelCommand(redisClient *c) {
         dictDelete(sentinel.masters,c->argv[2]->ptr);
         sentinelFlushConfig();
         addReply(c,shared.ok);
+    } else if (!strcasecmp(c->argv[1]->ptr,"ckquorum")) {
+        /* SENTINEL CKQUORUM <name> */
+        sentinelRedisInstance *ri;
+        int usable;
+
+        if ((ri = sentinelGetMasterByNameOrReplyError(c,c->argv[2]))
+            == NULL) return;
+        int result = sentinelIsQuorumReachable(ri,&usable);
+        if (result == SENTINEL_ISQR_OK) {
+            addReplySds(c, sdscatfmt(sdsempty(),
+                "+OK %i usable Sentinels. Quorum and failover authorization "
+                "can be reached\r\n",usable));
+        } else {
+            sds e = sdscatfmt(sdsempty(),
+                "-NOQUORUM %i usable Sentinels. ",usable);
+            if (result & SENTINEL_ISQR_NOQUORUM)
+                e = sdscat(e,"Not enough available Sentinels to reach the"
+                             " specified quorum for this master");
+            if (result & SENTINEL_ISQR_NOAUTH) {
+                if (result & SENTINEL_ISQR_NOQUORUM) e = sdscat(e,". ");
+                e = sdscat(e, "Not enough available Sentinels to reach the"
+                              " majority and authorize a failover");
+            }
+            e = sdscat(e,"\r\n");
+            addReplySds(c,e);
+        }
     } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);
@@ -3051,36 +3310,38 @@ void sentinelPublishCommand(redisClient *c) {
 void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
     mstime_t elapsed = 0;
 
-    if (ri->last_ping_time)
-        elapsed = mstime() - ri->last_ping_time;
+    if (ri->link->act_ping_time)
+        elapsed = mstime() - ri->link->act_ping_time;
 
     /* Check if we are in need for a reconnection of one of the
      * links, because we are detecting low activity.
      *
      * 1) Check if the command link seems connected, was connected not less
      *    than SENTINEL_MIN_LINK_RECONNECT_PERIOD, but still we have a
      *    pending ping for more than half the timeout. */
-    if (ri->cc &&
-        (mstime() - ri->cc_conn_time) > SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
-        ri->last_ping_time != 0 && /* Ther is a pending ping... */
+    if (ri->link->cc &&
+        (mstime() - ri->link->cc_conn_time) >
+        SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
+        ri->link->act_ping_time != 0 && /* Ther is a pending ping... */
         /* The pending ping is delayed, and we did not received
          * error replies as well. */
-        (mstime() - ri->last_ping_time) > (ri->down_after_period/2) &&
-        (mstime() - ri->last_pong_time) > (ri->down_after_period/2))
+        (mstime() - ri->link->act_ping_time) > (ri->down_after_period/2) &&
+        (mstime() - ri->link->last_pong_time) > (ri->down_after_period/2))
     {
-        sentinelKillLink(ri,ri->cc);
+        instanceLinkCloseConnection(ri->link,ri->link->cc);
     }
 
     /* 2) Check if the pubsub link seems connected, was connected not less
      *    than SENTINEL_MIN_LINK_RECONNECT_PERIOD, but still we have no
      *    activity in the Pub/Sub channel for more than
      *    SENTINEL_PUBLISH_PERIOD * 3.
      */
-    if (ri->pc &&
-        (mstime() - ri->pc_conn_time) > SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
-        (mstime() - ri->pc_last_activity) > (SENTINEL_PUBLISH_PERIOD*3))
+    if (ri->link->pc &&
+        (mstime() - ri->link->pc_conn_time) >
+         SENTINEL_MIN_LINK_RECONNECT_PERIOD &&
+        (mstime() - ri->link->pc_last_activity) > (SENTINEL_PUBLISH_PERIOD*3))
     {
-        sentinelKillLink(ri,ri->pc);
+        instanceLinkCloseConnection(ri->link,ri->link->pc);
     }
 
     /* Update the SDOWN flag. We believe the instance is SDOWN if:
@@ -3154,12 +3415,12 @@ void sentinelCheckObjectivelyDown(sentinelRedisInstance *master) {
 /* Receive the SENTINEL is-master-down-by-addr reply, see the
  * sentinelAskMasterStateToOtherSentinels() function for more information. */
 void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    sentinelRedisInstance *ri = privdata;
+    instanceLink *link = c->data;
     redisReply *r;
-    REDIS_NOTUSED(privdata);
 
-    if (ri) ri->pending_commands--;
-    if (!reply || !ri) return;
+    if (!reply || !link) return;
+    link->pending_commands--;
     r = reply;
 
     /* Ignore every error or unexpected reply.
@@ -3220,21 +3481,21 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
          * 2) Sentinel is connected.
          * 3) We did not received the info within SENTINEL_ASK_PERIOD ms. */
         if ((master->flags & SRI_S_DOWN) == 0) continue;
-        if (ri->flags & SRI_DISCONNECTED) continue;
+        if (ri->link->disconnected) continue;
         if (!(flags & SENTINEL_ASK_FORCED) &&
             mstime() - ri->last_master_down_reply_time < SENTINEL_ASK_PERIOD)
             continue;
 
         /* Ask */
         ll2string(port,sizeof(port),master->addr->port);
-        retval = redisAsyncCommand(ri->cc,
-                    sentinelReceiveIsMasterDownReply, NULL,
+        retval = redisAsyncCommand(ri->link->cc,
+                    sentinelReceiveIsMasterDownReply, ri,
                     "SENTINEL is-master-down-by-addr %s %s %llu %s",
                     master->addr->ip, port,
                     sentinel.current_epoch,
                     (master->failover_state > SENTINEL_FAILOVER_STATE_NONE) ?
-                    server.runid : "*");
-        if (retval == REDIS_OK) ri->pending_commands++;
+                    sentinel.myid : "*");
+        if (retval == REDIS_OK) ri->link->pending_commands++;
     }
     dictReleaseIterator(di);
 }
@@ -3265,7 +3526,7 @@ char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char
         /* If we did not voted for ourselves, set the master failover start
          * time to now, in order to force a delay before we can start a
          * failover for the same master. */
-        if (strcasecmp(master->leader,server.runid))
+        if (strcasecmp(master->leader,sentinel.myid))
             master->failover_start_time = mstime()+rand()%SENTINEL_MAX_DESYNC;
     }
 
@@ -3346,7 +3607,7 @@ char *sentinelGetLeader(sentinelRedisInstance *master, uint64_t epoch) {
     if (winner)
         myvote = sentinelVoteLeader(master,epoch,winner,&leader_epoch);
     else
-        myvote = sentinelVoteLeader(master,epoch,server.runid,&leader_epoch);
+        myvote = sentinelVoteLeader(master,epoch,sentinel.myid,&leader_epoch);
 
     if (myvote && leader_epoch == epoch) {
         uint64_t votes = sentinelLeaderIncr(counters,myvote);
@@ -3400,35 +3661,35 @@ int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port) {
      *
      * Note that we don't check the replies returned by commands, since we
      * will observe instead the effects in the next INFO output. */
-    retval = redisAsyncCommand(ri->cc,
-        sentinelDiscardReplyCallback, NULL, "MULTI");
+    retval = redisAsyncCommand(ri->link->cc,
+        sentinelDiscardReplyCallback, ri, "MULTI");
     if (retval == REDIS_ERR) return retval;
-    ri->pending_commands++;
+    ri->link->pending_commands++;
 
-    retval = redisAsyncCommand(ri->cc,
-        sentinelDiscardReplyCallback, NULL, "SLAVEOF %s %s", host, portstr);
+    retval = redisAsyncCommand(ri->link->cc,
+        sentinelDiscardReplyCallback, ri, "SLAVEOF %s %s", host, portstr);
     if (retval == REDIS_ERR) return retval;
-    ri->pending_commands++;
+    ri->link->pending_commands++;
 
-    retval = redisAsyncCommand(ri->cc,
-        sentinelDiscardReplyCallback, NULL, "CONFIG REWRITE");
+    retval = redisAsyncCommand(ri->link->cc,
+        sentinelDiscardReplyCallback, ri, "CONFIG REWRITE");
     if (retval == REDIS_ERR) return retval;
-    ri->pending_commands++;
+    ri->link->pending_commands++;
 
     /* CLIENT KILL TYPE <type> is only supported starting from Redis 2.8.12,
      * however sending it to an instance not understanding this command is not
      * an issue because CLIENT is variadic command, so Redis will not
      * recognized as a syntax error, and the transaction will not fail (but
      * only the unsupported command will fail). */
-    retval = redisAsyncCommand(ri->cc,
-        sentinelDiscardReplyCallback, NULL, "CLIENT KILL TYPE normal");
+    retval = redisAsyncCommand(ri->link->cc,
+        sentinelDiscardReplyCallback, ri, "CLIENT KILL TYPE normal");
     if (retval == REDIS_ERR) return retval;
-    ri->pending_commands++;
+    ri->link->pending_commands++;
 
-    retval = redisAsyncCommand(ri->cc,
-        sentinelDiscardReplyCallback, NULL, "EXEC");
+    retval = redisAsyncCommand(ri->link->cc,
+        sentinelDiscardReplyCallback, ri, "EXEC");
     if (retval == REDIS_ERR) return retval;
-    ri->pending_commands++;
+    ri->link->pending_commands++;
 
     return REDIS_OK;
 }
@@ -3566,8 +3827,9 @@ sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master) {
         sentinelRedisInstance *slave = dictGetVal(de);
         mstime_t info_validity_time;
 
-        if (slave->flags & (SRI_S_DOWN|SRI_O_DOWN|SRI_DISCONNECTED)) continue;
-        if (mstime() - slave->last_avail_time > SENTINEL_PING_PERIOD*5) continue;
+        if (slave->flags & (SRI_S_DOWN|SRI_O_DOWN)) continue;
+        if (slave->link->disconnected) continue;
+        if (mstime() - slave->link->last_avail_time > SENTINEL_PING_PERIOD*5) continue;
         if (slave->slave_priority == 0) continue;
 
         /* If the master is in SDOWN state we get INFO for slaves every second.
@@ -3598,7 +3860,7 @@ void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
 
     /* Check if we are the leader for the failover epoch. */
     leader = sentinelGetLeader(ri, ri->failover_epoch);
-    isleader = leader && strcasecmp(leader,server.runid) == 0;
+    isleader = leader && strcasecmp(leader,sentinel.myid) == 0;
     sdsfree(leader);
 
     /* If I'm not the leader, and it is not a forced failover via
@@ -3648,7 +3910,7 @@ void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
     /* We can't send the command to the promoted slave if it is now
      * disconnected. Retry again and again with this state until the timeout
      * is reached, then abort the failover. */
-    if (ri->promoted_slave->flags & SRI_DISCONNECTED) {
+    if (ri->link->disconnected) {
         if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
             sentinelEvent(REDIS_WARNING,"-failover-abort-slave-timeout",ri,"%@");
             sentinelAbortFailover(ri);
@@ -3727,8 +3989,8 @@ void sentinelFailoverDetectEnd(sentinelRedisInstance *master) {
             sentinelRedisInstance *slave = dictGetVal(de);
             int retval;
 
-            if (slave->flags &
-                (SRI_RECONF_DONE|SRI_RECONF_SENT|SRI_DISCONNECTED)) continue;
+            if (slave->flags & (SRI_RECONF_DONE|SRI_RECONF_SENT)) continue;
+            if (slave->link->disconnected) continue;
 
             retval = sentinelSendSlaveOf(slave,
                     master->promoted_slave->addr->ip,
@@ -3783,8 +4045,8 @@ void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
 
         /* Nothing to do for instances that are disconnected or already
          * in RECONF_SENT state. */
-        if (slave->flags & (SRI_DISCONNECTED|SRI_RECONF_SENT|SRI_RECONF_INPROG))
-            continue;
+        if (slave->flags & (SRI_RECONF_SENT|SRI_RECONF_INPROG)) continue;
+        if (slave->link->disconnected) continue;
 
         /* Send SLAVEOF <new master>. */
         retval = sentinelSendSlaveOf(slave,