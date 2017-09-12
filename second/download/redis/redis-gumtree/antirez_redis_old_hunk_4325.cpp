        /* write all collected blocks at once */
        if((nwritten = writev(fd, iov, ion)) < 0) {
            if (errno != EAGAIN) {
                redisLog(REDIS_DEBUG,
                         "Error writing to client: %s", strerror(errno));
                freeClient(c);
                return;
