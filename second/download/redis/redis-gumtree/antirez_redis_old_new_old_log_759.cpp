serverLog(REDIS_WARNING,
            "Can't open %s in order to acquire a lock: %s",
            filename, strerror(errno));