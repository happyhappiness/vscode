            strerror(errno));
        return REDIS_ERR;
    }
    dumpsize = atoi(buf+1);
    redisLog(REDIS_NOTICE,"Receiving %d bytes data dump from MASTER",dumpsize);
    /* Read the bulk write data on a temp file */
