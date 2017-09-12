serverLog(REDIS_WARNING,
                "Can't rewrite append only file in background: fork: %s",
                strerror(errno));