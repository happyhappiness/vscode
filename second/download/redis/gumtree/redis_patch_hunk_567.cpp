     freeReplicationBacklog(); /* Don't allow our chained slaves to PSYNC. */
 
     /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
      * and the server.repl_master_runid and repl_master_initial_offset are
      * already populated. */
     if (psync_result == PSYNC_NOT_SUPPORTED) {
-        redisLog(REDIS_NOTICE,"Retrying with SYNC...");
+        serverLog(LL_NOTICE,"Retrying with SYNC...");
         if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
-            redisLog(REDIS_WARNING,"I/O error writing to MASTER: %s",
+            serverLog(LL_WARNING,"I/O error writing to MASTER: %s",
                 strerror(errno));
             goto error;
         }
     }
 
     /* Prepare a suitable temp file for bulk transfer */
