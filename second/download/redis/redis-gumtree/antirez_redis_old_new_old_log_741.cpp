serverLog(REDIS_WARNING,
                "Error trying to rename the temporary AOF file: %s", strerror(errno));