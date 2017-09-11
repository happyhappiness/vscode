    server.repl_transfer_left -= nread;
    /* Check if the transfer is now complete */
    if (server.repl_transfer_left == 0) {
        if (rename(server.repl_transfer_tmpfile,server.dbfilename) == -1) {
            redisLog(REDIS_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
            replicationAbortSyncTransfer();
            return;
