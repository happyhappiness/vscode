void syncWithMaster(aeEventLoop *el, int fd, void *privdata, int mask) {
    char tmpfile[256], *err;
    int dfd, maxtries = 5;
    int sockerr = 0, psync_result;
    socklen_t errlen = sizeof(sockerr);
    UNUSED(el);
    UNUSED(privdata);
    UNUSED(mask);

    /* If this event fired after the user turned the instance into a master
     * with SLAVEOF NO ONE we must just return ASAP. */
    if (server.repl_state == REPL_STATE_NONE) {
        close(fd);
        return;
    }

    /* Check for errors in the socket. */
    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &sockerr, &errlen) == -1)
        sockerr = errno;
    if (sockerr) {
        aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
        serverLog(LL_WARNING,"Error condition on socket for SYNC: %s",
            strerror(sockerr));
        goto error;
    }

    /* If we were connecting, it's time to send a non blocking PING, we want to
     * make sure the master is able to reply before going into the actual
     * replication process where we have long timeouts in the order of
     * seconds (in the meantime the slave would block). */
    if (server.repl_state == REPL_STATE_CONNECTING) {
        serverLog(LL_NOTICE,"Non blocking connect for SYNC fired the event.");
        /* Delete the writable event so that the readable event remains
         * registered and we can wait for the PONG reply. */
        aeDeleteFileEvent(server.el,fd,AE_WRITABLE);
        server.repl_state = REPL_STATE_RECEIVE_PONG;
        /* Send the PING, don't check for errors at all, we have the timeout
         * that will take care about this. */
        syncWrite(fd,"PING\r\n",6,100);
        return;
    }

    /* Receive the PONG command. */
    if (server.repl_state == REPL_STATE_RECEIVE_PONG) {
        char buf[1024];

        /* Delete the readable event, we no longer need it now that there is
         * the PING reply to read. */
        aeDeleteFileEvent(server.el,fd,AE_READABLE);

        /* Read the reply with explicit timeout. */
        buf[0] = '\0';
        if (syncReadLine(fd,buf,sizeof(buf),
            server.repl_syncio_timeout*1000) == -1)
        {
            serverLog(LL_WARNING,
                "I/O error reading PING reply from master: %s",
                strerror(errno));
            goto error;
        }

        /* We accept only two replies as valid, a positive +PONG reply
         * (we just check for "+") or an authentication error.
         * Note that older versions of Redis replied with "operation not
         * permitted" instead of using a proper error code, so we test
         * both. */
        if (buf[0] != '+' &&
            strncmp(buf,"-NOAUTH",7) != 0 &&
            strncmp(buf,"-ERR operation not permitted",28) != 0)
        {
            serverLog(LL_WARNING,"Error reply to PING from master: '%s'",buf);
            goto error;
        } else {
            serverLog(LL_NOTICE,
                "Master replied to PING, replication can continue...");
        }
    }

    /* AUTH with the master if required. */
    if(server.masterauth) {
        err = sendSynchronousCommand(fd,"AUTH",server.masterauth,NULL);
        if (err[0] == '-') {
            serverLog(LL_WARNING,"Unable to AUTH to MASTER: %s",err);
            sdsfree(err);
            goto error;
        }
        sdsfree(err);
    }

    /* Set the slave port, so that Master's INFO command can list the
     * slave listening port correctly. */
    {
        sds port = sdsfromlonglong(server.port);
        err = sendSynchronousCommand(fd,"REPLCONF","listening-port",port,
                                         NULL);
        sdsfree(port);
        /* Ignore the error if any, not all the Redis versions support
         * REPLCONF listening-port. */
        if (err[0] == '-') {
            serverLog(LL_NOTICE,"(Non critical) Master does not understand REPLCONF listening-port: %s", err);
        }
        sdsfree(err);
    }

    /* Try a partial resynchonization. If we don't have a cached master
     * slaveTryPartialResynchronization() will at least try to use PSYNC
     * to start a full resynchronization so that we get the master run id
     * and the global offset, to try a partial resync at the next
     * reconnection attempt. */
    psync_result = slaveTryPartialResynchronization(fd);
    if (psync_result == PSYNC_CONTINUE) {
        serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Master accepted a Partial Resynchronization.");
        return;
    }

    /* Fall back to SYNC if needed. Otherwise psync_result == PSYNC_FULLRESYNC
     * and the server.repl_master_runid and repl_master_initial_offset are
     * already populated. */
    if (psync_result == PSYNC_NOT_SUPPORTED) {
        serverLog(LL_NOTICE,"Retrying with SYNC...");
        if (syncWrite(fd,"SYNC\r\n",6,server.repl_syncio_timeout*1000) == -1) {
            serverLog(LL_WARNING,"I/O error writing to MASTER: %s",
                strerror(errno));
            goto error;
        }
    }

    /* Prepare a suitable temp file for bulk transfer */
    while(maxtries--) {
        snprintf(tmpfile,256,
            "temp-%d.%ld.rdb",(int)server.unixtime,(long int)getpid());
        dfd = open(tmpfile,O_CREAT|O_WRONLY|O_EXCL,0644);
        if (dfd != -1) break;
        sleep(1);
    }
    if (dfd == -1) {
        serverLog(LL_WARNING,"Opening the temp file needed for MASTER <-> SLAVE synchronization: %s",strerror(errno));
        goto error;
    }

    /* Setup the non blocking download of the bulk file. */
    if (aeCreateFileEvent(server.el,fd, AE_READABLE,readSyncBulkPayload,NULL)
            == AE_ERR)
    {
        serverLog(LL_WARNING,
            "Can't create readable event for SYNC: %s (fd=%d)",
            strerror(errno),fd);
        goto error;
    }

    server.repl_state = REPL_STATE_TRANSFER;
    server.repl_transfer_size = -1;
    server.repl_transfer_read = 0;
    server.repl_transfer_last_fsync_off = 0;
    server.repl_transfer_fd = dfd;
    server.repl_transfer_lastio = server.unixtime;
    server.repl_transfer_tmpfile = zstrdup(tmpfile);
    return;

error:
    close(fd);
    server.repl_transfer_s = -1;
    server.repl_state = REPL_STATE_CONNECT;
    return;
}