/* Internal helper function to try and get a reply from the reader,
 * or set an error in the context otherwise. */
int redisGetReplyFromReader(redisContext *c, void **reply) {
    __redisCreateReplyReader(c);
    if (redisReplyReaderGetReply(c->reader,reply) == REDIS_ERR) {
        __redisSetError(c,REDIS_ERR_PROTOCOL,
            sdsnew(((redisReader*)c->reader)->error));
        return REDIS_ERR;
    }
    return REDIS_OK;
