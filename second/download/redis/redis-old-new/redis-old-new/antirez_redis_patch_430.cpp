@@ -44,12 +44,12 @@ typedef struct configEnum {
 } configEnum;
 
 configEnum maxmemory_policy_enum[] = {
-    {"volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU},
-    {"volatile-random",REDIS_MAXMEMORY_VOLATILE_RANDOM},
-    {"volatile-ttl",REDIS_MAXMEMORY_VOLATILE_TTL},
-    {"allkeys-lru",REDIS_MAXMEMORY_ALLKEYS_LRU},
-    {"allkeys-random",REDIS_MAXMEMORY_ALLKEYS_RANDOM},
-    {"noeviction",REDIS_MAXMEMORY_NO_EVICTION},
+    {"volatile-lru", MAXMEMORY_VOLATILE_LRU},
+    {"volatile-random",MAXMEMORY_VOLATILE_RANDOM},
+    {"volatile-ttl",MAXMEMORY_VOLATILE_TTL},
+    {"allkeys-lru",MAXMEMORY_ALLKEYS_LRU},
+    {"allkeys-random",MAXMEMORY_ALLKEYS_RANDOM},
+    {"noeviction",MAXMEMORY_NO_EVICTION},
     {NULL, 0}
 };
 
@@ -67,18 +67,18 @@ configEnum syslog_facility_enum[] = {
 };
 
 configEnum loglevel_enum[] = {
-    {"debug", REDIS_DEBUG},
-    {"verbose", REDIS_VERBOSE},
-    {"notice", REDIS_NOTICE},
-    {"warning", REDIS_WARNING},
+    {"debug", LL_DEBUG},
+    {"verbose", LL_VERBOSE},
+    {"notice", LL_NOTICE},
+    {"warning", LL_WARNING},
     {NULL,0}
 };
 
 configEnum supervised_mode_enum[] = {
-    {"upstart", REDIS_SUPERVISED_UPSTART},
-    {"systemd", REDIS_SUPERVISED_SYSTEMD},
-    {"auto", REDIS_SUPERVISED_AUTODETECT},
-    {"no", REDIS_SUPERVISED_NONE},
+    {"upstart", SUPERVISED_UPSTART},
+    {"systemd", SUPERVISED_SYSTEMD},
+    {"auto", SUPERVISED_AUTODETECT},
+    {"no", SUPERVISED_NONE},
     {NULL, 0}
 };
 
@@ -90,7 +90,7 @@ configEnum aof_fsync_enum[] = {
 };
 
 /* Output buffer limits presets. */
-clientBufferLimitsConfig clientBufferLimitsDefaults[REDIS_CLIENT_TYPE_COUNT] = {
+clientBufferLimitsConfig clientBufferLimitsDefaults[CLIENT_TYPE_COUNT] = {
     {0, 0, 0}, /* normal */
     {1024*1024*256, 1024*1024*64, 60}, /* slave */
     {1024*1024*32, 1024*1024*8, 60}  /* pubsub */
@@ -209,7 +209,7 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"bind") && argc >= 2) {
             int j, addresses = argc-1;
 
-            if (addresses > REDIS_BINDADDR_MAX) {
+            if (addresses > CONFIG_BINDADDR_MAX) {
                 err = "Too many bind addresses specified"; goto loaderr;
             }
             for (j = 0; j < addresses; j++)
@@ -236,7 +236,7 @@ void loadServerConfigFromString(char *config) {
             }
         } else if (!strcasecmp(argv[0],"dir") && argc == 2) {
             if (chdir(argv[1]) == -1) {
-                serverLog(REDIS_WARNING,"Can't chdir to '%s': %s",
+                serverLog(LL_WARNING,"Can't chdir to '%s': %s",
                     argv[1], strerror(errno));
                 exit(1);
             }
@@ -308,7 +308,7 @@ void loadServerConfigFromString(char *config) {
             slaveof_linenum = linenum;
             server.masterhost = sdsnew(argv[1]);
             server.masterport = atoi(argv[2]);
-            server.repl_state = REDIS_REPL_CONNECT;
+            server.repl_state = REPL_STATE_CONNECT;
         } else if (!strcasecmp(argv[0],"repl-ping-slave-period") && argc == 2) {
             server.repl_ping_slave_period = atoi(argv[1]);
             if (server.repl_ping_slave_period <= 0) {
@@ -376,15 +376,15 @@ void loadServerConfigFromString(char *config) {
             }
         } else if (!strcasecmp(argv[0],"hz") && argc == 2) {
             server.hz = atoi(argv[1]);
-            if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
-            if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
+            if (server.hz < CONFIG_MIN_HZ) server.hz = CONFIG_MIN_HZ;
+            if (server.hz > CONFIG_MAX_HZ) server.hz = CONFIG_MAX_HZ;
         } else if (!strcasecmp(argv[0],"appendonly") && argc == 2) {
             int yes;
 
             if ((yes = yesnotoi(argv[1])) == -1) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
-            server.aof_state = yes ? REDIS_AOF_ON : REDIS_AOF_OFF;
+            server.aof_state = yes ? AOF_ON : AOF_OFF;
         } else if (!strcasecmp(argv[0],"appendfilename") && argc == 2) {
             if (!pathIsBaseName(argv[1])) {
                 err = "appendfilename can't be a path, just a filename";
@@ -427,8 +427,8 @@ void loadServerConfigFromString(char *config) {
                 err = "argument must be 'yes' or 'no'"; goto loaderr;
             }
         } else if (!strcasecmp(argv[0],"requirepass") && argc == 2) {
-            if (strlen(argv[1]) > REDIS_AUTHPASS_MAX_LEN) {
-                err = "Password is longer than REDIS_AUTHPASS_MAX_LEN";
+            if (strlen(argv[1]) > CONFIG_AUTHPASS_MAX_LEN) {
+                err = "Password is longer than CONFIG_AUTHPASS_MAX_LEN";
                 goto loaderr;
             }
             server.requirepass = zstrdup(argv[1]);
@@ -637,7 +637,7 @@ void loadServerConfigFromString(char *config) {
  * just load a string. */
 void loadServerConfig(char *filename, char *options) {
     sds config = sdsempty();
-    char buf[REDIS_CONFIGLINE_MAX+1];
+    char buf[CONFIG_MAX_LINE+1];
 
     /* Load the file content */
     if (filename) {
@@ -647,12 +647,12 @@ void loadServerConfig(char *filename, char *options) {
             fp = stdin;
         } else {
             if ((fp = fopen(filename,"r")) == NULL) {
-                serverLog(REDIS_WARNING,
+                serverLog(LL_WARNING,
                     "Fatal error, can't open config file '%s'", filename);
                 exit(1);
             }
         }
-        while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL)
+        while(fgets(buf,CONFIG_MAX_LINE+1,fp) != NULL)
             config = sdscat(config,buf);
         if (fp != stdin) fclose(fp);
     }
@@ -718,7 +718,7 @@ void configSetCommand(client *c) {
         zfree(server.rdb_filename);
         server.rdb_filename = zstrdup(o->ptr);
     } config_set_special_field("requirepass") {
-        if (sdslen(o->ptr) > REDIS_AUTHPASS_MAX_LEN) goto badfmt;
+        if (sdslen(o->ptr) > CONFIG_AUTHPASS_MAX_LEN) goto badfmt;
         zfree(server.requirepass);
         server.requirepass = ((char*)o->ptr)[0] ? zstrdup(o->ptr) : NULL;
     } config_set_special_field("masterauth") {
@@ -739,10 +739,10 @@ void configSetCommand(client *c) {
                 return;
             }
             if ((unsigned int) aeGetSetSize(server.el) <
-                server.maxclients + REDIS_EVENTLOOP_FDSET_INCR)
+                server.maxclients + CONFIG_FDSET_INCR)
             {
                 if (aeResizeSetSize(server.el,
-                    server.maxclients + REDIS_EVENTLOOP_FDSET_INCR) == AE_ERR)
+                    server.maxclients + CONFIG_FDSET_INCR) == AE_ERR)
                 {
                     addReplyError(c,"The event loop API used by Redis is not able to handle the specified number of clients");
                     server.maxclients = orig_value;
@@ -754,9 +754,9 @@ void configSetCommand(client *c) {
         int enable = yesnotoi(o->ptr);
 
         if (enable == -1) goto badfmt;
-        if (enable == 0 && server.aof_state != REDIS_AOF_OFF) {
+        if (enable == 0 && server.aof_state != AOF_OFF) {
             stopAppendOnly();
-        } else if (enable && server.aof_state == REDIS_AOF_OFF) {
+        } else if (enable && server.aof_state == AOF_OFF) {
             if (startAppendOnly() == C_ERR) {
                 addReplyError(c,
                     "Unable to turn on AOF. Check server logs.");
@@ -940,8 +940,8 @@ void configSetCommand(client *c) {
       "hz",server.hz,0,LLONG_MAX) {
         /* Hz is more an hint from the user, so we accept values out of range
          * but cap them to reasonable values. */
-        if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
-        if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
+        if (server.hz < CONFIG_MIN_HZ) server.hz = CONFIG_MIN_HZ;
+        if (server.hz > CONFIG_MAX_HZ) server.hz = CONFIG_MAX_HZ;
     } config_set_numerical_field(
       "watchdog-period",ll,0,LLONG_MAX) {
         if (ll)
@@ -954,7 +954,7 @@ void configSetCommand(client *c) {
     } config_set_memory_field("maxmemory",server.maxmemory) {
         if (server.maxmemory) {
             if (server.maxmemory < zmalloc_used_memory()) {
-                serverLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
+                serverLog(LL_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
             }
             freeMemoryIfNeeded();
         }
@@ -1130,7 +1130,7 @@ void configGetCommand(client *c) {
 
     if (stringmatch(pattern,"appendonly",0)) {
         addReplyBulkCString(c,"appendonly");
-        addReplyBulkCString(c,server.aof_state == REDIS_AOF_OFF ? "no" : "yes");
+        addReplyBulkCString(c,server.aof_state == AOF_OFF ? "no" : "yes");
         matches++;
     }
     if (stringmatch(pattern,"dir",0)) {
@@ -1163,13 +1163,13 @@ void configGetCommand(client *c) {
         sds buf = sdsempty();
         int j;
 
-        for (j = 0; j < REDIS_CLIENT_TYPE_COUNT; j++) {
+        for (j = 0; j < CLIENT_TYPE_COUNT; j++) {
             buf = sdscatprintf(buf,"%s %llu %llu %ld",
                     getClientTypeName(j),
                     server.client_obuf_limits[j].hard_limit_bytes,
                     server.client_obuf_limits[j].soft_limit_bytes,
                     (long) server.client_obuf_limits[j].soft_limit_seconds);
-            if (j != REDIS_CLIENT_TYPE_COUNT-1)
+            if (j != CLIENT_TYPE_COUNT-1)
                 buf = sdscatlen(buf," ",1);
         }
         addReplyBulkCString(c,"client-output-buffer-limit");
@@ -1297,7 +1297,7 @@ void rewriteConfigMarkAsProcessed(struct rewriteConfigState *state, const char *
 struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
     FILE *fp = fopen(path,"r");
     struct rewriteConfigState *state = zmalloc(sizeof(*state));
-    char buf[REDIS_CONFIGLINE_MAX+1];
+    char buf[CONFIG_MAX_LINE+1];
     int linenum = -1;
 
     if (fp == NULL && errno != ENOENT) return NULL;
@@ -1310,7 +1310,7 @@ struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
     if (fp == NULL) return state;
 
     /* Read the old file line by line, populate the state. */
-    while(fgets(buf,REDIS_CONFIGLINE_MAX+1,fp) != NULL) {
+    while(fgets(buf,CONFIG_MAX_LINE+1,fp) != NULL) {
         int argc;
         sds *argv;
         sds line = sdstrim(sdsnew(buf),"\r\n\t ");
@@ -1566,7 +1566,7 @@ void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state
     int j;
     char *option = "client-output-buffer-limit";
 
-    for (j = 0; j < REDIS_CLIENT_TYPE_COUNT; j++) {
+    for (j = 0; j < CLIENT_TYPE_COUNT; j++) {
         int force = (server.client_obuf_limits[j].hard_limit_bytes !=
                     clientBufferLimitsDefaults[j].hard_limit_bytes) ||
                     (server.client_obuf_limits[j].soft_limit_bytes !=
@@ -1657,7 +1657,7 @@ void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
         /* Don't blank lines about options the rewrite process
          * don't understand. */
         if (dictFind(state->rewritten,option) == NULL) {
-            serverLog(REDIS_DEBUG,"Not rewritten option: %s", option);
+            serverLog(LL_DEBUG,"Not rewritten option: %s", option);
             continue;
         }
 
@@ -1751,12 +1751,12 @@ int rewriteConfig(char *path) {
 
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,CONFIG_DEFAULT_PID_FILE);
-    rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
-    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,REDIS_TCP_BACKLOG);
+    rewriteConfigNumericalOption(state,"port",server.port,CONFIG_DEFAULT_SERVER_PORT);
+    rewriteConfigNumericalOption(state,"tcp-backlog",server.tcp_backlog,CONFIG_DEFAULT_TCP_BACKLOG);
     rewriteConfigBindOption(state);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
     rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,CONFIG_DEFAULT_UNIX_SOCKET_PERM);
-    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
+    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,CONFIG_DEFAULT_CLIENT_TIMEOUT);
     rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,CONFIG_DEFAULT_TCP_KEEPALIVE);
     rewriteConfigEnumOption(state,"loglevel",server.verbosity,loglevel_enum,CONFIG_DEFAULT_VERBOSITY);
     rewriteConfigStringOption(state,"logfile",server.logfile,CONFIG_DEFAULT_LOGFILE);
@@ -1774,8 +1774,8 @@ int rewriteConfig(char *path) {
     rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
     rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA);
     rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,CONFIG_DEFAULT_SLAVE_READ_ONLY);
-    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,REDIS_REPL_PING_SLAVE_PERIOD);
-    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,REDIS_REPL_TIMEOUT);
+    rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD);
+    rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,CONFIG_DEFAULT_REPL_TIMEOUT);
     rewriteConfigBytesOption(state,"repl-backlog-size",server.repl_backlog_size,CONFIG_DEFAULT_REPL_BACKLOG_SIZE);
     rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
     rewriteConfigYesNoOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY);
@@ -1789,22 +1789,22 @@ int rewriteConfig(char *path) {
     rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,CONFIG_DEFAULT_MAXMEMORY);
     rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,maxmemory_policy_enum,CONFIG_DEFAULT_MAXMEMORY_POLICY);
     rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,CONFIG_DEFAULT_MAXMEMORY_SAMPLES);
-    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != REDIS_AOF_OFF,0);
+    rewriteConfigYesNoOption(state,"appendonly",server.aof_state != AOF_OFF,0);
     rewriteConfigStringOption(state,"appendfilename",server.aof_filename,CONFIG_DEFAULT_AOF_FILENAME);
     rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,aof_fsync_enum,CONFIG_DEFAULT_AOF_FSYNC);
     rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
-    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
-    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
-    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
+    rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,AOF_REWRITE_PERC);
+    rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,AOF_REWRITE_MIN_SIZE);
+    rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,LUA_SCRIPT_TIME_LIMIT);
     rewriteConfigYesNoOption(state,"cluster-enabled",server.cluster_enabled,0);
     rewriteConfigStringOption(state,"cluster-config-file",server.cluster_configfile,CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
     rewriteConfigYesNoOption(state,"cluster-require-full-coverage",server.cluster_require_full_coverage,REDIS_CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE);
     rewriteConfigNumericalOption(state,"cluster-node-timeout",server.cluster_node_timeout,REDIS_CLUSTER_DEFAULT_NODE_TIMEOUT);
     rewriteConfigNumericalOption(state,"cluster-migration-barrier",server.cluster_migration_barrier,REDIS_CLUSTER_DEFAULT_MIGRATION_BARRIER);
     rewriteConfigNumericalOption(state,"cluster-slave-validity-factor",server.cluster_slave_validity_factor,REDIS_CLUSTER_DEFAULT_SLAVE_VALIDITY);
-    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,REDIS_SLOWLOG_LOG_SLOWER_THAN);
+    rewriteConfigNumericalOption(state,"slowlog-log-slower-than",server.slowlog_log_slower_than,CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN);
     rewriteConfigNumericalOption(state,"latency-monitor-threshold",server.latency_monitor_threshold,CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD);
-    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,REDIS_SLOWLOG_MAX_LEN);
+    rewriteConfigNumericalOption(state,"slowlog-max-len",server.slowlog_max_len,CONFIG_DEFAULT_SLOWLOG_MAX_LEN);
     rewriteConfigNotifykeyspaceeventsOption(state);
     rewriteConfigNumericalOption(state,"hash-max-ziplist-entries",server.hash_max_ziplist_entries,OBJ_HASH_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"hash-max-ziplist-value",server.hash_max_ziplist_value,OBJ_HASH_MAX_ZIPLIST_VALUE);
@@ -1819,7 +1819,7 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"hz",server.hz,CONFIG_DEFAULT_HZ);
     rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
     rewriteConfigYesNoOption(state,"aof-load-truncated",server.aof_load_truncated,CONFIG_DEFAULT_AOF_LOAD_TRUNCATED);
-    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,REDIS_SUPERVISED_NONE);
+    rewriteConfigEnumOption(state,"supervised",server.supervised_mode,supervised_mode_enum,SUPERVISED_NONE);
 
     /* Rewrite Sentinel config if in Sentinel mode. */
     if (server.sentinel_mode) rewriteConfigSentinelOption(state);
@@ -1862,10 +1862,10 @@ void configCommand(client *c) {
             return;
         }
         if (rewriteConfig(server.configfile) == -1) {
-            serverLog(REDIS_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
+            serverLog(LL_WARNING,"CONFIG REWRITE failed: %s", strerror(errno));
             addReplyErrorFormat(c,"Rewriting config file: %s", strerror(errno));
         } else {
-            serverLog(REDIS_WARNING,"CONFIG REWRITE executed with success.");
+            serverLog(LL_WARNING,"CONFIG REWRITE executed with success.");
             addReply(c,shared.ok);
         }
     } else {