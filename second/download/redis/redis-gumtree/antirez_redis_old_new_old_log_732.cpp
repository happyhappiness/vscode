serverLog(REDIS_WARNING,"Error opening /setting AOF rewrite IPC pipes: %s",
        strerror(errno));