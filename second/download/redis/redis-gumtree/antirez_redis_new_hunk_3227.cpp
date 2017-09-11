            strerror(errno));
        return REDIS_ERR;
    }
    if (fwrite("REDIS0002",9,1,fp) == 0) goto werr;
    for (j = 0; j < server.dbnum; j++) {
        redisDb *db = server.db+j;
        dict *d = db->dict;
