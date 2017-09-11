        if (rdbLoad(server.rdb_filename,&rsi) != C_OK) {
            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            cancelReplicationHandshake();
            /* Re-enable the AOF if we disabled it earlier, in order to restore
             * the original configuration. */
            if (aof_is_enabled) restartAOF();
            return;
        }
        /* Final setup of the connected slave <- master link */
