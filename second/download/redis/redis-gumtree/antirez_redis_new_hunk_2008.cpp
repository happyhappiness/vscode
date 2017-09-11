    char *line;
    int maxline, j;
   
    if (fp == NULL) {
        if (errno == ENOENT) {
            return REDIS_ERR;
        } else {
            redisLog(REDIS_WARNING,
                "Loading the cluster node config from %s: %s",
                filename, strerror(errno));
            exit(1);
        }
    }

    /* Check if the file is zero-length: if so return REDIS_ERR to signal
     * we have to write the config. */
