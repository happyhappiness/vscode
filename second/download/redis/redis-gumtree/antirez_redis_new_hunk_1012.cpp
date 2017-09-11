    else mode = "standalone";

    if (server.syslog_enabled) {
        serverLog(LL_NOTICE,
            "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
            REDIS_VERSION,
            redisGitSHA1(),
