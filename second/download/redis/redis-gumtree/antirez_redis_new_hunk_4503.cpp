        return REDIS_ERR;
    }
    /* Read the bulk write count */
    if (syncReadLine(fd,buf,1024,3600) == -1) {
        close(fd);
        redisLog(REDIS_WARNING,"I/O error reading bulk count from MASTER: %s",
            strerror(errno));
