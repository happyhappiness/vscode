@@ -171,6 +171,7 @@ struct redisCommand redisCommandTable[] = {
     {"zrem",zremCommand,-3,"w",0,NULL,1,1,1,0,0},
     {"zremrangebyscore",zremrangebyscoreCommand,4,"w",0,NULL,1,1,1,0,0},
     {"zremrangebyrank",zremrangebyrankCommand,4,"w",0,NULL,1,1,1,0,0},
+    {"zremrangebylex",zremrangebylexCommand,4,"w",0,NULL,1,1,1,0,0},
     {"zunionstore",zunionstoreCommand,-4,"wm",0,zunionInterGetKeys,0,0,0,0,0},
     {"zinterstore",zinterstoreCommand,-4,"wm",0,zunionInterGetKeys,0,0,0,0,0},
     {"zrange",zrangeCommand,-4,"r",0,NULL,1,1,1,0,0},
@@ -179,6 +180,7 @@ struct redisCommand redisCommandTable[] = {
     {"zrangebylex",zrangebylexCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zrevrangebylex",zrevrangebylexCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zcount",zcountCommand,4,"r",0,NULL,1,1,1,0,0},
+    {"zlexcount",zlexcountCommand,4,"r",0,NULL,1,1,1,0,0},
     {"zrevrange",zrevrangeCommand,-4,"r",0,NULL,1,1,1,0,0},
     {"zcard",zcardCommand,2,"r",0,NULL,1,1,1,0,0},
     {"zscore",zscoreCommand,3,"r",0,NULL,1,1,1,0,0},
@@ -272,9 +274,9 @@ struct redisCommand redisCommandTable[] = {
     {"wait",waitCommand,3,"rs",0,NULL,0,0,0,0,0},
     {"pfselftest",pfselftestCommand,1,"r",0,NULL,0,0,0,0,0},
     {"pfadd",pfaddCommand,-2,"wm",0,NULL,1,1,1,0,0},
-    {"pfcount",pfcountCommand,2,"w",0,NULL,1,1,1,0,0},
+    {"pfcount",pfcountCommand,-2,"w",0,NULL,1,1,1,0,0},
     {"pfmerge",pfmergeCommand,-2,"wm",0,NULL,1,-1,1,0,0},
-    {"pfgetreg",pfgetregCommand,2,"r",0,NULL,0,0,0,0,0}
+    {"pfdebug",pfdebugCommand,-3,"w",0,NULL,0,0,0,0,0}
 };
 
 struct evictionPoolEntry *evictionPoolAlloc(void);
@@ -1421,6 +1423,7 @@ void initServerConfig() {
     server.set_max_intset_entries = REDIS_SET_MAX_INTSET_ENTRIES;
     server.zset_max_ziplist_entries = REDIS_ZSET_MAX_ZIPLIST_ENTRIES;
     server.zset_max_ziplist_value = REDIS_ZSET_MAX_ZIPLIST_VALUE;
+    server.hll_sparse_max_bytes = REDIS_DEFAULT_HLL_SPARSE_MAX_BYTES;
     server.shutdown_asap = 0;
     server.repl_ping_slave_period = REDIS_REPL_PING_SLAVE_PERIOD;
     server.repl_timeout = REDIS_REPL_TIMEOUT;
@@ -1555,24 +1558,28 @@ void adjustOpenFilesLimit(void) {
                     redisLog(REDIS_WARNING,"Your current 'ulimit -n' "
                         "of %llu is not enough for Redis to start. "
                         "Please increase your open file limit to at least "
-                        "%llu. Exiting.", oldlimit, maxfiles);
+                        "%llu. Exiting.",
+                        (unsigned long long) oldlimit,
+                        (unsigned long long) maxfiles);
                     exit(1);
                 }
                 redisLog(REDIS_WARNING,"You requested maxclients of %d "
                     "requiring at least %llu max file descriptors.",
-                    old_maxclients, maxfiles);
+                    old_maxclients,
+                    (unsigned long long) maxfiles);
                 redisLog(REDIS_WARNING,"Redis can't set maximum open files "
                     "to %llu because of OS error: %s.",
-                    maxfiles, strerror(setrlimit_error));
+                    (unsigned long long) maxfiles, strerror(setrlimit_error));
                 redisLog(REDIS_WARNING,"Current maximum open files is %llu. "
                     "maxclients has been reduced to %d to compensate for "
                     "low ulimit. "
                     "If you need higher maxclients increase 'ulimit -n'.",
-                    oldlimit, server.maxclients);
+                    (unsigned long long) oldlimit, server.maxclients);
             } else {
                 redisLog(REDIS_NOTICE,"Increased maximum number of open files "
                     "to %llu (it was originally set to %llu).",
-                    maxfiles, oldlimit);
+                    (unsigned long long) maxfiles,
+                    (unsigned long long) oldlimit);
             }
         }
     }