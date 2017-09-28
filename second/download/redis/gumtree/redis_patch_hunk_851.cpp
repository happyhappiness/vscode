         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
             serverLog(LL_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));
+            aofClosePipes();
             return C_ERR;
         }
         serverLog(LL_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
         server.aof_rewrite_scheduled = 0;
         server.aof_rewrite_time_start = time(NULL);
