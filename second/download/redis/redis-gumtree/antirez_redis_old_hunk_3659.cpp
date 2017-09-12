    zset *zs;

    /* Parse the range arguments. */
    zslParseRange(c->argv[2],c->argv[3],&range);

    if ((o = lookupKeyWriteOrReply(c,c->argv[1],shared.czero)) == NULL ||
        checkType(c,o,REDIS_ZSET)) return;
