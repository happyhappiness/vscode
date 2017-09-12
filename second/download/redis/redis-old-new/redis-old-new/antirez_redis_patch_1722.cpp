@@ -174,7 +174,7 @@ struct redisCommand readonlyCommandTable[] = {
     {"flushdb",flushdbCommand,1,0,NULL,0,0,0,0},
     {"flushall",flushallCommand,1,0,NULL,0,0,0,0},
     {"sort",sortCommand,-2,REDIS_CMD_DENYOOM,NULL,1,1,1,0},
-    {"info",infoCommand,1,0,NULL,0,0,0,0},
+    {"info",infoCommand,-1,0,NULL,0,0,0,0},
     {"monitor",monitorCommand,1,0,NULL,0,0,0,0},
     {"ttl",ttlCommand,2,0,NULL,1,1,1,0},
     {"persist",persistCommand,2,0,NULL,1,1,1,0},
@@ -1156,204 +1156,277 @@ void bytesToHuman(char *s, unsigned long long n) {
 /* Create the string returned by the INFO command. This is decoupled
  * by the INFO command itself as we need to report the same information
  * on memory corruption problems. */
-sds genRedisInfoString(void) {
-    sds info;
+sds genRedisInfoString(char *section) {
+    sds info = sdsempty();
     time_t uptime = time(NULL)-server.stat_starttime;
     int j, numcommands;
     char hmem[64];
     struct rusage self_ru, c_ru;
     unsigned long lol, bib;
+    int allsections = 0, defsections = 0;
+    int sections = 0;
+    
+    if (section) {
+        allsections = strcasecmp(section,"all") == 0;
+        allsections = strcasecmp(section,"default") == 0;
+    }
 
     getrusage(RUSAGE_SELF, &self_ru);
     getrusage(RUSAGE_CHILDREN, &c_ru);
     getClientsMaxBuffers(&lol,&bib);
-
     bytesToHuman(hmem,zmalloc_used_memory());
-    info = sdscatprintf(sdsempty(),
-        "redis_version:%s\r\n"
-        "redis_git_sha1:%s\r\n"
-        "redis_git_dirty:%d\r\n"
-        "arch_bits:%s\r\n"
-        "multiplexing_api:%s\r\n"
-        "process_id:%ld\r\n"
-        "uptime_in_seconds:%ld\r\n"
-        "uptime_in_days:%ld\r\n"
-        "lru_clock:%ld\r\n"
-        "used_cpu_sys:%.2f\r\n"
-        "used_cpu_user:%.2f\r\n"
-        "used_cpu_sys_childrens:%.2f\r\n"
-        "used_cpu_user_childrens:%.2f\r\n"
-        "connected_clients:%d\r\n"
-        "connected_slaves:%d\r\n"
-        "client_longest_output_list:%lu\r\n"
-        "client_biggest_input_buf:%lu\r\n"
-        "blocked_clients:%d\r\n"
-        "used_memory:%zu\r\n"
-        "used_memory_human:%s\r\n"
-        "used_memory_rss:%zu\r\n"
-        "mem_fragmentation_ratio:%.2f\r\n"
-        "use_tcmalloc:%d\r\n"
-        "loading:%d\r\n"
-        "aof_enabled:%d\r\n"
-        "changes_since_last_save:%lld\r\n"
-        "bgsave_in_progress:%d\r\n"
-        "last_save_time:%ld\r\n"
-        "bgrewriteaof_in_progress:%d\r\n"
-        "total_connections_received:%lld\r\n"
-        "total_commands_processed:%lld\r\n"
-        "expired_keys:%lld\r\n"
-        "evicted_keys:%lld\r\n"
-        "keyspace_hits:%lld\r\n"
-        "keyspace_misses:%lld\r\n"
-        "hash_max_zipmap_entries:%zu\r\n"
-        "hash_max_zipmap_value:%zu\r\n"
-        "pubsub_channels:%ld\r\n"
-        "pubsub_patterns:%u\r\n"
-        "ds_enabled:%d\r\n"
-        "role:%s\r\n"
-        ,REDIS_VERSION,
-        redisGitSHA1(),
-        strtol(redisGitDirty(),NULL,10) > 0,
-        (sizeof(long) == 8) ? "64" : "32",
-        aeGetApiName(),
-        (long) getpid(),
-        uptime,
-        uptime/(3600*24),
-        (unsigned long) server.lruclock,
-        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
-        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
-        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
-        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
-        listLength(server.clients)-listLength(server.slaves),
-        listLength(server.slaves),
-        lol, bib,
-        server.bpop_blocked_clients,
-        zmalloc_used_memory(),
-        hmem,
-        zmalloc_get_rss(),
-        zmalloc_get_fragmentation_ratio(),
-#ifdef USE_TCMALLOC
-        1,
-#else
-        0,
-#endif
-        server.loading,
-        server.appendonly,
-        server.dirty,
-        server.bgsavechildpid != -1 || server.bgsavethread != (pthread_t) -1,
-        server.lastsave,
-        server.bgrewritechildpid != -1,
-        server.stat_numconnections,
-        server.stat_numcommands,
-        server.stat_expiredkeys,
-        server.stat_evictedkeys,
-        server.stat_keyspace_hits,
-        server.stat_keyspace_misses,
-        server.hash_max_zipmap_entries,
-        server.hash_max_zipmap_value,
-        dictSize(server.pubsub_channels),
-        listLength(server.pubsub_patterns),
-        server.ds_enabled != 0,
-        server.masterhost == NULL ? "master" : "slave"
-    );
-    if (server.masterhost) {
+
+    /* Server */
+    if (allsections || defsections || !strcasecmp(section,"server")) {
+        if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
-            "master_host:%s\r\n"
-            "master_port:%d\r\n"
-            "master_link_status:%s\r\n"
-            "master_last_io_seconds_ago:%d\r\n"
-            "master_sync_in_progress:%d\r\n"
-            ,server.masterhost,
-            server.masterport,
-            (server.replstate == REDIS_REPL_CONNECTED) ?
-                "up" : "down",
-            server.master ? ((int)(time(NULL)-server.master->lastinteraction)) : -1,
-            server.replstate == REDIS_REPL_TRANSFER
-        );
-
-        if (server.replstate == REDIS_REPL_TRANSFER) {
-            info = sdscatprintf(info,
-                "master_sync_left_bytes:%ld\r\n"
-                "master_sync_last_io_seconds_ago:%d\r\n"
-                ,(long)server.repl_transfer_left,
-                (int)(time(NULL)-server.repl_transfer_lastio)
+            "# Server\r\n"
+            "redis_version:%s\r\n"
+            "redis_git_sha1:%s\r\n"
+            "redis_git_dirty:%d\r\n"
+            "arch_bits:%s\r\n"
+            "multiplexing_api:%s\r\n"
+            "process_id:%ld\r\n"
+            "tcp_port:%d\r\n"
+            "uptime_in_seconds:%ld\r\n"
+            "uptime_in_days:%ld\r\n"
+            "lru_clock:%ld\r\n",
+            REDIS_VERSION,
+            redisGitSHA1(),
+            strtol(redisGitDirty(),NULL,10) > 0,
+            (sizeof(long) == 8) ? "64" : "32",
+            aeGetApiName(),
+            (long) getpid(),
+            server.port,
+            uptime,
+            uptime/(3600*24),
+            (unsigned long) server.lruclock);
+    }
+
+    /* Clients */
+    if (allsections || defsections || !strcasecmp(section,"clients")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+            "# Clients\r\n"
+            "connected_clients:%d\r\n"
+            "client_longest_output_list:%lu\r\n"
+            "client_biggest_input_buf:%lu\r\n"
+            "blocked_clients:%d\r\n",
+            listLength(server.clients)-listLength(server.slaves),
+            lol, bib,
+            server.bpop_blocked_clients);
+    }
+
+    /* Memory */
+    if (allsections || defsections || !strcasecmp(section,"memory")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+            "# Memory\r\n"
+            "used_memory:%zu\r\n"
+            "used_memory_human:%s\r\n"
+            "used_memory_rss:%zu\r\n"
+            "mem_fragmentation_ratio:%.2f\r\n"
+            "use_tcmalloc:%d\r\n",
+            zmalloc_used_memory(),
+            hmem,
+            zmalloc_get_rss(),
+            zmalloc_get_fragmentation_ratio(),
+    #ifdef USE_TCMALLOC
+            1
+    #else
+            0
+    #endif
             );
+        info = sdscat(info,"allocation_stats:");
+        for (j = 0; j <= ZMALLOC_MAX_ALLOC_STAT; j++) {
+            size_t count = zmalloc_allocations_for_size(j);
+            if (count) {
+                if (info[sdslen(info)-1] != ':') info = sdscatlen(info,",",1);
+                info = sdscatprintf(info,"%s%d=%zu",
+                    (j == ZMALLOC_MAX_ALLOC_STAT) ? ">=" : "",
+                    j,count);
+            }
         }
     }
-    if (server.ds_enabled) {
-        lockThreadedIO();
+
+    /* Persistence */
+    if (allsections || defsections || !strcasecmp(section,"persistence")) {
+        if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
-            "cache_max_memory:%llu\r\n"
-            "cache_blocked_clients:%lu\r\n"
-            ,(unsigned long long) server.cache_max_memory,
-            (unsigned long) server.cache_blocked_clients
-        );
-        unlockThreadedIO();
+            "# Persistence\r\n"
+            "loading:%d\r\n"
+            "aof_enabled:%d\r\n"
+            "changes_since_last_save:%lld\r\n"
+            "bgsave_in_progress:%d\r\n"
+            "last_save_time:%ld\r\n"
+            "bgrewriteaof_in_progress:%d\r\n",
+            server.loading,
+            server.appendonly,
+            server.dirty,
+                server.bgsavechildpid != -1 ||
+                server.bgsavethread != (pthread_t) -1,
+            server.lastsave,
+            server.bgrewritechildpid != -1);
+
+        if (server.loading) {
+            double perc;
+            time_t eta, elapsed;
+            off_t remaining_bytes = server.loading_total_bytes-
+                                    server.loading_loaded_bytes;
+
+            perc = ((double)server.loading_loaded_bytes /
+                   server.loading_total_bytes) * 100;
+
+            elapsed = time(NULL)-server.loading_start_time;
+            if (elapsed == 0) {
+                eta = 1; /* A fake 1 second figure if we don't have
+                            enough info */
+            } else {
+                eta = (elapsed*remaining_bytes)/server.loading_loaded_bytes;
+            }
+
+            info = sdscatprintf(info,
+                "loading_start_time:%ld\r\n"
+                "loading_total_bytes:%llu\r\n"
+                "loading_loaded_bytes:%llu\r\n"
+                "loading_loaded_perc:%.2f\r\n"
+                "loading_eta_seconds:%ld\r\n"
+                ,(unsigned long) server.loading_start_time,
+                (unsigned long long) server.loading_total_bytes,
+                (unsigned long long) server.loading_loaded_bytes,
+                perc,
+                eta
+            );
+        }
     }
-    if (server.loading) {
-        double perc;
-        time_t eta, elapsed;
-        off_t remaining_bytes = server.loading_total_bytes-
-                                server.loading_loaded_bytes;
-
-        perc = ((double)server.loading_loaded_bytes /
-               server.loading_total_bytes) * 100;
-
-        elapsed = time(NULL)-server.loading_start_time;
-        if (elapsed == 0) {
-            eta = 1; /* A fake 1 second figure if we don't have enough info */
-        } else {
-            eta = (elapsed*remaining_bytes)/server.loading_loaded_bytes;
+
+    /* Diskstore */
+    if (allsections || defsections || !strcasecmp(section,"diskstore")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+            "# Diskstore\r\n"
+            "ds_enabled:%d\r\n",
+            server.ds_enabled != 0);
+        if (server.ds_enabled) {
+            lockThreadedIO();
+            info = sdscatprintf(info,
+                "cache_max_memory:%llu\r\n"
+                "cache_blocked_clients:%lu\r\n"
+                ,(unsigned long long) server.cache_max_memory,
+                (unsigned long) server.cache_blocked_clients
+            );
+            unlockThreadedIO();
         }
+    }
 
+    /* Stats */
+    if (allsections || defsections || !strcasecmp(section,"stats")) {
+        if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
-            "loading_start_time:%ld\r\n"
-            "loading_total_bytes:%llu\r\n"
-            "loading_loaded_bytes:%llu\r\n"
-            "loading_loaded_perc:%.2f\r\n"
-            "loading_eta_seconds:%ld\r\n"
-            ,(unsigned long) server.loading_start_time,
-            (unsigned long long) server.loading_total_bytes,
-            (unsigned long long) server.loading_loaded_bytes,
-            perc,
-            eta
-        );
+            "# Stats\r\n"
+            "total_connections_received:%lld\r\n"
+            "total_commands_processed:%lld\r\n"
+            "expired_keys:%lld\r\n"
+            "evicted_keys:%lld\r\n"
+            "keyspace_hits:%lld\r\n"
+            "keyspace_misses:%lld\r\n"
+            "pubsub_channels:%ld\r\n"
+            "pubsub_patterns:%u\r\n",
+            server.stat_numconnections,
+            server.stat_numcommands,
+            server.stat_expiredkeys,
+            server.stat_evictedkeys,
+            server.stat_keyspace_hits,
+            server.stat_keyspace_misses,
+            dictSize(server.pubsub_channels),
+            listLength(server.pubsub_patterns));
     }
 
-    info = sdscat(info,"allocation_stats:");
-    for (j = 0; j <= ZMALLOC_MAX_ALLOC_STAT; j++) {
-        size_t count = zmalloc_allocations_for_size(j);
-        if (count) {
-            if (info[sdslen(info)-1] != ':') info = sdscatlen(info,",",1);
-            info = sdscatprintf(info,"%s%d=%zu",
-                (j == ZMALLOC_MAX_ALLOC_STAT) ? ">=" : "",
-                j,count);
+    /* Replication */
+    if (allsections || defsections || !strcasecmp(section,"replication")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+            "# Replication\r\n"
+            "role:%s\r\n",
+            server.masterhost == NULL ? "master" : "slave");
+        if (server.masterhost) {
+            info = sdscatprintf(info,
+                "master_host:%s\r\n"
+                "master_port:%d\r\n"
+                "master_link_status:%s\r\n"
+                "master_last_io_seconds_ago:%d\r\n"
+                "master_sync_in_progress:%d\r\n"
+                ,server.masterhost,
+                server.masterport,
+                (server.replstate == REDIS_REPL_CONNECTED) ?
+                    "up" : "down",
+                server.master ?
+                ((int)(time(NULL)-server.master->lastinteraction)) : -1,
+                server.replstate == REDIS_REPL_TRANSFER
+            );
+
+            if (server.replstate == REDIS_REPL_TRANSFER) {
+                info = sdscatprintf(info,
+                    "master_sync_left_bytes:%ld\r\n"
+                    "master_sync_last_io_seconds_ago:%d\r\n"
+                    ,(long)server.repl_transfer_left,
+                    (int)(time(NULL)-server.repl_transfer_lastio)
+                );
+            }
         }
+        info = sdscatprintf(info,
+            "connected_slaves:%d\r\n",
+            listLength(server.slaves));
     }
-    info = sdscat(info,"\r\n");
 
-    numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
-    for (j = 0; j < numcommands; j++) {
-        struct redisCommand *c = readonlyCommandTable+j;
-        info = sdscatprintf(info,"command_%s:microseconds:%lld\r\n",
-            c->name, c->microseconds);
+    /* Profiling */
+    if (allsections || defsections || !strcasecmp(section,"profiling")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info,
+        "# Profiling\r\n"
+        "used_cpu_sys:%.2f\r\n"
+        "used_cpu_user:%.2f\r\n"
+        "used_cpu_sys_childrens:%.2f\r\n"
+        "used_cpu_user_childrens:%.2f\r\n",
+        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
+        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
+        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
+        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000);
+
+        numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
+        for (j = 0; j < numcommands; j++) {
+            struct redisCommand *c = readonlyCommandTable+j;
+            info = sdscatprintf(info,"used_time_cmd_%s:%lld\r\n",
+                c->name, c->microseconds);
+        }
     }
 
-    for (j = 0; j < server.dbnum; j++) {
-        long long keys, vkeys;
+    /* Key space */
+    if (allsections || defsections || !strcasecmp(section,"keyspace")) {
+        if (sections++) info = sdscat(info,"\r\n");
+        info = sdscatprintf(info, "# Keyspace\r\n");
+        for (j = 0; j < server.dbnum; j++) {
+            long long keys, vkeys;
 
-        keys = dictSize(server.db[j].dict);
-        vkeys = dictSize(server.db[j].expires);
-        if (keys || vkeys) {
-            info = sdscatprintf(info, "db%d:keys=%lld,expires=%lld\r\n",
-                j, keys, vkeys);
+            keys = dictSize(server.db[j].dict);
+            vkeys = dictSize(server.db[j].expires);
+            if (keys || vkeys) {
+                info = sdscatprintf(info, "db%d:keys=%lld,expires=%lld\r\n",
+                    j, keys, vkeys);
+            }
         }
     }
     return info;
 }
 
 void infoCommand(redisClient *c) {
-    sds info = genRedisInfoString();
+    char *section = c->argc == 2 ? c->argv[1]->ptr : "default";
+
+    if (c->argc > 2) {
+        addReply(c,shared.syntaxerr);
+        return;
+    }
+    sds info = genRedisInfoString(section);
     addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n",
         (unsigned long)sdslen(info)));
     addReplySds(c,info);
@@ -1619,7 +1692,7 @@ void segvHandler(int sig, siginfo_t *info, void *secret) {
 
     redisLog(REDIS_WARNING,
         "======= Ooops! Redis %s got signal: -%d- =======", REDIS_VERSION, sig);
-    infostring = genRedisInfoString();
+    infostring = genRedisInfoString("all");
     redisLog(REDIS_WARNING, "%s",infostring);
     /* It's not safe to sdsfree() the returned string under memory
      * corruption conditions. Let it leak as we are going to abort */