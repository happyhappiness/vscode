    if ((server.saveparamslen > 0 && !nosave) || save) {
        serverLog(REDIS_NOTICE,"Saving the final RDB snapshot before exiting.");
        /* Snapshotting. Perform a SYNC SAVE and exit */
        if (rdbSave(server.rdb_filename) != REDIS_OK) {
            /* Ooops.. error saving! The best we can do is to continue
             * operating. Note that if there was a background saving process,
             * in the next cron() Redis will be notified that the background
             * saving aborted, handling special stuff like slaves pending for
             * synchronization... */
            serverLog(REDIS_WARNING,"Error trying to save the DB, can't exit.");
            return REDIS_ERR;
        }
    }
    if (server.daemonize || server.pidfile) {
