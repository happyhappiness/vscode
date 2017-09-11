        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
        strerror(errno));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;

