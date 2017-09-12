
void setbitCommand(redisClient *c) {
    robj *o;
    char *err = "bit is not an integer or out of range";
    size_t bitoffset;
    long long bitvalue;
    int byte, bit, on;

    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
        return;

    if (getLongLongFromObjectOrReply(c,c->argv[3],&bitvalue,err) != REDIS_OK)
        return;

    /* A bit can only be set to be on or off... */
    if (bitvalue & ~1) {
        addReplyError(c,err);
        return;
    }

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o == NULL) {
        o = createObject(REDIS_STRING,sdsempty());
        dbAdd(c->db,c->argv[1],o);
    } else {
        if (checkType(c,o,REDIS_STRING)) return;
