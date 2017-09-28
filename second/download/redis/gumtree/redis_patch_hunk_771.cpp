     if (!usemark) {
         if (server.repl_transfer_read == server.repl_transfer_size)
             eof_reached = 1;
     }
 
     if (eof_reached) {
+        int aof_is_enabled = server.aof_state != AOF_OFF;
+
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             cancelReplicationHandshake();
             return;
         }
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
+        /* We need to stop any AOFRW fork before flusing and parsing
+         * RDB, otherwise we'll create a copy-on-write disaster. */
+        if(aof_is_enabled) stopAppendOnly();
         signalFlushedDb(-1);
-        emptyDb(replicationEmptyDbCallback);
+        emptyDb(
+            -1,
+            server.repl_slave_lazy_flush ? EMPTYDB_ASYNC : EMPTYDB_NO_FLAGS,
+            replicationEmptyDbCallback);
         /* Before loading the DB into memory we need to delete the readable
          * handler, otherwise it will get called recursively since
          * rdbLoad() will call the event loop to process events from time to
          * time for non blocking loading. */
         aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
-        if (rdbLoad(server.rdb_filename) != C_OK) {
+        rdbSaveInfo rsi = RDB_SAVE_INFO_INIT;
+        if (rdbLoad(server.rdb_filename,&rsi) != C_OK) {
             serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             cancelReplicationHandshake();
+            /* Re-enable the AOF if we disabled it earlier, in order to restore
+             * the original configuration. */
+            if (aof_is_enabled) restartAOF();
             return;
         }
         /* Final setup of the connected slave <- master link */
         zfree(server.repl_transfer_tmpfile);
         close(server.repl_transfer_fd);
-        replicationCreateMasterClient(server.repl_transfer_s);
+        replicationCreateMasterClient(server.repl_transfer_s,rsi.repl_stream_db);
+        server.repl_state = REPL_STATE_CONNECTED;
+        /* After a full resynchroniziation we use the replication ID and
+         * offset of the master. The secondary ID / offset are cleared since
+         * we are starting a new history. */
+        memcpy(server.replid,server.master->replid,sizeof(server.replid));
+        server.master_repl_offset = server.master->reploff;
+        clearReplicationId2();
+        /* Let's create the replication backlog if needed. Slaves need to
+         * accumulate the backlog regardless of the fact they have sub-slaves
+         * or not, in order to behave correctly if they are promoted to
+         * masters after a failover. */
+        if (server.repl_backlog == NULL) createReplicationBacklog();
+
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
          * to the new file. */
-        if (server.aof_state != AOF_OFF) {
-            int retry = 10;
-
-            stopAppendOnly();
-            while (retry-- && startAppendOnly() == C_ERR) {
-                serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
-                sleep(1);
-            }
-            if (!retry) {
-                serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
-                exit(1);
-            }
-        }
+        if (aof_is_enabled) restartAOF();
     }
-
     return;
 
 error:
     cancelReplicationHandshake();
     return;
 }
