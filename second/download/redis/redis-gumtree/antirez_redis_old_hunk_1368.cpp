    fd = anetTcpNonBlockBestEffortBindConnect(NULL,
        server.masterhost,server.masterport,REDIS_BIND_ADDR);
    if (fd == -1) {
        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
            strerror(errno));
        return REDIS_ERR;
    }
