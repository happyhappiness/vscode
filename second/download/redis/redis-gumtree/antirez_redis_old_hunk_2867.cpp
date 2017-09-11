
static void setProtocolError(redisClient *c, int pos);

void *dupClientReplyValue(void *o) {
    incrRefCount((robj*)o);
    return o;
