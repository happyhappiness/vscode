int extractLongLatOrReply(redisClient *c, robj **argv,
                                        double *xy) {
    for (int i = 0; i < 2; i++) {
        if (getDoubleFromObjectOrReply(c, argv[i], xy + i, NULL) !=
            REDIS_OK) {
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}