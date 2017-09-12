int dsSet(redisDb *db, robj *key, robj *val) {
    char buf[1024], buf2[1024];
    FILE *fp;
    int retval, len;

    len = dsKeyToPath(db,buf,key);
    memcpy(buf2,buf,len);
    snprintf(buf2+len,sizeof(buf2)-len,"-%ld-%ld",(long)time(NULL),(long)val);
    while ((fp = fopen(buf2,"w")) == NULL) {
        if (errno == ENOSPC) {
            redisLog(REDIS_WARNING,"Diskstore: No space left on device. Please make room and wait 30 seconds for Redis to continue.");
            sleep(30);
        } else {
            redisLog(REDIS_WARNING,"diskstore error opening %s: %s",
                buf2, strerror(errno));
            redisPanic("Unrecoverable diskstore error. Exiting.");
        }
    }
    if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
        return REDIS_ERR;
    fclose(fp);
    if (retval == 0) {
        /* Expired key. Unlink failing not critical */
        unlink(buf);
        unlink(buf2);
    } else {
        /* Use rename for atomic updadte of value */
        if (rename(buf2,buf) == -1) {
            redisLog(REDIS_WARNING,"rename(2) returned an error: %s",
                strerror(errno));
            redisPanic("Unrecoverable diskstore error. Exiting.");
        }
    }
    return REDIS_OK;
}