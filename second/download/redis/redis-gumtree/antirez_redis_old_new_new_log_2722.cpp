redisLog(REDIS_WARNING,
                    "Short write trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));