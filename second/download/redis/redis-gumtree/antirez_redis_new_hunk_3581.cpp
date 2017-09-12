        redisLog(REDIS_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
        return REDIS_ERR;
    }

    /* Setup the non blocking download of the bulk file. */
    if (aeCreateFileEvent(server.el, fd, AE_READABLE,readSyncBulkPayload) ==
        AE_ERR)
    {
        close(fd);
        redisLog(REDIS_WARNING,"Can't create readable event for SYNC");
        return REDIS_ERR;
    }
    server.replstate = REDIS_REPL_TRANSFER;
    server.repl_transfer_left = dumpsize;
    server.repl_transfer_s = fd;
    server.repl_transfer_fd = dfd;
    server.repl_transfer_lastio = time(NULL);
    server.repl_transfer_tmpfile = zstrdup(tmpfile);
    return REDIS_OK;
}

