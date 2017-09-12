__redisSetError(c,REDIS_ERR_EOF,
            sdsnew("Server closed the connection"));