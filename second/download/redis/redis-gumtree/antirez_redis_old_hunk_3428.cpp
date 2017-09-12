    FILE *fp;
    int retval;

    dsKeyToPath(buf,key);
    fp = fopen(buf,"w");
    if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
        return REDIS_ERR;
    fclose(fp);
    if (retval == 0) unlink(buf); /* Expired key */
    return REDIS_OK;
}

robj *dsGet(redisDb *db, robj *key, time_t *expire) {
    return createStringObject("foo",3);
}

int dsDel(redisDb *db, robj *key) {
}

int dsExists(redisDb *db, robj *key) {
