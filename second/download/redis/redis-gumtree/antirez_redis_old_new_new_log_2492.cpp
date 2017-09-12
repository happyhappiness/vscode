__redisReaderSetError(r,REDIS_ERR_PROTOCOL,
            "No support for nested multi bulk replies with depth > 2");