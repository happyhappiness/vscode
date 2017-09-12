int redisGetReplyFromReader(redisContext *c, void **reply) {
    if (redisReaderGetReply(c->reader,reply) == REDIS_ERR) {
        __redisSetError(c,c->reader->err,c->reader->errstr);
        return REDIS_ERR;
    }
    return REDIS_OK;
}