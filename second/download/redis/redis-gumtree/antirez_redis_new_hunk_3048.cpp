            strerror(errno));
        return REDIS_ERR;
    }

    rdb = rioInitWithFile(fp);
    if (rdbWriteRaw(&rdb,"REDIS0002",9) == -1) goto werr;

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;
        dict *d = db->dict;
