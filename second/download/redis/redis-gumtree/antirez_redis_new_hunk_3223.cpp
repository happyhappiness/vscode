 * If "justcount", only the number of elements in the range is returned. */
void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
    zrangespec range;
    robj *key = c->argv[1];
    robj *emptyreply, *zobj;
    int offset = 0, limit = -1;
    int withscores = 0;
    unsigned long rangelen = 0;
    void *replylen = NULL;
    int minidx, maxidx;

    /* Parse the range arguments. */
    if (reverse) {
        /* Range is given as [max,min] */
        maxidx = 2; minidx = 3;
    } else {
        /* Range is given as [min,max] */
        minidx = 2; maxidx = 3;
    }

    if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != REDIS_OK) {
        addReplyError(c,"min or max is not a double");
        return;
    }
