        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
        if (rdbLoad(server.rdb_filename) != C_OK) {
            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            replicationAbortSyncTransfer();
            return;
        }
        /* Final setup of the connected slave <- master link */
