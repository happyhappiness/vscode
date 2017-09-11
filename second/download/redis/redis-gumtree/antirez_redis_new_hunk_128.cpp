    }

    if (eof_reached) {
        int aof_is_enabled = server.aof_state != AOF_OFF;
        if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
            serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
            cancelReplicationHandshake();
            return;
        }
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
        if(aof_is_enabled) /* we need to stop any AOFRW fork before flusing and parsing RDB, otherwise we'll create a CoW disaster */
            stopAppendOnly();
        signalFlushedDb(-1);
        emptyDb(
            -1,
