    zrangeGenericCommand(c,1);
}

static void zlenCommand(redisClient *c) {
    robj *o;
    zset *zs;
