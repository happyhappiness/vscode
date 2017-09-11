    server.repl_transfer_lastio = time(NULL);
    if (write(server.repl_transfer_fd,buf,nread) != nread) {
        redisLog(REDIS_WARNING,"Write error or short write writing to the DB dump file needed for MASTER <-> SLAVE synchrnonization: %s", strerror(errno));
        replicationAbortSyncTransfer();
        return;
    }
    server.repl_transfer_left -= nread;
    /* Check if the transfer is now complete */
