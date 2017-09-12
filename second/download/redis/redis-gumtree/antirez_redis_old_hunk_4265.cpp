
static int cliConnect(void) {
    char err[ANET_ERR_LEN];
    int fd;

    fd = anetTcpConnect(err,config.hostip,config.hostport);
    if (fd == ANET_ERR) {
        fprintf(stderr,"Connect: %s\n",err);
        return -1;
    }
    anetTcpNoDelay(NULL,fd);
    return fd;
}

