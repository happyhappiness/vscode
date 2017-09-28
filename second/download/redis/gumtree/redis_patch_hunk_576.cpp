         server.repl_backlog)
     {
         time_t idle = server.unixtime - server.repl_no_slaves_since;
 
         if (idle > server.repl_backlog_time_limit) {
             freeReplicationBacklog();
-            redisLog(REDIS_NOTICE,
+            serverLog(LL_NOTICE,
                 "Replication backlog freed after %d seconds "
                 "without connected slaves.",
                 (int) server.repl_backlog_time_limit);
         }
     }
 
     /* If AOF is disabled and we no longer have attached slaves, we can
      * free our Replication Script Cache as there is no need to propagate
      * EVALSHA at all. */
     if (listLength(server.slaves) == 0 &&
-        server.aof_state == REDIS_AOF_OFF &&
+        server.aof_state == AOF_OFF &&
         listLength(server.repl_scriptcache_fifo) != 0)
     {
         replicationScriptCacheFlush();
     }
 
     /* If we are using diskless replication and there are slaves waiting
