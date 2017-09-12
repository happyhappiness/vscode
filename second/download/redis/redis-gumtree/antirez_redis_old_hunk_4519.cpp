        }
    } else {
        /* Parent */
        redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
        server.bgsaveinprogress = 1;
        return REDIS_OK;
