void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
    client *slave = privdata;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);
    char buf[REDIS_IOBUF_LEN];
    ssize_t nwritten, buflen;

    /* Before sending the RDB file, we send the preamble as configured by the
     * replication process. Currently the preamble is just the bulk count of
     * the file in the form "$<length>\r\n". */
    if (slave->replpreamble) {
        nwritten = write(fd,slave->replpreamble,sdslen(slave->replpreamble));
        if (nwritten == -1) {
            serverLog(REDIS_VERBOSE,"Write error sending RDB preamble to slave: %s",
                strerror(errno));
            freeClient(slave);
            return;
        }
        server.stat_net_output_bytes += nwritten;
        sdsrange(slave->replpreamble,nwritten,-1);
        if (sdslen(slave->replpreamble) == 0) {
            sdsfree(slave->replpreamble);
            slave->replpreamble = NULL;
            /* fall through sending data. */
        } else {
            return;
        }
    }

    /* If the preamble was already transfered, send the RDB bulk data. */
    lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
    buflen = read(slave->repldbfd,buf,REDIS_IOBUF_LEN);
    if (buflen <= 0) {
        serverLog(REDIS_WARNING,"Read error sending DB to slave: %s",
            (buflen == 0) ? "premature EOF" : strerror(errno));
        freeClient(slave);
        return;
    }
    if ((nwritten = write(fd,buf,buflen)) == -1) {
        if (errno != EAGAIN) {
            serverLog(REDIS_WARNING,"Write error sending DB to slave: %s",
                strerror(errno));
            freeClient(slave);
        }
        return;
    }
    slave->repldboff += nwritten;
    server.stat_net_output_bytes += nwritten;
    if (slave->repldboff == slave->repldbsize) {
        close(slave->repldbfd);
        slave->repldbfd = -1;
        aeDeleteFileEvent(server.el,slave->fd,AE_WRITABLE);
        putSlaveOnline(slave);
    }
}