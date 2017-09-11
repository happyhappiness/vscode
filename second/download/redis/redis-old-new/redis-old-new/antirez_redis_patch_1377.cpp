@@ -211,7 +211,7 @@ struct redisCommand redisCommandTable[] = {
     {"lastsave",lastsaveCommand,1,"r",0,NULL,0,0,0,0,0},
     {"type",typeCommand,2,"r",0,NULL,1,1,1,0,0},
     {"multi",multiCommand,1,"rs",0,NULL,0,0,0,0,0},
-    {"exec",execCommand,1,"wms",0,NULL,0,0,0,0,0},
+    {"exec",execCommand,1,"s",0,NULL,0,0,0,0,0},
     {"discard",discardCommand,1,"rs",0,NULL,0,0,0,0,0},
     {"sync",syncCommand,1,"ars",0,NULL,0,0,0,0,0},
     {"flushdb",flushdbCommand,1,"w",0,NULL,0,0,0,0,0},
@@ -223,13 +223,13 @@ struct redisCommand redisCommandTable[] = {
     {"pttl",pttlCommand,2,"r",0,NULL,1,1,1,0,0},
     {"persist",persistCommand,2,"w",0,NULL,1,1,1,0,0},
     {"slaveof",slaveofCommand,3,"aws",0,NULL,0,0,0,0,0},
-    {"debug",debugCommand,-2,"aws",0,NULL,0,0,0,0,0},
+    {"debug",debugCommand,-2,"as",0,NULL,0,0,0,0,0},
     {"config",configCommand,-2,"ar",0,NULL,0,0,0,0,0},
     {"subscribe",subscribeCommand,-2,"rps",0,NULL,0,0,0,0,0},
     {"unsubscribe",unsubscribeCommand,-1,"rps",0,NULL,0,0,0,0,0},
     {"psubscribe",psubscribeCommand,-2,"rps",0,NULL,0,0,0,0,0},
     {"punsubscribe",punsubscribeCommand,-1,"rps",0,NULL,0,0,0,0,0},
-    {"publish",publishCommand,3,"rpf",0,NULL,0,0,0,0,0},
+    {"publish",publishCommand,3,"pf",0,NULL,0,0,0,0,0},
     {"watch",watchCommand,-2,"rs",0,noPreloadGetKeys,1,-1,1,0,0},
     {"unwatch",unwatchCommand,1,"rs",0,NULL,0,0,0,0,0},
     {"cluster",clusterCommand,-2,"ar",0,NULL,0,0,0,0,0},
@@ -239,10 +239,11 @@ struct redisCommand redisCommandTable[] = {
     {"dump",dumpCommand,2,"ar",0,NULL,1,1,1,0,0},
     {"object",objectCommand,-2,"r",0,NULL,2,2,2,0,0},
     {"client",clientCommand,-2,"ar",0,NULL,0,0,0,0,0},
-    {"eval",evalCommand,-3,"wms",0,zunionInterGetKeys,0,0,0,0,0},
-    {"evalsha",evalShaCommand,-3,"wms",0,zunionInterGetKeys,0,0,0,0,0},
+    {"eval",evalCommand,-3,"s",0,zunionInterGetKeys,0,0,0,0,0},
+    {"evalsha",evalShaCommand,-3,"s",0,zunionInterGetKeys,0,0,0,0,0},
     {"slowlog",slowlogCommand,-2,"r",0,NULL,0,0,0,0,0},
-    {"script",scriptCommand,-2,"ras",0,NULL,0,0,0,0,0}
+    {"script",scriptCommand,-2,"ras",0,NULL,0,0,0,0,0},
+    {"time",timeCommand,1,"rR",0,NULL,0,0,0,0,0}
 };
 
 /*============================ Utility functions ============================ */
@@ -615,6 +616,110 @@ void updateLRUClock(void) {
                                                 REDIS_LRU_CLOCK_MAX;
 }
 
+
+/* Add a sample to the operations per second array of samples. */
+void trackOperationsPerSecond(void) {
+    long long t = mstime() - server.ops_sec_last_sample_time;
+    long long ops = server.stat_numcommands - server.ops_sec_last_sample_ops;
+    long long ops_sec;
+
+    ops_sec = t > 0 ? (ops*1000/t) : 0;
+
+    server.ops_sec_samples[server.ops_sec_idx] = ops_sec;
+    server.ops_sec_idx = (server.ops_sec_idx+1) % REDIS_OPS_SEC_SAMPLES;
+    server.ops_sec_last_sample_time = mstime();
+    server.ops_sec_last_sample_ops = server.stat_numcommands;
+}
+
+/* Return the mean of all the samples. */
+long long getOperationsPerSecond(void) {
+    int j;
+    long long sum = 0;
+
+    for (j = 0; j < REDIS_OPS_SEC_SAMPLES; j++)
+        sum += server.ops_sec_samples[j];
+    return sum / REDIS_OPS_SEC_SAMPLES;
+}
+
+/* Check for timeouts. Returns non-zero if the client was terminated */
+int clientsCronHandleTimeout(redisClient *c) {
+    time_t now = server.unixtime;
+
+    if (server.maxidletime &&
+        !(c->flags & REDIS_SLAVE) &&    /* no timeout for slaves */
+        !(c->flags & REDIS_MASTER) &&   /* no timeout for masters */
+        !(c->flags & REDIS_BLOCKED) &&  /* no timeout for BLPOP */
+        dictSize(c->pubsub_channels) == 0 && /* no timeout for pubsub */
+        listLength(c->pubsub_patterns) == 0 &&
+        (now - c->lastinteraction > server.maxidletime))
+    {
+        redisLog(REDIS_VERBOSE,"Closing idle client");
+        freeClient(c);
+        return 1;
+    } else if (c->flags & REDIS_BLOCKED) {
+        if (c->bpop.timeout != 0 && c->bpop.timeout < now) {
+            addReply(c,shared.nullmultibulk);
+            unblockClientWaitingData(c);
+        }
+    }
+    return 0;
+}
+
+/* The client query buffer is an sds.c string that can end with a lot of
+ * free space not used, this function reclaims space if needed.
+ *
+ * The funciton always returns 0 as it never terminates the client. */
+int clientsCronResizeQueryBuffer(redisClient *c) {
+    size_t querybuf_size = sdsAllocSize(c->querybuf);
+    time_t idletime = server.unixtime - c->lastinteraction;
+
+    /* There are two conditions to resize the query buffer:
+     * 1) Query buffer is > BIG_ARG and too big for latest peak.
+     * 2) Client is inactive and the buffer is bigger than 1k. */
+    if (((querybuf_size > REDIS_MBULK_BIG_ARG) &&
+         (querybuf_size/(c->querybuf_peak+1)) > 2) ||
+         (querybuf_size > 1024 && idletime > 2))
+    {
+        /* Only resize the query buffer if it is actually wasting space. */
+        if (sdsavail(c->querybuf) > 1024) {
+            c->querybuf = sdsRemoveFreeSpace(c->querybuf);
+        }
+    }
+    /* Reset the peak again to capture the peak memory usage in the next
+     * cycle. */
+    c->querybuf_peak = 0;
+    return 0;
+}
+
+void clientsCron(void) {
+    /* Make sure to process at least 1/100 of clients per call.
+     * Since this function is called 10 times per second we are sure that
+     * in the worst case we process all the clients in 10 seconds.
+     * In normal conditions (a reasonable number of clients) we process
+     * all the clients in a shorter time. */
+    int numclients = listLength(server.clients);
+    int iterations = numclients/100;
+
+    if (iterations < 50)
+        iterations = (numclients < 50) ? numclients : 50;
+    while(listLength(server.clients) && iterations--) {
+        redisClient *c;
+        listNode *head;
+
+        /* Rotate the list, take the current head, process.
+         * This way if the client must be removed from the list it's the
+         * first element and we don't incur into O(N) computation. */
+        listRotate(server.clients);
+        head = listFirst(server.clients);
+        c = listNodeValue(head);
+        /* The following functions do different service checks on the client.
+         * The protocol is that they return non-zero if the client was
+         * terminated. */
+        if (clientsCronHandleTimeout(c)) continue;
+        if (clientsCronResizeQueryBuffer(c)) continue;
+    }
+}
+
 int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     int j, loops = server.cronloops;
     REDIS_NOTUSED(eventLoop);
@@ -627,6 +732,8 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
      * To access a global var is faster than calling time(NULL) */
     server.unixtime = time(NULL);
 
+    trackOperationsPerSecond();
+
     /* We have just 22 bits per object for LRU information.
      * So we use an (eventually wrapping) LRU clock with 10 seconds resolution.
      * 2^22 bits with 10 seconds resoluton is more or less 1.5 years.
@@ -684,9 +791,8 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             zmalloc_used_memory());
     }
 
-    /* Close connections of timedout clients */
-    if ((server.maxidletime && !(loops % 100)) || server.bpop_blocked_clients)
-        closeTimedoutClients();
+    /* We need to do a few operations on clients asynchronously. */
+    clientsCron();
 
     /* Start a scheduled AOF rewrite if this was requested by the user while
      * a BGSAVE was in progress. */
@@ -832,6 +938,12 @@ void createSharedObjects(void) {
         "-LOADING Redis is loading the dataset in memory\r\n"));
     shared.slowscripterr = createObject(REDIS_STRING,sdsnew(
         "-BUSY Redis is busy running a script. You can only call SCRIPT KILL or SHUTDOWN NOSAVE.\r\n"));
+    shared.bgsaveerr = createObject(REDIS_STRING,sdsnew(
+        "-MISCONF Redis is configured to save RDB snapshots, but is currently not able to persist on disk. Commands that may modify the data set are disabled. Please check Redis logs for details about the error.\r\n"));
+    shared.roslaveerr = createObject(REDIS_STRING,sdsnew(
+        "-READONLY You can't write against a read only slave.\r\n"));
+    shared.oomerr = createObject(REDIS_STRING,sdsnew(
+        "-OOM command not allowed when used memory > 'maxmemory'.\r\n"));
     shared.space = createObject(REDIS_STRING,sdsnew(" "));
     shared.colon = createObject(REDIS_STRING,sdsnew(":"));
     shared.plus = createObject(REDIS_STRING,sdsnew("+"));
@@ -852,6 +964,8 @@ void createSharedObjects(void) {
     shared.psubscribebulk = createStringObject("$10\r\npsubscribe\r\n",17);
     shared.punsubscribebulk = createStringObject("$12\r\npunsubscribe\r\n",19);
     shared.del = createStringObject("DEL",3);
+    shared.rpop = createStringObject("RPOP",4);
+    shared.lpop = createStringObject("LPOP",4);
     for (j = 0; j < REDIS_SHARED_INTEGERS; j++) {
         shared.integers[j] = createObject(REDIS_STRING,(void*)(long)j);
         shared.integers[j]->encoding = REDIS_ENCODING_INT;
@@ -865,6 +979,8 @@ void createSharedObjects(void) {
 }
 
 void initServerConfig() {
+    getRandomHexChars(server.runid,REDIS_RUN_ID_SIZE);
+    server.runid[REDIS_RUN_ID_SIZE] = '\0';
     server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
     server.port = REDIS_SERVERPORT;
     server.bindaddr = NULL;
@@ -905,8 +1021,8 @@ void initServerConfig() {
     server.maxmemory = 0;
     server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
     server.maxmemory_samples = 3;
-    server.hash_max_zipmap_entries = REDIS_HASH_MAX_ZIPMAP_ENTRIES;
-    server.hash_max_zipmap_value = REDIS_HASH_MAX_ZIPMAP_VALUE;
+    server.hash_max_ziplist_entries = REDIS_HASH_MAX_ZIPLIST_ENTRIES;
+    server.hash_max_ziplist_value = REDIS_HASH_MAX_ZIPLIST_VALUE;
     server.list_max_ziplist_entries = REDIS_LIST_MAX_ZIPLIST_ENTRIES;
     server.list_max_ziplist_value = REDIS_LIST_MAX_ZIPLIST_VALUE;
     server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
@@ -936,6 +1052,7 @@ void initServerConfig() {
     server.repl_state = REDIS_REPL_NONE;
     server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = 1;
+    server.repl_slave_ro = 1;
     server.repl_down_since = -1;
 
     /* Client output buffer limits */
@@ -962,6 +1079,7 @@ void initServerConfig() {
     populateCommandTable();
     server.delCommand = lookupCommandByCString("del");
     server.multiCommand = lookupCommandByCString("multi");
+    server.lpushCommand = lookupCommandByCString("lpush");
     
     /* Slow log */
     server.slowlog_log_slower_than = REDIS_SLOWLOG_LOG_SLOWER_THAN;
@@ -1083,7 +1201,13 @@ void initServer() {
     server.stat_peak_memory = 0;
     server.stat_fork_time = 0;
     server.stat_rejected_conn = 0;
+    memset(server.ops_sec_samples,0,sizeof(server.ops_sec_samples));
+    server.ops_sec_idx = 0;
+    server.ops_sec_last_sample_time = mstime();
+    server.ops_sec_last_sample_ops = 0;
     server.unixtime = time(NULL);
+    server.lastbgsave_status = REDIS_OK;
+    server.stop_writes_on_bgsave_err = 1;
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
     if (server.ipfd > 0 && aeCreateFileEvent(server.el,server.ipfd,AE_READABLE,
         acceptTcpHandler,NULL) == AE_ERR) oom("creating file event");
@@ -1160,6 +1284,43 @@ void resetCommandTableStats(void) {
     }
 }
 
+/* ========================== Redis OP Array API ============================ */
+
+void redisOpArrayInit(redisOpArray *oa) {
+    oa->ops = NULL;
+    oa->numops = 0;
+}
+
+int redisOpArrayAppend(redisOpArray *oa, struct redisCommand *cmd, int dbid,
+                       robj **argv, int argc, int target)
+{
+    redisOp *op;
+
+    oa->ops = zrealloc(oa->ops,sizeof(redisOp)*(oa->numops+1));
+    op = oa->ops+oa->numops;
+    op->cmd = cmd;
+    op->dbid = dbid;
+    op->argv = argv;
+    op->argc = argc;
+    op->target = target;
+    oa->numops++;
+    return oa->numops;
+}
+
+void redisOpArrayFree(redisOpArray *oa) {
+    while(oa->numops) {
+        int j;
+        redisOp *op;
+
+        oa->numops--;
+        op = oa->ops+oa->numops;
+        for (j = 0; j < op->argc; j++)
+            decrRefCount(op->argv[j]);
+        zfree(op->argv);
+    }
+    zfree(oa->ops);
+}
+
 /* ====================== Commands lookup and execution ===================== */
 
 struct redisCommand *lookupCommand(sds name) {
@@ -1175,10 +1336,42 @@ struct redisCommand *lookupCommandByCString(char *s) {
     return cmd;
 }
 
+/* Propagate the specified command (in the context of the specified database id)
+ * to AOF, Slaves and Monitors.
+ *
+ * flags are an xor between:
+ * + REDIS_PROPAGATE_NONE (no propagation of command at all)
+ * + REDIS_PROPAGATE_AOF (propagate into the AOF file if is enabled)
+ * + REDIS_PROPAGATE_REPL (propagate into the replication link)
+ */
+void propagate(struct redisCommand *cmd, int dbid, robj **argv, int argc,
+               int flags)
+{
+    if (server.aof_state != REDIS_AOF_OFF && flags & REDIS_PROPAGATE_AOF)
+        feedAppendOnlyFile(cmd,dbid,argv,argc);
+    if (flags & REDIS_PROPAGATE_REPL && listLength(server.slaves))
+        replicationFeedSlaves(server.slaves,dbid,argv,argc);
+}
+
+/* Used inside commands to schedule the propagation of additional commands
+ * after the current command is propagated to AOF / Replication. */
+void alsoPropagate(struct redisCommand *cmd, int dbid, robj **argv, int argc,
+                   int target)
+{
+    redisOpArrayAppend(&server.also_propagate,cmd,dbid,argv,argc,target);
+}
+
 /* Call() is the core of Redis execution of a command */
 void call(redisClient *c, int flags) {
     long long dirty, start = ustime(), duration;
 
+    /* Sent the command to clients in MONITOR mode, only if the commands are
+     * not geneated from reading an AOF. */
+    if (listLength(server.monitors) && !server.loading)
+        replicationFeedMonitors(c,server.monitors,c->db->id,c->argv,c->argc);
+
+    /* Call the command. */
+    redisOpArrayInit(&server.also_propagate);
     dirty = server.dirty;
     c->cmd->proc(c);
     dirty = server.dirty-dirty;
@@ -1189,20 +1382,37 @@ void call(redisClient *c, int flags) {
     if (server.loading && c->flags & REDIS_LUA_CLIENT)
         flags &= ~(REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);
 
+    /* Log the command into the Slow log if needed, and populate the
+     * per-command statistics that we show in INFO commandstats. */
     if (flags & REDIS_CALL_SLOWLOG)
         slowlogPushEntryIfNeeded(c->argv,c->argc,duration);
     if (flags & REDIS_CALL_STATS) {
         c->cmd->microseconds += duration;
         c->cmd->calls++;
     }
+
+    /* Propagate the command into the AOF and replication link */
     if (flags & REDIS_CALL_PROPAGATE) {
-        if (server.aof_state != REDIS_AOF_OFF && dirty > 0)
-            feedAppendOnlyFile(c->cmd,c->db->id,c->argv,c->argc);
-        if ((dirty > 0 || c->cmd->flags & REDIS_CMD_FORCE_REPLICATION) &&
-            listLength(server.slaves))
-            replicationFeedSlaves(server.slaves,c->db->id,c->argv,c->argc);
-        if (listLength(server.monitors))
-            replicationFeedMonitors(server.monitors,c->db->id,c->argv,c->argc);
+        int flags = REDIS_PROPAGATE_NONE;
+
+        if (c->cmd->flags & REDIS_CMD_FORCE_REPLICATION)
+            flags |= REDIS_PROPAGATE_REPL;
+        if (dirty)
+            flags |= (REDIS_PROPAGATE_REPL | REDIS_PROPAGATE_AOF);
+        if (flags != REDIS_PROPAGATE_NONE)
+            propagate(c->cmd,c->db->id,c->argv,c->argc,flags);
+    }
+    /* Commands such as LPUSH or BRPOPLPUSH may propagate an additional
+     * PUSH command. */
+    if (server.also_propagate.numops) {
+        int j;
+        redisOp *rop;
+
+        for (j = 0; j < server.also_propagate.numops; j++) {
+            rop = &server.also_propagate.ops[j];
+            propagate(rop->cmd, rop->dbid, rop->argv, rop->argc, rop->target);
+        }
+        redisOpArrayFree(&server.also_propagate);
     }
     server.stat_numcommands++;
 }
@@ -1278,12 +1488,31 @@ int processCommand(redisClient *c) {
     if (server.maxmemory) {
         int retval = freeMemoryIfNeeded();
         if ((c->cmd->flags & REDIS_CMD_DENYOOM) && retval == REDIS_ERR) {
-            addReplyError(c,
-                "command not allowed when used memory > 'maxmemory'");
+            addReply(c, shared.oomerr);
             return REDIS_OK;
         }
     }
 
+    /* Don't accept write commands if there are problems persisting on disk. */
+    if (server.stop_writes_on_bgsave_err &&
+        server.saveparamslen > 0
+        && server.lastbgsave_status == REDIS_ERR &&
+        c->cmd->flags & REDIS_CMD_WRITE)
+    {
+        addReply(c, shared.bgsaveerr);
+        return REDIS_OK;
+    }
+
+    /* Don't accept wirte commands if this is a read only slave. But
+     * accept write commands if this is our master. */
+    if (server.masterhost && server.repl_slave_ro &&
+        !(c->flags & REDIS_MASTER) &&
+        c->cmd->flags & REDIS_CMD_WRITE)
+    {
+        addReply(c, shared.roslaveerr);
+        return REDIS_OK;
+    }
+
     /* Only allow SUBSCRIBE and UNSUBSCRIBE in the context of Pub/Sub */
     if ((dictSize(c->pubsub_channels) > 0 || listLength(c->pubsub_patterns) > 0)
         &&
@@ -1416,6 +1645,17 @@ void echoCommand(redisClient *c) {
     addReplyBulk(c,c->argv[1]);
 }
 
+void timeCommand(redisClient *c) {
+    struct timeval tv;
+
+    /* gettimeofday() can only fail if &tv is a bad addresss so we
+     * don't check for errors. */
+    gettimeofday(&tv,NULL);
+    addReplyMultiBulkLen(c,2);
+    addReplyBulkLongLong(c,tv.tv_sec);
+    addReplyBulkLongLong(c,tv.tv_usec);
+}
+
 /* Convert an amount of bytes into a human readable string in the form
  * of 100B, 2G, 100M, 4K, and so forth. */
 void bytesToHuman(char *s, unsigned long long n) {
@@ -1470,6 +1710,7 @@ sds genRedisInfoString(char *section) {
             "multiplexing_api:%s\r\n"
             "gcc_version:%d.%d.%d\r\n"
             "process_id:%ld\r\n"
+            "run_id:%s\r\n"
             "tcp_port:%d\r\n"
             "uptime_in_seconds:%ld\r\n"
             "uptime_in_days:%ld\r\n"
@@ -1485,6 +1726,7 @@ sds genRedisInfoString(char *section) {
             0,0,0,
 #endif
             (long) getpid(),
+            server.runid,
             server.port,
             uptime,
             uptime/(3600*24),
@@ -1544,12 +1786,14 @@ sds genRedisInfoString(char *section) {
             "changes_since_last_save:%lld\r\n"
             "bgsave_in_progress:%d\r\n"
             "last_save_time:%ld\r\n"
+            "last_bgsave_status:%s\r\n"
             "bgrewriteaof_in_progress:%d\r\n",
             server.loading,
             server.aof_state != REDIS_AOF_OFF,
             server.dirty,
             server.rdb_child_pid != -1,
             server.lastsave,
+            server.lastbgsave_status == REDIS_OK ? "ok" : "err",
             server.aof_child_pid != -1);
 
         if (server.aof_state != REDIS_AOF_OFF) {
@@ -1605,6 +1849,7 @@ sds genRedisInfoString(char *section) {
             "# Stats\r\n"
             "total_connections_received:%lld\r\n"
             "total_commands_processed:%lld\r\n"
+            "instantaneous_ops_per_sec:%lld\r\n"
             "rejected_connections:%lld\r\n"
             "expired_keys:%lld\r\n"
             "evicted_keys:%lld\r\n"
@@ -1615,6 +1860,7 @@ sds genRedisInfoString(char *section) {
             "latest_fork_usec:%lld\r\n",
             server.stat_numconnections,
             server.stat_numcommands,
+            getOperationsPerSecond(),
             server.stat_rejected_conn,
             server.stat_expiredkeys,
             server.stat_evictedkeys,
@@ -1990,16 +2236,17 @@ void daemonize(void) {
 }
 
 void version() {
-    printf("Redis server version %s (%s:%d)\n", REDIS_VERSION,
-        redisGitSHA1(), atoi(redisGitDirty()) > 0);
+    printf("Redis server v=%s sha=%s:%d malloc=%s\n", REDIS_VERSION,
+        redisGitSHA1(), atoi(redisGitDirty()) > 0, ZMALLOC_LIB);
     exit(0);
 }
 
 void usage() {
     fprintf(stderr,"Usage: ./redis-server [/path/to/redis.conf] [options]\n");
     fprintf(stderr,"       ./redis-server - (read config from stdin)\n");
     fprintf(stderr,"       ./redis-server -v or --version\n");
-    fprintf(stderr,"       ./redis-server -h or --help\n\n");
+    fprintf(stderr,"       ./redis-server -h or --help\n");
+    fprintf(stderr,"       ./redis-server --test-memory <megabytes>\n\n");
     fprintf(stderr,"Examples:\n");
     fprintf(stderr,"       ./redis-server (run the server with default conf)\n");
     fprintf(stderr,"       ./redis-server /etc/redis/6379.conf\n");
@@ -2055,6 +2302,8 @@ void setupSignalHandlers(void) {
     return;
 }
 
+void memtest(size_t megabytes, int passes);
+
 int main(int argc, char **argv) {
     long long start;
     struct timeval tv;
@@ -2076,6 +2325,17 @@ int main(int argc, char **argv) {
             strcmp(argv[1], "--version") == 0) version();
         if (strcmp(argv[1], "--help") == 0 ||
             strcmp(argv[1], "-h") == 0) usage();
+        if (strcmp(argv[1], "--test-memory") == 0) {
+            if (argc == 3) {
+                memtest(atoi(argv[2]),50);
+                exit(0);
+            } else {
+                fprintf(stderr,"Please specify the amount of memory to test in megabytes.\n");
+                fprintf(stderr,"Example: ./redis-server --test-memory 4096\n\n");
+                exit(1);
+            }
+        }
+
         /* First argument is the config file name? */
         if (argv[j][0] != '-' || argv[j][1] != '-')
             configfile = argv[j++];