static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)
{
    client c = privdata;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(fd);
    REDIS_NOTUSED(mask);

    if (c->state == CLIENT_CONNECTING) {
        c->state = CLIENT_SENDQUERY;
        c->start = mstime();
    }
    if (sdslen(c->obuf) > c->written) {
        void *ptr = c->obuf+c->written;
        int len = sdslen(c->obuf) - c->written;
        int nwritten = write(c->fd, ptr, len);
        if (nwritten == -1) {
            if (errno != EPIPE)
                fprintf(stderr, "Writing to socket: %s\n", strerror(errno));
            freeClient(c);
            return;
        }
        c->written += nwritten;
        if (sdslen(c->obuf) == c->written) {
            aeDeleteFileEvent(config.el,c->fd,AE_WRITABLE);
            aeCreateFileEvent(config.el,c->fd,AE_READABLE,readHandler,c);
            c->state = CLIENT_READREPLY;
        }
    }
}