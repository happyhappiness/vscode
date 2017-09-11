 * If "justcount", only the number of elements in the range is returned. */
void genericZrangebyscoreCommand(redisClient *c, int reverse, int justcount) {
    zrangespec range;
    robj *o, *emptyreply;
    zset *zsetobj;
    zskiplist *zsl;
    zskiplistNode *ln;
    int offset = 0, limit = -1;
    int withscores = 0;
    unsigned long rangelen = 0;
    void *replylen = NULL;

    /* Parse the range arguments. */
    if (zslParseRange(c->argv[2],c->argv[3],&range) != REDIS_OK) {
        addReplyError(c,"min or max is not a double");
        return;
    }
