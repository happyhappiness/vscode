int redisBufferRead(redisContext *c) {
    char buf[1024*16];
    int nread = read(c->fd,buf,sizeof(buf));
    if (nread == -1) {
        if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
            /* Try again later */
        } else {
            __redisSetError(c,REDIS_ERR_IO,NULL);
            return REDIS_ERR;
        }
    } else if (nread == 0) {
        __redisSetError(c,REDIS_ERR_EOF,
            sdsnew("Server closed the connection"));
        return REDIS_ERR;
    } else {
        __redisCreateReplyReader(c);
        redisReplyReaderFeed(c->reader,buf,nread);
    }
    return REDIS_OK;
}