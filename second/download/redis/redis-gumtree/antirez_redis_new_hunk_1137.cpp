        checkTcpBacklogSettings();
        loadDataFromDisk();
        if (server.cluster_enabled) {
            if (verifyClusterConfigWithData() == C_ERR) {
                serverLog(REDIS_WARNING,
                    "You can't have keys in a DB different than DB 0 when in "
                    "Cluster mode. Exiting.");
