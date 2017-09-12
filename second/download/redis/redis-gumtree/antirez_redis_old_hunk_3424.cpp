    buf[0] = '_';
    memcpy(buf+1,hex,40);
    buf[41] = '\0';
}

int dsSet(redisDb *db, robj *key, robj *val) {
    char buf[1024];
    FILE *fp;
    int retval;

    dsKeyToPath(db,buf,key);
    fp = fopen(buf,"w");
    if ((retval = rdbSaveKeyValuePair(fp,db,key,val,time(NULL))) == -1)
        return REDIS_ERR;
    fclose(fp);
    if (retval == 0) unlink(buf); /* Expired key. Unlink failing not critical */
    return REDIS_OK;
}

