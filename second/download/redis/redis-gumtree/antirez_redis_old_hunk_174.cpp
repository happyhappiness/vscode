    }

    /* PSYNC failed or is not supported: we want our slaves to resync with us
     * as well, if we have any (chained replication case). The mater may
     * transfer us an entirely different data set and we have no way to
     * incrementally feed our slaves after that. */
    disconnectSlaves(); /* Force our slaves to resync with us as well. */
    freeReplicationBacklog(); /* Don't allow our chained slaves to PSYNC. */

    /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
     * and the server.repl_master_runid and repl_master_initial_offset are
     * already populated. */
    if (psync_result == PSYNC_NOT_SUPPORTED) {
        serverLog(LL_NOTICE,"Retrying with SYNC...");
