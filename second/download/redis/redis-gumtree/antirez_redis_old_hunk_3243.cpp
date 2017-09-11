    if (sdslen(c->obuf) > 0) {
        nwritten = write(c->fd,c->obuf,sdslen(c->obuf));
        if (nwritten == -1) {
            if (errno == EAGAIN) {
                /* Try again later */
            } else {
                __redisSetError(c,REDIS_ERR_IO,NULL);
