    }

    rioInitWithFile(&rdb,fp);
    if (rdbWriteRaw(&rdb,"REDIS0004",9) == -1) goto werr;

    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;
