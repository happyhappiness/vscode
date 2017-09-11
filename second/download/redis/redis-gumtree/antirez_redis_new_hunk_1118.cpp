    if (fd == -1) {
        serverLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
            strerror(errno));
        return C_ERR;
    }

    if (aeCreateFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE,syncWithMaster,NULL) ==
            AE_ERR)
    {
        close(fd);
        serverLog(REDIS_WARNING,"Can't create readable event for SYNC");
        return C_ERR;
    }

    server.repl_transfer_lastio = server.unixtime;
    server.repl_transfer_s = fd;
    server.repl_state = REDIS_REPL_CONNECTING;
    return C_OK;
}

/* This function can be called when a non blocking connection is currently
