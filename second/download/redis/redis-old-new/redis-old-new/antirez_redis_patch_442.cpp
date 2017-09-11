@@ -306,7 +306,7 @@ void serverLogRaw(int level, const char *msg) {
     const char *c = ".-*#";
     FILE *fp;
     char buf[64];
-    int rawmode = (level & REDIS_LOG_RAW);
+    int rawmode = (level & LL_RAW);
     int log_to_stdout = server.logfile[0] == '\0';
 
     level &= 0xff; /* clear flags */
@@ -347,7 +347,7 @@ void serverLogRaw(int level, const char *msg) {
  * the INFO output on crash. */
 void serverLog(int level, const char *fmt, ...) {
     va_list ap;
-    char msg[REDIS_MAX_LOGMSG_LEN];
+    char msg[LOG_MAX_LEN];
 
     if ((level&0xff) < server.verbosity) return;
 
@@ -663,10 +663,10 @@ int htNeedsResize(dict *dict) {
     size = dictSlots(dict);
     used = dictSize(dict);
     return (size && used && size > DICT_HT_INITIAL_SIZE &&
-            (used*100/size < REDIS_HT_MINFILL));
+            (used*100/size < HASHTABLE_MIN_FILL));
 }
 
-/* If the percentage of used slots in the HT reaches REDIS_HT_MINFILL
+/* If the percentage of used slots in the HT reaches HASHTABLE_MIN_FILL
  * we resize the hash table to save memory */
 void tryResizeHashTables(int dbid) {
     if (htNeedsResize(server.db[dbid].dict))
@@ -730,7 +730,7 @@ int activeExpireCycleTryExpire(redisDb *db, dictEntry *de, long long now) {
 
         propagateExpire(db,keyobj);
         dbDelete(db,keyobj);
-        notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
+        notifyKeyspaceEvent(NOTIFY_EXPIRED,
             "expired",keyobj,db->id);
         decrRefCount(keyobj);
         server.stat_expiredkeys++;
@@ -745,7 +745,7 @@ int activeExpireCycleTryExpire(redisDb *db, dictEntry *de, long long now) {
  * it will get more aggressive to avoid that too much memory is used by
  * keys that can be removed from the keyspace.
  *
- * No more than REDIS_DBCRON_DBS_PER_CALL databases are tested at every
+ * No more than CRON_DBS_PER_CALL databases are tested at every
  * iteration.
  *
  * This kind of call is used when Redis detects that timelimit_exit is
@@ -770,7 +770,7 @@ void activeExpireCycle(int type) {
     static long long last_fast_cycle = 0; /* When last fast cycle ran. */
 
     int j, iteration = 0;
-    int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
+    int dbs_per_call = CRON_DBS_PER_CALL;
     long long start = ustime(), timelimit;
 
     if (type == ACTIVE_EXPIRE_CYCLE_FAST) {
@@ -782,7 +782,7 @@ void activeExpireCycle(int type) {
         last_fast_cycle = start;
     }
 
-    /* We usually should test REDIS_DBCRON_DBS_PER_CALL per iteration, with
+    /* We usually should test CRON_DBS_PER_CALL per iteration, with
      * two exceptions:
      *
      * 1) Don't test more DBs than we have.
@@ -881,7 +881,7 @@ void activeExpireCycle(int type) {
 }
 
 unsigned int getLRUClock(void) {
-    return (mstime()/REDIS_LRU_CLOCK_RESOLUTION) & REDIS_LRU_CLOCK_MAX;
+    return (mstime()/LRU_CLOCK_RESOLUTION) & LRU_CLOCK_MAX;
 }
 
 /* Add a sample to the operations per second array of samples. */
@@ -896,7 +896,7 @@ void trackInstantaneousMetric(int metric, long long current_reading) {
     server.inst_metric[metric].samples[server.inst_metric[metric].idx] =
         ops_sec;
     server.inst_metric[metric].idx++;
-    server.inst_metric[metric].idx %= REDIS_METRIC_SAMPLES;
+    server.inst_metric[metric].idx %= STATS_METRIC_SAMPLES;
     server.inst_metric[metric].last_sample_time = mstime();
     server.inst_metric[metric].last_sample_count = current_reading;
 }
@@ -906,9 +906,9 @@ long long getInstantaneousMetric(int metric) {
     int j;
     long long sum = 0;
 
-    for (j = 0; j < REDIS_METRIC_SAMPLES; j++)
+    for (j = 0; j < STATS_METRIC_SAMPLES; j++)
         sum += server.inst_metric[metric].samples[j];
-    return sum / REDIS_METRIC_SAMPLES;
+    return sum / STATS_METRIC_SAMPLES;
 }
 
 /* Check for timeouts. Returns non-zero if the client was terminated.
@@ -919,16 +919,16 @@ int clientsCronHandleTimeout(client *c, mstime_t now_ms) {
     time_t now = now_ms/1000;
 
     if (server.maxidletime &&
-        !(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
-        !(c->flags & REDIS_MASTER) &&   /* no timeout for masters */
-        !(c->flags & REDIS_BLOCKED) &&  /* no timeout for BLPOP */
-        !(c->flags & REDIS_PUBSUB) &&   /* no timeout for Pub/Sub clients */
+        !(c->flags & CLIENT_SLAVE) &&    /* no timeout for slaves */
+        !(c->flags & CLIENT_MASTER) &&   /* no timeout for masters */
+        !(c->flags & CLIENT_BLOCKED) &&  /* no timeout for BLPOP */
+        !(c->flags & CLIENT_PUBSUB) &&   /* no timeout for Pub/Sub clients */
         (now - c->lastinteraction > server.maxidletime))
     {
-        serverLog(REDIS_VERBOSE,"Closing idle client");
+        serverLog(LL_VERBOSE,"Closing idle client");
         freeClient(c);
         return 1;
-    } else if (c->flags & REDIS_BLOCKED) {
+    } else if (c->flags & CLIENT_BLOCKED) {
         /* Blocked OPS timeout is handled with milliseconds resolution.
          * However note that the actual resolution is limited by
          * server.hz. */
@@ -958,7 +958,7 @@ int clientsCronResizeQueryBuffer(client *c) {
     /* There are two conditions to resize the query buffer:
      * 1) Query buffer is > BIG_ARG and too big for latest peak.
      * 2) Client is inactive and the buffer is bigger than 1k. */
-    if (((querybuf_size > REDIS_MBULK_BIG_ARG) &&
+    if (((querybuf_size > PROTO_MBULK_BIG_ARG) &&
          (querybuf_size/(c->querybuf_peak+1)) > 2) ||
          (querybuf_size > 1024 && idletime > 2))
     {
@@ -1026,7 +1026,7 @@ void databasesCron(void) {
          * cron loop iteration. */
         static unsigned int resize_db = 0;
         static unsigned int rehash_db = 0;
-        int dbs_per_call = REDIS_DBCRON_DBS_PER_CALL;
+        int dbs_per_call = CRON_DBS_PER_CALL;
         int j;
 
         /* Don't test more DBs than we have. */
@@ -1083,9 +1083,9 @@ void updateCachedTime(void) {
 
 int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     int j;
-    REDIS_NOTUSED(eventLoop);
-    REDIS_NOTUSED(id);
-    REDIS_NOTUSED(clientData);
+    UNUSED(eventLoop);
+    UNUSED(id);
+    UNUSED(clientData);
 
     /* Software watchdog: deliver the SIGALRM that will reach the signal
      * handler if we don't return here fast enough. */
@@ -1095,14 +1095,14 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     updateCachedTime();
 
     run_with_period(100) {
-        trackInstantaneousMetric(REDIS_METRIC_COMMAND,server.stat_numcommands);
-        trackInstantaneousMetric(REDIS_METRIC_NET_INPUT,
+        trackInstantaneousMetric(STATS_METRIC_COMMAND,server.stat_numcommands);
+        trackInstantaneousMetric(STATS_METRIC_NET_INPUT,
                 server.stat_net_input_bytes);
-        trackInstantaneousMetric(REDIS_METRIC_NET_OUTPUT,
+        trackInstantaneousMetric(STATS_METRIC_NET_OUTPUT,
                 server.stat_net_output_bytes);
     }
 
-    /* We have just REDIS_LRU_BITS bits per object for LRU information.
+    /* We have just LRU_BITS bits per object for LRU information.
      * So we use an (eventually wrapping) LRU clock.
      *
      * Note that even if the counter wraps it's not a big problem,
@@ -1112,7 +1112,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * not likely.
      *
      * Note that you can change the resolution altering the
-     * REDIS_LRU_CLOCK_RESOLUTION define. */
+     * LRU_CLOCK_RESOLUTION define. */
     server.lruclock = getLRUClock();
 
     /* Record the max memory used since the server was started. */
@@ -1126,7 +1126,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * not ok doing so inside the signal handler. */
     if (server.shutdown_asap) {
         if (prepareForShutdown(0) == C_OK) exit(0);
-        serverLog(REDIS_WARNING,"SIGTERM received but errors trying to shut down the server, check the logs for more information");
+        serverLog(LL_WARNING,"SIGTERM received but errors trying to shut down the server, check the logs for more information");
         server.shutdown_asap = 0;
     }
 
@@ -1139,7 +1139,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             used = dictSize(server.db[j].dict);
             vkeys = dictSize(server.db[j].expires);
             if (used || vkeys) {
-                serverLog(REDIS_VERBOSE,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
+                serverLog(LL_VERBOSE,"DB %d: %lld keys (%lld volatile) in %lld slots HT.",j,used,vkeys,size);
                 /* dictPrintStats(server.dict); */
             }
         }
@@ -1148,7 +1148,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     /* Show information about connected clients */
     if (!server.sentinel_mode) {
         run_with_period(5000) {
-            serverLog(REDIS_VERBOSE,
+            serverLog(LL_VERBOSE,
                 "%lu clients connected (%lu slaves), %zu bytes in use",
                 listLength(server.clients)-listLength(server.slaves),
                 listLength(server.slaves),
@@ -1186,7 +1186,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             } else if (pid == server.aof_child_pid) {
                 backgroundRewriteDoneHandler(exitcode,bysignal);
             } else {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "Warning, detected child with unmatched pid: %ld",
                     (long)pid);
             }
@@ -1201,14 +1201,14 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             /* Save if we reached the given amount of changes,
              * the given amount of seconds, and if the latest bgsave was
              * successful or if, in case of an error, at least
-             * REDIS_BGSAVE_RETRY_DELAY seconds already elapsed. */
+             * CONFIG_BGSAVE_RETRY_DELAY seconds already elapsed. */
             if (server.dirty >= sp->changes &&
                 server.unixtime-server.lastsave > sp->seconds &&
                 (server.unixtime-server.lastbgsave_try >
-                 REDIS_BGSAVE_RETRY_DELAY ||
+                 CONFIG_BGSAVE_RETRY_DELAY ||
                  server.lastbgsave_status == C_OK))
             {
-                serverLog(REDIS_NOTICE,"%d changes in %d seconds. Saving...",
+                serverLog(LL_NOTICE,"%d changes in %d seconds. Saving...",
                     sp->changes, (int)sp->seconds);
                 rdbSaveBackground(server.rdb_filename);
                 break;
@@ -1225,7 +1225,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                             server.aof_rewrite_base_size : 1;
             long long growth = (server.aof_current_size*100/base) - 100;
             if (growth >= server.aof_rewrite_perc) {
-                serverLog(REDIS_NOTICE,"Starting automatic rewriting of AOF on %lld%% growth",growth);
+                serverLog(LL_NOTICE,"Starting automatic rewriting of AOF on %lld%% growth",growth);
                 rewriteAppendOnlyFileBackground();
             }
          }
@@ -1278,7 +1278,7 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
  * main loop of the event driven library, that is, before to sleep
  * for ready file descriptors. */
 void beforeSleep(struct aeEventLoop *eventLoop) {
-    REDIS_NOTUSED(eventLoop);
+    UNUSED(eventLoop);
 
     /* Call the Redis Cluster before sleep function. Note that this function
      * may change the state of Redis Cluster (from ok to fail or vice versa),
@@ -1373,7 +1373,7 @@ void createSharedObjects(void) {
     shared.colon = createObject(OBJ_STRING,sdsnew(":"));
     shared.plus = createObject(OBJ_STRING,sdsnew("+"));
 
-    for (j = 0; j < REDIS_SHARED_SELECT_CMDS; j++) {
+    for (j = 0; j < PROTO_SHARED_SELECT_CMDS; j++) {
         char dictid_str[64];
         int dictid_len;
 
@@ -1393,11 +1393,11 @@ void createSharedObjects(void) {
     shared.rpop = createStringObject("RPOP",4);
     shared.lpop = createStringObject("LPOP",4);
     shared.lpush = createStringObject("LPUSH",5);
-    for (j = 0; j < REDIS_SHARED_INTEGERS; j++) {
+    for (j = 0; j < OBJ_SHARED_INTEGERS; j++) {
         shared.integers[j] = createObject(OBJ_STRING,(void*)(long)j);
         shared.integers[j]->encoding = OBJ_ENCODING_INT;
     }
-    for (j = 0; j < REDIS_SHARED_BULKHDR_LEN; j++) {
+    for (j = 0; j < OBJ_SHARED_BULKHDR_LEN; j++) {
         shared.mbulkhdr[j] = createObject(OBJ_STRING,
             sdscatprintf(sdsempty(),"*%d\r\n",j));
         shared.bulkhdr[j] = createObject(OBJ_STRING,
@@ -1414,24 +1414,24 @@ void createSharedObjects(void) {
 void initServerConfig(void) {
     int j;
 
-    getRandomHexChars(server.runid,REDIS_RUN_ID_SIZE);
+    getRandomHexChars(server.runid,CONFIG_RUN_ID_SIZE);
     server.configfile = NULL;
     server.hz = CONFIG_DEFAULT_HZ;
-    server.runid[REDIS_RUN_ID_SIZE] = '\0';
+    server.runid[CONFIG_RUN_ID_SIZE] = '\0';
     server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
-    server.port = REDIS_SERVERPORT;
-    server.tcp_backlog = REDIS_TCP_BACKLOG;
+    server.port = CONFIG_DEFAULT_SERVER_PORT;
+    server.tcp_backlog = CONFIG_DEFAULT_TCP_BACKLOG;
     server.bindaddr_count = 0;
     server.unixsocket = NULL;
     server.unixsocketperm = CONFIG_DEFAULT_UNIX_SOCKET_PERM;
     server.ipfd_count = 0;
     server.sofd = -1;
     server.dbnum = CONFIG_DEFAULT_DBNUM;
     server.verbosity = CONFIG_DEFAULT_VERBOSITY;
-    server.maxidletime = REDIS_MAXIDLETIME;
+    server.maxidletime = CONFIG_DEFAULT_CLIENT_TIMEOUT;
     server.tcpkeepalive = CONFIG_DEFAULT_TCP_KEEPALIVE;
     server.active_expire_enabled = 1;
-    server.client_max_querybuf_len = REDIS_MAX_QUERYBUF_LEN;
+    server.client_max_querybuf_len = PROTO_MAX_QUERYBUF_LEN;
     server.saveparams = NULL;
     server.loading = 0;
     server.logfile = zstrdup(CONFIG_DEFAULT_LOGFILE);
@@ -1440,12 +1440,12 @@ void initServerConfig(void) {
     server.syslog_facility = LOG_LOCAL0;
     server.daemonize = CONFIG_DEFAULT_DAEMONIZE;
     server.supervised = 0;
-    server.supervised_mode = REDIS_SUPERVISED_NONE;
-    server.aof_state = REDIS_AOF_OFF;
+    server.supervised_mode = SUPERVISED_NONE;
+    server.aof_state = AOF_OFF;
     server.aof_fsync = CONFIG_DEFAULT_AOF_FSYNC;
     server.aof_no_fsync_on_rewrite = CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE;
-    server.aof_rewrite_perc = REDIS_AOF_REWRITE_PERC;
-    server.aof_rewrite_min_size = REDIS_AOF_REWRITE_MIN_SIZE;
+    server.aof_rewrite_perc = AOF_REWRITE_PERC;
+    server.aof_rewrite_min_size = AOF_REWRITE_MIN_SIZE;
     server.aof_rewrite_base_size = 0;
     server.aof_rewrite_scheduled = 0;
     server.aof_last_fsync = time(NULL);
@@ -1481,8 +1481,8 @@ void initServerConfig(void) {
     server.zset_max_ziplist_value = OBJ_ZSET_MAX_ZIPLIST_VALUE;
     server.hll_sparse_max_bytes = CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES;
     server.shutdown_asap = 0;
-    server.repl_ping_slave_period = REDIS_REPL_PING_SLAVE_PERIOD;
-    server.repl_timeout = REDIS_REPL_TIMEOUT;
+    server.repl_ping_slave_period = CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD;
+    server.repl_timeout = CONFIG_DEFAULT_REPL_TIMEOUT;
     server.repl_min_slaves_to_write = CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE;
     server.repl_min_slaves_max_lag = CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG;
     server.cluster_enabled = 0;
@@ -1492,7 +1492,7 @@ void initServerConfig(void) {
     server.cluster_require_full_coverage = REDIS_CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE;
     server.cluster_configfile = zstrdup(CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
     server.lua_caller = NULL;
-    server.lua_time_limit = REDIS_LUA_TIME_LIMIT;
+    server.lua_time_limit = LUA_SCRIPT_TIME_LIMIT;
     server.lua_client = NULL;
     server.lua_timedout = 0;
     server.migrate_cached_sockets = dictCreate(&migrateCacheDictType,NULL);
@@ -1512,8 +1512,8 @@ void initServerConfig(void) {
     server.master = NULL;
     server.cached_master = NULL;
     server.repl_master_initial_offset = -1;
-    server.repl_state = REDIS_REPL_NONE;
-    server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
+    server.repl_state = REPL_STATE_NONE;
+    server.repl_syncio_timeout = CONFIG_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA;
     server.repl_slave_ro = CONFIG_DEFAULT_SLAVE_READ_ONLY;
     server.repl_down_since = 0; /* Never connected, repl is down since EVER. */
@@ -1533,7 +1533,7 @@ void initServerConfig(void) {
     server.repl_no_slaves_since = time(NULL);
 
     /* Client output buffer limits */
-    for (j = 0; j < REDIS_CLIENT_TYPE_COUNT; j++)
+    for (j = 0; j < CLIENT_TYPE_COUNT; j++)
         server.client_obuf_limits[j] = clientBufferLimitsDefaults[j];
 
     /* Double constants initialization */
@@ -1556,8 +1556,8 @@ void initServerConfig(void) {
     server.sremCommand = lookupCommandByCString("srem");
 
     /* Slow log */
-    server.slowlog_log_slower_than = REDIS_SLOWLOG_LOG_SLOWER_THAN;
-    server.slowlog_max_len = REDIS_SLOWLOG_MAX_LEN;
+    server.slowlog_log_slower_than = CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN;
+    server.slowlog_max_len = CONFIG_DEFAULT_SLOWLOG_MAX_LEN;
 
     /* Latency monitor */
     server.latency_monitor_threshold = CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD;
@@ -1572,20 +1572,20 @@ void initServerConfig(void) {
 
 /* This function will try to raise the max number of open files accordingly to
  * the configured max number of clients. It also reserves a number of file
- * descriptors (REDIS_MIN_RESERVED_FDS) for extra operations of
+ * descriptors (CONFIG_MIN_RESERVED_FDS) for extra operations of
  * persistence, listening sockets, log files and so forth.
  *
  * If it will not be possible to set the limit accordingly to the configured
  * max number of clients, the function will do the reverse setting
  * server.maxclients to the value that we can actually handle. */
 void adjustOpenFilesLimit(void) {
-    rlim_t maxfiles = server.maxclients+REDIS_MIN_RESERVED_FDS;
+    rlim_t maxfiles = server.maxclients+CONFIG_MIN_RESERVED_FDS;
     struct rlimit limit;
 
     if (getrlimit(RLIMIT_NOFILE,&limit) == -1) {
-        serverLog(REDIS_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
+        serverLog(LL_WARNING,"Unable to obtain the current NOFILE limit (%s), assuming 1024 and setting the max clients configuration accordingly.",
             strerror(errno));
-        server.maxclients = 1024-REDIS_MIN_RESERVED_FDS;
+        server.maxclients = 1024-CONFIG_MIN_RESERVED_FDS;
     } else {
         rlim_t oldlimit = limit.rlim_cur;
 
@@ -1618,30 +1618,30 @@ void adjustOpenFilesLimit(void) {
 
             if (bestlimit < maxfiles) {
                 int old_maxclients = server.maxclients;
-                server.maxclients = bestlimit-REDIS_MIN_RESERVED_FDS;
+                server.maxclients = bestlimit-CONFIG_MIN_RESERVED_FDS;
                 if (server.maxclients < 1) {
-                    serverLog(REDIS_WARNING,"Your current 'ulimit -n' "
+                    serverLog(LL_WARNING,"Your current 'ulimit -n' "
                         "of %llu is not enough for Redis to start. "
                         "Please increase your open file limit to at least "
                         "%llu. Exiting.",
                         (unsigned long long) oldlimit,
                         (unsigned long long) maxfiles);
                     exit(1);
                 }
-                serverLog(REDIS_WARNING,"You requested maxclients of %d "
+                serverLog(LL_WARNING,"You requested maxclients of %d "
                     "requiring at least %llu max file descriptors.",
                     old_maxclients,
                     (unsigned long long) maxfiles);
-                serverLog(REDIS_WARNING,"Redis can't set maximum open files "
+                serverLog(LL_WARNING,"Redis can't set maximum open files "
                     "to %llu because of OS error: %s.",
                     (unsigned long long) maxfiles, strerror(setrlimit_error));
-                serverLog(REDIS_WARNING,"Current maximum open files is %llu. "
+                serverLog(LL_WARNING,"Current maximum open files is %llu. "
                     "maxclients has been reduced to %d to compensate for "
                     "low ulimit. "
                     "If you need higher maxclients increase 'ulimit -n'.",
                     (unsigned long long) bestlimit, server.maxclients);
             } else {
-                serverLog(REDIS_NOTICE,"Increased maximum number of open files "
+                serverLog(LL_NOTICE,"Increased maximum number of open files "
                     "to %llu (it was originally set to %llu).",
                     (unsigned long long) maxfiles,
                     (unsigned long long) oldlimit);
@@ -1660,7 +1660,7 @@ void checkTcpBacklogSettings(void) {
     if (fgets(buf,sizeof(buf),fp) != NULL) {
         int somaxconn = atoi(buf);
         if (somaxconn > 0 && somaxconn < server.tcp_backlog) {
-            serverLog(REDIS_WARNING,"WARNING: The TCP backlog setting of %d cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of %d.", server.tcp_backlog, somaxconn);
+            serverLog(LL_WARNING,"WARNING: The TCP backlog setting of %d cannot be enforced because /proc/sys/net/core/somaxconn is set to the lower value of %d.", server.tcp_backlog, somaxconn);
         }
     }
     fclose(fp);
@@ -1721,7 +1721,7 @@ int listenToPort(int port, int *fds, int *count) {
                 server.tcp_backlog);
         }
         if (fds[*count] == ANET_ERR) {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Creating Server TCP listening socket %s:%d: %s",
                 server.bindaddr[j] ? server.bindaddr[j] : "*",
                 port, server.neterr);
@@ -1751,7 +1751,7 @@ void resetServerStats(void) {
     server.stat_sync_full = 0;
     server.stat_sync_partial_ok = 0;
     server.stat_sync_partial_err = 0;
-    for (j = 0; j < REDIS_METRIC_COUNT; j++) {
+    for (j = 0; j < STATS_METRIC_COUNT; j++) {
         server.inst_metric[j].idx = 0;
         server.inst_metric[j].last_sample_time = mstime();
         server.inst_metric[j].last_sample_count = 0;
@@ -1791,7 +1791,7 @@ void initServer(void) {
 
     createSharedObjects();
     adjustOpenFilesLimit();
-    server.el = aeCreateEventLoop(server.maxclients+REDIS_EVENTLOOP_FDSET_INCR);
+    server.el = aeCreateEventLoop(server.maxclients+CONFIG_FDSET_INCR);
     server.db = zmalloc(sizeof(redisDb)*server.dbnum);
 
     /* Open the TCP listening socket for the user commands. */
@@ -1805,15 +1805,15 @@ void initServer(void) {
         server.sofd = anetUnixServer(server.neterr,server.unixsocket,
             server.unixsocketperm, server.tcp_backlog);
         if (server.sofd == ANET_ERR) {
-            serverLog(REDIS_WARNING, "Opening Unix socket: %s", server.neterr);
+            serverLog(LL_WARNING, "Opening Unix socket: %s", server.neterr);
             exit(1);
         }
         anetNonBlock(NULL,server.sofd);
     }
 
     /* Abort if there are no listening sockets at all. */
     if (server.ipfd_count == 0 && server.sofd < 0) {
-        serverLog(REDIS_WARNING, "Configured to not listen anywhere, exiting.");
+        serverLog(LL_WARNING, "Configured to not listen anywhere, exiting.");
         exit(1);
     }
 
@@ -1835,7 +1835,7 @@ void initServer(void) {
     server.cronloops = 0;
     server.rdb_child_pid = -1;
     server.aof_child_pid = -1;
-    server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
+    server.rdb_child_type = RDB_CHILD_TYPE_NONE;
     aofRewriteBufferReset();
     server.aof_buf = sdsempty();
     server.lastsave = time(NULL); /* At startup we consider the DB saved. */
@@ -1857,7 +1857,7 @@ void initServer(void) {
     /* Create the serverCron() time event, that's our main way to process
      * background operations. */
     if(aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL) == AE_ERR) {
-        redisPanic("Can't create the serverCron time event.");
+        serverPanic("Can't create the serverCron time event.");
         exit(1);
     }
 
@@ -1867,19 +1867,19 @@ void initServer(void) {
         if (aeCreateFileEvent(server.el, server.ipfd[j], AE_READABLE,
             acceptTcpHandler,NULL) == AE_ERR)
             {
-                redisPanic(
+                serverPanic(
                     "Unrecoverable error creating server.ipfd file event.");
             }
     }
     if (server.sofd > 0 && aeCreateFileEvent(server.el,server.sofd,AE_READABLE,
-        acceptUnixHandler,NULL) == AE_ERR) redisPanic("Unrecoverable error creating server.sofd file event.");
+        acceptUnixHandler,NULL) == AE_ERR) serverPanic("Unrecoverable error creating server.sofd file event.");
 
     /* Open the AOF file if needed. */
-    if (server.aof_state == REDIS_AOF_ON) {
+    if (server.aof_state == AOF_ON) {
         server.aof_fd = open(server.aof_filename,
                                O_WRONLY|O_APPEND|O_CREAT,0644);
         if (server.aof_fd == -1) {
-            serverLog(REDIS_WARNING, "Can't open the append-only file: %s",
+            serverLog(LL_WARNING, "Can't open the append-only file: %s",
                 strerror(errno));
             exit(1);
         }
@@ -1890,9 +1890,9 @@ void initServer(void) {
      * at 3 GB using maxmemory with 'noeviction' policy'. This avoids
      * useless crashes of the Redis instance for out of memory. */
     if (server.arch_bits == 32 && server.maxmemory == 0) {
-        serverLog(REDIS_WARNING,"Warning: 32 bit instance detected but no memory limit set. Setting 3 GB maxmemory limit with 'noeviction' policy now.");
+        serverLog(LL_WARNING,"Warning: 32 bit instance detected but no memory limit set. Setting 3 GB maxmemory limit with 'noeviction' policy now.");
         server.maxmemory = 3072LL*(1024*1024); /* 3 GB */
-        server.maxmemory_policy = REDIS_MAXMEMORY_NO_EVICTION;
+        server.maxmemory_policy = MAXMEMORY_NO_EVICTION;
     }
 
     if (server.cluster_enabled) clusterInit();
@@ -1916,20 +1916,20 @@ void populateCommandTable(void) {
 
         while(*f != '\0') {
             switch(*f) {
-            case 'w': c->flags |= REDIS_CMD_WRITE; break;
-            case 'r': c->flags |= REDIS_CMD_READONLY; break;
-            case 'm': c->flags |= REDIS_CMD_DENYOOM; break;
-            case 'a': c->flags |= REDIS_CMD_ADMIN; break;
-            case 'p': c->flags |= REDIS_CMD_PUBSUB; break;
-            case 's': c->flags |= REDIS_CMD_NOSCRIPT; break;
-            case 'R': c->flags |= REDIS_CMD_RANDOM; break;
-            case 'S': c->flags |= REDIS_CMD_SORT_FOR_SCRIPT; break;
-            case 'l': c->flags |= REDIS_CMD_LOADING; break;
-            case 't': c->flags |= REDIS_CMD_STALE; break;
-            case 'M': c->flags |= REDIS_CMD_SKIP_MONITOR; break;
-            case 'k': c->flags |= REDIS_CMD_ASKING; break;
-            case 'F': c->flags |= REDIS_CMD_FAST; break;
-            default: redisPanic("Unsupported command flag"); break;
+            case 'w': c->flags |= CMD_WRITE; break;
+            case 'r': c->flags |= CMD_READONLY; break;
+            case 'm': c->flags |= CMD_DENYOOM; break;
+            case 'a': c->flags |= CMD_ADMIN; break;
+            case 'p': c->flags |= CMD_PUBSUB; break;
+            case 's': c->flags |= CMD_NOSCRIPT; break;
+            case 'R': c->flags |= CMD_RANDOM; break;
+            case 'S': c->flags |= CMD_SORT_FOR_SCRIPT; break;
+            case 'l': c->flags |= CMD_LOADING; break;
+            case 't': c->flags |= CMD_STALE; break;
+            case 'M': c->flags |= CMD_SKIP_MONITOR; break;
+            case 'k': c->flags |= CMD_ASKING; break;
+            case 'F': c->flags |= CMD_FAST; break;
+            default: serverPanic("Unsupported command flag"); break;
             }
             f++;
         }
@@ -2024,19 +2024,19 @@ struct redisCommand *lookupCommandOrOriginal(sds name) {
  * to AOF and Slaves.
  *
  * flags are an xor between:
- * + REDIS_PROPAGATE_NONE (no propagation of command at all)
- * + REDIS_PROPAGATE_AOF (propagate into the AOF file if is enabled)
- * + REDIS_PROPAGATE_REPL (propagate into the replication link)
+ * + PROPAGATE_NONE (no propagation of command at all)
+ * + PROPAGATE_AOF (propagate into the AOF file if is enabled)
+ * + PROPAGATE_REPL (propagate into the replication link)
  *
  * This should not be used inside commands implementation. Use instead
  * alsoPropagate(), preventCommandPropagation(), forceCommandPropagation().
  */
 void propagate(struct redisCommand *cmd, int dbid, robj **argv, int argc,
                int flags)
 {
-    if (server.aof_state != REDIS_AOF_OFF && flags & REDIS_PROPAGATE_AOF)
+    if (server.aof_state != AOF_OFF && flags & PROPAGATE_AOF)
         feedAppendOnlyFile(cmd,dbid,argv,argc);
-    if (flags & REDIS_PROPAGATE_REPL)
+    if (flags & PROPAGATE_REPL)
         replicationFeedSlaves(server.slaves,dbid,argv,argc);
 }
 
@@ -2072,15 +2072,15 @@ void alsoPropagate(struct redisCommand *cmd, int dbid, robj **argv, int argc,
  * Redis command implementation in order to to force the propagation of a
  * specific command execution into AOF / Replication. */
 void forceCommandPropagation(client *c, int flags) {
-    if (flags & REDIS_PROPAGATE_REPL) c->flags |= REDIS_FORCE_REPL;
-    if (flags & REDIS_PROPAGATE_AOF) c->flags |= REDIS_FORCE_AOF;
+    if (flags & PROPAGATE_REPL) c->flags |= CLIENT_FORCE_REPL;
+    if (flags & PROPAGATE_AOF) c->flags |= CLIENT_FORCE_AOF;
 }
 
 /* Avoid that the executed command is propagated at all. This way we
  * are free to just propagate what we want using the alsoPropagate()
  * API. */
 void preventCommandPropagation(client *c) {
-    c->flags |= REDIS_PREVENT_PROP;
+    c->flags |= CLIENT_PREVENT_PROP;
 }
 
 /* Call() is the core of Redis execution of a command */
@@ -2092,13 +2092,13 @@ void call(client *c, int flags) {
      * not generated from reading an AOF. */
     if (listLength(server.monitors) &&
         !server.loading &&
-        !(c->cmd->flags & (REDIS_CMD_SKIP_MONITOR|REDIS_CMD_ADMIN)))
+        !(c->cmd->flags & (CMD_SKIP_MONITOR|CMD_ADMIN)))
     {
         replicationFeedMonitors(c,server.monitors,c->db->id,c->argv,c->argc);
     }
 
     /* Call the command. */
-    c->flags &= ~(REDIS_FORCE_AOF|REDIS_FORCE_REPL);
+    c->flags &= ~(CLIENT_FORCE_AOF|CLIENT_FORCE_REPL);
     redisOpArrayInit(&server.also_propagate);
     dirty = server.dirty;
     start = ustime();
@@ -2109,58 +2109,58 @@ void call(client *c, int flags) {
 
     /* When EVAL is called loading the AOF we don't want commands called
      * from Lua to go into the slowlog or to populate statistics. */
-    if (server.loading && c->flags & REDIS_LUA_CLIENT)
-        flags &= ~(REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);
+    if (server.loading && c->flags & CLIENT_LUA)
+        flags &= ~(CMD_CALL_SLOWLOG | CMD_CALL_STATS);
 
     /* If the caller is Lua, we want to force the EVAL caller to propagate
      * the script if the command flag or client flag are forcing the
      * propagation. */
-    if (c->flags & REDIS_LUA_CLIENT && server.lua_caller) {
-        if (c->flags & REDIS_FORCE_REPL)
-            server.lua_caller->flags |= REDIS_FORCE_REPL;
-        if (c->flags & REDIS_FORCE_AOF)
-            server.lua_caller->flags |= REDIS_FORCE_AOF;
+    if (c->flags & CLIENT_LUA && server.lua_caller) {
+        if (c->flags & CLIENT_FORCE_REPL)
+            server.lua_caller->flags |= CLIENT_FORCE_REPL;
+        if (c->flags & CLIENT_FORCE_AOF)
+            server.lua_caller->flags |= CLIENT_FORCE_AOF;
     }
 
     /* Log the command into the Slow log if needed, and populate the
      * per-command statistics that we show in INFO commandstats. */
-    if (flags & REDIS_CALL_SLOWLOG && c->cmd->proc != execCommand) {
-        char *latency_event = (c->cmd->flags & REDIS_CMD_FAST) ?
+    if (flags & CMD_CALL_SLOWLOG && c->cmd->proc != execCommand) {
+        char *latency_event = (c->cmd->flags & CMD_FAST) ?
                               "fast-command" : "command";
         latencyAddSampleIfNeeded(latency_event,duration/1000);
         slowlogPushEntryIfNeeded(c->argv,c->argc,duration);
     }
-    if (flags & REDIS_CALL_STATS) {
+    if (flags & CMD_CALL_STATS) {
         c->cmd->microseconds += duration;
         c->cmd->calls++;
     }
 
     /* Propagate the command into the AOF and replication link */
-    if (flags & REDIS_CALL_PROPAGATE && (c->flags & REDIS_PREVENT_PROP) == 0) {
-        int flags = REDIS_PROPAGATE_NONE;
+    if (flags & CMD_CALL_PROPAGATE && (c->flags & CLIENT_PREVENT_PROP) == 0) {
+        int flags = PROPAGATE_NONE;
 
-        if (c->flags & REDIS_FORCE_REPL) flags |= REDIS_PROPAGATE_REPL;
-        if (c->flags & REDIS_FORCE_AOF) flags |= REDIS_PROPAGATE_AOF;
+        if (c->flags & CLIENT_FORCE_REPL) flags |= PROPAGATE_REPL;
+        if (c->flags & CLIENT_FORCE_AOF) flags |= PROPAGATE_AOF;
         if (dirty)
-            flags |= (REDIS_PROPAGATE_REPL | REDIS_PROPAGATE_AOF);
-        if (flags != REDIS_PROPAGATE_NONE)
+            flags |= (PROPAGATE_REPL | PROPAGATE_AOF);
+        if (flags != PROPAGATE_NONE)
             propagate(c->cmd,c->db->id,c->argv,c->argc,flags);
     }
 
     /* Restore the old replication flags, since call can be executed
      * recursively. */
-    c->flags &= ~(REDIS_FORCE_AOF|REDIS_FORCE_REPL|REDIS_PREVENT_PROP);
+    c->flags &= ~(CLIENT_FORCE_AOF|CLIENT_FORCE_REPL|CLIENT_PREVENT_PROP);
     c->flags |= client_old_flags &
-        (REDIS_FORCE_AOF|REDIS_FORCE_REPL|REDIS_PREVENT_PROP);
+        (CLIENT_FORCE_AOF|CLIENT_FORCE_REPL|CLIENT_PREVENT_PROP);
 
     /* Handle the alsoPropagate() API to handle commands that want to propagate
      * multiple separated commands. Note that alsoPropagate() is not affected
-     * by REDIS_PREVENT_PROP flag. */
+     * by CLIENT_PREVENT_PROP flag. */
     if (server.also_propagate.numops) {
         int j;
         redisOp *rop;
 
-        if (flags & REDIS_CALL_PROPAGATE) {
+        if (flags & CMD_CALL_PROPAGATE) {
             for (j = 0; j < server.also_propagate.numops; j++) {
                 rop = &server.also_propagate.ops[j];
                 propagate(rop->cmd,rop->dbid,rop->argv,rop->argc,rop->target);
@@ -2186,7 +2186,7 @@ int processCommand(client *c) {
      * a regular command proc. */
     if (!strcasecmp(c->argv[0]->ptr,"quit")) {
         addReply(c,shared.ok);
-        c->flags |= REDIS_CLOSE_AFTER_REPLY;
+        c->flags |= CLIENT_CLOSE_AFTER_REPLY;
         return C_ERR;
     }
 
@@ -2219,9 +2219,9 @@ int processCommand(client *c) {
      * 1) The sender of this command is our master.
      * 2) The command has no key arguments. */
     if (server.cluster_enabled &&
-        !(c->flags & REDIS_MASTER) &&
-        !(c->flags & REDIS_LUA_CLIENT &&
-          server.lua_caller->flags & REDIS_MASTER) &&
+        !(c->flags & CLIENT_MASTER) &&
+        !(c->flags & CLIENT_LUA &&
+          server.lua_caller->flags & CLIENT_MASTER) &&
         !(c->cmd->getkeys_proc == NULL && c->cmd->firstkey == 0))
     {
         int hashslot;
@@ -2248,7 +2248,7 @@ int processCommand(client *c) {
      * is returning an error. */
     if (server.maxmemory) {
         int retval = freeMemoryIfNeeded();
-        if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == C_ERR) {
+        if ((c->cmd->flags & CMD_DENYOOM) && retval == C_ERR) {
             flagTransaction(c);
             addReply(c, shared.oomerr);
             return C_OK;
@@ -2262,7 +2262,7 @@ int processCommand(client *c) {
           server.lastbgsave_status == C_ERR) ||
           server.aof_last_write_status == C_ERR) &&
         server.masterhost == NULL &&
-        (c->cmd->flags & REDIS_CMD_WRITE ||
+        (c->cmd->flags & CMD_WRITE ||
          c->cmd->proc == pingCommand))
     {
         flagTransaction(c);
@@ -2281,7 +2281,7 @@ int processCommand(client *c) {
     if (server.masterhost == NULL &&
         server.repl_min_slaves_to_write &&
         server.repl_min_slaves_max_lag &&
-        c->cmd->flags & REDIS_CMD_WRITE &&
+        c->cmd->flags & CMD_WRITE &&
         server.repl_good_slaves_count < server.repl_min_slaves_to_write)
     {
         flagTransaction(c);
@@ -2292,15 +2292,15 @@ int processCommand(client *c) {
     /* Don't accept write commands if this is a read only slave. But
      * accept write commands if this is our master. */
     if (server.masterhost && server.repl_slave_ro &&
-        !(c->flags & REDIS_MASTER) &&
-        c->cmd->flags & REDIS_CMD_WRITE)
+        !(c->flags & CLIENT_MASTER) &&
+        c->cmd->flags & CMD_WRITE)
     {
         addReply(c, shared.roslaveerr);
         return C_OK;
     }
 
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
-    if (c->flags & REDIS_PUBSUB &&
+    if (c->flags & CLIENT_PUBSUB &&
         c->cmd->proc != pingCommand &&
         c->cmd->proc != subscribeCommand &&
         c->cmd->proc != unsubscribeCommand &&
@@ -2312,18 +2312,18 @@ int processCommand(client *c) {
 
     /* Only allow INFO and SLAVEOF when slave-serve-stale-data is no and
      * we are a slave with a broken link with master. */
-    if (server.masterhost && server.repl_state != REDIS_REPL_CONNECTED &&
+    if (server.masterhost && server.repl_state != REPL_STATE_CONNECTED &&
         server.repl_serve_stale_data == 0 &&
-        !(c->cmd->flags & REDIS_CMD_STALE))
+        !(c->cmd->flags & CMD_STALE))
     {
         flagTransaction(c);
         addReply(c, shared.masterdownerr);
         return C_OK;
     }
 
     /* Loading DB? Return an error if the command has not the
-     * REDIS_CMD_LOADING flag. */
-    if (server.loading && !(c->cmd->flags & REDIS_CMD_LOADING)) {
+     * CMD_LOADING flag. */
+    if (server.loading && !(c->cmd->flags & CMD_LOADING)) {
         addReply(c, shared.loadingerr);
         return C_OK;
     }
@@ -2345,14 +2345,14 @@ int processCommand(client *c) {
     }
 
     /* Exec the command */
-    if (c->flags & REDIS_MULTI &&
+    if (c->flags & CLIENT_MULTI &&
         c->cmd->proc != execCommand && c->cmd->proc != discardCommand &&
         c->cmd->proc != multiCommand && c->cmd->proc != watchCommand)
     {
         queueMultiCommand(c);
         addReply(c,shared.queued);
     } else {
-        call(c,REDIS_CALL_FULL);
+        call(c,CMD_CALL_FULL);
         c->woff = server.master_repl_offset;
         if (listLength(server.ready_keys))
             handleClientsBlockedOnLists();
@@ -2372,62 +2372,62 @@ void closeListeningSockets(int unlink_unix_socket) {
     if (server.cluster_enabled)
         for (j = 0; j < server.cfd_count; j++) close(server.cfd[j]);
     if (unlink_unix_socket && server.unixsocket) {
-        serverLog(REDIS_NOTICE,"Removing the unix socket file.");
+        serverLog(LL_NOTICE,"Removing the unix socket file.");
         unlink(server.unixsocket); /* don't care if this fails */
     }
 }
 
 int prepareForShutdown(int flags) {
-    int save = flags & REDIS_SHUTDOWN_SAVE;
-    int nosave = flags & REDIS_SHUTDOWN_NOSAVE;
+    int save = flags & SHUTDOWN_SAVE;
+    int nosave = flags & SHUTDOWN_NOSAVE;
 
-    serverLog(REDIS_WARNING,"User requested shutdown...");
+    serverLog(LL_WARNING,"User requested shutdown...");
     /* Kill the saving child if there is a background saving in progress.
        We want to avoid race conditions, for instance our saving child may
        overwrite the synchronous saving did by SHUTDOWN. */
     if (server.rdb_child_pid != -1) {
-        serverLog(REDIS_WARNING,"There is a child saving an .rdb. Killing it!");
+        serverLog(LL_WARNING,"There is a child saving an .rdb. Killing it!");
         kill(server.rdb_child_pid,SIGUSR1);
         rdbRemoveTempFile(server.rdb_child_pid);
     }
-    if (server.aof_state != REDIS_AOF_OFF) {
+    if (server.aof_state != AOF_OFF) {
         /* Kill the AOF saving child as the AOF we already have may be longer
          * but contains the full dataset anyway. */
         if (server.aof_child_pid != -1) {
             /* If we have AOF enabled but haven't written the AOF yet, don't
              * shutdown or else the dataset will be lost. */
-            if (server.aof_state == REDIS_AOF_WAIT_REWRITE) {
-                serverLog(REDIS_WARNING, "Writing initial AOF, can't exit.");
+            if (server.aof_state == AOF_WAIT_REWRITE) {
+                serverLog(LL_WARNING, "Writing initial AOF, can't exit.");
                 return C_ERR;
             }
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "There is a child rewriting the AOF. Killing it!");
             kill(server.aof_child_pid,SIGUSR1);
         }
         /* Append only file: fsync() the AOF and exit */
-        serverLog(REDIS_NOTICE,"Calling fsync() on the AOF file.");
+        serverLog(LL_NOTICE,"Calling fsync() on the AOF file.");
         aof_fsync(server.aof_fd);
     }
     if ((server.saveparamslen > 0 && !nosave) || save) {
-        serverLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
+        serverLog(LL_NOTICE,"Saving the final RDB snapshot before exiting.");
         /* Snapshotting. Perform a SYNC SAVE and exit */
         if (rdbSave(server.rdb_filename) != C_OK) {
             /* Ooops.. error saving! The best we can do is to continue
              * operating. Note that if there was a background saving process,
              * in the next cron() Redis will be notified that the background
              * saving aborted, handling special stuff like slaves pending for
              * synchronization... */
-            serverLog(REDIS_WARNING,"Error trying to save the DB, can't exit.");
+            serverLog(LL_WARNING,"Error trying to save the DB, can't exit.");
             return C_ERR;
         }
     }
     if (server.daemonize || server.pidfile) {
-        serverLog(REDIS_NOTICE,"Removing the pid file.");
+        serverLog(LL_NOTICE,"Removing the pid file.");
         unlink(server.pidfile);
     }
     /* Close the listening sockets. Apparently this allows faster restarts. */
     closeListeningSockets(1);
-    serverLog(REDIS_WARNING,"%s is now ready to exit, bye bye...",
+    serverLog(LL_WARNING,"%s is now ready to exit, bye bye...",
         server.sentinel_mode ? "Sentinel" : "Redis");
     return C_OK;
 }
@@ -2444,7 +2444,7 @@ int prepareForShutdown(int flags) {
  * possible branch misprediction related leak.
  */
 int time_independent_strcmp(char *a, char *b) {
-    char bufa[REDIS_AUTHPASS_MAX_LEN], bufb[REDIS_AUTHPASS_MAX_LEN];
+    char bufa[CONFIG_AUTHPASS_MAX_LEN], bufb[CONFIG_AUTHPASS_MAX_LEN];
     /* The above two strlen perform len(a) + len(b) operations where either
      * a or b are fixed (our password) length, and the difference is only
      * relative to the length of the user provided string, so no information
@@ -2498,7 +2498,7 @@ void pingCommand(client *c) {
         return;
     }
 
-    if (c->flags & REDIS_PUBSUB) {
+    if (c->flags & CLIENT_PUBSUB) {
         addReply(c,shared.mbulkhdr[2]);
         addReplyBulkCBuffer(c,"pong",4);
         if (c->argc == 1)
@@ -2549,19 +2549,19 @@ void addReplyCommand(client *c, struct redisCommand *cmd) {
 
         int flagcount = 0;
         void *flaglen = addDeferredMultiBulkLength(c);
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_WRITE, "write");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_READONLY, "readonly");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_DENYOOM, "denyoom");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_ADMIN, "admin");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_PUBSUB, "pubsub");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_NOSCRIPT, "noscript");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_RANDOM, "random");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_SORT_FOR_SCRIPT,"sort_for_script");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_LOADING, "loading");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_STALE, "stale");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_SKIP_MONITOR, "skip_monitor");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_ASKING, "asking");
-        flagcount += addReplyCommandFlag(c,cmd,REDIS_CMD_FAST, "fast");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_WRITE, "write");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_READONLY, "readonly");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_DENYOOM, "denyoom");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_ADMIN, "admin");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_PUBSUB, "pubsub");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_NOSCRIPT, "noscript");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_RANDOM, "random");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_SORT_FOR_SCRIPT,"sort_for_script");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_LOADING, "loading");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_STALE, "stale");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_SKIP_MONITOR, "skip_monitor");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_ASKING, "asking");
+        flagcount += addReplyCommandFlag(c,cmd,CMD_FAST, "fast");
         if (cmd->getkeys_proc) {
             addReplyStatus(c, "movablekeys");
             flagcount += 1;
@@ -2832,7 +2832,7 @@ sds genRedisInfoString(char *section) {
             (intmax_t)server.rdb_save_time_last,
             (intmax_t)((server.rdb_child_pid == -1) ?
                 -1 : time(NULL)-server.rdb_save_time_start),
-            server.aof_state != REDIS_AOF_OFF,
+            server.aof_state != AOF_OFF,
             server.aof_child_pid != -1,
             server.aof_rewrite_scheduled,
             (intmax_t)server.aof_rewrite_time_last,
@@ -2841,7 +2841,7 @@ sds genRedisInfoString(char *section) {
             (server.aof_lastbgrewrite_status == C_OK) ? "ok" : "err",
             (server.aof_last_write_status == C_OK) ? "ok" : "err");
 
-        if (server.aof_state != REDIS_AOF_OFF) {
+        if (server.aof_state != AOF_OFF) {
             info = sdscatprintf(info,
                 "aof_current_size:%lld\r\n"
                 "aof_base_size:%lld\r\n"
@@ -2917,11 +2917,11 @@ sds genRedisInfoString(char *section) {
             "migrate_cached_sockets:%ld\r\n",
             server.stat_numconnections,
             server.stat_numcommands,
-            getInstantaneousMetric(REDIS_METRIC_COMMAND),
+            getInstantaneousMetric(STATS_METRIC_COMMAND),
             server.stat_net_input_bytes,
             server.stat_net_output_bytes,
-            (float)getInstantaneousMetric(REDIS_METRIC_NET_INPUT)/1024,
-            (float)getInstantaneousMetric(REDIS_METRIC_NET_OUTPUT)/1024,
+            (float)getInstantaneousMetric(STATS_METRIC_NET_INPUT)/1024,
+            (float)getInstantaneousMetric(STATS_METRIC_NET_OUTPUT)/1024,
             server.stat_rejected_conn,
             server.stat_sync_full,
             server.stat_sync_partial_ok,
@@ -2960,15 +2960,15 @@ sds genRedisInfoString(char *section) {
                 "slave_repl_offset:%lld\r\n"
                 ,server.masterhost,
                 server.masterport,
-                (server.repl_state == REDIS_REPL_CONNECTED) ?
+                (server.repl_state == REPL_STATE_CONNECTED) ?
                     "up" : "down",
                 server.master ?
                 ((int)(server.unixtime-server.master->lastinteraction)) : -1,
-                server.repl_state == REDIS_REPL_TRANSFER,
+                server.repl_state == REPL_STATE_TRANSFER,
                 slave_repl_offset
             );
 
-            if (server.repl_state == REDIS_REPL_TRANSFER) {
+            if (server.repl_state == REPL_STATE_TRANSFER) {
                 info = sdscatprintf(info,
                     "master_sync_left_bytes:%lld\r\n"
                     "master_sync_last_io_seconds_ago:%d\r\n"
@@ -2978,7 +2978,7 @@ sds genRedisInfoString(char *section) {
                 );
             }
 
-            if (server.repl_state != REDIS_REPL_CONNECTED) {
+            if (server.repl_state != REPL_STATE_CONNECTED) {
                 info = sdscatprintf(info,
                     "master_link_down_since_seconds:%jd\r\n",
                     (intmax_t)server.unixtime-server.repl_down_since);
@@ -3012,25 +3012,25 @@ sds genRedisInfoString(char *section) {
             while((ln = listNext(&li))) {
                 client *slave = listNodeValue(ln);
                 char *state = NULL;
-                char ip[REDIS_IP_STR_LEN];
+                char ip[NET_IP_STR_LEN];
                 int port;
                 long lag = 0;
 
                 if (anetPeerToString(slave->fd,ip,sizeof(ip),&port) == -1) continue;
                 switch(slave->replstate) {
-                case REDIS_REPL_WAIT_BGSAVE_START:
-                case REDIS_REPL_WAIT_BGSAVE_END:
+                case SLAVE_STATE_WAIT_BGSAVE_START:
+                case SLAVE_STATE_WAIT_BGSAVE_END:
                     state = "wait_bgsave";
                     break;
-                case REDIS_REPL_SEND_BULK:
+                case SLAVE_STATE_SEND_BULK:
                     state = "send_bulk";
                     break;
-                case REDIS_REPL_ONLINE:
+                case SLAVE_STATE_ONLINE:
                     state = "online";
                     break;
                 }
                 if (state == NULL) continue;
-                if (slave->replstate == REDIS_REPL_ONLINE)
+                if (slave->replstate == SLAVE_STATE_ONLINE)
                     lag = time(NULL) - slave->repl_ack_time;
 
                 info = sdscatprintf(info,
@@ -3125,9 +3125,9 @@ void infoCommand(client *c) {
 
 void monitorCommand(client *c) {
     /* ignore MONITOR if already slave or in monitor mode */
-    if (c->flags & REDIS_SLAVE) return;
+    if (c->flags & CLIENT_SLAVE) return;
 
-    c->flags |= (REDIS_SLAVE|REDIS_MONITOR);
+    c->flags |= (CLIENT_SLAVE|CLIENT_MONITOR);
     listAddNodeTail(server.monitors,c);
     addReply(c,shared.ok);
 }
@@ -3157,7 +3157,7 @@ void monitorCommand(client *c) {
  * Redis uses an approximation of the LRU algorithm that runs in constant
  * memory. Every time there is a key to expire, we sample N keys (with
  * N very small, usually in around 5) to populate a pool of best keys to
- * evict of M keys (the pool size is defined by REDIS_EVICTION_POOL_SIZE).
+ * evict of M keys (the pool size is defined by MAXMEMORY_EVICTION_POOL_SIZE).
  *
  * The N keys sampled are added in the pool of good keys to expire (the one
  * with an old access time) if they are better than one of the current keys
@@ -3177,8 +3177,8 @@ struct evictionPoolEntry *evictionPoolAlloc(void) {
     struct evictionPoolEntry *ep;
     int j;
 
-    ep = zmalloc(sizeof(*ep)*REDIS_EVICTION_POOL_SIZE);
-    for (j = 0; j < REDIS_EVICTION_POOL_SIZE; j++) {
+    ep = zmalloc(sizeof(*ep)*MAXMEMORY_EVICTION_POOL_SIZE);
+    for (j = 0; j < MAXMEMORY_EVICTION_POOL_SIZE; j++) {
         ep[j].idle = 0;
         ep[j].key = NULL;
     }
@@ -3228,23 +3228,23 @@ void evictionPoolPopulate(dict *sampledict, dict *keydict, struct evictionPoolEn
          * First, find the first empty bucket or the first populated
          * bucket that has an idle time smaller than our idle time. */
         k = 0;
-        while (k < REDIS_EVICTION_POOL_SIZE &&
+        while (k < MAXMEMORY_EVICTION_POOL_SIZE &&
                pool[k].key &&
                pool[k].idle < idle) k++;
-        if (k == 0 && pool[REDIS_EVICTION_POOL_SIZE-1].key != NULL) {
+        if (k == 0 && pool[MAXMEMORY_EVICTION_POOL_SIZE-1].key != NULL) {
             /* Can't insert if the element is < the worst element we have
              * and there are no empty buckets. */
             continue;
-        } else if (k < REDIS_EVICTION_POOL_SIZE && pool[k].key == NULL) {
+        } else if (k < MAXMEMORY_EVICTION_POOL_SIZE && pool[k].key == NULL) {
             /* Inserting into empty position. No setup needed before insert. */
         } else {
             /* Inserting in the middle. Now k points to the first element
              * greater than the element to insert.  */
-            if (pool[REDIS_EVICTION_POOL_SIZE-1].key == NULL) {
+            if (pool[MAXMEMORY_EVICTION_POOL_SIZE-1].key == NULL) {
                 /* Free space on the right? Insert at k shifting
                  * all the elements from k to end to the right. */
                 memmove(pool+k+1,pool+k,
-                    sizeof(pool[0])*(REDIS_EVICTION_POOL_SIZE-k-1));
+                    sizeof(pool[0])*(MAXMEMORY_EVICTION_POOL_SIZE-k-1));
             } else {
                 /* No free space on right? Insert at k-1 */
                 k--;
@@ -3282,15 +3282,15 @@ int freeMemoryIfNeeded(void) {
                 mem_used -= obuf_bytes;
         }
     }
-    if (server.aof_state != REDIS_AOF_OFF) {
+    if (server.aof_state != AOF_OFF) {
         mem_used -= sdslen(server.aof_buf);
         mem_used -= aofRewriteBufferSize();
     }
 
     /* Check if we are over the memory limit. */
     if (mem_used <= server.maxmemory) return C_OK;
 
-    if (server.maxmemory_policy == REDIS_MAXMEMORY_NO_EVICTION)
+    if (server.maxmemory_policy == MAXMEMORY_NO_EVICTION)
         return C_ERR; /* We need to free memory, but policy forbids. */
 
     /* Compute how much memory we need to free. */
@@ -3307,8 +3307,8 @@ int freeMemoryIfNeeded(void) {
             redisDb *db = server.db+j;
             dict *dict;
 
-            if (server.maxmemory_policy == REDIS_MAXMEMORY_ALLKEYS_LRU ||
-                server.maxmemory_policy == REDIS_MAXMEMORY_ALLKEYS_RANDOM)
+            if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU ||
+                server.maxmemory_policy == MAXMEMORY_ALLKEYS_RANDOM)
             {
                 dict = server.db[j].dict;
             } else {
@@ -3317,35 +3317,35 @@ int freeMemoryIfNeeded(void) {
             if (dictSize(dict) == 0) continue;
 
             /* volatile-random and allkeys-random policy */
-            if (server.maxmemory_policy == REDIS_MAXMEMORY_ALLKEYS_RANDOM ||
-                server.maxmemory_policy == REDIS_MAXMEMORY_VOLATILE_RANDOM)
+            if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_RANDOM ||
+                server.maxmemory_policy == MAXMEMORY_VOLATILE_RANDOM)
             {
                 de = dictGetRandomKey(dict);
                 bestkey = dictGetKey(de);
             }
 
             /* volatile-lru and allkeys-lru policy */
-            else if (server.maxmemory_policy == REDIS_MAXMEMORY_ALLKEYS_LRU ||
-                server.maxmemory_policy == REDIS_MAXMEMORY_VOLATILE_LRU)
+            else if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU ||
+                server.maxmemory_policy == MAXMEMORY_VOLATILE_LRU)
             {
                 struct evictionPoolEntry *pool = db->eviction_pool;
 
                 while(bestkey == NULL) {
                     evictionPoolPopulate(dict, db->dict, db->eviction_pool);
                     /* Go backward from best to worst element to evict. */
-                    for (k = REDIS_EVICTION_POOL_SIZE-1; k >= 0; k--) {
+                    for (k = MAXMEMORY_EVICTION_POOL_SIZE-1; k >= 0; k--) {
                         if (pool[k].key == NULL) continue;
                         de = dictFind(dict,pool[k].key);
 
                         /* Remove the entry from the pool. */
                         sdsfree(pool[k].key);
                         /* Shift all elements on its right to left. */
                         memmove(pool+k,pool+k+1,
-                            sizeof(pool[0])*(REDIS_EVICTION_POOL_SIZE-k-1));
+                            sizeof(pool[0])*(MAXMEMORY_EVICTION_POOL_SIZE-k-1));
                         /* Clear the element on the right which is empty
                          * since we shifted one position to the left.  */
-                        pool[REDIS_EVICTION_POOL_SIZE-1].key = NULL;
-                        pool[REDIS_EVICTION_POOL_SIZE-1].idle = 0;
+                        pool[MAXMEMORY_EVICTION_POOL_SIZE-1].key = NULL;
+                        pool[MAXMEMORY_EVICTION_POOL_SIZE-1].idle = 0;
 
                         /* If the key exists, is our pick. Otherwise it is
                          * a ghost and we need to try the next element. */
@@ -3361,7 +3361,7 @@ int freeMemoryIfNeeded(void) {
             }
 
             /* volatile-ttl */
-            else if (server.maxmemory_policy == REDIS_MAXMEMORY_VOLATILE_TTL) {
+            else if (server.maxmemory_policy == MAXMEMORY_VOLATILE_TTL) {
                 for (k = 0; k < server.maxmemory_samples; k++) {
                     sds thiskey;
                     long thisval;
@@ -3402,7 +3402,7 @@ int freeMemoryIfNeeded(void) {
                 delta -= (long long) zmalloc_used_memory();
                 mem_freed += delta;
                 server.stat_evictedkeys++;
-                notifyKeyspaceEvent(REDIS_NOTIFY_EVICTED, "evicted",
+                notifyKeyspaceEvent(NOTIFY_EVICTED, "evicted",
                     keyobj, db->id);
                 decrRefCount(keyobj);
                 keys_freed++;
@@ -3444,10 +3444,10 @@ int linuxOvercommitMemoryValue(void) {
 
 void linuxMemoryWarnings(void) {
     if (linuxOvercommitMemoryValue() == 0) {
-        serverLog(REDIS_WARNING,"WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
+        serverLog(LL_WARNING,"WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.");
     }
     if (THPIsEnabled()) {
-        serverLog(REDIS_WARNING,"WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.");
+        serverLog(LL_WARNING,"WARNING you have Transparent Huge Pages (THP) support enabled in your kernel. This will create latency and memory usage issues with Redis. To fix this issue run the command 'echo never > /sys/kernel/mm/transparent_hugepage/enabled' as root, and add it to your /etc/rc.local in order to retain the setting after a reboot. Redis must be restarted after THP is disabled.");
     }
 }
 #endif /* __linux__ */
@@ -3520,7 +3520,7 @@ void redisAsciiArt(void) {
     else mode = "standalone";
 
     if (server.syslog_enabled) {
-        serverLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
             REDIS_VERSION,
             redisGitSHA1(),
@@ -3538,7 +3538,7 @@ void redisAsciiArt(void) {
             mode, server.port,
             (long) getpid()
         );
-        serverLogRaw(REDIS_NOTICE|REDIS_LOG_RAW,buf);
+        serverLogRaw(LL_NOTICE|LL_RAW,buf);
     }
     zfree(buf);
 }
@@ -3562,14 +3562,14 @@ static void sigShutdownHandler(int sig) {
      * the user really wanting to quit ASAP without waiting to persist
      * on disk. */
     if (server.shutdown_asap && sig == SIGINT) {
-        serverLogFromHandler(REDIS_WARNING, "You insist... exiting now.");
+        serverLogFromHandler(LL_WARNING, "You insist... exiting now.");
         rdbRemoveTempFile(getpid());
         exit(1); /* Exit with an error since this was not a clean shutdown. */
     } else if (server.loading) {
         exit(0);
     }
 
-    serverLogFromHandler(REDIS_WARNING, msg);
+    serverLogFromHandler(LL_WARNING, msg);
     server.shutdown_asap = 1;
 }
 
@@ -3612,24 +3612,24 @@ int checkForSentinelMode(int argc, char **argv) {
 /* Function called at startup to load RDB or AOF file in memory. */
 void loadDataFromDisk(void) {
     long long start = ustime();
-    if (server.aof_state == REDIS_AOF_ON) {
+    if (server.aof_state == AOF_ON) {
         if (loadAppendOnlyFile(server.aof_filename) == C_OK)
-            serverLog(REDIS_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
+            serverLog(LL_NOTICE,"DB loaded from append only file: %.3f seconds",(float)(ustime()-start)/1000000);
     } else {
         if (rdbLoad(server.rdb_filename) == C_OK) {
-            serverLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
+            serverLog(LL_NOTICE,"DB loaded from disk: %.3f seconds",
                 (float)(ustime()-start)/1000000);
         } else if (errno != ENOENT) {
-            serverLog(REDIS_WARNING,"Fatal error loading the DB: %s. Exiting.",strerror(errno));
+            serverLog(LL_WARNING,"Fatal error loading the DB: %s. Exiting.",strerror(errno));
             exit(1);
         }
     }
 }
 
 void redisOutOfMemoryHandler(size_t allocation_size) {
-    serverLog(REDIS_WARNING,"Out Of Memory allocating %zu bytes!",
+    serverLog(LL_WARNING,"Out Of Memory allocating %zu bytes!",
         allocation_size);
-    redisPanic("Redis aborting for OUT OF MEMORY");
+    serverPanic("Redis aborting for OUT OF MEMORY");
 }
 
 void redisSetProcTitle(char *title) {
@@ -3644,7 +3644,7 @@ void redisSetProcTitle(char *title) {
         server.port,
         server_mode);
 #else
-    REDIS_NOTUSED(title);
+    UNUSED(title);
 #endif
 }
 
@@ -3656,12 +3656,12 @@ int redisSupervisedUpstart(void) {
     const char *upstart_job = getenv("UPSTART_JOB");
 
     if (!upstart_job) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
                 "upstart supervision requested, but UPSTART_JOB not found");
         return 0;
     }
 
-    serverLog(REDIS_NOTICE, "supervised by upstart, will stop to signal readyness");
+    serverLog(LL_NOTICE, "supervised by upstart, will stop to signal readyness");
     raise(SIGSTOP);
     unsetenv("UPSTART_JOB");
     return 1;
@@ -3676,7 +3676,7 @@ int redisSupervisedSystemd(void) {
     int sendto_flags = 0;
 
     if (!notify_socket) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
                 "systemd supervision requested, but NOTIFY_SOCKET not found");
         return 0;
     }
@@ -3685,9 +3685,9 @@ int redisSupervisedSystemd(void) {
         return 0;
     }
 
-    serverLog(REDIS_NOTICE, "supervised by systemd, will signal readyness");
+    serverLog(LL_NOTICE, "supervised by systemd, will signal readyness");
     if ((fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
-        serverLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
                 "Can't connect to systemd socket %s", notify_socket);
         return 0;
     }
@@ -3716,7 +3716,7 @@ int redisSupervisedSystemd(void) {
     sendto_flags |= MSG_NOSIGNAL;
 #endif
     if (sendmsg(fd, &hdr, sendto_flags) < 0) {
-        serverLog(REDIS_WARNING, "Can't send notification to systemd");
+        serverLog(LL_WARNING, "Can't send notification to systemd");
         close(fd);
         return 0;
     }
@@ -3725,7 +3725,7 @@ int redisSupervisedSystemd(void) {
 }
 
 int redisIsSupervised(int mode) {
-    if (mode == REDIS_SUPERVISED_AUTODETECT) {
+    if (mode == SUPERVISED_AUTODETECT) {
         const char *upstart_job = getenv("UPSTART_JOB");
         const char *notify_socket = getenv("NOTIFY_SOCKET");
 
@@ -3734,9 +3734,9 @@ int redisIsSupervised(int mode) {
         } else if (notify_socket) {
             redisSupervisedSystemd();
         }
-    } else if (mode == REDIS_SUPERVISED_UPSTART) {
+    } else if (mode == SUPERVISED_UPSTART) {
         return redisSupervisedUpstart();
-    } else if (mode == REDIS_SUPERVISED_SYSTEMD) {
+    } else if (mode == SUPERVISED_SYSTEMD) {
         return redisSupervisedSystemd();
     }
 
@@ -3847,9 +3847,9 @@ int main(int argc, char **argv) {
             j++;
         }
         if (server.sentinel_mode && configfile && *configfile == '-') {
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Sentinel config from STDIN not allowed.");
-            serverLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Sentinel needs config file on disk to save state.  Exiting...");
             exit(1);
         }
@@ -3858,7 +3858,7 @@ int main(int argc, char **argv) {
         loadServerConfig(configfile,options);
         sdsfree(options);
     } else {
-        serverLog(REDIS_WARNING, "Warning: no config file specified, using the default config. In order to specify a config file use %s /path/to/%s.conf", argv[0], server.sentinel_mode ? "sentinel" : "redis");
+        serverLog(LL_WARNING, "Warning: no config file specified, using the default config. In order to specify a config file use %s /path/to/%s.conf", argv[0], server.sentinel_mode ? "sentinel" : "redis");
     }
 
     server.supervised = redisIsSupervised(server.supervised_mode);
@@ -3872,31 +3872,31 @@ int main(int argc, char **argv) {
 
     if (!server.sentinel_mode) {
         /* Things not needed when running in Sentinel mode. */
-        serverLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
+        serverLog(LL_WARNING,"Server started, Redis version " REDIS_VERSION);
     #ifdef __linux__
         linuxMemoryWarnings();
     #endif
         checkTcpBacklogSettings();
         loadDataFromDisk();
         if (server.cluster_enabled) {
             if (verifyClusterConfigWithData() == C_ERR) {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "You can't have keys in a DB different than DB 0 when in "
                     "Cluster mode. Exiting.");
                 exit(1);
             }
         }
         if (server.ipfd_count > 0)
-            serverLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
+            serverLog(LL_NOTICE,"The server is now ready to accept connections on port %d", server.port);
         if (server.sofd > 0)
-            serverLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
+            serverLog(LL_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
     } else {
         sentinelIsRunning();
     }
 
     /* Warning the user about suspicious maxmemory setting. */
     if (server.maxmemory > 0 && server.maxmemory < 1024*1024) {
-        serverLog(REDIS_WARNING,"WARNING: You specified a maxmemory value that is less than 1MB (current value is %llu bytes). Are you sure this is what you really want?", server.maxmemory);
+        serverLog(LL_WARNING,"WARNING: You specified a maxmemory value that is less than 1MB (current value is %llu bytes). Are you sure this is what you really want?", server.maxmemory);
     }
 
     aeSetBeforeSleepProc(server.el,beforeSleep);