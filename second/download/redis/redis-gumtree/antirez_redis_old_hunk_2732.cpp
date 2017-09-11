    return;

socket_wr_err:
    redisLog(REDIS_NOTICE,"Can't write to target node for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
        strerror(errno));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;

socket_rd_err:
    redisLog(REDIS_NOTICE,"Can't read from target node for MIGRATE: %s",
        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
        strerror(errno));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;
