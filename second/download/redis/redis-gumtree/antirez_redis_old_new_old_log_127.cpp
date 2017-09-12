serverLog(LL_NOTICE,
            "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
            REDIS_VERSION,
            redisGitSHA1(),
            strtol(redisGitDirty(),NULL,10) > 0,
            (sizeof(long) == 8) ? "64" : "32",
            mode, server.port,
            (long) getpid()
        );