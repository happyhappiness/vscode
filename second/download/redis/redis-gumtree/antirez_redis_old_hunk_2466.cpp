
    nwritten = write(fd, link->sndbuf, sdslen(link->sndbuf));
    if (nwritten <= 0) {
        redisLog(REDIS_NOTICE,"I/O error writing to node link: %s",
            strerror(errno));
        handleLinkIOError(link);
        return;
