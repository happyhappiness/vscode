            AE_ERR)
    {
        close(fd);
        serverLog(REDIS_WARNING,"Can't create readable event for SYNC");
        return REDIS_ERR;
    }

