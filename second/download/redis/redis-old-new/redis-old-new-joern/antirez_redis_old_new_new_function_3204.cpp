void incrDecrCommand(redisClient *c, long long incr) {
    long long value, oldvalue;
    robj *o;

    o = lookupKeyWrite(c->db,c->argv[1]);
    if (o != NULL && checkType(c,o,REDIS_STRING)) return;
    if (getLongLongFromObjectOrReply(c,o,&value,NULL) != REDIS_OK) return;

    oldvalue = value;
    value += incr;
    if ((incr < 0 && value > oldvalue) || (incr > 0 && value < oldvalue)) {
        addReplyError(c,"increment or decrement would overflow");
        return;
    }
    o = createStringObjectFromLongLong(value);
    dbReplace(c->db,c->argv[1],o);
    touchWatchedKey(c->db,c->argv[1]);
    server.dirty++;
    addReply(c,shared.colon);
    addReply(c,o);
    addReply(c,shared.crlf);
}