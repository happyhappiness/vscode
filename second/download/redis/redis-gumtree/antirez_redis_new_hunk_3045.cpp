        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
        strerror(errno));
    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;
}
