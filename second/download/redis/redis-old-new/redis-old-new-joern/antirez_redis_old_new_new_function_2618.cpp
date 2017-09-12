void incrbyfloatCommand(redisClient *c) {
    long double incr, value;
    robj *o, *new;

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o != NULL && checkType(c,o,REDIS_STRING)) return;
    if (getLongDoubleFromObjectOrReply(c,o,&value,NULL) != REDIS_OK ||
        getLongDoubleFromObjectOrReply(c,c->argv[2],&incr,NULL) != REDIS_OK)
        return;

    value += incr;
    if (isnan(value) || isinf(value)) {
        addReplyError(c,"increment would produce NaN or Infinity");
        return;
    }
    new = createStringObjectFromLongDouble(value);
    if (o)
        dbOverwrite(c->db,c->argv[1],new);
    else
        dbAdd(c->db,c->argv[1],new);
    signalModifiedKey(c->db,c->argv[1]);
    server.dirty++;
    addReplyBulk(c,new);
}