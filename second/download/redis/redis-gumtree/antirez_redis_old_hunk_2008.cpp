    char *line;
    int maxline, j;
   
    if (fp == NULL) return REDIS_ERR;

    /* Check if the file is zero-length: if so return REDIS_ERR to signal
     * we have to write the config. */
