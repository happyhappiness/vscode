        strerror(errno));
    addReplyErrorFormat(c,"MIGRATE failed, reading from target node: %s.",
        strerror(errno));
    fclose(fp);
    close(fd);
    return;
}
