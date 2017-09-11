
    if (!server.sentinel_mode) {
        /* Things not needed when running in Sentinel mode. */
        redisLog(REDIS_WARNING,"Server started, Redis version " REDIS_VERSION);
    #ifdef __linux__
        linuxMemoryWarnings();
    #endif
        checkTcpBacklogSettings();
        loadDataFromDisk();
        if (server.cluster_enabled) {
            if (verifyClusterConfigWithData() == REDIS_ERR) {
                redisLog(REDIS_WARNING,
                    "You can't have keys in a DB different than DB 0 when in "
                    "Cluster mode. Exiting.");
                exit(1);
            }
        }
        if (server.ipfd_count > 0)
            redisLog(REDIS_NOTICE,"The server is now ready to accept connections on port %d", server.port);
        if (server.sofd > 0)
            redisLog(REDIS_NOTICE,"The server is now ready to accept connections at %s", server.unixsocket);
    } else {
        sentinelIsRunning();
    }

    /* Warning the user about suspicious maxmemory setting. */
    if (server.maxmemory > 0 && server.maxmemory < 1024*1024) {
        redisLog(REDIS_WARNING,"WARNING: You specified a maxmemory value that is less than 1MB (current value is %llu bytes). Are you sure this is what you really want?", server.maxmemory);
    }

    aeSetBeforeSleepProc(server.el,beforeSleep);
