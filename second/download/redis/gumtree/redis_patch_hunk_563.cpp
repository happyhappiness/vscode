         if (server.repl_transfer_read == server.repl_transfer_size)
             eof_reached = 1;
     }
 
     if (eof_reached) {
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
-            redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
-            replicationAbortSyncTransfer();
+            serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
+            cancelReplicationHandshake();
             return;
         }
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
         signalFlushedDb(-1);
         emptyDb(replicationEmptyDbCallback);
         /* Before loading the DB into memory we need to delete the readable
          * handler, otherwise it will get called recursively since
          * rdbLoad() will call the event loop to process events from time to
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
-        if (rdbLoad(server.rdb_filename) != REDIS_OK) {
-            redisLog(REDIS_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
-            replicationAbortSyncTransfer();
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
+        if (rdbLoad(server.rdb_filename) != C_OK) {
+            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
+            cancelReplicationHandshake();
             return;
         }
         /* Final setup of the connected slave <- master link */
         zfree(server.repl_transfer_tmpfile);
         close(server.repl_transfer_fd);
-        server.master = createClient(server.repl_transfer_s);
-        server.master->flags |= REDIS_MASTER;
-        server.master->authenticated = 1;
-        server.repl_state = REDIS_REPL_CONNECTED;
-        server.master->reploff = server.repl_master_initial_offset;
-        memcpy(server.master->replrunid, server.repl_master_runid,
-            sizeof(server.repl_master_runid));
-        /* If master offset is set to -1, this master is old and is not
-         * PSYNC capable, so we flag it accordingly. */
-        if (server.master->reploff == -1)
-            server.master->flags |= REDIS_PRE_PSYNC;
-        redisLog(REDIS_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
+        replicationCreateMasterClient(server.repl_transfer_s);
+        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
          * to the new file. */
-        if (server.aof_state != REDIS_AOF_OFF) {
+        if (server.aof_state != AOF_OFF) {
             int retry = 10;
 
             stopAppendOnly();
-            while (retry-- && startAppendOnly() == REDIS_ERR) {
-                redisLog(REDIS_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
+            while (retry-- && startAppendOnly() == C_ERR) {
+                serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                 sleep(1);
             }
             if (!retry) {
-                redisLog(REDIS_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
+                serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
                 exit(1);
             }
         }
     }
 
     return;
 
 error:
-    replicationAbortSyncTransfer();
+    cancelReplicationHandshake();
     return;
 }
 
 /* Send a synchronous command to the master. Used to send AUTH and
  * REPLCONF commands before starting the replication with SYNC.
  *
