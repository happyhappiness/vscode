@@ -36,6 +36,7 @@
 #include <arpa/inet.h>
 #include <sys/socket.h>
 #include <sys/wait.h>
+#include <fcntl.h>
 
 extern char **environ;
 
@@ -58,45 +59,34 @@ typedef struct sentinelAddr {
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
-#define SRI_I_AM_THE_LEADER (1<<9)     /* We are the leader for this master. */
-#define SRI_PROMOTED (1<<10)            /* Slave selected for promotion. */
-#define SRI_RECONF_SENT (1<<11)     /* SLAVEOF <newmaster> sent. */
-#define SRI_RECONF_INPROG (1<<12)   /* Slave synchronization in progress. */
-#define SRI_RECONF_DONE (1<<13)     /* Slave synchronized with new master. */
-#define SRI_FORCE_FAILOVER (1<<14)  /* Force failover with master up. */
-#define SRI_SCRIPT_KILL_SENT (1<<15) /* SCRIPT KILL already sent on -BUSY */
-#define SRI_DEMOTE (1<<16)   /* If the instance claims to be a master, demote
-                                it into a slave sending SLAVEOF. */
+#define SRI_PROMOTED (1<<8)            /* Slave selected for promotion. */
+#define SRI_RECONF_SENT (1<<9)     /* SLAVEOF <newmaster> sent. */
+#define SRI_RECONF_INPROG (1<<10)   /* Slave synchronization in progress. */
+#define SRI_RECONF_DONE (1<<11)     /* Slave synchronized with new master. */
+#define SRI_FORCE_FAILOVER (1<<12)  /* Force failover with master up. */
+#define SRI_SCRIPT_KILL_SENT (1<<13) /* SCRIPT KILL already sent on -BUSY */
 
 #define SENTINEL_INFO_PERIOD 10000
 #define SENTINEL_PING_PERIOD 1000
 #define SENTINEL_ASK_PERIOD 1000
-#define SENTINEL_PUBLISH_PERIOD 5000
-#define SENTINEL_DOWN_AFTER_PERIOD 30000
+#define SENTINEL_PUBLISH_PERIOD 2000
+#define SENTINEL_DEFAULT_DOWN_AFTER 30000
 #define SENTINEL_HELLO_CHANNEL "__sentinel__:hello"
 #define SENTINEL_TILT_TRIGGER 2000
 #define SENTINEL_TILT_PERIOD (SENTINEL_PING_PERIOD*30)
 #define SENTINEL_DEFAULT_SLAVE_PRIORITY 100
-#define SENTINEL_PROMOTION_RETRY_PERIOD 30000
 #define SENTINEL_SLAVE_RECONF_RETRY_PERIOD 10000
 #define SENTINEL_DEFAULT_PARALLEL_SYNCS 1
 #define SENTINEL_MIN_LINK_RECONNECT_PERIOD 15000
-#define SENTINEL_DEFAULT_FAILOVER_TIMEOUT (60*15*1000)
+#define SENTINEL_DEFAULT_FAILOVER_TIMEOUT (60*3*1000)
 #define SENTINEL_MAX_PENDING_COMMANDS 100
-#define SENTINEL_EXTENDED_SDOWN_MULTIPLIER 10
+#define SENTINEL_ELECTION_TIMEOUT 10000
 
 /* How many milliseconds is an information valid? This applies for instance
  * to the reply to SENTINEL IS-MASTER-DOWN-BY-ADDR replies. */
 #define SENTINEL_INFO_VALIDITY_TIME 5000
-#define SENTINEL_FAILOVER_FIXED_DELAY 5000
-#define SENTINEL_FAILOVER_MAX_RANDOM_DELAY 10000
 
 /* Failover machine different states. */
 #define SENTINEL_FAILOVER_STATE_NONE 0  /* No failover in progress. */
@@ -105,20 +95,18 @@ typedef struct sentinelAddr {
 #define SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE 3 /* Slave -> Master */
 #define SENTINEL_FAILOVER_STATE_WAIT_PROMOTION 4 /* Wait slave to change role */
 #define SENTINEL_FAILOVER_STATE_RECONF_SLAVES 5 /* SLAVEOF newmaster */
-#define SENTINEL_FAILOVER_STATE_WAIT_NEXT_SLAVE 6 /* wait replication */
-#define SENTINEL_FAILOVER_STATE_ALERT_CLIENTS 7 /* Run user script. */
-#define SENTINEL_FAILOVER_STATE_WAIT_ALERT_SCRIPT 8 /* Wait script exec. */
-#define SENTINEL_FAILOVER_STATE_DETECT_END 9 /* Check for failover end. */
-#define SENTINEL_FAILOVER_STATE_UPDATE_CONFIG 10 /* Monitor promoted slave. */
+#define SENTINEL_FAILOVER_STATE_UPDATE_CONFIG 6 /* Monitor promoted slave. */
 
 #define SENTINEL_MASTER_LINK_STATUS_UP 0
 #define SENTINEL_MASTER_LINK_STATUS_DOWN 1
 
-/* Generic flags that can be used with different functions. */
+/* Generic flags that can be used with different functions.
+ * They use higher bits to avoid colliding with the function specific
+ * flags. */
 #define SENTINEL_NO_FLAGS 0
-#define SENTINEL_GENERATE_EVENT 1
-#define SENTINEL_LEADER 2
-#define SENTINEL_OBSERVER 4
+#define SENTINEL_GENERATE_EVENT (1<<16)
+#define SENTINEL_LEADER (1<<17)
+#define SENTINEL_OBSERVER (1<<18)
 
 /* Script execution flags and limits. */
 #define SENTINEL_SCRIPT_NONE 0
@@ -133,6 +121,7 @@ typedef struct sentinelRedisInstance {
     int flags;      /* See SRI_... defines */
     char *name;     /* Master name from the point of view of this sentinel. */
     char *runid;    /* run ID of this instance. */
+    uint64_t config_epoch;  /* Configuration epoch. */
     sentinelAddr *addr; /* Master host. */
     redisAsyncContext *cc; /* Hiredis context for commands. */
     redisAsyncContext *pc; /* Hiredis context for Pub / Sub. */
@@ -156,6 +145,15 @@ typedef struct sentinelRedisInstance {
     mstime_t down_after_period; /* Consider it down after that period. */
     mstime_t info_refresh;  /* Time at which we received INFO output from it. */
 
+    /* Role and the first time we observed it.
+     * This is useful in order to delay replacing what the instance reports
+     * with our own configuration. We need to always wait some time in order
+     * to give a chance to the leader to report the new configuration before
+     * we do silly things. */
+    int role_reported;
+    mstime_t role_reported_time;
+    mstime_t slave_conf_change_time; /* Last time slave master addr changed. */
+
     /* Master specific. */
     dict *sentinels;    /* Other sentinels monitoring the same master. */
     dict *slaves;       /* Slaves for this master instance. */
@@ -167,20 +165,21 @@ typedef struct sentinelRedisInstance {
     mstime_t master_link_down_time; /* Slave replication link down time. */
     int slave_priority; /* Slave priority according to its INFO output. */
     mstime_t slave_reconf_sent_time; /* Time at which we sent SLAVE OF <new> */
-    struct sentinelRedisInstance *master; /* Master instance if SRI_SLAVE is set. */
+    struct sentinelRedisInstance *master; /* Master instance if it's slave. */
     char *slave_master_host;    /* Master host as reported by INFO */
     int slave_master_port;      /* Master port as reported by INFO */
     int slave_master_link_status; /* Master link status as reported by INFO */
+    unsigned long long slave_repl_offset; /* Slave replication offset. */
     /* Failover */
     char *leader;       /* If this is a master instance, this is the runid of
                            the Sentinel that should perform the failover. If
                            this is a Sentinel, this is the runid of the Sentinel
-                           that this other Sentinel is voting as leader.
-                           This field is valid only if SRI_MASTER_DOWN is
-                           set on the Sentinel instance. */
+                           that this Sentinel voted as leader. */
+    uint64_t leader_epoch; /* Epoch of the 'leader' field. */
+    uint64_t failover_epoch; /* Epoch of the currently started failover. */
     int failover_state; /* See SENTINEL_FAILOVER_STATE_* defines. */
     mstime_t failover_state_change_time;
-    mstime_t failover_start_time;   /* When to start to failover if leader. */
+    mstime_t failover_start_time;   /* Last failover attempt start time. */
     mstime_t failover_timeout;      /* Max time to refresh failover state. */
     struct sentinelRedisInstance *promoted_slave; /* Promoted slave instance. */
     /* Scripts executed to notify admin or reconfigure clients: when they
@@ -191,13 +190,14 @@ typedef struct sentinelRedisInstance {
 
 /* Main state. */
 struct sentinelState {
+    uint64_t current_epoch;     /* Current epoch. */
     dict *masters;      /* Dictionary of master sentinelRedisInstances.
                            Key is the instance name, value is the
                            sentinelRedisInstance structure pointer. */
     int tilt;           /* Are we in TILT mode? */
     int running_scripts;    /* Number of scripts in execution right now. */
     mstime_t tilt_start_time;   /* When TITL started. */
-    mstime_t previous_time;     /* Time last time we ran the time handler. */
+    mstime_t previous_time;     /* Last time we ran the time handler. */
     list *scripts_queue;    /* Queue of user scripts to execute. */
 } sentinel;
 
@@ -325,9 +325,11 @@ void sentinelAbortFailover(sentinelRedisInstance *ri);
 void sentinelEvent(int level, char *type, sentinelRedisInstance *ri, const char *fmt, ...);
 sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master);
 void sentinelScheduleScriptExecution(char *path, ...);
-void sentinelStartFailover(sentinelRedisInstance *master, int state);
+void sentinelStartFailover(sentinelRedisInstance *master);
 void sentinelDiscardReplyCallback(redisAsyncContext *c, void *reply, void *privdata);
 int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port);
+char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch);
+void sentinelFlushConfig(void);
 
 /* ========================= Dictionary types =============================== */
 
@@ -402,6 +404,7 @@ void initSentinel(void) {
     }
 
     /* Initialize various data structures. */
+    sentinel.current_epoch = 0;
     sentinel.masters = dictCreate(&instancesDictType,NULL);
     sentinel.tilt = 0;
     sentinel.tilt_start_time = 0;
@@ -410,6 +413,17 @@ void initSentinel(void) {
     sentinel.scripts_queue = listCreate();
 }
 
+/* This function gets called when the server is in Sentinel mode, started,
+ * loaded the configuration, and is ready for normal operations. */
+void sentinelIsRunning(void) {
+    redisLog(REDIS_WARNING,"Sentinel runid is %s", server.runid);
+
+    if (server.configfile == NULL || access(server.configfile,W_OK) == -1) {
+        redisLog(REDIS_WARNING,"Sentinel started without a config file, or config file not writable. Exiting...");
+        exit(1);
+    }
+}
+
 /* ============================== sentinelAddr ============================== */
 
 /* Create a sentinelAddr object and return it on success.
@@ -435,12 +449,27 @@ sentinelAddr *createSentinelAddr(char *hostname, int port) {
     return sa;
 }
 
+/* Return a duplicate of the source address. */
+sentinelAddr *dupSentinelAddr(sentinelAddr *src) {
+    sentinelAddr *sa;
+
+    sa = zmalloc(sizeof(*sa));
+    sa->ip = sdsnew(src->ip);
+    sa->port = src->port;
+    return sa;
+}
+
 /* Free a Sentinel address. Can't fail. */
 void releaseSentinelAddr(sentinelAddr *sa) {
     sdsfree(sa->ip);
     zfree(sa);
 }
 
+/* Return non-zero if two addresses are equal. */
+int sentinelAddrIsEqual(sentinelAddr *a, sentinelAddr *b) {
+    return a->port == b->port && !strcasecmp(a->ip,b->ip);
+}
+
 /* =========================== Events notification ========================== */
 
 /* Send an event to log, pub/sub, user notification script.
@@ -776,15 +805,13 @@ void sentinelPendingScriptsCommand(redisClient *c) {
  *
  * <master-name> <role> <state> <from-ip> <from-port> <to-ip> <to-port>
  *
- * It is called every time a failover starts, ends, or is aborted.
+ * It is called every time a failover is performed.
  *
- * <state> is "start", "end" or "abort".
+ * <state> is currently always "failover".
  * <role> is either "leader" or "observer".
  *
  * from/to fields are respectively master -> promoted slave addresses for
- * "start" and "end", or the reverse (promoted slave -> master) in case of
- * "abort".
- */
+ * "start" and "end". */
 void sentinelCallClientReconfScript(sentinelRedisInstance *master, int role, char *state, sentinelAddr *from, sentinelAddr *to) {
     char fromport[32], toport[32];
 
@@ -861,6 +888,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->flags = flags | SRI_DISCONNECTED;
     ri->name = sdsname;
     ri->runid = NULL;
+    ri->config_epoch = 0;
     ri->addr = addr;
     ri->cc = NULL;
     ri->pc = NULL;
@@ -876,14 +904,15 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->s_down_since_time = 0;
     ri->o_down_since_time = 0;
     ri->down_after_period = master ? master->down_after_period :
-                            SENTINEL_DOWN_AFTER_PERIOD;
+                            SENTINEL_DEFAULT_DOWN_AFTER;
     ri->master_link_down_time = 0;
     ri->auth_pass = NULL;
     ri->slave_priority = SENTINEL_DEFAULT_SLAVE_PRIORITY;
     ri->slave_reconf_sent_time = 0;
     ri->slave_master_host = NULL;
     ri->slave_master_port = 0;
     ri->slave_master_link_status = SENTINEL_MASTER_LINK_STATUS_DOWN;
+    ri->slave_repl_offset = 0;
     ri->sentinels = dictCreate(&instancesDictType,NULL);
     ri->quorum = quorum;
     ri->parallel_syncs = SENTINEL_DEFAULT_PARALLEL_SYNCS;
@@ -893,6 +922,8 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
 
     /* Failover state. */
     ri->leader = NULL;
+    ri->leader_epoch = 0;
+    ri->failover_epoch = 0;
     ri->failover_state = SENTINEL_FAILOVER_STATE_NONE;
     ri->failover_state_change_time = 0;
     ri->failover_start_time = 0;
@@ -901,6 +932,11 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->notification_script = NULL;
     ri->client_reconfig_script = NULL;
 
+    /* Role */
+    ri->role_reported = ri->flags & (SRI_MASTER|SRI_SLAVE);
+    ri->role_reported_time = mstime();
+    ri->slave_conf_change_time = mstime();
+
     /* Add into the right table. */
     dictAdd(table, ri->name, ri);
     return ri;
@@ -1030,7 +1066,7 @@ sentinelRedisInstance *getSentinelRedisInstanceByAddrAndRunID(dict *instances, c
     return instance;
 }
 
-/* Simple master lookup by name */
+/* Master lookup by name */
 sentinelRedisInstance *sentinelGetMasterByName(char *name) {
     sentinelRedisInstance *ri;
     sds sdsname = sdsnew(name);
@@ -1075,15 +1111,19 @@ void sentinelDelFlagsToDictOfRedisInstances(dict *instances, int flags) {
  * 5) In the process of doing this undo the failover if in progress.
  * 6) Disconnect the connections with the master (will reconnect automatically).
  */
+
+#define SENTINEL_RESET_NO_SENTINELS (1<<0)
 void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
     redisAssert(ri->flags & SRI_MASTER);
     dictRelease(ri->slaves);
-    dictRelease(ri->sentinels);
     ri->slaves = dictCreate(&instancesDictType,NULL);
-    ri->sentinels = dictCreate(&instancesDictType,NULL);
+    if (!(flags & SENTINEL_RESET_NO_SENTINELS)) {
+        dictRelease(ri->sentinels);
+        ri->sentinels = dictCreate(&instancesDictType,NULL);
+    }
     if (ri->cc) sentinelKillLink(ri,ri->cc);
     if (ri->pc) sentinelKillLink(ri,ri->pc);
-    ri->flags &= SRI_MASTER|SRI_CAN_FAILOVER|SRI_DISCONNECTED;
+    ri->flags &= SRI_MASTER|SRI_DISCONNECTED;
     if (ri->leader) {
         sdsfree(ri->leader);
         ri->leader = NULL;
@@ -1127,28 +1167,67 @@ int sentinelResetMastersByPattern(char *pattern, int flags) {
 /* Reset the specified master with sentinelResetMaster(), and also change
  * the ip:port address, but take the name of the instance unmodified.
  *
- * This is used to handle the +switch-master and +redirect-to-master events.
+ * This is used to handle the +switch-master event.
  *
  * The function returns REDIS_ERR if the address can't be resolved for some
- * reason. Otherwise REDIS_OK is returned.
- *
- * TODO: make this reset so that original sentinels are re-added with
- * same ip / port / runid.
- */
+ * reason. Otherwise REDIS_OK is returned.  */
 int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip, int port) {
     sentinelAddr *oldaddr, *newaddr;
+    sentinelAddr **slaves = NULL;
+    int numslaves = 0, j;
+    dictIterator *di;
+    dictEntry *de;
 
     newaddr = createSentinelAddr(ip,port);
     if (newaddr == NULL) return REDIS_ERR;
-    sentinelResetMaster(master,SENTINEL_NO_FLAGS);
+
+    /* Make a list of slaves to add back after the reset.
+     * Don't include the one having the address we are switching to. */
+    di = dictGetIterator(master->slaves);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *slave = dictGetVal(de);
+
+        if (sentinelAddrIsEqual(slave->addr,newaddr)) continue;
+        slaves = zrealloc(slaves,sizeof(sentinelAddr*)*(numslaves+1));
+        slaves[numslaves++] = createSentinelAddr(slave->addr->ip,
+                                                 slave->addr->port);
+    }
+    dictReleaseIterator(di);
+    
+    /* If we are switching to a different address, include the old address
+     * as a slave as well, so that we'll be able to sense / reconfigure
+     * the old master. */
+    if (!sentinelAddrIsEqual(newaddr,master->addr)) {
+        slaves = zrealloc(slaves,sizeof(sentinelAddr*)*(numslaves+1));
+        slaves[numslaves++] = createSentinelAddr(master->addr->ip,
+                                                 master->addr->port);
+    }
+
+    /* Reset and switch address. */
+    sentinelResetMaster(master,SENTINEL_RESET_NO_SENTINELS);
     oldaddr = master->addr;
     master->addr = newaddr;
     master->o_down_since_time = 0;
     master->s_down_since_time = 0;
 
+    /* Add slaves back. */
+    for (j = 0; j < numslaves; j++) {
+        sentinelRedisInstance *slave;
+
+        slave = createSentinelRedisInstance(NULL,SRI_SLAVE,slaves[j]->ip,
+                    slaves[j]->port, master->quorum, master);
+        releaseSentinelAddr(slaves[j]);
+        if (slave) {
+            sentinelEvent(REDIS_NOTICE,"+slave",slave,"%@");
+            sentinelFlushConfig();
+        }
+    }
+    zfree(slaves);
+
     /* Release the old address at the end so we are safe even if the function
      * gets the master->addr->ip and master->addr->port as arguments. */
     releaseSentinelAddr(oldaddr);
+    sentinelFlushConfig();
     return REDIS_OK;
 }
 
@@ -1163,6 +1242,24 @@ int sentinelRedisInstanceNoDownFor(sentinelRedisInstance *ri, mstime_t ms) {
     return most_recent == 0 || (mstime() - most_recent) > ms;
 }
 
+/* Return the current master address, that is, its address or the address
+ * of the promoted slave if already operational. */
+sentinelAddr *sentinelGetCurrentMasterAddress(sentinelRedisInstance *master) {
+    /* If we are failing over the master, and the state is already
+     * SENTINEL_FAILOVER_STATE_RECONF_SLAVES or greater, it means that we
+     * already have the new configuration epoch in the master, and the
+     * slave acknowledged the configuration switch. Advertise the new
+     * address. */
+    if ((master->flags & SRI_FAILOVER_IN_PROGRESS) &&
+        master->promoted_slave &&
+        master->failover_state >= SENTINEL_FAILOVER_STATE_RECONF_SLAVES)
+    {
+        return master->promoted_slave->addr;
+    } else {
+        return master->addr;
+    }
+}
+
 /* ============================ Config handling ============================= */
 char *sentinelHandleConfiguration(char **argv, int argc) {
     sentinelRedisInstance *ri;
@@ -1195,17 +1292,6 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
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
@@ -1231,12 +1317,180 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         ri->auth_pass = sdsnew(argv[2]);
+    } else if (!strcasecmp(argv[0],"config-epoch") && argc == 3) {
+        /* config-epoch <name> <epoch> */
+        ri = sentinelGetMasterByName(argv[1]);
+        if (!ri) return "No such master with specified name.";
+        ri->config_epoch = strtoull(argv[2],NULL,10);
+        if (ri->config_epoch > sentinel.current_epoch)
+            sentinel.current_epoch = ri->config_epoch;
+    } else if (!strcasecmp(argv[0],"known-slave") && argc == 4) {
+        sentinelRedisInstance *slave;
+
+        /* known-slave <name> <ip> <port> */
+        ri = sentinelGetMasterByName(argv[1]);
+        if (!ri) return "No such master with specified name.";
+        if ((slave = createSentinelRedisInstance(NULL,SRI_SLAVE,argv[2],
+                    atoi(argv[3]), ri->quorum, ri)) == NULL)
+        {
+            return "Wrong hostname or port for slave.";
+        }
+    } else if (!strcasecmp(argv[0],"known-sentinel") &&
+               (argc == 4 || argc == 5)) {
+        sentinelRedisInstance *si;
+
+        /* known-sentinel <name> <ip> <port> [runid] */
+        ri = sentinelGetMasterByName(argv[1]);
+        if (!ri) return "No such master with specified name.";
+        if ((si = createSentinelRedisInstance(NULL,SRI_SENTINEL,argv[2],
+                    atoi(argv[3]), ri->quorum, ri)) == NULL)
+        {
+            return "Wrong hostname or port for sentinel.";
+        }
+        if (argc == 5) si->runid = sdsnew(argv[4]);
     } else {
         return "Unrecognized sentinel configuration statement.";
     }
     return NULL;
 }
 
+/* Implements CONFIG REWRITE for "sentinel" option.
+ * This is used not just to rewrite the configuration given by the user
+ * (the configured masters) but also in order to retain the state of
+ * Sentinel across restarts: config epoch of masters, associated slaves
+ * and sentinel instances, and so forth. */
+void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
+    dictIterator *di, *di2;
+    dictEntry *de;
+
+    /* For every master emit a "sentinel monitor" config entry. */
+    di = dictGetIterator(sentinel.masters);
+    while((de = dictNext(di)) != NULL) {
+        sentinelRedisInstance *master, *ri;
+        sentinelAddr *master_addr;
+        sds line;
+
+        /* sentinel monitor */
+        master = dictGetVal(de);
+        master_addr = sentinelGetCurrentMasterAddress(master);
+        line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
+            master->name, master_addr->ip, master_addr->port,
+            master->quorum);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+
+        /* sentinel down-after-milliseconds */
+        if (master->down_after_period != SENTINEL_DEFAULT_DOWN_AFTER) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel down-after-milliseconds %s %ld",
+                master->name, (long) master->down_after_period);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel failover-timeout */
+        if (master->failover_timeout != SENTINEL_DEFAULT_FAILOVER_TIMEOUT) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel failover-timeout %s %ld",
+                master->name, (long) master->failover_timeout);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel parallel-syncs */
+        if (master->parallel_syncs != SENTINEL_DEFAULT_PARALLEL_SYNCS) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel parallel-syncs %s %d",
+                master->name, master->parallel_syncs);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel notification-script */
+        if (master->notification_script) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel notification-script %s %s",
+                master->name, master->notification_script);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel client-reconfig-script */
+        if (master->client_reconfig_script) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel client-reconfig-script %s %s",
+                master->name, master->client_reconfig_script);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel auth-pass */
+        if (master->auth_pass) {
+            line = sdscatprintf(sdsempty(),
+                "sentinel auth-pass %s %s",
+                master->name, master->auth_pass);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+
+        /* sentinel config-epoch */
+        line = sdscatprintf(sdsempty(),
+            "sentinel config-epoch %s %llu",
+            master->name, (unsigned long long) master->config_epoch);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+
+        /* sentinel known-slave */
+        di2 = dictGetIterator(master->slaves);
+        while((de = dictNext(di2)) != NULL) {
+            sentinelAddr *slave_addr;
+
+            ri = dictGetVal(de);
+            slave_addr = ri->addr;
+
+            /* If master_addr (obtained using sentinelGetCurrentMasterAddress()
+             * so it may be the address of the promoted slave) is equal to this
+             * slave's address, a failover is in progress and the slave was
+             * already successfully promoted. So as the address of this slave
+             * we use the old master address instead. */
+            if (sentinelAddrIsEqual(slave_addr,master_addr))
+                slave_addr = master->addr;
+            line = sdscatprintf(sdsempty(),
+                "sentinel known-slave %s %s %d",
+                master->name, ri->addr->ip, ri->addr->port);
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+        dictReleaseIterator(di2);
+
+        /* sentinel known-sentinel */
+        di2 = dictGetIterator(master->sentinels);
+        while((de = dictNext(di2)) != NULL) {
+            ri = dictGetVal(de);
+            line = sdscatprintf(sdsempty(),
+                "sentinel known-sentinel %s %s %d%s%s",
+                master->name, ri->addr->ip, ri->addr->port,
+                ri->runid ? " " : "",
+                ri->runid ? ri->runid : "");
+            rewriteConfigRewriteLine(state,"sentinel",line,1);
+        }
+        dictReleaseIterator(di2);
+    }
+    dictReleaseIterator(di);
+}
+
+/* This function uses the config rewriting Redis engine in order to persist
+ * the state of the Sentinel in the current configuration file.
+ *
+ * Before returning the function calls fsync() against the generated
+ * configuration file to make sure changes are committed to disk.
+ *
+ * On failure the function logs a warning on the Redis log. */
+void sentinelFlushConfig(void) {
+    int fd;
+
+    if (rewriteConfig(server.configfile) == -1) {
+        redisLog(REDIS_WARNING,"WARNING: Senitnel was not able to save the new configuration on disk!!!: %s", strerror(errno));
+        return;
+    }
+    if ((fd = open(server.configfile,O_RDONLY)) != -1) {
+        fsync(fd);
+        close(fd);
+    }
+    return;
+}
+
 /* ====================== hiredis connection handling ======================= */
 
 /* Completely disconnect an hiredis link from an instance. */
@@ -1330,7 +1584,7 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
         }
     }
     /* Pub / Sub */
-    if ((ri->flags & SRI_MASTER) && ri->pc == NULL) {
+    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && ri->pc == NULL) {
         ri->pc = redisAsyncConnect(ri->addr->ip,ri->addr->port);
         if (ri->pc->err) {
             sentinelEvent(REDIS_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
@@ -1368,6 +1622,19 @@ void sentinelReconnectInstance(sentinelRedisInstance *ri) {
 
 /* ======================== Redis instances pinging  ======================== */
 
+/* Return true if master looks "sane", that is:
+ * 1) It is actually a master in the current configuration.
+ * 2) It reports itself as a master.
+ * 3) It is not SDOWN or ODOWN.
+ * 4) We obtained last INFO no more than two times the INFO period of time ago. */
+int sentinelMasterLooksSane(sentinelRedisInstance *master) {
+    return
+        master->flags & SRI_MASTER &&
+        master->role_reported == SRI_MASTER &&
+        (master->flags & (SRI_S_DOWN|SRI_O_DOWN)) == 0 &&
+        (mstime() - master->info_refresh) < SENTINEL_INFO_PERIOD*2;
+}
+
 /* Process the INFO output from masters. */
 void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
     sds *lines;
@@ -1454,13 +1721,24 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
         if (role == SRI_SLAVE) {
             /* master_host:<host> */
             if (sdslen(l) >= 12 && !memcmp(l,"master_host:",12)) {
-                sdsfree(ri->slave_master_host);
-                ri->slave_master_host = sdsnew(l+12);
+                if (ri->slave_master_host == NULL ||
+                    strcasecmp(l+12,ri->slave_master_host))
+                {
+                    sdsfree(ri->slave_master_host);
+                    ri->slave_master_host = sdsnew(l+12);
+                    ri->slave_conf_change_time = mstime();
+                }
             }
 
             /* master_port:<port> */
-            if (sdslen(l) >= 12 && !memcmp(l,"master_port:",12))
-                ri->slave_master_port = atoi(l+12);
+            if (sdslen(l) >= 12 && !memcmp(l,"master_port:",12)) {
+                int slave_master_port = atoi(l+12);
+
+                if (ri->slave_master_port != slave_master_port) {
+                    ri->slave_master_port = slave_master_port;
+                    ri->slave_conf_change_time = mstime();
+                }
+            }
             
             /* master_link_status:<status> */
             if (sdslen(l) >= 19 && !memcmp(l,"master_link_status:",19)) {
@@ -1473,6 +1751,10 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
             /* slave_priority:<priority> */
             if (sdslen(l) >= 15 && !memcmp(l,"slave_priority:",15))
                 ri->slave_priority = atoi(l+15);
+
+            /* slave_repl_offset:<offset> */
+            if (sdslen(l) >= 18 && !memcmp(l,"slave_repl_offset:",18))
+                ri->slave_repl_offset = strtoull(l+18,NULL,10);
         }
     }
     ri->info_refresh = mstime();
@@ -1482,124 +1764,81 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
      * Some things will not happen if sentinel.tilt is true, but some will
      * still be processed. */
 
-    /* When what we believe is our master, turned into a slave, the wiser
-     * thing we can do is to follow the events and redirect to the new
-     * master, always. */
-    if ((ri->flags & SRI_MASTER) && role == SRI_SLAVE && ri->slave_master_host)
-    {
-        sentinelEvent(REDIS_WARNING,"+redirect-to-master",ri,
-            "%s %s %d %s %d",
-            ri->name, ri->addr->ip, ri->addr->port,
-            ri->slave_master_host, ri->slave_master_port);
-        sentinelResetMasterAndChangeAddress(ri,ri->slave_master_host,
-                                               ri->slave_master_port);
-        return; /* Don't process anything after this event. */
+    /* Handle master -> slave role switch. */
+    if ((ri->flags & SRI_MASTER) && role == SRI_SLAVE) {
+        if (ri->role_reported != SRI_SLAVE) {
+            ri->role_reported_time = mstime();
+            ri->role_reported = SRI_SLAVE;
+            ri->slave_conf_change_time = mstime();
+        }
     }
 
     /* Handle slave -> master role switch. */
     if ((ri->flags & SRI_SLAVE) && role == SRI_MASTER) {
-        if (!sentinel.tilt && ri->flags & SRI_DEMOTE) {
-            /* If this sentinel was partitioned from the slave's master,
-             * or tilted recently, wait some time before to act,
-             * so that DOWN and roles INFO will be refreshed. */
-            mstime_t wait_time = SENTINEL_INFO_PERIOD*2 +
-                                 ri->master->down_after_period*2;
-
-            if (!sentinelRedisInstanceNoDownFor(ri->master,wait_time) ||
-                (mstime()-sentinel.tilt_start_time) < wait_time)
-                return;
+        if (ri->role_reported != SRI_MASTER) {
+            ri->role_reported_time = mstime();
+            ri->role_reported = SRI_MASTER;
+        }
 
-            /* Old master returned back? Turn it into a slave ASAP if
-             * we can reach what we believe is the new master now, and
-             * have a recent role information for it.
-             *
-             * Note: we'll clear the DEMOTE flag only when we have the
-             * acknowledge that it's a slave again. */
-            if (ri->master->flags & SRI_MASTER &&
-                (ri->master->flags & (SRI_S_DOWN|SRI_O_DOWN)) == 0 &&
-                (mstime() - ri->master->info_refresh) < SENTINEL_INFO_PERIOD*2)
+        /* If this is a promoted slave we can change state to the
+         * failover state machine. */
+        if (!sentinel.tilt &&
+            (ri->master->flags & SRI_FAILOVER_IN_PROGRESS) &&
+            (ri->master->failover_state ==
+                SENTINEL_FAILOVER_STATE_WAIT_PROMOTION))
+        {
+            /* Now that we are sure the slave was reconfigured as a master
+             * set the master configuration epoch to the epoch we won the
+             * election to perform this failover. This will force the other
+             * Sentinels to update their config (assuming there is not
+             * a newer one already available). */
+            ri->master->config_epoch = ri->master->failover_epoch;
+            ri->master->failover_state = SENTINEL_FAILOVER_STATE_RECONF_SLAVES;
+            ri->master->failover_state_change_time = mstime();
+            sentinelFlushConfig();
+            sentinelEvent(REDIS_WARNING,"+promoted-slave",ri,"%@");
+            sentinelEvent(REDIS_WARNING,"+failover-state-reconf-slaves",
+                ri->master,"%@");
+            sentinelCallClientReconfScript(ri->master,SENTINEL_LEADER,
+                "start",ri->master->addr,ri->addr);
+        } else if (!sentinel.tilt) {
+            /* A slave turned into a master. We want to force our view and
+             * reconfigure as slave. Wait some time after the change before
+             * going forward, to receive new configs if any. */
+            mstime_t wait_time = SENTINEL_PUBLISH_PERIOD*4;
+
+            if (sentinelMasterLooksSane(ri->master) &&
+               sentinelRedisInstanceNoDownFor(ri,wait_time) &&
+               mstime() - ri->role_reported_time > wait_time)
             {
-                int retval;
-                retval = sentinelSendSlaveOf(ri,
+                int retval = sentinelSendSlaveOf(ri,
                         ri->master->addr->ip,
                         ri->master->addr->port);
                 if (retval == REDIS_OK)
-                    sentinelEvent(REDIS_NOTICE,"+demote-old-slave",ri,"%@");
-            } else {
-                /* Otherwise if there are not the conditions to demote, we
-                 * no longer trust the DEMOTE flag and remove it. */
-                ri->flags &= ~SRI_DEMOTE;
-                sentinelEvent(REDIS_NOTICE,"-demote-flag-cleared",ri,"%@");
+                    sentinelEvent(REDIS_NOTICE,"+convert-to-slave",ri,"%@");
             }
-        } else if (!(ri->master->flags & SRI_FAILOVER_IN_PROGRESS) &&
-                    (runid_changed || first_runid))
-        {
-            /* If a slave turned into master but:
-             *
-             * 1) Failover not in progress.
-             * 2) RunID has changed or its the first time we see an INFO output.
-             * 
-             * We assume this is a reboot with a wrong configuration.
-             * Log the event and remove the slave. Note that this is processed
-             * in tilt mode as well, otherwise we lose the information that the
-             * runid changed (reboot?) and when the tilt mode ends a fake
-             * failover will be detected. */
-            int retval;
+        }
+    }
 
-            sentinelEvent(REDIS_WARNING,"-slave-restart-as-master",ri,"%@ #removing it from the attached slaves");
-            retval = dictDelete(ri->master->slaves,ri->name);
-            redisAssert(retval == REDIS_OK);
-            return;
-        } else if (!sentinel.tilt && ri->flags & SRI_PROMOTED) {
-            /* If this is a promoted slave we can change state to the
-             * failover state machine. */
-            if ((ri->master->flags & SRI_FAILOVER_IN_PROGRESS) &&
-                (ri->master->flags & SRI_I_AM_THE_LEADER) &&
-                (ri->master->failover_state ==
-                    SENTINEL_FAILOVER_STATE_WAIT_PROMOTION))
-            {
-                ri->master->failover_state = SENTINEL_FAILOVER_STATE_RECONF_SLAVES;
-                ri->master->failover_state_change_time = mstime();
-                sentinelEvent(REDIS_WARNING,"+promoted-slave",ri,"%@");
-                sentinelEvent(REDIS_WARNING,"+failover-state-reconf-slaves",
-                    ri->master,"%@");
-                sentinelCallClientReconfScript(ri->master,SENTINEL_LEADER,
-                    "start",ri->master->addr,ri->addr);
-            }
-        } else if (!sentinel.tilt && (
-                    !(ri->master->flags & SRI_FAILOVER_IN_PROGRESS) ||
-                     ((ri->master->flags & SRI_FAILOVER_IN_PROGRESS) &&
-                      (ri->master->flags & SRI_I_AM_THE_LEADER) &&
-                       ri->master->failover_state ==
-                       SENTINEL_FAILOVER_STATE_WAIT_START)))
-        {
-            /* No failover in progress? Then it is the start of a failover
-             * and we are an observer.
-             *
-             * We also do that if we are a leader doing a failover, in wait
-             * start, but well, somebody else started before us. */
-
-            if (ri->master->flags & SRI_FAILOVER_IN_PROGRESS) {
-                sentinelEvent(REDIS_WARNING,"-failover-abort-race",
-                                ri->master, "%@");
-                sentinelAbortFailover(ri->master);
-            }
+    /* Handle slaves replicating to a different master address. */
+    if ((ri->flags & SRI_SLAVE) && !sentinel.tilt &&
+        role == SRI_SLAVE &&
+        (ri->slave_master_port != ri->master->addr->port ||
+         strcasecmp(ri->slave_master_host,ri->master->addr->ip)))
+    {
+        mstime_t wait_time = ri->master->failover_timeout;
 
-            ri->master->flags |= SRI_FAILOVER_IN_PROGRESS;
-            sentinelEvent(REDIS_WARNING,"+failover-detected",ri->master,"%@");
-            ri->master->failover_state = SENTINEL_FAILOVER_STATE_DETECT_END;
-            ri->master->failover_state_change_time = mstime();
-            ri->master->promoted_slave = ri;
-            ri->flags |= SRI_PROMOTED;
-            ri->flags &= ~SRI_DEMOTE;
-            sentinelCallClientReconfScript(ri->master,SENTINEL_OBSERVER,
-                "start", ri->master->addr,ri->addr);
-            /* We are an observer, so we can only assume that the leader
-             * is reconfiguring the slave instances. For this reason we
-             * set all the instances as RECONF_SENT waiting for progresses
-             * on this side. */
-            sentinelAddFlagsToDictOfRedisInstances(ri->master->slaves,
-                SRI_RECONF_SENT);
+        /* Make sure the master is sane before reconfiguring this instance
+         * into a slave. */
+        if (sentinelMasterLooksSane(ri->master) &&
+            sentinelRedisInstanceNoDownFor(ri,wait_time) &&
+            mstime() - ri->slave_conf_change_time > wait_time)
+        {
+            int retval = sentinelSendSlaveOf(ri,
+                    ri->master->addr->ip,
+                    ri->master->addr->port);
+            if (retval == REDIS_OK)
+                sentinelEvent(REDIS_NOTICE,"+fix-slave-config",ri,"%@");
         }
     }
 
@@ -1631,19 +1870,8 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
             ri->flags &= ~SRI_RECONF_INPROG;
             ri->flags |= SRI_RECONF_DONE;
             sentinelEvent(REDIS_NOTICE,"+slave-reconf-done",ri,"%@");
-            /* If we are moving forward (a new slave is now configured)
-             * we update the change_time as we are conceptually passing
-             * to the next slave. */
-            ri->failover_state_change_time = mstime();
         }
     }
-
-    /* Detect if the old master was demoted as slave and generate the
-     * +slave event. */
-    if (role == SRI_SLAVE && ri->flags & SRI_DEMOTE) {
-        sentinelEvent(REDIS_NOTICE,"+slave",ri,"%@");
-        ri->flags &= ~SRI_DEMOTE;
-    }
 }
 
 void sentinelInfoReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
@@ -1721,12 +1949,14 @@ void sentinelPublishReplyCallback(redisAsyncContext *c, void *reply, void *privd
 /* This is our Pub/Sub callback for the Hello channel. It's useful in order
  * to discover other sentinels attached at the same master. */
 void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privdata) {
-    sentinelRedisInstance *ri = c->data;
+    sentinelRedisInstance *ri = c->data, *master;
     redisReply *r;
 
     if (!reply || !ri) return;
     r = reply;
 
+    master = (ri->flags & SRI_MASTER) ? ri : ri->master;
+
     /* Update the last activity in the pubsub channel. Note that since we
      * receive our messages as well this timestamp can be used to detect
      * if the link is probably disconnected even if it seems otherwise. */
@@ -1745,60 +1975,132 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
     if (strstr(r->element[2]->str,server.runid) != NULL) return;
 
     {
-        int numtokens, port, removed, canfailover;
-        /* Separator changed from ":" to "," in recent versions in order to
-         * play well with IPv6 addresses. For now we make sure to parse both
-         * correctly detecting if there is "," inside the string. */
-        char *sep = strchr(r->element[2]->str,',') ? "," : ":";
+        /* Format is composed of 8 tokens:
+         * 0=ip,1=port,2=runid,3=current_epoch,4=master_name,
+         * 5=master_ip,6=master_port,7=master_config_epoch. */
+        int numtokens, port, removed, master_port;
+        uint64_t current_epoch, master_config_epoch;
         char **token = sdssplitlen(r->element[2]->str,
                                    r->element[2]->len,
-                                   sep,1,&numtokens);
-        sentinelRedisInstance *sentinel;
+                                   ",",1,&numtokens);
+        sentinelRedisInstance *si;
 
-        if (numtokens == 4) {
+        if (numtokens == 8) {
             /* First, try to see if we already have this sentinel. */
             port = atoi(token[1]);
-            canfailover = atoi(token[3]);
-            sentinel = getSentinelRedisInstanceByAddrAndRunID(
-                            ri->sentinels,token[0],port,token[2]);
-
-            if (!sentinel) {
+            master_port = atoi(token[6]);
+            si = getSentinelRedisInstanceByAddrAndRunID(
+                            master->sentinels,token[0],port,token[2]);
+            current_epoch = strtoull(token[3],NULL,10);
+            master_config_epoch = strtoull(token[7],NULL,10);
+            sentinelRedisInstance *msgmaster;
+
+            if (!si) {
                 /* If not, remove all the sentinels that have the same runid
                  * OR the same ip/port, because it's either a restart or a
                  * network topology change. */
-                removed = removeMatchingSentinelsFromMaster(ri,token[0],port,
+                removed = removeMatchingSentinelsFromMaster(master,token[0],port,
                                 token[2]);
                 if (removed) {
-                    sentinelEvent(REDIS_NOTICE,"-dup-sentinel",ri,
+                    sentinelEvent(REDIS_NOTICE,"-dup-sentinel",master,
                         "%@ #duplicate of %s:%d or %s",
                         token[0],port,token[2]);
                 }
 
                 /* Add the new sentinel. */
-                sentinel = createSentinelRedisInstance(NULL,SRI_SENTINEL,
-                                token[0],port,ri->quorum,ri);
-                if (sentinel) {
-                    sentinelEvent(REDIS_NOTICE,"+sentinel",sentinel,"%@");
+                si = createSentinelRedisInstance(NULL,SRI_SENTINEL,
+                                token[0],port,master->quorum,master);
+                if (si) {
+                    sentinelEvent(REDIS_NOTICE,"+sentinel",si,"%@");
                     /* The runid is NULL after a new instance creation and
                      * for Sentinels we don't have a later chance to fill it,
                      * so do it now. */
-                    sentinel->runid = sdsnew(token[2]);
+                    si->runid = sdsnew(token[2]);
+                    sentinelFlushConfig();
                 }
             }
 
-            /* Update the state of the Sentinel. */
-            if (sentinel) {
-                sentinel->last_hello_time = mstime();
-                if (canfailover)
-                    sentinel->flags |= SRI_CAN_FAILOVER;
-                else
-                    sentinel->flags &= ~SRI_CAN_FAILOVER;
+            /* Update local current_epoch if received current_epoch is greater.*/
+            if (current_epoch > sentinel.current_epoch) {
+                sentinel.current_epoch = current_epoch;
+                sentinelEvent(REDIS_WARNING,"+new-epoch",ri,"%llu",
+                    (unsigned long long) sentinel.current_epoch);
             }
+
+            /* Update master info if received configuration is newer. */
+            if ((msgmaster = sentinelGetMasterByName(token[4])) != NULL) {
+                if (msgmaster->config_epoch < master_config_epoch) {
+                    msgmaster->config_epoch = master_config_epoch;
+                    if (master_port != msgmaster->addr->port ||
+                        !strcmp(msgmaster->addr->ip, token[5]))
+                    {
+                        sentinelAddr *old_addr;
+
+                        sentinelEvent(REDIS_WARNING,"+switch-master",
+                            msgmaster,"%s %s %d %s %d",
+                            msgmaster->name,
+                            msgmaster->addr->ip, msgmaster->addr->port,
+                            token[5], master_port);
+
+                        old_addr = dupSentinelAddr(msgmaster->addr);
+                        sentinelResetMasterAndChangeAddress(msgmaster,
+                                                    token[5], master_port);
+                        sentinelCallClientReconfScript(msgmaster,
+                            SENTINEL_OBSERVER,"start",
+                            old_addr,msgmaster->addr);
+                        releaseSentinelAddr(old_addr);
+                    }
+                }
+            }
+
+            /* Update the state of the Sentinel. */
+            if (si) si->last_hello_time = mstime();
         }
         sdsfreesplitres(token,numtokens);
     }
 }
 
+/* Send an "Hello" message via Pub/Sub to the specified 'ri' Redis
+ * instance in order to broadcast the current configuraiton for this
+ * master, and to advertise the existence of this Sentinel at the same time.
+ *
+ * The message has the following format:
+ *
+ * sentinel_ip,sentinel_port,sentinel_runid,current_epoch,
+ * master_name,master_ip,master_port,master_config_epoch.
+ *
+ * Returns REDIS_OK if the PUBLISH was queued correctly, otherwise
+ * REDIS_ERR is returned. */
+int sentinelSendHello(sentinelRedisInstance *ri) {
+    char ip[REDIS_IP_STR_LEN];
+    char payload[REDIS_IP_STR_LEN+1024];
+    int retval;
+    sentinelRedisInstance *master = (ri->flags & SRI_MASTER) ? ri : ri->master;
+    sentinelAddr *master_addr = sentinelGetCurrentMasterAddress(master);
+
+    /* Try to obtain our own IP address. */
+    if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) == -1) return REDIS_ERR;
+    if (ri->flags & SRI_DISCONNECTED) return REDIS_ERR;
+
+    /* Format and send the Hello message. */
+    snprintf(payload,sizeof(payload),
+        "%s,%d,%s,%llu," /* Info about this sentinel. */
+        "%s,%s,%d,%lld", /* Info about current master. */
+        ip, server.port, server.runid,
+        (unsigned long long) sentinel.current_epoch,
+        /* --- */
+        master->name,master_addr->ip,master_addr->port,
+        master->config_epoch);
+    retval = redisAsyncCommand(ri->cc,
+        sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
+            SENTINEL_HELLO_CHANNEL,payload);
+    if (retval != REDIS_OK) return REDIS_ERR;
+    ri->pending_commands++;
+    return REDIS_OK;
+}
+
+/* Send periodic PING, INFO, and PUBLISH to the Hello channel to
+ * the specified master or slave instance. */
 void sentinelPingInstance(sentinelRedisInstance *ri) {
     mstime_t now = mstime();
     mstime_t info_period;
@@ -1842,23 +2144,11 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
             sentinelPingReplyCallback, NULL, "PING");
         if (retval != REDIS_OK) return;
         ri->pending_commands++;
-    } else if ((ri->flags & SRI_MASTER) &&
+    } else if ((ri->flags & SRI_SENTINEL) == 0 &&
                (now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD)
     {
-        /* PUBLISH hello messages only to masters. */
-        char ip[REDIS_IP_STR_LEN];
-        if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
-            char myaddr[REDIS_IP_STR_LEN+128];
-
-            snprintf(myaddr,sizeof(myaddr),"%s,%d,%s,%d",
-                ip, server.port, server.runid,
-                (ri->flags & SRI_CAN_FAILOVER) != 0);
-            retval = redisAsyncCommand(ri->cc,
-                sentinelPublishReplyCallback, NULL, "PUBLISH %s %s",
-                    SENTINEL_HELLO_CHANNEL,myaddr);
-            if (retval != REDIS_OK) return;
-            ri->pending_commands++;
-        }
+        /* PUBLISH hello messages to masters and slaves. */
+        sentinelSendHello(ri);
     }
 }
 
@@ -1872,8 +2162,6 @@ const char *sentinelFailoverStateStr(int state) {
     case SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE: return "send_slaveof_noone";
     case SENTINEL_FAILOVER_STATE_WAIT_PROMOTION: return "wait_promotion";
     case SENTINEL_FAILOVER_STATE_RECONF_SLAVES: return "reconf_slaves";
-    case SENTINEL_FAILOVER_STATE_ALERT_CLIENTS: return "alert_clients";
-    case SENTINEL_FAILOVER_STATE_DETECT_END: return "detect_end";
     case SENTINEL_FAILOVER_STATE_UPDATE_CONFIG: return "update_config";
     default: return "unknown";
     }
@@ -1913,13 +2201,10 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
     if (ri->flags & SRI_MASTER_DOWN) flags = sdscat(flags,"master_down,");
     if (ri->flags & SRI_FAILOVER_IN_PROGRESS)
         flags = sdscat(flags,"failover_in_progress,");
-    if (ri->flags & SRI_I_AM_THE_LEADER)
-        flags = sdscat(flags,"i_am_the_leader,");
     if (ri->flags & SRI_PROMOTED) flags = sdscat(flags,"promoted,");
     if (ri->flags & SRI_RECONF_SENT) flags = sdscat(flags,"reconf_sent,");
     if (ri->flags & SRI_RECONF_INPROG) flags = sdscat(flags,"reconf_inprog,");
     if (ri->flags & SRI_RECONF_DONE) flags = sdscat(flags,"reconf_done,");
-    if (ri->flags & SRI_DEMOTE) flags = sdscat(flags,"demote,");
 
     if (sdslen(flags) != 0) sdsrange(flags,0,-2); /* remove last "," */
     addReplyBulkCString(c,flags);
@@ -1961,10 +2246,23 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
         addReplyBulkCString(c,"info-refresh");
         addReplyBulkLongLong(c,mstime() - ri->info_refresh);
         fields++;
+
+        addReplyBulkCString(c,"role-reported");
+        addReplyBulkCString(c, (ri->role_reported == SRI_MASTER) ? "master" :
+                                                                   "slave");
+        fields++;
+
+        addReplyBulkCString(c,"role-reported-time");
+        addReplyBulkLongLong(c,mstime() - ri->role_reported_time);
+        fields++;
     }
 
     /* Only masters */
     if (ri->flags & SRI_MASTER) {
+        addReplyBulkCString(c,"config-epoch");
+        addReplyBulkLongLong(c,ri->config_epoch);
+        fields++;
+
         addReplyBulkCString(c,"num-slaves");
         addReplyBulkLongLong(c,dictSize(ri->slaves));
         fields++;
@@ -2002,6 +2300,10 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
         addReplyBulkCString(c,"slave-priority");
         addReplyBulkLongLong(c,ri->slave_priority);
         fields++;
+
+        addReplyBulkCString(c,"slave-repl-offset");
+        addReplyBulkLongLong(c,ri->slave_repl_offset);
+        fields++;
     }
 
     /* Only sentinels */
@@ -2010,15 +2312,13 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
         addReplyBulkLongLong(c,mstime() - ri->last_hello_time);
         fields++;
 
-        addReplyBulkCString(c,"can-failover-its-master");
-        addReplyBulkLongLong(c,(ri->flags & SRI_CAN_FAILOVER) != 0);
+        addReplyBulkCString(c,"voted-leader");
+        addReplyBulkCString(c,ri->leader ? ri->leader : "?");
         fields++;
 
-        if (ri->flags & SRI_MASTER_DOWN) {
-            addReplyBulkCString(c,"subjective-leader");
-            addReplyBulkCString(c,ri->leader ? ri->leader : "?");
-            fields++;
-        }
+        addReplyBulkCString(c,"voted-leader-epoch");
+        addReplyBulkLongLong(c,ri->leader_epoch);
+        fields++;
     }
 
     setDeferredMultiBulkLength(c,mbl,fields*2);
@@ -2079,14 +2379,18 @@ void sentinelCommand(redisClient *c) {
             return;
         addReplyDictOfRedisInstances(c,ri->sentinels);
     } else if (!strcasecmp(c->argv[1]->ptr,"is-master-down-by-addr")) {
-        /* SENTINEL IS-MASTER-DOWN-BY-ADDR <ip> <port> */
+        /* SENTINEL IS-MASTER-DOWN-BY-ADDR <ip> <port> <current-epoch> <runid> */
         sentinelRedisInstance *ri;
+        long long req_epoch;
+        uint64_t leader_epoch = 0;
         char *leader = NULL;
         long port;
         int isdown = 0;
 
-        if (c->argc != 4) goto numargserr;
-        if (getLongFromObjectOrReply(c,c->argv[3],&port,NULL) != REDIS_OK)
+        if (c->argc != 6) goto numargserr;
+        if (getLongFromObjectOrReply(c,c->argv[3],&port,NULL) != REDIS_OK ||
+            getLongLongFromObjectOrReply(c,c->argv[4],&req_epoch,NULL)
+                                                              != REDIS_OK)
             return;
         ri = getSentinelRedisInstanceByAddrAndRunID(sentinel.masters,
             c->argv[2]->ptr,port,NULL);
@@ -2096,12 +2400,21 @@ void sentinelCommand(redisClient *c) {
         if (!sentinel.tilt && ri && (ri->flags & SRI_S_DOWN) &&
                                     (ri->flags & SRI_MASTER))
             isdown = 1;
-        if (ri) leader = sentinelGetSubjectiveLeader(ri);
 
-        /* Reply with a two-elements multi-bulk reply: down state, leader. */
-        addReplyMultiBulkLen(c,2);
+        /* Vote for the master (or fetch the previous vote) if the request
+         * includes a runid, otherwise the sender is not seeking for a vote. */
+        if (ri && ri->flags & SRI_MASTER && strcasecmp(c->argv[5]->ptr,"*")) {
+            leader = sentinelVoteLeader(ri,(uint64_t)req_epoch,
+                                            c->argv[5]->ptr,
+                                            &leader_epoch);
+        }
+
+        /* Reply with a three-elements multi-bulk reply:
+         * down state, leader, vote epoch. */
+        addReplyMultiBulkLen(c,3);
         addReply(c, isdown ? shared.cone : shared.czero);
-        addReplyBulkCString(c, leader ? leader : "?");
+        addReplyBulkCString(c, leader ? leader : "*");
+        addReplyLongLong(c, (long long)leader_epoch);
         if (leader) sdsfree(leader);
     } else if (!strcasecmp(c->argv[1]->ptr,"reset")) {
         /* SENTINEL RESET <pattern> */
@@ -2118,18 +2431,8 @@ void sentinelCommand(redisClient *c) {
         } else if (ri->info_refresh == 0) {
             addReplySds(c,sdsnew("-IDONTKNOW I have not enough information to reply. Please ask another Sentinel.\r\n"));
         } else {
-            sentinelAddr *addr = ri->addr;
-
-            /* If we are in the middle of a failover, and the slave was
-             * already successfully switched to master role, we can advertise
-             * the new address as slave in order to allow clients to talk
-             * with the new master ASAP. */
-            if ((ri->flags & SRI_FAILOVER_IN_PROGRESS) &&
-                ri->promoted_slave &&
-                ri->failover_state >= SENTINEL_FAILOVER_STATE_RECONF_SLAVES)
-            {
-                addr = ri->promoted_slave->addr;
-            }
+            sentinelAddr *addr = sentinelGetCurrentMasterAddress(ri);
+
             addReplyMultiBulkLen(c,2);
             addReplyBulkCString(c,addr->ip);
             addReplyBulkLongLong(c,addr->port);
@@ -2149,7 +2452,9 @@ void sentinelCommand(redisClient *c) {
             addReplySds(c,sdsnew("-NOGOODSLAVE No suitable slave to promote\r\n"));
             return;
         }
-        sentinelStartFailover(ri,SENTINEL_FAILOVER_STATE_WAIT_START);
+        redisLog(REDIS_WARNING,"Executing user requested FAILOVER of '%s'",
+            ri->name);
+        sentinelStartFailover(ri);
         ri->flags |= SRI_FORCE_FAILOVER;
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"pending-scripts")) {
@@ -2258,8 +2563,18 @@ void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
         sentinelKillLink(ri,ri->pc);
     }
 
-    /* Update the subjectively down flag. */
-    if (elapsed > ri->down_after_period) {
+    /* Update the subjectively down flag. We believe the instance is in SDOWN
+     * state if:
+     * 1) It is not replying.
+     * 2) We believe it is a master, it reports to be a slave for enough time
+     *    to meet the down_after_period, plus enough time to get two times
+     *    INFO report from the instance. */
+    if (elapsed > ri->down_after_period ||
+        (ri->flags & SRI_MASTER &&
+         ri->role_reported == SRI_SLAVE &&
+         mstime() - ri->role_reported_time >
+          (ri->down_after_period+SENTINEL_INFO_PERIOD*2)))
+    {
         /* Is subjectively down */
         if ((ri->flags & SRI_S_DOWN) == 0) {
             sentinelEvent(REDIS_WARNING,"+sdown",ri,"%@");
@@ -2324,29 +2639,44 @@ void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *p
     /* Ignore every error or unexpected reply.
      * Note that if the command returns an error for any reason we'll
      * end clearing the SRI_MASTER_DOWN flag for timeout anyway. */
-    if (r->type == REDIS_REPLY_ARRAY && r->elements == 2 &&
+    if (r->type == REDIS_REPLY_ARRAY && r->elements == 3 &&
         r->element[0]->type == REDIS_REPLY_INTEGER &&
-        r->element[1]->type == REDIS_REPLY_STRING)
+        r->element[1]->type == REDIS_REPLY_STRING &&
+        r->element[2]->type == REDIS_REPLY_INTEGER)
     {
         ri->last_master_down_reply_time = mstime();
         if (r->element[0]->integer == 1) {
             ri->flags |= SRI_MASTER_DOWN;
         } else {
             ri->flags &= ~SRI_MASTER_DOWN;
         }
-        sdsfree(ri->leader);
-        ri->leader = sdsnew(r->element[1]->str);
+        if (strcmp(r->element[1]->str,"*")) {
+            /* If the runid in the reply is not "*" the Sentinel actually
+             * replied with a vote. */
+            sdsfree(ri->leader);
+            ri->leader = sdsnew(r->element[1]->str);
+            ri->leader_epoch = r->element[2]->integer;
+        }
     }
 }
 
 /* If we think (subjectively) the master is down, we start sending
  * SENTINEL IS-MASTER-DOWN-BY-ADDR requests to other sentinels
  * in order to get the replies that allow to reach the quorum and
  * possibly also mark the master as objectively down. */
-void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master) {
+#define SENTINEL_ASK_FORCED (1<<0)
+void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int flags) {
     dictIterator *di;
     dictEntry *de;
 
+    /* Vote for myself if I see the master is already in ODOWN state. */
+    if (master->flags & SRI_O_DOWN) {
+        uint64_t leader_epoch;
+
+        sentinelVoteLeader(master,sentinel.current_epoch,server.runid,
+                                    &leader_epoch);
+    }
+
     di = dictGetIterator(master->sentinels);
     while((de = dictNext(di)) != NULL) {
         sentinelRedisInstance *ri = dictGetVal(de);
@@ -2366,158 +2696,149 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master) {
          * 1) We believe it is down, or there is a failover in progress.
          * 2) Sentinel is connected.
          * 3) We did not received the info within SENTINEL_ASK_PERIOD ms. */
-        if ((master->flags & (SRI_S_DOWN|SRI_FAILOVER_IN_PROGRESS)) == 0)
-            continue;
+        if ((master->flags & SRI_S_DOWN) == 0) continue;
         if (ri->flags & SRI_DISCONNECTED) continue;
-        if (mstime() - ri->last_master_down_reply_time < SENTINEL_ASK_PERIOD)
+        if (!(flags & SENTINEL_ASK_FORCED) &&
+            mstime() - ri->last_master_down_reply_time < SENTINEL_ASK_PERIOD)
             continue;
 
         /* Ask */
         ll2string(port,sizeof(port),master->addr->port);
         retval = redisAsyncCommand(ri->cc,
                     sentinelReceiveIsMasterDownReply, NULL,
-                    "SENTINEL is-master-down-by-addr %s %s",
-                    master->addr->ip, port);
+                    "SENTINEL is-master-down-by-addr %s %s %llu %s",
+                    master->addr->ip, port,
+                    sentinel.current_epoch,
+                    (master->failover_state > SENTINEL_FAILOVER_STATE_NONE) ?
+                    server.runid : "*");
         if (retval == REDIS_OK) ri->pending_commands++;
     }
     dictReleaseIterator(di);
 }
 
 /* =============================== FAILOVER ================================= */
 
-/* Given a master get the "subjective leader", that is, among all the sentinels
- * with given characteristics, the one with the lexicographically smaller
- * runid. The characteristics required are:
+/* Vote for the sentinel with 'req_runid' or return the old vote if already
+ * voted for the specifed 'req_epoch' or one greater.
  *
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
-char *sentinelGetSubjectiveLeader(sentinelRedisInstance *master) {
-    dictIterator *di;
-    dictEntry *de;
-    char **instance =
-        zmalloc(sizeof(char*)*(dictSize(master->sentinels)+1));
-    int instances = 0;
-    char *leader = NULL;
-
-    if (master->flags & SRI_CAN_FAILOVER) {
-        /* Add myself if I'm a Sentinel that can failover this master. */
-        instance[instances++] = server.runid;
+ * If a vote is not available returns NULL, otherwise return the Sentinel
+ * runid and populate the leader_epoch with the epoch of the vote. */
+char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
+    if (req_epoch > sentinel.current_epoch) {
+        sentinel.current_epoch = req_epoch;
+        sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+            (unsigned long long) sentinel.current_epoch);
     }
 
-    di = dictGetIterator(master->sentinels);
-    while((de = dictNext(di)) != NULL) {
-        sentinelRedisInstance *ri = dictGetVal(de);
-        mstime_t lag = mstime() - ri->last_avail_time;
-
-        if (lag > SENTINEL_INFO_VALIDITY_TIME ||
-            !(ri->flags & SRI_CAN_FAILOVER) ||
-            (ri->flags & SRI_DISCONNECTED) ||
-            ri->runid == NULL)
-            continue;
-        instance[instances++] = ri->runid;
+    if (master->leader_epoch < req_epoch && sentinel.current_epoch <= req_epoch)
+    {
+        sdsfree(master->leader);
+        master->leader = sdsnew(req_runid);
+        master->leader_epoch = sentinel.current_epoch;
+        sentinelEvent(REDIS_WARNING,"+vote-for-leader",master,"%s %llu",
+            master->leader, (unsigned long long) master->leader_epoch);
+        /* If we did not voted for ourselves, set the master failover start
+         * time to now, in order to force a delay before we can start a
+         * failover for the same master.
+         *
+         * The random addition is useful to desynchronize a bit the slaves
+         * and reduce the chance that no slave gets majority. */
+        if (strcasecmp(master->leader,server.runid))
+            master->failover_start_time = mstime() + rand() % 2000;
     }
-    dictReleaseIterator(di);
 
-    /* If we have at least one instance passing our checks, order the array
-     * by runid. */
-    if (instances) {
-        qsort(instance,instances,sizeof(char*),compareRunID);
-        leader = sdsnew(instance[0]);
-    }
-    zfree(instance);
-    return leader;
+    *leader_epoch = master->leader_epoch;
+    return master->leader ? sdsnew(master->leader) : NULL;
 }
 
 struct sentinelLeader {
     char *runid;
     unsigned long votes;
 };
 
-/* Helper function for sentinelGetObjectiveLeader, increment the counter
+/* Helper function for sentinelGetLeader, increment the counter
  * relative to the specified runid. */
-void sentinelObjectiveLeaderIncr(dict *counters, char *runid) {
+int sentinelLeaderIncr(dict *counters, char *runid) {
     dictEntry *de = dictFind(counters,runid);
     uint64_t oldval;
 
     if (de) {
         oldval = dictGetUnsignedIntegerVal(de);
         dictSetUnsignedIntegerVal(de,oldval+1);
+        return oldval+1;
     } else {
         de = dictAddRaw(counters,runid);
         redisAssert(de != NULL);
         dictSetUnsignedIntegerVal(de,1);
+        return 1;
     }
 }
 
-/* Scan all the Sentinels attached to this master to check what is the
- * most voted leader among Sentinels. */
-char *sentinelGetObjectiveLeader(sentinelRedisInstance *master) {
+/* Scan all the Sentinels attached to this master to check if there
+ * is a leader for the specified epoch.
+ *
+ * To be a leader for a given epoch, we should have the majorify of
+ * the Sentinels we know that reported the same instance as
+ * leader for the same epoch. */
+char *sentinelGetLeader(sentinelRedisInstance *master, uint64_t epoch) {
     dict *counters;
     dictIterator *di;
     dictEntry *de;
     unsigned int voters = 0, voters_quorum;
     char *myvote;
     char *winner = NULL;
+    uint64_t leader_epoch;
+    uint64_t max_votes = 0;
 
     redisAssert(master->flags & (SRI_O_DOWN|SRI_FAILOVER_IN_PROGRESS));
     counters = dictCreate(&leaderVotesDictType,NULL);
 
-    /* Count my vote. */
-    myvote = sentinelGetSubjectiveLeader(master);
-    if (myvote) {
-        sentinelObjectiveLeaderIncr(counters,myvote);
-        voters++;
-    }
-
     /* Count other sentinels votes */
     di = dictGetIterator(master->sentinels);
     while((de = dictNext(di)) != NULL) {
         sentinelRedisInstance *ri = dictGetVal(de);
-        if (ri->leader == NULL) continue;
-        /* If the failover is not already in progress we are only interested
-         * in Sentinels that believe the master is down. Otherwise the leader
-         * selection is useful for the "failover-takedown" when the original
-         * leader fails. In that case we consider all the voters. */
-        if (!(master->flags & SRI_FAILOVER_IN_PROGRESS) &&
-            !(ri->flags & SRI_MASTER_DOWN)) continue;
-        sentinelObjectiveLeaderIncr(counters,ri->leader);
+        if (ri->leader != NULL && ri->leader_epoch == sentinel.current_epoch)
+            sentinelLeaderIncr(counters,ri->leader);
         voters++;
     }
     dictReleaseIterator(di);
-    voters_quorum = voters/2+1;
 
     /* Check what's the winner. For the winner to win, it needs two conditions:
      * 1) Absolute majority between voters (50% + 1).
      * 2) And anyway at least master->quorum votes. */
-    {
-        uint64_t max_votes = 0; /* Max votes so far. */
+    di = dictGetIterator(counters);
+    while((de = dictNext(di)) != NULL) {
+        uint64_t votes = dictGetUnsignedIntegerVal(de);
 
-        di = dictGetIterator(counters);
-        while((de = dictNext(di)) != NULL) {
-            uint64_t votes = dictGetUnsignedIntegerVal(de);
+        if (votes > max_votes) {
+            max_votes = votes;
+            winner = dictGetKey(de);
+        }
+    }
+    dictReleaseIterator(di);
 
-            if (max_votes < votes) {
-                max_votes = votes;
-                winner = dictGetKey(de);
-            }
+    /* Count this Sentinel vote:
+     * if this Sentinel did not voted yet, either vote for the most
+     * common voted sentinel, or for itself if no vote exists at all. */
+    if (winner)
+        myvote = sentinelVoteLeader(master,epoch,winner,&leader_epoch);
+    else
+        myvote = sentinelVoteLeader(master,epoch,server.runid,&leader_epoch);
+
+    if (myvote && leader_epoch == epoch) {
+        uint64_t votes = sentinelLeaderIncr(counters,myvote);
+
+        if (votes > max_votes) {
+            max_votes = votes;
+            winner = myvote;
         }
-        dictReleaseIterator(di);
-        if (winner && (max_votes < voters_quorum || max_votes < master->quorum))
-            winner = NULL;
     }
+    voters++; /* Anyway, count me as one of the voters. */
+
+    voters_quorum = voters/2+1;
+    if (winner && (max_votes < voters_quorum || max_votes < master->quorum))
+        winner = NULL;
+
     winner = winner ? sdsnew(winner) : NULL;
     sdsfree(myvote);
     dictRelease(counters);
@@ -2558,100 +2879,44 @@ int sentinelSendSlaveOf(sentinelRedisInstance *ri, char *host, int port) {
     return REDIS_OK;
 }
 
-/* Setup the master state to start a failover as a leader.
- *
- * State can be either:
- *
- * SENTINEL_FAILOVER_STATE_WAIT_START: starts a failover from scratch.
- * SENTINEL_FAILOVER_STATE_RECONF_SLAVES: takedown a failed failover.
- */
-void sentinelStartFailover(sentinelRedisInstance *master, int state) {
+/* Setup the master state to start a failover. */
+void sentinelStartFailover(sentinelRedisInstance *master) {
     redisAssert(master->flags & SRI_MASTER);
-    redisAssert(state == SENTINEL_FAILOVER_STATE_WAIT_START ||
-                state == SENTINEL_FAILOVER_STATE_RECONF_SLAVES);
-
-    master->failover_state = state;
-    master->flags |= SRI_FAILOVER_IN_PROGRESS|SRI_I_AM_THE_LEADER;
-    sentinelEvent(REDIS_WARNING,"+failover-triggered",master,"%@");
-
-    /* Pick a random delay if it's a fresh failover (WAIT_START), and not
-     * a recovery of a failover started by another sentinel. */
-    if (master->failover_state == SENTINEL_FAILOVER_STATE_WAIT_START) {
-        master->failover_start_time = mstime() +
-            SENTINEL_FAILOVER_FIXED_DELAY +
-            (rand() % SENTINEL_FAILOVER_MAX_RANDOM_DELAY);
-        sentinelEvent(REDIS_WARNING,"+failover-state-wait-start",master,
-            "%@ #starting in %lld milliseconds",
-            master->failover_start_time-mstime());
-    }
+
+    master->failover_state = SENTINEL_FAILOVER_STATE_WAIT_START;
+    master->flags |= SRI_FAILOVER_IN_PROGRESS;
+    master->failover_epoch = ++sentinel.current_epoch;
+    sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
+        (unsigned long long) sentinel.current_epoch);
+    sentinelEvent(REDIS_WARNING,"+try-failover",master,"%@");
+    master->failover_start_time = mstime();
     master->failover_state_change_time = mstime();
 }
 
 /* This function checks if there are the conditions to start the failover,
  * that is:
  *
- * 1) Enough time has passed since O_DOWN.
- * 2) The master is marked as SRI_CAN_FAILOVER, so we can failover it.
- * 3) We are the objectively leader for this master.
+ * 1) Master must be in ODOWN condition.
+ * 2) No failover already in progress.
+ * 3) No failover already attempted recently.
+ * 
+ * We still don't know if we'll win the election so it is possible that we
+ * start the failover but that we'll not be able to act.
  *
- * If the conditions are met we flag the master as SRI_FAILOVER_IN_PROGRESS
- * and SRI_I_AM_THE_LEADER.
- */
-void sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
-    char *leader;
-    int isleader;
+ * Return non-zero if a failover was started. */
+int sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
+    /* We can't failover if the master is not in O_DOWN state. */
+    if (!(master->flags & SRI_O_DOWN)) return 0;
 
-    /* We can't failover if the master is not in O_DOWN state or if
-     * there is not already a failover in progress (to perform the
-     * takedown if the leader died) or if this Sentinel is not allowed
-     * to start a failover. */
-    if (!(master->flags & SRI_CAN_FAILOVER) ||
-        !(master->flags & (SRI_O_DOWN|SRI_FAILOVER_IN_PROGRESS))) return;
+    /* Failover already in progress? */
+    if (master->flags & SRI_FAILOVER_IN_PROGRESS) return 0;
 
-    leader = sentinelGetObjectiveLeader(master);
-    isleader = leader && strcasecmp(leader,server.runid) == 0;
-    sdsfree(leader);
+    /* Last failover attempt started too little time ago? */
+    if (mstime() - master->failover_start_time <
+        master->failover_timeout*2) return 0;
 
-    /* If I'm not the leader, I can't failover for sure. */
-    if (!isleader) return;
-
-    /* If the failover is already in progress there are two options... */
-    if (master->flags & SRI_FAILOVER_IN_PROGRESS) {
-        if (master->flags & SRI_I_AM_THE_LEADER) {
-            /* 1) I'm flagged as leader so I already started the failover.
-             *    Just return. */
-            return;
-        } else {
-            mstime_t elapsed = mstime() - master->failover_state_change_time;
-
-            /* 2) I'm the new leader, but I'm not flagged as leader in the
-             *    master: I did not started the failover, but the original
-             *    leader has no longer the leadership.
-             *
-             *    In this case if the failover appears to be lagging
-             *    for at least 25% of the configured failover timeout,
-             *    I can assume I can take control. Otherwise
-             *    it's better to return and wait more. */
-            if (elapsed < (master->failover_timeout/4)) return;
-            sentinelEvent(REDIS_WARNING,"+failover-takedown",master,"%@");
-            /* We have already an elected slave if we are in
-             * FAILOVER_IN_PROGRESS state, that is, the slave that we
-             * observed turning into a master. */
-            sentinelStartFailover(master,SENTINEL_FAILOVER_STATE_RECONF_SLAVES);
-            /* As an observer we flagged all the slaves as RECONF_SENT but
-             * now we are in charge of actually sending the reconfiguration
-             * command so let's clear this flag for all the instances. */
-            sentinelDelFlagsToDictOfRedisInstances(master->slaves,
-                SRI_RECONF_SENT);
-        }
-    } else {
-        /* Brand new failover as SRI_FAILOVER_IN_PROGRESS was not set.
-         *
-         * Do we have a slave to promote? Otherwise don't start a failover
-         * at all. */
-        if (sentinelSelectSlave(master) == NULL) return;
-        sentinelStartFailover(master,SENTINEL_FAILOVER_STATE_WAIT_START);
-    }
+    sentinelStartFailover(master);
+    return 1;
 }
 
 /* Select a suitable slave to promote. The current algorithm only uses
@@ -2672,6 +2937,9 @@ void sentinelStartFailoverIfNeeded(sentinelRedisInstance *master) {
  * NULL if no suitable slave was found.
  */
 
+/* Helper for sentinelSelectSlave(). This is used by qsort() in order to
+ * sort suitable slaves in a "better first" order, to take the first of
+ * the list. */
 int compareSlavesForPromotion(const void *a, const void *b) {
     sentinelRedisInstance **sa = (sentinelRedisInstance **)a,
                           **sb = (sentinelRedisInstance **)b;
@@ -2680,8 +2948,16 @@ int compareSlavesForPromotion(const void *a, const void *b) {
     if ((*sa)->slave_priority != (*sb)->slave_priority)
         return (*sa)->slave_priority - (*sb)->slave_priority;
 
-    /* If priority is the same, select the slave with that has the
-     * lexicographically smaller runid. Note that we try to handle runid
+    /* If priority is the same, select the slave with greater replication
+     * offset (processed more data frmo the master). */
+    if ((*sa)->slave_repl_offset > (*sb)->slave_repl_offset) {
+        return -1; /* a < b */
+    } else if ((*sa)->slave_repl_offset < (*sb)->slave_repl_offset) {
+        return 1; /* b > a */
+    }
+
+    /* If the replication offset is the same select the slave with that has
+     * the lexicographically smaller runid. Note that we try to handle runid
      * == NULL as there are old Redis versions that don't publish runid in
      * INFO. A NULL runid is considered bigger than any other runid. */
     sa_runid = (*sa)->runid;
@@ -2711,7 +2987,6 @@ sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master) {
         mstime_t info_validity_time = mstime()-SENTINEL_INFO_VALIDITY_TIME;
 
         if (slave->flags & (SRI_S_DOWN|SRI_O_DOWN|SRI_DISCONNECTED)) continue;
-        if (slave->flags & SRI_DEMOTE) continue; /* Old master not yet ready. */
         if (slave->last_avail_time < info_validity_time) continue;
         if (slave->slave_priority == 0) continue;
 
@@ -2736,34 +3011,41 @@ sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master) {
 
 /* ---------------- Failover state machine implementation ------------------- */
 void sentinelFailoverWaitStart(sentinelRedisInstance *ri) {
-    /* If we in "wait start" but the master is no longer in ODOWN nor in
-     * SDOWN condition we abort the failover. This is important as it
-     * prevents a useless failover in a a notable case of netsplit, where
-     * the sentinels are split from the redis instances. In this case
-     * the failover will not start while there is the split because no
-     * good slave can be reached. However when the split is resolved, we
-     * can go to waitstart if the slave is back reachable a few milliseconds
-     * before the master is. In that case when the master is back online
-     * we cancel the failover. */
-    if ((ri->flags & (SRI_S_DOWN|SRI_O_DOWN|SRI_FORCE_FAILOVER)) == 0) {
-        sentinelEvent(REDIS_WARNING,"-failover-abort-master-is-back",
-            ri,"%@");
-        sentinelAbortFailover(ri);
-        return;
-    }
+    char *leader;
+    int isleader;
 
-    /* Start the failover going to the next state if enough time has
-     * elapsed. */
-    if (mstime() >= ri->failover_start_time) {
-        ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
-        ri->failover_state_change_time = mstime();
-        sentinelEvent(REDIS_WARNING,"+failover-state-select-slave",ri,"%@");
+    /* Check if we are the leader for the failover epoch. */
+    leader = sentinelGetLeader(ri, ri->failover_epoch);
+    isleader = leader && strcasecmp(leader,server.runid) == 0;
+    sdsfree(leader);
+
+    /* If I'm not the leader, and it is not a forced failover via
+     * SENTINEL FAILOVER, then I can't continue with the failover. */
+    if (!isleader && !(ri->flags & SRI_FORCE_FAILOVER)) {
+        int election_timeout = SENTINEL_ELECTION_TIMEOUT;
+
+        /* The election timeout is the MIN between SENTINEL_ELECTION_TIMEOUT
+         * and the configured failover timeout. */
+        if (election_timeout > ri->failover_timeout)
+            election_timeout = ri->failover_timeout;
+        /* Abort the failover if I'm not the leader after some time. */
+        if (mstime() - ri->failover_start_time > election_timeout) {
+            sentinelEvent(REDIS_WARNING,"-failover-abort-not-elected",ri,"%@");
+            sentinelAbortFailover(ri);
+        }
+        return;
     }
+    sentinelEvent(REDIS_WARNING,"+elected-leader",ri,"%@");
+    ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
+    ri->failover_state_change_time = mstime();
+    sentinelEvent(REDIS_WARNING,"+failover-state-select-slave",ri,"%@");
 }
 
 void sentinelFailoverSelectSlave(sentinelRedisInstance *ri) {
     sentinelRedisInstance *slave = sentinelSelectSlave(ri);
 
+    /* We don't handle the timeout in this state as the function aborts
+     * the failover or go forward in the next state. */
     if (slave == NULL) {
         sentinelEvent(REDIS_WARNING,"-failover-abort-no-good-slave",ri,"%@");
         sentinelAbortFailover(ri);
@@ -2781,7 +3063,16 @@ void sentinelFailoverSelectSlave(sentinelRedisInstance *ri) {
 void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
     int retval;
 
-    if (ri->promoted_slave->flags & SRI_DISCONNECTED) return;
+    /* We can't send the command to the promoted slave if it is now
+     * disconnected. Retry again and again with this state until the timeout
+     * is reached, then abort the failover. */
+    if (ri->promoted_slave->flags & SRI_DISCONNECTED) {
+        if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
+            sentinelEvent(REDIS_WARNING,"-failover-abort-slave-timeout",ri,"%@");
+            sentinelAbortFailover(ri);
+        }
+        return;
+    }
 
     /* Send SLAVEOF NO ONE command to turn the slave into a master.
      * We actually register a generic callback for this command as we don't
@@ -2798,16 +3089,11 @@ void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
 /* We actually wait for promotion indirectly checking with INFO when the
  * slave turns into a master. */
 void sentinelFailoverWaitPromotion(sentinelRedisInstance *ri) {
-    mstime_t elapsed = mstime() - ri->failover_state_change_time;
-
-    if (elapsed >= SENTINEL_PROMOTION_RETRY_PERIOD) {
-        sentinelEvent(REDIS_WARNING,"-promotion-timeout",ri->promoted_slave,
-            "%@");
-        sentinelEvent(REDIS_WARNING,"+failover-state-select-slave",ri,"%@");
-        ri->failover_state = SENTINEL_FAILOVER_STATE_SELECT_SLAVE;
-        ri->failover_state_change_time = mstime();
-        ri->promoted_slave->flags &= ~SRI_PROMOTED;
-        ri->promoted_slave = NULL;
+    /* Just handle the timeout. Switching to the next state is handled
+     * by the function parsing the INFO command of the promoted slave. */
+    if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
+        sentinelEvent(REDIS_WARNING,"-failover-abort-slave-timeout",ri,"%@");
+        sentinelAbortFailover(ri);
     }
 }
 
@@ -2842,20 +3128,15 @@ void sentinelFailoverDetectEnd(sentinelRedisInstance *master) {
     }
 
     if (not_reconfigured == 0) {
-        int role = (master->flags & SRI_I_AM_THE_LEADER) ? SENTINEL_LEADER :
-                                                           SENTINEL_OBSERVER;
-
         sentinelEvent(REDIS_WARNING,"+failover-end",master,"%@");
         master->failover_state = SENTINEL_FAILOVER_STATE_UPDATE_CONFIG;
         master->failover_state_change_time = mstime();
-        sentinelCallClientReconfScript(master,role,"end",master->addr,
-            master->promoted_slave->addr);
     }
 
     /* If I'm the leader it is a good idea to send a best effort SLAVEOF
      * command to all the slaves still not reconfigured to replicate with
      * the new master. */
-    if (timeout && (master->flags & SRI_I_AM_THE_LEADER)) {
+    if (timeout) {
         dictIterator *di;
         dictEntry *de;
 
@@ -2932,6 +3213,8 @@ void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
         }
     }
     dictReleaseIterator(di);
+
+    /* Check if all the slaves are reconfigured and handle timeout. */
     sentinelFailoverDetectEnd(master);
 }
 
@@ -2955,17 +3238,6 @@ void sentinelFailoverSwitchToPromotedSlave(sentinelRedisInstance *master) {
     old_master_ip = sdsdup(master->addr->ip);
     old_master_port = master->addr->port;
     sentinelResetMasterAndChangeAddress(master,ref->addr->ip,ref->addr->port);
-    /* If this is a real switch, that is, we have master->promoted_slave not
-     * NULL, then we want to add the old master as a slave of the new master,
-     * but flagging it with SRI_DEMOTE so that we know we'll need to send
-     * SLAVEOF once the old master is reachable again. */
-    if (master != ref) {
-        /* Add the new slave, but don't generate a Sentinel event as it will
-         * happen later when finally the instance will claim to be a slave
-         * in the INFO output. */
-        createSentinelRedisInstance(NULL,SRI_SLAVE|SRI_DEMOTE,
-                    old_master_ip, old_master_port, master->quorum, master);
-    }
     sdsfree(old_master_ip);
 }
 
@@ -2990,84 +3262,27 @@ void sentinelFailoverStateMachine(sentinelRedisInstance *ri) {
         case SENTINEL_FAILOVER_STATE_RECONF_SLAVES:
             sentinelFailoverReconfNextSlave(ri);
             break;
-        case SENTINEL_FAILOVER_STATE_DETECT_END:
-            sentinelFailoverDetectEnd(ri);
-            break;
     }
 }
 
-/* Abort a failover in progress with the following steps:
- * 1) If this instance is the leaer send a SLAVEOF command to all the already
- *    reconfigured slaves if any to configure them to replicate with the
- *    original master.
- * 2) For both leaders and observers: clear the failover flags and state in
- *    the master instance.
- * 3) If there is already a promoted slave and we are the leader, and this
- *    slave is not DISCONNECTED, try to reconfigure it to replicate
- *    back to the master as well, sending a best effort SLAVEOF command.
- */
+/* Abort a failover in progress:
+ *
+ * This function can only be called before the promoted slave acknowledged
+ * the slave -> master switch. Otherwise the failover can't be aborted and
+ * will reach its end (possibly by timeout). */
 void sentinelAbortFailover(sentinelRedisInstance *ri) {
-    dictIterator *di;
-    dictEntry *de;
-    int sentinel_role;
-
     redisAssert(ri->flags & SRI_FAILOVER_IN_PROGRESS);
+    redisAssert(ri->failover_state <= SENTINEL_FAILOVER_STATE_WAIT_PROMOTION);
 
-    /* Clear failover related flags from slaves.
-     * Also if we are the leader make sure to send SLAVEOF commands to all the
-     * already reconfigured slaves in order to turn them back into slaves of
-     * the original master. */
-    di = dictGetIterator(ri->slaves);
-    while((de = dictNext(di)) != NULL) {
-        sentinelRedisInstance *slave = dictGetVal(de);
-        if ((ri->flags & SRI_I_AM_THE_LEADER) &&
-            !(slave->flags & SRI_DISCONNECTED) &&
-             (slave->flags & (SRI_PROMOTED|SRI_RECONF_SENT|SRI_RECONF_INPROG|
-                              SRI_RECONF_DONE)))
-        {
-            int retval;
-
-            retval = sentinelSendSlaveOf(slave,ri->addr->ip,ri->addr->port);
-            if (retval == REDIS_OK)
-                sentinelEvent(REDIS_NOTICE,"-slave-reconf-undo",slave,"%@");
-        }
-        slave->flags &= ~(SRI_RECONF_SENT|SRI_RECONF_INPROG|SRI_RECONF_DONE);
-    }
-    dictReleaseIterator(di);
-
-    sentinel_role = (ri->flags & SRI_I_AM_THE_LEADER) ? SENTINEL_LEADER :
-                                                        SENTINEL_OBSERVER;
-    ri->flags &= ~(SRI_FAILOVER_IN_PROGRESS|SRI_I_AM_THE_LEADER|SRI_FORCE_FAILOVER);
+    ri->flags &= ~(SRI_FAILOVER_IN_PROGRESS|SRI_FORCE_FAILOVER);
     ri->failover_state = SENTINEL_FAILOVER_STATE_NONE;
     ri->failover_state_change_time = mstime();
     if (ri->promoted_slave) {
-        sentinelCallClientReconfScript(ri,sentinel_role,"abort",
-            ri->promoted_slave->addr,ri->addr);
         ri->promoted_slave->flags &= ~SRI_PROMOTED;
         ri->promoted_slave = NULL;
     }
 }
 
-/* The following is called only for master instances and will abort the
- * failover process if:
- *
- * 1) The failover is in progress.
- * 2) We already promoted a slave.
- * 3) The promoted slave is in extended SDOWN condition.
- */
-void sentinelAbortFailoverIfNeeded(sentinelRedisInstance *ri) {
-    /* Failover is in progress? Do we have a promoted slave? */
-    if (!(ri->flags & SRI_FAILOVER_IN_PROGRESS) || !ri->promoted_slave) return;
-
-    /* Is the promoted slave into an extended SDOWN state? */
-    if (!(ri->promoted_slave->flags & SRI_S_DOWN) ||
-        (mstime() - ri->promoted_slave->s_down_since_time) <
-        (ri->down_after_period * SENTINEL_EXTENDED_SDOWN_MULTIPLIER)) return;
-
-    sentinelEvent(REDIS_WARNING,"-failover-abort-x-sdown",ri->promoted_slave,"%@");
-    sentinelAbortFailover(ri);
-}
-
 /* ======================== SENTINEL timer handler ==========================
  * This is the "main" our Sentinel, being sentinel completely non blocking
  * in design. The function is called every second.
@@ -3080,16 +3295,6 @@ void sentinelHandleRedisInstance(sentinelRedisInstance *ri) {
     sentinelReconnectInstance(ri);
     sentinelPingInstance(ri);
 
-    /* Masters and slaves */
-    if (ri->flags & (SRI_MASTER|SRI_SLAVE)) {
-        /* Nothing so far. */
-    }
-
-    /* Only masters */
-    if (ri->flags & SRI_MASTER) {
-        sentinelAskMasterStateToOtherSentinels(ri);
-    }
-
     /* ============== ACTING HALF ============= */
     /* We don't proceed with the acting half if we are in TILT mode.
      * TILT happens when we find something odd with the time, like a
@@ -3111,9 +3316,10 @@ void sentinelHandleRedisInstance(sentinelRedisInstance *ri) {
     /* Only masters */
     if (ri->flags & SRI_MASTER) {
         sentinelCheckObjectivelyDown(ri);
-        sentinelStartFailoverIfNeeded(ri);
+        if (sentinelStartFailoverIfNeeded(ri))
+            sentinelAskMasterStateToOtherSentinels(ri,SENTINEL_ASK_FORCED);
         sentinelFailoverStateMachine(ri);
-        sentinelAbortFailoverIfNeeded(ri);
+        sentinelAskMasterStateToOtherSentinels(ri,SENTINEL_NO_FLAGS);
     }
 }
 