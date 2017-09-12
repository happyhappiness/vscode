
    len = dsKeyToPath(db,buf,key);
    memcpy(buf2,buf,len);
    snprintf(buf2+len,sizeof(buf2)-len,"_%ld_%ld",(long)time(NULL),(long)val);
    while ((fp = fopen(buf2,"w")) == NULL) {
        if (errno == ENOSPC) {
            redisLog(REDIS_WARNING,"Diskstore: No space left on device. Please make room and wait 30 seconds for Redis to continue.");
