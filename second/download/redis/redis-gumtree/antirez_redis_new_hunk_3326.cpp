    int appendonly = server.appendonly;
    long loops = 0;

    if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
        fclose(fp);
        return REDIS_ERR;
    }

    if (fp == NULL) {
        redisLog(REDIS_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
