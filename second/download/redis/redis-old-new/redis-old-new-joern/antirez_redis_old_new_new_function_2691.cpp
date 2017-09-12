void restoreCommand(redisClient *c) {
    long ttl;
    rio payload;
    int type;
    robj *obj;

    /* Make sure this key does not already exist here... */
    if (lookupKeyWrite(c->db,c->argv[1]) != NULL) {
        addReplyError(c,"Target key name is busy.");
        return;
    }

    /* Check if the TTL value makes sense */
    if (getLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != REDIS_OK) {
        return;
    } else if (ttl < 0) {
        addReplyError(c,"Invalid TTL value, must be >= 0");
        return;
    }

    payload = rioInitWithBuffer(c->argv[3]->ptr);
    if (((type = rdbLoadObjectType(&payload)) == -1) ||
        ((obj = rdbLoadObject(type,&payload)) == NULL))
    {
        addReplyError(c,"Bad data format");
        return;
    }

    /* Create the key and set the TTL if any */
    dbAdd(c->db,c->argv[1],obj);
    if (ttl) setExpire(c->db,c->argv[1],time(NULL)+ttl);
    addReply(c,shared.ok);
}