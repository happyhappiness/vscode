        int nread, nwritten;

        nread = read(fd,buf,(dumpsize < 1024)?dumpsize:1024);
        if (nread <= 0) {
            redisLog(REDIS_WARNING,"I/O error trying to sync with MASTER: %s",
                (nread == -1) ? strerror(errno) : "connection lost");
            close(fd);
            close(dfd);
            return REDIS_ERR;
