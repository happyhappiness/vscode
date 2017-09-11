        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, writing to target node: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;

