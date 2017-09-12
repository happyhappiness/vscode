/* Blocking RPOP/LPOP */
void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
    long long lltimeout;
    time_t timeout;
    int j;

    /* Make sure timeout is an integer value */
    if (getLongLongFromObjectOrReply(c,c->argv[c->argc-1],&lltimeout,
            "timeout is not an integer") != REDIS_OK) return;

    /* Make sure the timeout is not negative */
    if (lltimeout < 0) {
        addReplyError(c,"timeout is negative");
        return;
    }

    for (j = 1; j < c->argc-1; j++) {
        o = lookupKeyWrite(c->db,c->argv[j]);
        if (o != NULL) {
