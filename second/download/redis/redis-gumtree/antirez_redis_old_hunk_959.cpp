error:
    close(fd);
    server.repl_transfer_s = -1;
    server.repl_state = REDIS_REPL_CONNECT;
    return;
}

int connectWithMaster(void) {
    int fd;

    fd = anetTcpNonBlockBestEffortBindConnect(NULL,
        server.masterhost,server.masterport,REDIS_BIND_ADDR);
    if (fd == -1) {
        serverLog(REDIS_WARNING,"Unable to connect to MASTER: %s",
            strerror(errno));
        return C_ERR;
    }
