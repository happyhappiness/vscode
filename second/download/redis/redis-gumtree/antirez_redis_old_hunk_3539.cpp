    return 1;
}

/* Blocking RPOP/LPOP */
void blockingPopGenericCommand(redisClient *c, int where) {
    robj *o;
