/* Blocking RPOP/LPOP */
void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
    time_t timeout;
    int j;

    if (checkTimeout(c, c->argv[c->argc - 1], &timeout) != REDIS_OK) {
        return;
    }

