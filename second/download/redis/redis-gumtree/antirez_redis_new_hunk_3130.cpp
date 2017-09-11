        sleep(1);
    }
    if (dfd == -1) {
        redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
        goto error;
    }

    /* Setup the non blocking download of the bulk file. */
    if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
            == AE_ERR)
    {
        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
        goto error;
    }

    server.replstate = REDIS_REPL_TRANSFER;
    server.repl_transfer_left = -1;
    server.repl_transfer_fd = dfd;
    server.repl_transfer_lastio = time(NULL);
    server.repl_transfer_tmpfile = zstrdup(tmpfile);
    return;

error:
    server.replstate = REDIS_REPL_CONNECT;
    close(fd);
    return;
}

int connectWithMaster(void) {
    int fd;

    fd = anetTcpNonBlockConnect(NULL,server.masterhost,server.masterport);
    if (fd == -1) {
        redisLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
            strerror(errno));
        return REDIS_ERR;
    }

    if (aeCreateFileEvent(server.el,fd,AE_WRITABLE,syncWithMaster,NULL) ==
            AE_ERR)
    {
        close(fd);
        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
        return REDIS_ERR;
    }

    server.repl_transfer_s = fd;
    server.replstate = REDIS_REPL_CONNECTING;
    return REDIS_OK;
}

