redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));