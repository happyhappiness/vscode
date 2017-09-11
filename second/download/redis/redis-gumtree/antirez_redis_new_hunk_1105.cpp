    if (!fp) {
        serverLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));
        return C_ERR;
    }

    rioInitWithFile(&rdb,fp);
    if (rdbSaveRio(&rdb,&error) == C_ERR) {
        errno = error;
        goto werr;
    }
