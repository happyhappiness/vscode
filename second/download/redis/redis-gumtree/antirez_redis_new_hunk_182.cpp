        if (rdbLoad(server.rdb_filename) != C_OK) {
            serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
            cancelReplicationHandshake();
            if (aof_is_enabled) /* re-enable so that on the next attempt, we can detect that AOF was enabled */
                restartAOF();
            return;
        }
        /* Final setup of the connected slave <- master link */
