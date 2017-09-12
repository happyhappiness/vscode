static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    client c = privdata;
    void *reply = NULL;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(fd);
    REDIS_NOTUSED(mask);

    if (redisBufferRead(c->context) != REDIS_OK) {
        fprintf(stderr,"Error: %s\n",c->context->errstr);
        exit(1);
    } else {
        if (redisGetReply(c->context,&reply) != REDIS_OK) {
            fprintf(stderr,"Error: %s\n",c->context->errstr);
            exit(1);
        }
        if (reply != NULL)
            clientDone(c);
    }
}