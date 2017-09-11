    buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
    if (write(c->fd,buf,buflen) != buflen) {
        freeClientAsync(c);
        return REDIS_OK;
    }
    psync_len = addReplyReplicationBacklog(c,psync_offset);
    serverLog(REDIS_NOTICE,
