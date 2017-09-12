        return;
    }
    if ((nwritten = write(fd,buf,buflen)) == -1) {
        redisLog(REDIS_DEBUG,"Write error sending DB to slave: %s",
            strerror(errno));
        freeClient(slave);
        return;
