            strerror(errno));
        return REDIS_ERR;
    }
    dumpsize = atoi(buf);
    redisLog(REDIS_NOTICE,"Receiving %d bytes data dump from MASTER",dumpsize);
    /* Read the bulk write data on a temp file */
    snprintf(tmpfile,256,"temp-%d.%ld.rdb",(int)time(NULL),(long int)random());
