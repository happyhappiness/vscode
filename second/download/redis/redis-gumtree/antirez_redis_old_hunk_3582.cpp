    REDIS_NOTUSED(fd);
    REDIS_NOTUSED(mask);

    if (redisBufferRead(c->context) != REDIS_OK) {
        fprintf(stderr,"Error: %s\n",c->context->errstr);
        exit(1);
