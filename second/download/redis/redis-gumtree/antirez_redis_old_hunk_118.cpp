    else if (server.sentinel_mode) mode = "sentinel";
    else mode = "standalone";

    if (server.syslog_enabled) {
        serverLog(LL_NOTICE,
            "Redis %s (%s/%d) %s bit, %s mode, port %d, pid %ld ready to start.",
            REDIS_VERSION,
            redisGitSHA1(),
            strtol(redisGitDirty(),NULL,10) > 0,
            (sizeof(long) == 8) ? "64" : "32",
            mode, server.port,
            (long) getpid()
        );
    } else {
        snprintf(buf,1024*16,ascii_logo,
