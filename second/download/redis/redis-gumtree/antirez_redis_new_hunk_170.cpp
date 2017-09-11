         * time for non blocking loading. */
        aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
        rdbSaveInfo rsi = RDB_SAVE_INFO_INIT;
        if (rdbLoad(server.rdb_filename,&rsi) != C_OK) {
            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            cancelReplicationHandshake();
            return;
        }
        /* Final setup of the connected slave <- master link */
        zfree(server.repl_transfer_tmpfile);
        close(server.repl_transfer_fd);
        replicationCreateMasterClient(server.repl_transfer_s,rsi.repl_stream_db);
        server.repl_state = REPL_STATE_CONNECTED;
        /* After a full resynchroniziation we use the replication ID and
         * offset of the master. The secondary ID / offset are cleared since
         * we are starting a new history. */
        memcpy(server.replid,server.master->replid,sizeof(server.replid));
        server.master_repl_offset = server.master->reploff;
        clearReplicationId2();
        /* Let's create the replication backlog if needed. Slaves need to
         * accumulate the backlog regardless of the fact they have sub-slaves
         * or not, in order to behave correctly if they are promoted to
         * masters after a failover. */
        if (server.repl_backlog == NULL) createReplicationBacklog();

        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Finished with success");
        /* Restart the AOF subsystem now that we finished the sync. This
         * will trigger an AOF rewrite, and when done will start appending
