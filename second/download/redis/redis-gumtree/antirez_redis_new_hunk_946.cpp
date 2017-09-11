
    if (eof_reached) {
        if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
            serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
            replicationAbortSyncTransfer();
            return;
        }
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
        signalFlushedDb(-1);
        emptyDb(replicationEmptyDbCallback);
        /* Before loading the DB into memory we need to delete the readable
         * handler, otherwise it will get called recursively since
         * rdbLoad() will call the event loop to process events from time to
         * time for non blocking loading. */
        aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
        if (rdbLoad(server.rdb_filename) != C_OK) {
            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            replicationAbortSyncTransfer();
            return;
        }
        /* Final setup of the connected slave <- master link */
        zfree(server.repl_transfer_tmpfile);
        close(server.repl_transfer_fd);
        replicationCreateMasterClient(server.repl_transfer_s);
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
        /* Restart the AOF subsystem now that we finished the sync. This
         * will trigger an AOF rewrite, and when done will start appending
         * to the new file. */
        if (server.aof_state != AOF_OFF) {
            int retry = 10;

            stopAppendOnly();
            while (retry-- && startAppendOnly() == C_ERR) {
                serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
                sleep(1);
            }
            if (!retry) {
                serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
                exit(1);
            }
        }
