snprintf(buf,1024*16,ascii_logo,
        REDIS_VERSION,
        redisGitSHA1(),
        strtol(redisGitDirty(),NULL,10) > 0,
        (sizeof(long) == 8) ? "64" : "32",
        server.cluster_enabled ? "cluster" : "stand alone",
        server.port,
        (long) getpid()
    );