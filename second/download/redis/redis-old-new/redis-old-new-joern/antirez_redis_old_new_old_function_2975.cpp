void zincrbyCommand(redisClient *c) {
    double scoreval;
    if (getDoubleFromObjectOrReply(c,c->argv[2],&scoreval,NULL) != REDIS_OK) return;
    c->argv[3] = tryObjectEncoding(c->argv[3]);
    zaddGenericCommand(c,c->argv[1],c->argv[3],scoreval,1);
}