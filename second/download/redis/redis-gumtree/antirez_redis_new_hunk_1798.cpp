    }

    /* Check if the transfer is now complete */
    if (!usemark) {
        if (server.repl_transfer_read == server.repl_transfer_size)
            eof_reached = 1;
    }

    if (eof_reached) {
        if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
            redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
            replicationAbortSyncTransfer();
