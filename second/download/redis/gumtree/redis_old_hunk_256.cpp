}

void moveCommand(redisClient *c) {
    robj *o;
    redisDb *src, *dst;
    int srcid;
    long long dbid, expire;

    /* Obtain source and target DB pointers */
    src = c->db;
    srcid = c->db->id;

    if (getLongLongFromObject(c->argv[2],&dbid) == REDIS_ERR ||
