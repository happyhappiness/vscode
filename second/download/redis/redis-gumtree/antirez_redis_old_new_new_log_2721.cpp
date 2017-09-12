redisLog(REDIS_WARNING,
                    "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));