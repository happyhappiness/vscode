serverLog(REDIS_WARNING,
                "I/O error reading PING reply from master: %s",
                strerror(errno));