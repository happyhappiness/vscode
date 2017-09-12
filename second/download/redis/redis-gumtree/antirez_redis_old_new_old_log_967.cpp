serverLog(REDIS_WARNING,
                "I/O error reading bulk count from MASTER: %s",
                strerror(errno));