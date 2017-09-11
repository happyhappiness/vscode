        if (rdbLoad(server.rdb_filename) != C_OK) {
            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            cancelReplicationHandshake();
            return;
        }
        /* Final setup of the connected slave <- master link */
