serverLog(REDIS_WARNING,"Can't seek the end of the AOF file: %s",
                    strerror(errno));