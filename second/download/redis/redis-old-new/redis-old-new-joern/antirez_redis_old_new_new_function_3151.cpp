int dsSet(redisDb *db, robj *key, robj *val) {
    char buf[1024], buf2[1024];
    FILE *fp;
    int retval, len;

    len = dsKeyToPath(db,buf,key);
    memcpy(buf2,buf,len);
    snprintf(buf2+len,sizeof(buf2)-len,"_%ld_%ld",(long)time(NULL),(long)val);
    fp = fopen(buf2,"w");
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