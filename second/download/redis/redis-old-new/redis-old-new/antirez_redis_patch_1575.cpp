@@ -116,9 +116,9 @@ struct redisCommand redisCommandTable[] = {
     {"sdiff",sdiffCommand,-2,REDIS_CMD_DENYOOM,NULL,1,-1,1,0,0},
     {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_DENYOOM,NULL,2,-1,1,0,0},
     {"smembers",sinterCommand,2,0,NULL,1,1,1,0,0},
-    {"zadd",zaddCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
+    {"zadd",zaddCommand,-4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
     {"zincrby",zincrbyCommand,4,REDIS_CMD_DENYOOM,NULL,1,1,1,0,0},
-    {"zrem",zremCommand,3,0,NULL,1,1,1,0,0},
+    {"zrem",zremCommand,-3,0,NULL,1,1,1,0,0},
     {"zremrangebyscore",zremrangebyscoreCommand,4,0,NULL,1,1,1,0,0},
     {"zremrangebyrank",zremrangebyrankCommand,4,0,NULL,1,1,1,0,0},
     {"zunionstore",zunionstoreCommand,-4,REDIS_CMD_DENYOOM,zunionInterGetKeys,0,0,0,0,0},
@@ -635,6 +635,14 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     if ((server.maxidletime && !(loops % 100)) || server.bpop_blocked_clients)
         closeTimedoutClients();
 
+    /* Start a scheduled AOF rewrite if this was requested by the user while
+     * a BGSAVE was in progress. */
+    if (server.bgsavechildpid == -1 && server.bgrewritechildpid == -1 &&
+        server.aofrewrite_scheduled)
+    {
+        rewriteAppendOnlyFileBackground();
+    }
+
     /* Check if a background saving or AOF rewrite in progress terminated. */
     if (server.bgsavechildpid != -1 || server.bgrewritechildpid != -1) {
         int statloc;
@@ -669,9 +677,10 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             }
         }
     } else if (!server.ds_enabled) {
-        /* If there is not a background saving in progress check if
-         * we have to save now */
          time_t now = time(NULL);
+
+        /* If there is not a background saving/rewrite in progress check if
+         * we have to save/rewrite now */
          for (j = 0; j < server.saveparamslen; j++) {
             struct saveparam *sp = server.saveparams+j;
 
@@ -683,6 +692,21 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
                 break;
             }
          }
+
+         /* Trigger an AOF rewrite if needed */
+         if (server.bgsavechildpid == -1 &&
+             server.bgrewritechildpid == -1 &&
+             server.auto_aofrewrite_perc &&
+             server.appendonly_current_size > server.auto_aofrewrite_min_size)
+         {
+            int base = server.auto_aofrewrite_base_size ?
+                            server.auto_aofrewrite_base_size : 1;
+            long long growth = (server.appendonly_current_size*100/base) - 100;
+            if (growth >= server.auto_aofrewrite_perc) {
+                redisLog(REDIS_NOTICE,"Starting automatic rewriting of AOF on %lld%% growth",growth);
+                rewriteAppendOnlyFileBackground();
+            }
+         }
     }
 
     /* Expire a few keys per cycle, only if this is a master.
@@ -832,6 +856,10 @@ void initServerConfig() {
     server.appendonly = 0;
     server.appendfsync = APPENDFSYNC_EVERYSEC;
     server.no_appendfsync_on_rewrite = 0;
+    server.auto_aofrewrite_perc = REDIS_AUTO_AOFREWRITE_PERC;
+    server.auto_aofrewrite_min_size = REDIS_AUTO_AOFREWRITE_MIN_SIZE;
+    server.auto_aofrewrite_base_size = 0;
+    server.aofrewrite_scheduled = 0;
     server.lastfsync = time(NULL);
     server.appendfd = -1;
     server.appendseldb = -1; /* Make sure the first time will not match */
@@ -876,6 +904,7 @@ void initServerConfig() {
     server.masterport = 6379;
     server.master = NULL;
     server.replstate = REDIS_REPL_NONE;
+    server.repl_syncio_timeout = REDIS_REPL_SYNCIO_TIMEOUT;
     server.repl_serve_stale_data = 1;
 
     /* Double constants initialization */
@@ -968,6 +997,7 @@ void initServer() {
     server.stat_keyspace_misses = 0;
     server.stat_keyspace_hits = 0;
     server.stat_peak_memory = 0;
+    server.stat_fork_time = 0;
     server.unixtime = time(NULL);
     aeCreateTimeEvent(server.el, 1, serverCron, NULL, NULL);
     if (server.ipfd > 0 && aeCreateFileEvent(server.el,server.ipfd,AE_READABLE,
@@ -1373,6 +1403,16 @@ sds genRedisInfoString(char *section) {
             server.lastsave,
             server.bgrewritechildpid != -1);
 
+        if (server.appendonly) {
+            info = sdscatprintf(info,
+                "aof_current_size:%lld\r\n"
+                "aof_base_size:%lld\r\n"
+                "aof_pending_rewrite:%d\r\n",
+                (long long) server.appendonly_current_size,
+                (long long) server.auto_aofrewrite_base_size,
+                server.aofrewrite_scheduled);
+        }
+
         if (server.loading) {
             double perc;
             time_t eta, elapsed;
@@ -1446,15 +1486,17 @@ sds genRedisInfoString(char *section) {
             "keyspace_hits:%lld\r\n"
             "keyspace_misses:%lld\r\n"
             "pubsub_channels:%ld\r\n"
-            "pubsub_patterns:%u\r\n",
+            "pubsub_patterns:%u\r\n"
+            "latest_fork_usec:%lld\r\n",
             server.stat_numconnections,
             server.stat_numcommands,
             server.stat_expiredkeys,
             server.stat_evictedkeys,
             server.stat_keyspace_hits,
             server.stat_keyspace_misses,
             dictSize(server.pubsub_channels),
-            listLength(server.pubsub_patterns));
+            listLength(server.pubsub_patterns),
+            server.stat_fork_time);
     }
 
     /* Replication */