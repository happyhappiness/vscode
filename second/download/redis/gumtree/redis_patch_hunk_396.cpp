         /* Handle the AOF write error. */
         if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
             /* We can't recover when the fsync policy is ALWAYS since the
              * reply for the client is already in the output buffers, and we
              * have the contract with the user that on acknowledged write data
              * is synced on disk. */
-            redisLog(REDIS_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
+            serverLog(LL_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
             exit(1);
         } else {
             /* Recover from failed write leaving data into the buffer. However
              * set an error to stop accepting writes as long as the error
              * condition is not cleared. */
-            server.aof_last_write_status = REDIS_ERR;
+            server.aof_last_write_status = C_ERR;
 
             /* Trim the sds buffer if there was a partial write, and there
              * was no way to undo it with ftruncate(2). */
             if (nwritten > 0) {
                 server.aof_current_size += nwritten;
                 sdsrange(server.aof_buf,nwritten,-1);
             }
             return; /* We'll try again on the next call... */
         }
     } else {
         /* Successful write(2). If AOF was in error state, restore the
          * OK state and log the event. */
-        if (server.aof_last_write_status == REDIS_ERR) {
-            redisLog(REDIS_WARNING,
+        if (server.aof_last_write_status == C_ERR) {
+            serverLog(LL_WARNING,
                 "AOF write error looks solved, Redis can write again.");
-            server.aof_last_write_status = REDIS_OK;
+            server.aof_last_write_status = C_OK;
         }
     }
     server.aof_current_size += nwritten;
 
     /* Re-use AOF buffer when it is small enough. The maximum comes from the
      * arena size of 4k minus some overhead (but is otherwise arbitrary). */
