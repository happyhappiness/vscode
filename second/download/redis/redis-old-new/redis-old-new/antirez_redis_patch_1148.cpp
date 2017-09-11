@@ -164,12 +164,9 @@ void loadServerConfigFromString(char *config) {
         } else if (!strcasecmp(argv[0],"logfile") && argc == 2) {
             FILE *logfp;
 
+            zfree(server.logfile);
             server.logfile = zstrdup(argv[1]);
-            if (!strcasecmp(server.logfile,"stdout")) {
-                zfree(server.logfile);
-                server.logfile = NULL;
-            }
-            if (server.logfile) {
+            if (server.logfile[0] != '\0') {
                 /* Test if we are able to open the file. The server will not
                  * be able to abort just for this problem later... */
                 logfp = fopen(server.logfile,"a");
@@ -1550,54 +1547,55 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);
     rewriteConfigStringOption(state,"bindaddr",server.bindaddr,NULL);
     rewriteConfigStringOption(state,"unixsocket",server.unixsocket,NULL);
-    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,0);
-    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,0);
-    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,0);
+    rewriteConfigOctalOption(state,"unixsocketperm",server.unixsocketperm,REDIS_DEFAULT_UNIX_SOCKET_PERM);
+    rewriteConfigNumericalOption(state,"timeout",server.maxidletime,REDIS_MAXIDLETIME);
+    rewriteConfigNumericalOption(state,"tcp-keepalive",server.tcpkeepalive,REDIS_DEFAULT_TCP_KEEPALIVE);
     rewriteConfigEnumOption(state,"loglevel",server.verbosity,
         "debug", REDIS_DEBUG,
         "verbose", REDIS_VERBOSE,
         "notice", REDIS_NOTICE,
         "warning", REDIS_WARNING,
-        NULL, REDIS_NOTICE);
-    rewriteConfigStringOption(state,"logfile",server.logfile,"stdout");
-    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,0);
+        NULL, REDIS_DEFAULT_VERBOSITY);
+    rewriteConfigStringOption(state,"logfile",server.logfile,REDIS_DEFAULT_LOGFILE);
+    rewriteConfigYesNoOption(state,"syslog-enabled",server.syslog_enabled,REDIS_DEFAULT_SYSLOG_ENABLED);
     rewriteConfigStringOption(state,"syslog-ident",server.syslog_ident,REDIS_DEFAULT_SYSLOG_IDENT);
     rewriteConfigSyslogfacilityOption(state);
     rewriteConfigSaveOption(state);
     rewriteConfigNumericalOption(state,"databases",server.dbnum,REDIS_DEFAULT_DBNUM);
-    rewriteConfigYesNoOption(state,"stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err,1);
-    rewriteConfigYesNoOption(state,"rdbcompression",server.rdb_compression,1);
-    rewriteConfigYesNoOption(state,"rdbchecksum",server.rdb_checksum,1);
-    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,"dump.rdb");
+    rewriteConfigYesNoOption(state,"stop-writes-on-bgsave-error",server.stop_writes_on_bgsave_err,REDIS_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR);
+    rewriteConfigYesNoOption(state,"rdbcompression",server.rdb_compression,REDIS_DEFAULT_RDB_COMPRESSION);
+    rewriteConfigYesNoOption(state,"rdbchecksum",server.rdb_checksum,REDIS_DEFAULT_RDB_CHECKSUM);
+    rewriteConfigStringOption(state,"dbfilename",server.rdb_filename,REDIS_DEFAULT_RDB_FILENAME);
     rewriteConfigDirOption(state);
     rewriteConfigSlaveofOption(state);
     rewriteConfigStringOption(state,"masterauth",server.masterauth,NULL);
-    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,1);
-    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,1);
+    rewriteConfigYesNoOption(state,"slave-serve-stale-data",server.repl_serve_stale_data,REDIS_DEFAULT_SLAVE_SERVE_STALE_DATA);
+    rewriteConfigYesNoOption(state,"slave-read-only",server.repl_slave_ro,REDIS_DEFAULT_SLAVE_READ_ONLY);
     rewriteConfigNumericalOption(state,"repl-ping-slave-period",server.repl_ping_slave_period,REDIS_REPL_PING_SLAVE_PERIOD);
     rewriteConfigNumericalOption(state,"repl-timeout",server.repl_timeout,REDIS_REPL_TIMEOUT);
     rewriteConfigNumericalOption(state,"repl-backlog-size",server.repl_backlog_size,REDIS_DEFAULT_REPL_BACKLOG_SIZE);
     rewriteConfigBytesOption(state,"repl-backlog-ttl",server.repl_backlog_time_limit,REDIS_DEFAULT_REPL_BACKLOG_TIME_LIMIT);
+    rewriteConfigBytesOption(state,"repl-disable-tcp-nodelay",server.repl_disable_tcp_nodelay,REDIS_DEFAULT_REPL_DISABLE_TCP_NODELAY);
     rewriteConfigNumericalOption(state,"slave-priority",server.slave_priority,REDIS_DEFAULT_SLAVE_PRIORITY);
     rewriteConfigStringOption(state,"requirepass",server.requirepass,NULL);
     rewriteConfigNumericalOption(state,"maxclients",server.maxclients,REDIS_MAX_CLIENTS);
-    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,0);
+    rewriteConfigBytesOption(state,"maxmemory",server.maxmemory,REDIS_DEFAULT_MAXMEMORY);
     rewriteConfigEnumOption(state,"maxmemory-policy",server.maxmemory_policy,
         "volatile-lru", REDIS_MAXMEMORY_VOLATILE_LRU,
         "allkeys-lru", REDIS_MAXMEMORY_ALLKEYS_LRU,
         "volatile-random", REDIS_MAXMEMORY_VOLATILE_RANDOM,
         "allkeys-random", REDIS_MAXMEMORY_ALLKEYS_RANDOM,
         "volatile-ttl", REDIS_MAXMEMORY_VOLATILE_TTL,
         "noeviction", REDIS_MAXMEMORY_NO_EVICTION,
-        NULL, REDIS_MAXMEMORY_VOLATILE_LRU);
-    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,3);
+        NULL, REDIS_DEFAULT_MAXMEMORY_POLICY);
+    rewriteConfigNumericalOption(state,"maxmemory-samples",server.maxmemory_samples,REDIS_DEFAULT_MAXMEMORY_SAMPLES);
     rewriteConfigAppendonlyOption(state);
     rewriteConfigEnumOption(state,"appendfsync",server.aof_fsync,
         "eveysec", AOF_FSYNC_EVERYSEC,
         "always", AOF_FSYNC_ALWAYS,
         "no", AOF_FSYNC_NO,
-        NULL, AOF_FSYNC_EVERYSEC);
-    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,0);
+        NULL, REDIS_DEFAULT_AOF_FSYNC);
+    rewriteConfigYesNoOption(state,"no-appendfsync-on-rewrite",server.aof_no_fsync_on_rewrite,REDIS_DEFAULT_AOF_NO_FSYNC_ON_REWRITE);
     rewriteConfigNumericalOption(state,"auto-aof-rewrite-percentage",server.aof_rewrite_perc,REDIS_AOF_REWRITE_PERC);
     rewriteConfigBytesOption(state,"auto-aof-rewrite-min-size",server.aof_rewrite_min_size,REDIS_AOF_REWRITE_MIN_SIZE);
     rewriteConfigNumericalOption(state,"lua-time-limit",server.lua_time_limit,REDIS_LUA_TIME_LIMIT);
@@ -1614,10 +1612,10 @@ int rewriteConfig(char *path) {
     rewriteConfigNumericalOption(state,"set-max-intset-entries",server.set_max_intset_entries,REDIS_SET_MAX_INTSET_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-entries",server.zset_max_ziplist_entries,REDIS_ZSET_MAX_ZIPLIST_ENTRIES);
     rewriteConfigNumericalOption(state,"zset-max-ziplist-value",server.zset_max_ziplist_value,REDIS_ZSET_MAX_ZIPLIST_VALUE);
-    rewriteConfigYesNoOption(state,"active-rehashing",server.activerehashing,1);
+    rewriteConfigYesNoOption(state,"active-rehashing",server.activerehashing,REDIS_DEFAULT_ACTIVE_REHASHING);
     rewriteConfigClientoutputbufferlimitOption(state);
     rewriteConfigNumericalOption(state,"hz",server.hz,REDIS_DEFAULT_HZ);
-    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,1);
+    rewriteConfigYesNoOption(state,"aof-rewrite-incremental-fsync",server.aof_rewrite_incremental_fsync,REDIS_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC);
 
     /* Step 3: remove all the orphaned lines in the old file, that is, lines
      * that were used by a config option and are no longer used, like in case