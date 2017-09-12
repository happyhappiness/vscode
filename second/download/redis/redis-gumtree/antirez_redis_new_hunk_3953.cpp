            strerror(errno));
        return REDIS_ERR;
    }
    if (buf[0] == '-') {
        close(fd);
        redisLog(REDIS_WARNING,"MASTER aborted replication with an error: %s",
            buf+1);
        return REDIS_ERR;
    } else if (buf[0] != '$') {
        close(fd);
        redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
        return REDIS_ERR;
