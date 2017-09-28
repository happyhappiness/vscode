}

void moveCommand(redisClient *c) {
    robj *o;
    redisDb *src, *dst;
    int srcid;
    long long dbid;

    if (server.cluster_enabled) {
        addReplyError(c,"MOVE is not allowed in cluster mode");
        return;
    }

    /* Obtain source and target DB pointers */
    src = c->db;
    srcid = c->db->id;

    if (getLongLongFromObject(c->argv[2],&dbid) == REDIS_ERR ||
